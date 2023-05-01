// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLY_FACTOR_H
#define F2POLY_FACTOR_H
#include "spffl/containers/tfacinfo.h"
#include "spffl/polynomials/f2_poly_t.h"

namespace spffl::factorization {

tfacinfo<spffl::polynomials::f2_poly_t> f2_poly_factor(
    const spffl::polynomials::f2_poly_t &f);

bool f2_poly_is_irreducible(const spffl::polynomials::f2_poly_t &f);

// Lexically lowest.
spffl::polynomials::f2_poly_t f2_poly_find_irreducible(int degree);

spffl::polynomials::f2_poly_t f2_poly_random_irreducible(int degree);

} // namespace spffl::factorization

#endif // F2POLY_FACTOR_H
