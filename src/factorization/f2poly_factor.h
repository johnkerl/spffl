// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLY_FACTOR_H
#define F2POLY_FACTOR_H
#include "f2poly_t.h"
#include "tfacinfo.h"

tfacinfo<f2poly_t> f2poly_factor(f2poly_t f);

int f2poly_is_irreducible(f2poly_t f);

// Lexically lowest.
f2poly_t f2poly_find_irr(int degree);

f2poly_t f2poly_random_irr(int degree);

#endif // F2POLY_FACTOR_H
