// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FP_UNITS_H
#define FP_UNITS_H
#include "intmod_t.h"

int fp_order(
	intmod_t a);

// The function return value is 1 if a generator was found, 0 otherwise.
// In the former case, rg holds the found generator.
int fp_find_generator(
	int        p,
	intmod_t & rg);

// Log base g of a, using Shanks' algorithm.
//
// Warning:  We assume that g is a generator.  We do not test this, not
// only for efficiency, but in case the caller is working within a subfield.
int fp_log(
	intmod_t g,
	intmod_t a);

#endif // FP_UNITS_H
