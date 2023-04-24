// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLY_FACTOR_H
#define FPPOLY_FACTOR_H
#include "fp_poly_t.h"
#include "tfacinfo.h"

tfacinfo<spffl::polynomials::fp_poly_t> fp_poly_factor(spffl::polynomials::fp_poly_t f);

int fppoly_is_irreducible(spffl::polynomials::fp_poly_t f);

// Lexically lowest (and therefore monic).
spffl::polynomials::fp_poly_t fppoly_find_irr(int p, int degree);

// Monic.
spffl::polynomials::fp_poly_t fppoly_random_irr(int p, int degree);

#endif // FPPOLY_FACTOR_H
