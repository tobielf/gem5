/*
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
 * Authors: Xiangyu Guo
 */
#ifndef __GDAC_COUNTER__
#define __GDAC_COUNTER__

#include "base/logging.hh"
#include "base/types.hh"

class GDACCounter
{
  public:
    /**
     * Constructor for the counter.
     */
    GDACCounter(unsigned int newsize) {
        direction.resize(newsize);
        hysteresis.resize(newsize >> 1);
        size = newsize;
    }

    /**
     * @brief default constructor for the counter.
     */
    GDACCounter() {
        size = 0;
    }

    /**
     * Resize the counter's capacity.
     */
    void resize(unsigned int newsize) {
        direction.resize(newsize);
        hysteresis.resize(newsize >> 1);
        size = newsize;
    }

    /**
     * Reset the counter's value.
     */
    void reset() {
        for (int i = 0; i < size; ++i) {
            direction[i] = 0;
            hysteresis[i>>1] = 1;
        }
    }

    /**
     * Increments the counter's current value.
     */
    void increment(unsigned index) {
        fatal_if(index >= size, "Index out of range.");
        uint8_t d = direction[index];
        uint8_t h = hysteresis[index >> 1];
        if (d == 0 && h == 1) {
            hysteresis[index >> 1] = 0;
        } else if (d == 0 && h == 0) {
            direction[index] = 1;
        } else if (d == 1 && h == 0) {
            hysteresis[index >> 1] = 1;
        } else {
            // do nothing
        }
    }

    /**
     * Decrements the counter's current value.
     */
    void decrement(unsigned index) {
        fatal_if(index >= size, "Index out of range.");
        uint8_t d = direction[index];
        uint8_t h = hysteresis[index >> 1];
        if (d == 1 && h == 1) {
            hysteresis[index >> 1] = 0;
        } else if (d == 1 && h == 0) {
            direction[index] = 0;
        } else if (d == 0 && h == 0) {
            hysteresis[index >> 1] = 1;
        } else {
            // do nothing
        }
    }

    /**
     * Read the counter's value.
     */
    bool predict(unsigned index) {
        fatal_if(index >= size, "Index out of range.");
        return direction[index];
    }

  private:
    unsigned int size;
    std::vector<uint8_t> direction;
    std::vector<uint8_t> hysteresis;
};

#endif