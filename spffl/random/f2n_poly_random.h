// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLY_RANDOM_H
#define F2NPOLY_RANDOM_H
#include "spffl/polynomials/f2n_poly_t.h"
namespace spffl::random {
spffl::polynomials::f2n_poly_t f2n_poly_random(
    const spffl::polynomials::f2_poly_t &m, int deg);
} // namespace spffl::random
#endif // F2NPOLY_RANDOM_H
