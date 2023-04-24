// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLY_FACTOR_H
#define F2POLY_FACTOR_H
#include "f2_poly_t.h"
#include "tfacinfo.h"

namespace spffl::factorization {

tfacinfo<spffl::polynomials::f2_poly_t> f2_poly_factor(spffl::polynomials::f2_poly_t f);

int f2poly_is_irreducible(spffl::polynomials::f2_poly_t f);

// Lexically lowest.
spffl::polynomials::f2_poly_t f2poly_find_irr(int degree);

spffl::polynomials::f2_poly_t f2poly_random_irr(int degree);

} // namespace

#endif // F2POLY_FACTOR_H