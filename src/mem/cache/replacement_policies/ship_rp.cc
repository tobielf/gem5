/**
 * Copyright (c) 2018 Inria
 * Copyright (c) 2019 Arizona State University
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
 * Authors: Daniel Carvalho
 *          Xiangyu Guo
 */

#include "mem/cache/replacement_policies/ship_rp.hh"

#include <cassert>
#include <memory>

#include "base/logging.hh" // For fatal_if
#include "base/random.hh"
#include "params/SHIPRP.hh"

#define SATURATING_COUNTER  (0b111)

#define SIGNATURE_BITS  (14)
#define SIGNATURE_MASK  (0x7FFF)

SHIPRP::SHIPRP(const Params *p)
    : BaseReplacementPolicy(p),
      maxRRPV(p->max_RRPV)
{
    shct = new SHCT();
    fatal_if(maxRRPV <= 0, "max_RRPV should be greater than zero.\n");
}

void
SHCT::incrementSHCT(unsigned long long signature)
{
    fatal_if((signature & ~SIGNATURE_MASK) != 0, "signature out of range.\n");
    table[signature]++;
    if (table[signature] > SATURATING_COUNTER)
        table[signature] = SATURATING_COUNTER;
}

void
SHCT::decrementSHCT(unsigned long long signature)
{
    fatal_if((signature & ~SIGNATURE_MASK) != 0, "signature out of range.\n");
    table[signature]--;
    if (table[signature] < 0)
        table[signature] = 0;
}

int
SHCT::getValue(unsigned long long signature)
{
    fatal_if((signature & ~SIGNATURE_MASK) != 0, "signature out of range.\n");
    return table[signature];
}

unsigned long long
SHCT::computeSignature(Addr address)
{
    unsigned long long signature = 0x0000000000003eef;

    // Get significant bits
    address >>= SIGNATURE_BITS;

    // XOR hash on significant bits
    while (address != 0) {
        signature ^= address & SIGNATURE_MASK;
        address >>= SIGNATURE_BITS;
    }

    return signature;
}

void
SHIPRP::invalidate(const std::shared_ptr<ReplacementData>& replacement_data)
const
{
    std::shared_ptr<SHIPReplData> casted_replacement_data =
        std::static_pointer_cast<SHIPReplData>(replacement_data);

    // Set RRPV to an invalid distance
    casted_replacement_data->rrpv = maxRRPV + 1;
}

void
SHIPRP::touch(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    std::shared_ptr<SHIPReplData> casted_replacement_data =
        std::static_pointer_cast<SHIPReplData>(replacement_data);

    casted_replacement_data->outcome = true;
    shct->incrementSHCT(casted_replacement_data->signature);
    // Update RRPV if not 0 yet
    // Every hit in HP mode makes the entry the last to be evicted, while
    // in FP mode a hit makes the entry less likely to be evicted
    casted_replacement_data->rrpv = 0;
}

void
SHIPRP::reset(const std::shared_ptr<ReplacementData>& replacement_data) const
{
    std::shared_ptr<SHIPReplData> casted_replacement_data =
        std::static_pointer_cast<SHIPReplData>(replacement_data);

    casted_replacement_data->outcome = false;
    casted_replacement_data->signature = shct->computeSignature(
                                                casted_replacement_data->_tag);

    // Reset RRPV
    // Replacement data is inserted as "long re-reference" if lower than btp,
    // "distant re-reference" otherwise
    if (shct->getValue(casted_replacement_data->signature) != 0) {
        casted_replacement_data->rrpv = maxRRPV-1;
    } else {
        casted_replacement_data->rrpv = maxRRPV;
    }
}

ReplaceableEntry*
SHIPRP::getVictim(const ReplacementCandidates& candidates) const
{
    // There must be at least one replacement candidate
    assert(candidates.size() > 0);

    // Use first candidate as dummy victim
    ReplaceableEntry* victim = candidates[0];

    // Store victim->rrpv in a variable to improve code readability
    int victim_RRPV = std::static_pointer_cast<SHIPReplData>(
                        victim->replacementData)->rrpv;

    // Visit all candidates to find victim
    for (const auto& candidate : candidates) {
        // Get candidate's rrpv
        int candidate_RRPV = std::static_pointer_cast<SHIPReplData>(
                                    candidate->replacementData)->rrpv;

        // Stop searching for victims if an invalid entry is found
        if (candidate_RRPV == maxRRPV + 1) {
            return candidate;
        // Update victim entry if necessary
        } else if (candidate_RRPV > victim_RRPV) {
            victim = candidate;
            victim_RRPV = candidate_RRPV;
        }
    }

    // Get difference of victim's RRPV to the highest possible RRPV in
    // order to update the RRPV of all the other entries accordingly
    int diff = maxRRPV - victim_RRPV;

    // No need to update RRPV if there is no difference
    if (diff > 0){
        // Update RRPV of all candidates
        for (const auto& candidate : candidates) {
            std::static_pointer_cast<SHIPReplData>(
                candidate->replacementData)->rrpv += diff;
        }
    }

    if (std::static_pointer_cast<SHIPReplData>(
                            victim->replacementData)->outcome != true) {
        shct->decrementSHCT(std::static_pointer_cast<SHIPReplData>(
                                        victim->replacementData)->signature);
    }

    return victim;
}

std::shared_ptr<ReplacementData>
SHIPRP::instantiateEntry()
{
    return std::shared_ptr<ReplacementData>(new SHIPReplData(maxRRPV));
}

SHIPRP*
SHIPRPParams::create()
{
    return new SHIPRP(this);
}
