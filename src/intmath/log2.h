// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef LOG2_H
#define LOG2_H

#include "intfc.h"

unsigned find_msb_16(unsigned short n);
unsigned find_msb_32(unsigned n);
unsigned find_msb_64(unsigned long long n);

unsigned find_lsb_32(unsigned n);
unsigned find_lsb_64(unsigned long long n);

// want_ceil is either IFLOOR or ICEIL
unsigned calc_log2_unsigned(unsigned n, int want_ceil);

// TODO: rename
unsigned long long calc_log2_unsigned_ll(unsigned long long n, int want_ceil);

#endif // LOG2_H
