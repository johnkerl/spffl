// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLY_FACTOR_H
#define F2NPOLY_FACTOR_H
#include "f2npoly_t.h"
#include "tfacinfo.h"
#include "tvector.h"

tfacinfo<f2npoly_t> f2n_poly_factor(f2npoly_t f);

// Without multiplicity.
int f2npoly_roots(f2npoly_t f, tvector<f2polymod_t> &rroots);

int f2npoly_is_irreducible(f2npoly_t f);

// Lexically lowest (and therefore monic).
f2npoly_t f2npoly_find_irr(f2poly_t m, int degree);

// Monic.
f2npoly_t f2npoly_random_irr(f2poly_t m, int degree);

#endif // F2NPOLY_FACTOR_H
