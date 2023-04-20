// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLY_FACTOR_H
#define FPPOLY_FACTOR_H
#include "fppoly_t.h"
#include "tfacinfo.h"

tfacinfo<fppoly_t> fppoly_factor(fppoly_t f);

int fppoly_is_irreducible(fppoly_t f);

// Lexically lowest (and therefore monic).
fppoly_t fppoly_find_irr(int p, int degree);

// Monic.
fppoly_t fppoly_random_irr(int p, int degree);

#endif // FPPOLY_FACTOR_H
