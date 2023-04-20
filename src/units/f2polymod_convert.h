// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYMOD_CONVERT_H
#define F2POLYMOD_CONVERT_H
#include "f2npoly_t.h"
#include "f2polymod_t.h"
#include "tmatrix.h"

int f2polymod_convert_prep(f2polymod_t g1, f2poly_t m2, f2polymod_t &rg2);

f2polymod_t f2polymod_convert_scalar(f2polymod_t g1, f2polymod_t g2,
                                     f2polymod_t a1);

f2npoly_t f2polymod_convert_poly(f2polymod_t g1, f2polymod_t g2, f2npoly_t f1);

tmatrix<f2polymod_t> f2polymod_convert_matrix(f2polymod_t g1, f2polymod_t g2,
                                              tmatrix<f2polymod_t> A1);

#endif // F2POLYMOD_CONVERT_H
