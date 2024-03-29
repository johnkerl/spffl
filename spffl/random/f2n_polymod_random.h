// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLYMOD_RANDOM_H
#define F2NPOLYMOD_RANDOM_H
#include "spffl/polynomials/f2n_polymod_t.h"
namespace spffl::random {
spffl::polynomials::f2n_polymod_t f2n_polymod_random(
    const spffl::polynomials::f2_poly_t &im,
    const spffl::polynomials::f2n_poly_t &om);
} // namespace spffl::random
#endif // F2NPOLYMOD_RANDOM_H
