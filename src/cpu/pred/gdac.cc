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

    if (!isPowerOf2(segOneBits)) {
        fatal("Invalid segment one size!\n");
    }

    if (!isPowerOf2(segTwoBits)) {
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
        fusionTable[i].setBits(2);

    DPRINTF(Fetch, "shared choice predictor size: %i\n",
            rootPredictorSize);

    // ToDo: Construct local components.
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

    // ToDo: reset local components.
}

void
GdacBP::btbUpdate(ThreadID tid, Addr branch_addr, void * &bp_history)
{
// Place holder for a function that is called to update predictor history when
// a BTB entry is invalid or not found.
}


bool
GdacBP::lookup(ThreadID tid, Addr branch_addr, void * &bp_history)
{
    bool taken = true;

    return taken;
}

void
GdacBP::update(ThreadID tid, Addr branch_addr, bool taken, void *bp_history,
                bool squashed, const StaticInstPtr & inst, Addr corrTarget)
{
    assert(bp_history == NULL);
    unsigned local_predictor_idx;

    // No state to restore, and we do not update on the wrong
    // path.
    if (squashed) {
        return;
    }

    // Update the local predictor.
    local_predictor_idx = 0;

    DPRINTF(Fetch, "Looking up index %#x\n", local_predictor_idx);

    if (taken) {
        DPRINTF(Fetch, "Branch updated as taken.\n");
        choiceCounters[local_predictor_idx].increment();
    } else {
        DPRINTF(Fetch, "Branch updated as not taken.\n");
        choiceCounters[local_predictor_idx].decrement();
    }
}

void
GdacBP::uncondBranch(ThreadID tid, Addr pc, void *&bp_history)
{
}

GdacBP*
gDACBPParams::create()
{
    return new GdacBP(this);
}
