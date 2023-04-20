// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLYMOD_UNITS_H
#define F2NPOLYMOD_UNITS_H
#include "f2npolymod_t.h"

int f2npolymod_order(f2npolymod_t a);

// The function return value is 1 if a generator was found, 0 otherwise.
// In the former case, rg holds the found generator.
int f2npolymod_find_generator(f2npoly_t m, f2npolymod_t &rg);

// Log base g of a, using Shanks' algorithm.
//
// Warning:  We assume that g is a generator.  We do not test this, not
// only for efficiency, but in case the caller is working within a subfield.
int f2npolymod_log(f2npolymod_t g, f2npolymod_t a);

#endif // F2NPOLYMOD_UNITS_H
