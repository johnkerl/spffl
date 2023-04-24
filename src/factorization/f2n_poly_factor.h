// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLY_FACTOR_H
#define F2NPOLY_FACTOR_H
#include "f2n_poly_t.h"
#include "tfacinfo.h"
#include "tvector.h"

namespace spffl::factorization {

tfacinfo<spffl::polynomials::f2n_poly_t> f2n_poly_factor(spffl::polynomials::f2n_poly_t f);

// Without multiplicity.
int f2npoly_roots(spffl::polynomials::f2n_poly_t f, tvector<spffl::polynomials::f2_polymod_t> &rroots);

int f2npoly_is_irreducible(spffl::polynomials::f2n_poly_t f);

// Lexically lowest (and therefore monic).
spffl::polynomials::f2n_poly_t f2npoly_find_irr(spffl::polynomials::f2_poly_t m, int degree);

// Monic.
spffl::polynomials::f2n_poly_t f2npoly_random_irr(spffl::polynomials::f2_poly_t m, int degree);

} // namespace

#endif // F2NPOLY_FACTOR_H