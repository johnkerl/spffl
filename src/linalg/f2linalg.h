// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2LINALG_H
#define F2LINALG_H

#include "bit_t.h"
#include "f2npoly_t.h"
#include "f2poly_t.h"
#include "tmatrix.h"

tvector<bit_t> f2_vector_from_base_rep(int base_rep, int len);

tmatrix<bit_t> f2_matrix_from_base_rep(int base_rep, int num_rows,
                                       int num_cols);

f2poly_t f2_char_poly(tmatrix<bit_t> &A);

tmatrix<bit_t> f2_companion_matrix(f2poly_t chpol);

f2npoly_t f2polymod_min_poly(f2polymod_t a);

f2npoly_t f2polymod_char_poly(f2polymod_t a);

#endif // F2LINALG_H
