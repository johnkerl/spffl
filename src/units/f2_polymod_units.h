// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYMOD_UNITS_H
#define F2POLYMOD_UNITS_H
#include "f2_polymod_t.h"

namespace spffl::units {

int f2polymod_order(spffl::polynomials::f2_polymod_t a);

// The function return value is 1 if a generator was found, 0 otherwise.
// In the former case, rg holds the found generator.
int f2polymod_find_generator(spffl::polynomials::f2_poly_t m, spffl::polynomials::f2_polymod_t &rg);

// Returns 1 if x generates the multiplicative group.  An irreducibility
// test is not done.
int f2poly_is_primitive(spffl::polynomials::f2_poly_t m);

int f2poly_period(spffl::polynomials::f2_poly_t m);

// Lexically lowest.
spffl::polynomials::f2_poly_t f2poly_find_prim(int degree, int need_irr);

spffl::polynomials::f2_poly_t f2poly_random_prim(int degree, int need_irr);

// Log base g of a, using Shanks' algorithm.
//
// Warning:  We assume that g is a generator.  We do not test this, not
// only for efficiency, but in case the caller is working within a subfield.
int f2polymod_log(spffl::polynomials::f2_polymod_t g, spffl::polynomials::f2_polymod_t a);

} // namespace

#endif // F2POLYMOD_UNITS_H
