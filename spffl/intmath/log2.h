// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef LOG2_H
#define LOG2_H

#include <cstdint>

namespace spffl::intmath {
unsigned find_msb_16(unsigned short n);
unsigned find_msb_32(unsigned n);
unsigned find_msb_64(uint64_t n);

unsigned find_lsb_32(unsigned n);
unsigned find_lsb_64(uint64_t n);

unsigned calc_log2_unsigned_floor(unsigned n);
unsigned calc_log2_unsigned_ceil(unsigned n);

uint64_t calc_log2_unsigned_ll_floor(uint64_t n);
uint64_t calc_log2_unsigned_ll_ceil(uint64_t n);
} // namespace spffl::intmath

#endif // LOG2_H
