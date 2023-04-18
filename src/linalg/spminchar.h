// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef SPMINCHAR_H
#define SPMINCHAR_H

#include "f2polymod_t.h"
#include "f2npolymod_t.h"
#include "fppolymod_t.h"

int f2pm_froblen (f2polymod_t  a);
int f2npm_froblen(f2npolymod_t a);
int fppm_froblen (fppolymod_t  a);

f2poly_t  f2pm_min_poly (f2polymod_t  a);
f2npoly_t f2npm_min_poly(f2npolymod_t a);
fppoly_t  fppm_min_poly (fppolymod_t  a);

f2poly_t  f2pm_char_poly (f2polymod_t  a);
f2npoly_t f2npm_char_poly(f2npolymod_t a);
fppoly_t  fppm_char_poly (fppolymod_t  a);

#endif // SPMINCHAR_H
