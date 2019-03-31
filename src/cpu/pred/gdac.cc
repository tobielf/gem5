/*
 * Copyright (c) 2004-2006 The Regents of The University of Michigan
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Kevin Lim
 */

#include "cpu/pred/gdac.hh"

#include "base/intmath.hh"
#include "base/logging.hh"
#include "base/trace.hh"
#include "debug/Fetch.hh"

GdacBP::GdacBP(const gDACBPParams *params)
    : BPredUnit(params),
      globalHistoryReg(params->numThreads, 0),
      choicePredictorSize(params->choicePredictorSize),
      rootPredictorSize(params->rootPredictorSize),
      segOneBits(params->segOneBits),
      segTwoBits(params->segTwoBits),
      segOneSize(params->segOneSize),
      segTwoSize(params->segTwoSize)
{
    if (!isPowerOf2(choicePredictorSize)) {
        fatal("Invalid shared choice predictor size!\n");
    }

    if (!isPowerOf2(rootPredictorSize)) {
        fatal("Invalid root predictor size!\n");
    }

    if (!isPowerOf2(segOneSize)) {
        fatal("Invalid segment one size!\n");
    }

    if (!isPowerOf2(segTwoSize)) {
        fatal("Invalid segment two size!\n");
    }

    // Setup the array of counters for the choice predictor.
    choiceCounters.resize(choicePredictorSize);

    for (unsigned i = 0; i < choicePredictorSize; ++i)
        choiceCounters[i].setBits(2);

    DPRINTF(Fetch, "shared choice predictor size: %i\n",
            choicePredictorSize);

    // Setup the array of counters for the root predictor.
    fusionTable.resize(rootPredictorSize);

    for (unsigned i = 0; i < rootPredictorSize; ++i)
        fusionTable[i].setBits(4);

    DPRINTF(Fetch, "root fusion predictor size: %i\n",
            rootPredictorSize);

    // Construct local components.
    comp[0] = new GdacComponents(segOneSize);
    comp[1] = new GdacComponents(segTwoSize);

    globalRegisterMask = mask(segOneBits + segTwoBits);
    choiceHistoryMask = choicePredictorSize - 1;
    rootHistoryMask = rootPredictorSize - 1;

    choiceThreshold = (ULL(1) << (2 - 1)) - 1;
    rootThreshold = (ULL(1) << (4 - 1)) - 1;
}

void
GdacBP::reset()
{
    for (unsigned i = 0; i < choicePredictorSize; ++i) {
        choiceCounters[i].reset();
    }

    for (unsigned i = 0; i < rootPredictorSize; ++i) {
        fusionTable[i].reset();
    }

    // reset local components.
    comp[0]->reset();
    comp[1]->reset();
}

void
GdacBP::btbUpdate(ThreadID tid, Addr branch_addr, void * &bp_history)
{
    globalHistoryReg[tid] &= (globalRegisterMask & ~ULL(1));
}


void
GdacBP::uncondBranch(ThreadID tid, Addr pc, void *&bp_history)
{
    BPHistory *history = new BPHistory;
    history->globalHistoryReg = globalHistoryReg[tid];
    history->takenUsed = true;
    history->finalPred = true;
    bp_history = static_cast<void*>(history);
    updateGlobalHistReg(tid, true);
}


bool
GdacBP::lookup(ThreadID tid, Addr branch_addr, void * &bp_history)
{
    unsigned choiceHistoryIdx = ((branch_addr >> instShiftAmt)
                                & choiceHistoryMask);
    unsigned seg1 = (globalHistoryReg[tid] >> segTwoBits) & mask(segOneBits);
    unsigned seg2 = (globalHistoryReg[tid]) & mask(segTwoBits);

    assert(choiceHistoryIdx < choicePredictorSize);
    bool choicePrediction = choiceCounters[choiceHistoryIdx].read()
                            > choiceThreshold;
    bool compPredictionOne = comp[0]->lookup(branch_addr, seg1,
                                                choicePrediction);
    bool compPredictionTwo = comp[1]->lookup(branch_addr, seg2,
                                                choicePrediction);

    // fusion table prediction.
    unsigned rootHistoryIdx = (branch_addr >> instShiftAmt)
                                ^ globalHistoryReg[tid];
    rootHistoryIdx = (rootHistoryIdx << 1) | compPredictionOne;
    rootHistoryIdx = (rootHistoryIdx << 1) | compPredictionTwo;
    rootHistoryIdx &= rootHistoryMask;
    assert(rootHistoryIdx < rootPredictorSize);
    bool finalPrediction = fusionTable[rootHistoryIdx].read() > rootThreshold;

    BPHistory *history = new BPHistory;
    history->globalHistoryReg = globalHistoryReg[tid];
    history->rootHistoryIdx = rootHistoryIdx;
    history->takenUsed = choicePrediction;
    history->finalPred = finalPrediction;
    bp_history = static_cast<void*>(history);
    updateGlobalHistReg(tid, finalPrediction);

    return finalPrediction;
}

