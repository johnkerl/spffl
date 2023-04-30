// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "bitrand/psdes.h"
#include <cstdint>
#include <sys/time.h>
#include <unistd.h>
namespace spffl::bitrand {

// ================================================================
static uint32_t non_reentrant_state0 = 0;
static uint32_t non_reentrant_state1 = 0;
static uint32_t non_reentrant_seeded = 0;

// ----------------------------------------------------------------
uint32_t iran32(void) {
  if (!non_reentrant_seeded) {
    sran32_timeofday();
  }
  return iran32_r(non_reentrant_state0, non_reentrant_state1);
}

// ----------------------------------------------------------------
void iran64(uint32_t &out0, uint32_t &out1) {
  if (!non_reentrant_seeded) {
    sran32_timeofday();
  }
  return iran64_r(out0, out1, non_reentrant_state0, non_reentrant_state1);
}

// ----------------------------------------------------------------
float fran32(void) {
  if (!non_reentrant_seeded) {
    sran32_timeofday();
  }
  return fran32_r(non_reentrant_state0, non_reentrant_state1);
}

// ---------------------------------------------------------------;-
void sran32(uint32_t s) {
  non_reentrant_state0 = 0;
  non_reentrant_state1 = s;
  non_reentrant_seeded = 1;
}

// ---------------------------------------------------------------;-
void sran32b(uint32_t s0, uint32_t s1) {
  non_reentrant_state0 = s0;
  non_reentrant_state1 = s1;
  non_reentrant_seeded = 1;
}

// ----------------------------------------------------------------
void sran32_timeofday(void) {
  struct timeval tod;
  (void)gettimeofday(&tod, 0);
  non_reentrant_state0 = getpid() ^ tod.tv_usec;
  non_reentrant_state1 = tod.tv_sec ^ (tod.tv_usec * tod.tv_usec + 1);
  non_reentrant_seeded = 1;
}

// ================================================================
uint32_t iran32_r(uint32_t &state0, uint32_t &state1) {
  uint32_t word0 = state0;
  uint32_t word1 = state1;
  psdes_hash_64(word0, word1);

  state1++;
  if (state1 == 0) {
    state0++;
  }

  // Return low 32 bits of hash output; discard high 32 bits.
  return word1;
}

// ----------------------------------------------------------------
void iran64_r(
    uint32_t &out0, uint32_t &out1, uint32_t &state0, uint32_t &state1) {
  out0 = state0;
  out1 = state1;
  psdes_hash_64(out0, out1);

  state1++;
  if (state1 == 0) {
    state0++;
  }
}

// ----------------------------------------------------------------
float fran32_r(uint32_t &state0, uint32_t &state1) {
  static uint32_t jflone  = 0x3f800000;
  static uint32_t jflmask = 0x007fffff;
  uint32_t word1          = iran32_r(state0, state1);
  // IEEE bit-bang
  uint32_t bits = jflone | (jflmask & word1);
  return (*(float *)&bits) - 1.0;
}

// ----------------------------------------------------------------
void sran32_timeofday_r(uint32_t &state0, uint32_t &state1) {
  struct timeval tod;
  (void)gettimeofday(&tod, 0);
  state0 = getpid() ^ tod.tv_usec;
  state1 = tod.tv_sec ^ (tod.tv_usec * tod.tv_usec + 1);
}

// ----------------------------------------------------------------
// A 64-bit in-place hash, loosely inspired by DES.
// From _Numerical Recipes in C_.
//
// This is a 4-round Feistel network with the following function on
// the right-hand member R:
//
// * XOR one constant into R.
// * Split into high and low 16-bit halves; remember these as iah and ial
// * Square each, forming two 32-bit products
// * Invert the bits in the high square
// * Add the inverted high square to the lower square, forming a
//   32-bit sum
// * Swap high and low 16-bit halves
// * XOR in another constant
// * Add the 32-bit product of iah and ial from above

#define NITER 4

void psdes_hash_64(uint32_t &word0, uint32_t &word1) {
  uint32_t i;                           // Round counter
  uint32_t iswap, ia, iah, ial, ib, ic; // Intermediate values
  static uint32_t c1[NITER] = {0xbaa96887, 0x1e17d32c, 0x03bcdc3c, 0x0f33d1b2};
  static uint32_t c2[NITER] = {0x4b0f3b58, 0xe874f0c3, 0x6955c5a6, 0x55a7ca46};

  for (i = 0; i < NITER; i++) {
    iswap = word1;

    ia    = iswap ^ c1[i];
    ial   = ia & 0xffff;
    iah   = ia >> 16;
    ib    = ial * ial + ~(iah * iah);
    ic    = (ib >> 16) | ((ib & 0xffff) << 16);
    word1 = word0 ^ ((ic ^ c2[i]) + ial * iah);

    word0 = iswap;
  }
}

} // namespace spffl::bitrand
