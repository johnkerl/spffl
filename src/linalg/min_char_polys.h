// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef SPMINCHAR_H
#define SPMINCHAR_H

#include "f2n_polymod_t.h"
#include "f2_polymod_t.h"
#include "fp_polymod_t.h"

int f2pm_froblen(f2_polymod_t a);
int f2npm_froblen(f2n_polymod_t a);
int fppm_froblen(fp_polymod_t a);

f2_poly_t f2pm_min_poly(f2_polymod_t a);
f2n_poly_t f2npm_min_poly(f2n_polymod_t a);
fp_poly_t fppm_min_poly(fp_polymod_t a);

f2_poly_t f2pm_char_poly(f2_polymod_t a);
f2n_poly_t f2npm_char_poly(f2n_polymod_t a);
fp_poly_t fppm_char_poly(fp_polymod_t a);

#endif // SPMINCHAR_H
