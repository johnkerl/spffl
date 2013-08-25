// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYMOD_UNITS_H
#define F2POLYMOD_UNITS_H
#include "f2polymod_t.h"

int f2polymod_order(
	f2polymod_t a);

// The function return value is 1 if a generator was found, 0 otherwise.
// In the former case, rg holds the found generator.
int f2polymod_find_generator(
	f2poly_t      m,
	f2polymod_t & rg);

// Returns 1 if x generates the multiplicative group.  An irreducibility
// test is not done.
int f2poly_is_primitive(
	f2poly_t m);

int f2poly_period(
	f2poly_t m);

// Lexically lowest.
f2poly_t f2poly_find_prim(
	int degree,
	int need_irr);

f2poly_t f2poly_random_prim(
	int degree,
	int need_irr);

// Log base g of a, using Shanks' algorithm.
//
// Warning:  We assume that g is a generator.  We do not test this, not
// only for efficiency, but in case the caller is working within a subfield.
int f2polymod_log(
	f2polymod_t g,
	f2polymod_t a);

#endif // F2POLYMOD_UNITS_H
