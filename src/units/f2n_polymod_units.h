// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLYMOD_UNITS_H
#define F2NPOLYMOD_UNITS_H
#include "f2n_polymod_t.h"

namespace spffl::units {

int f2n_polymod_order(spffl::polynomials::f2n_polymod_t a);

// The function return value is 1 if a generator was found, 0 otherwise.
// In the former case, rg holds the found generator.
int f2n_polymod_find_generator(spffl::polynomials::f2n_poly_t m,
                               spffl::polynomials::f2n_polymod_t &rg);

// Log base g of a, using Shanks' algorithm.
//
// Warning:  We assume that g is a generator.  We do not test this, not
// only for efficiency, but in case the caller is working within a subfield.
int f2n_polymod_log(spffl::polynomials::f2n_polymod_t g,
                    spffl::polynomials::f2n_polymod_t a);

} // namespace spffl::units

#endif // F2NPOLYMOD_UNITS_H
