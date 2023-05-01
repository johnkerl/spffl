// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYMOD_RANDOM_H
#define F2POLYMOD_RANDOM_H
#include "polynomials/f2_polymod_t.h"
namespace spffl::random {
spffl::polynomials::f2_polymod_t f2_polymod_random(
    const spffl::polynomials::f2_poly_t &m);
} // namespace spffl::random
#endif // F2POLYMOD_RANDOM_H