void
GdacBP::update(ThreadID tid, Addr branch_addr, bool taken, void *bp_history,
                bool squashed, const StaticInstPtr & inst, Addr corrTarget)
{
    assert(bp_history);

    BPHistory *history = static_cast<BPHistory*>(bp_history);

    // We do not update the counters speculatively on a squash.
    // We just restore the global history register.
    if (squashed) {
        globalHistoryReg[tid] = (history->globalHistoryReg << 1) | taken;
        return;
    }

    unsigned choiceHistoryIdx = ((branch_addr >> instShiftAmt)
                                & choiceHistoryMask);
    assert(choiceHistoryIdx < choicePredictorSize);
    unsigned seg1 = (globalHistoryReg[tid] >> segTwoBits) & mask(segOneBits);
    unsigned seg2 = (globalHistoryReg[tid]) & mask(segTwoBits);

    comp[0]->update(branch_addr, seg1, history->takenUsed, taken);
    comp[1]->update(branch_addr, seg2, history->takenUsed, taken);

    if (history->finalPred == taken) {
       /* If the final prediction matches the actual branch's
        * outcome and the choice predictor matches the final
        * outcome, we update the choice predictor, otherwise it
        * is not updated. While the designers of the bi-mode
        * predictor don't explicity say why this is done, one
        * can infer that it is to preserve the choice predictor's
        * bias with respect to the branch being predicted; afterall,
        * the whole point of the bi-mode predictor is to identify the
        * atypical case when a branch deviates from its bias.
        */
        if (history->finalPred == history->takenUsed) {
            if (taken) {
                choiceCounters[choiceHistoryIdx].increment();
            } else {
                choiceCounters[choiceHistoryIdx].decrement();
            }
        }
    } else {
        // always update the choice predictor on an incorrect prediction
        if (taken) {
            choiceCounters[choiceHistoryIdx].increment();
        } else {
            choiceCounters[choiceHistoryIdx].decrement();
        }
    }

    // Update root predictor
    if (taken) {
        fusionTable[history->rootHistoryIdx].increment();
    } else {
        fusionTable[history->rootHistoryIdx].decrement();
    }

    delete history;
}


void
GdacBP::squash(ThreadID tid, void *bp_history)
{
    BPHistory *history = static_cast<BPHistory*>(bp_history);
    globalHistoryReg[tid] = history->globalHistoryReg;

    delete history;
}


void
GdacBP::updateGlobalHistReg(ThreadID tid, bool taken)
{
    globalHistoryReg[tid] = taken ? (globalHistoryReg[tid] << 1) | 1 :
                               (globalHistoryReg[tid] << 1);
    globalHistoryReg[tid] &= globalRegisterMask;
}

GdacComponents::GdacComponents(unsigned seg_Size)
{
    segSize = seg_Size;
    segMask = segSize - 1;

    takenCounters.resize(segSize);
    notTakenCounters.resize(segSize);

    for (unsigned i = 0; i < segSize; ++i) {
        takenCounters[i].setBits(2);
        notTakenCounters[i].setBits(2);
    }

    localThreshold = (ULL(1) << (2 - 1)) - 1;
}

void
GdacComponents::reset()
{
    for (unsigned i = 0; i < segSize; ++i) {
        takenCounters[i].reset();
        notTakenCounters[i].reset();
    }
}

bool
GdacComponents::lookup(Addr branch_addr, unsigned seg, bool takenUsed)
{
    unsigned localHistoryIdx = 0;
    // ToDo: Hash compute the index.

    if (takenUsed) {
        return takenCounters[localHistoryIdx].read() > localThreshold;
    } else {
        return notTakenCounters[localHistoryIdx].read() > localThreshold;
    }
}

void
GdacComponents::update(Addr branch_addr, unsigned seg,
                        bool takenUsed, bool taken)
{
    unsigned localHistoryIdx = 0;
    // ToDo: Hash compute the index.

    if (takenUsed) {
        // if the taken array's prediction was used, update it
        if (taken) {
            takenCounters[localHistoryIdx].increment();
        } else {
            takenCounters[localHistoryIdx].decrement();
        }
    } else {
        // if the not-taken array's prediction was used, update it
        if (taken) {
            notTakenCounters[localHistoryIdx].increment();
        } else {
            notTakenCounters[localHistoryIdx].decrement();
        }
    }
}

GdacBP*
gDACBPParams::create()
{
    return new GdacBP(this);
}
