// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLYMOD_RANDOM_H
#define FPPOLYMOD_RANDOM_H
#include "spffl/polynomials/fp_polymod_t.h"
namespace spffl::random {
spffl::polynomials::fp_polymod_t fp_polymod_random(
    const spffl::polynomials::fp_poly_t &m);
} // namespace spffl::random
#endif // FPPOLYMOD_RANDOM_H
