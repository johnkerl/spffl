// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYMOD_CONVERT_H
#define F2POLYMOD_CONVERT_H
#include "f2n_poly_t.h"
#include "f2_polymod_t.h"
#include "tmatrix.h"

int f2polymod_convert_prep(f2_polymod_t g1, f2_poly_t m2, f2_polymod_t &rg2);

f2_polymod_t f2polymod_convert_scalar(f2_polymod_t g1, f2_polymod_t g2,
                                     f2_polymod_t a1);

f2n_poly_t f2polymod_convert_poly(f2_polymod_t g1, f2_polymod_t g2, f2n_poly_t f1);

tmatrix<f2_polymod_t> f2polymod_convert_matrix(f2_polymod_t g1, f2_polymod_t g2,
                                              tmatrix<f2_polymod_t> A1);

#endif // F2POLYMOD_CONVERT_H
