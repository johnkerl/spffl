// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLY_FACTOR_H
#define FPPOLY_FACTOR_H
#include "spffl/containers/tfacinfo.h"
#include "spffl/polynomials/fp_poly_t.h"

namespace spffl::factorization {

tfacinfo<spffl::polynomials::fp_poly_t> fp_poly_factor(const spffl::polynomials::fp_poly_t &f);

bool fp_poly_is_irreducible(const spffl::polynomials::fp_poly_t &f);

// Lexically lowest (and therefore monic).
spffl::polynomials::fp_poly_t fp_poly_find_irr(int p, int degree);

// Monic.
spffl::polynomials::fp_poly_t fp_poly_random_irr(int p, int degree);

} // namespace spffl::factorization

#endif // FPPOLY_FACTOR_H
