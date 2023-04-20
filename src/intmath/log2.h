// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef LOG2_H
#define LOG2_H

#include <cstdint>
#include "intfc.h"

unsigned find_msb_16(unsigned short n);
unsigned find_msb_32(unsigned n);
unsigned find_msb_64(uint64_t n);

unsigned find_lsb_32(unsigned n);
unsigned find_lsb_64(uint64_t n);

// want_ceil is either IFLOOR or ICEIL
unsigned calc_log2_unsigned(unsigned n, int want_ceil);

// TODO: rename
uint64_t calc_log2_unsigned_ll(uint64_t n, int want_ceil);

#endif // LOG2_H
