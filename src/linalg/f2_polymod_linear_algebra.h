// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2PMLINALG_H
#define F2PMLINALG_H

#include "f2n_poly_t.h"
#include "tmatrix.h"

f2n_poly_t f2pm_char_poly(tmatrix<f2_polymod_t> &A);

tmatrix<f2_polymod_t> f2np_companion_matrix(f2n_poly_t chpol);

// Test for diagonalizability over a splitting field.  (Diagonalizability over
// the base field is rare enough to be non-interesting, so we do not have a
// function for that.  If in fact the matrix is diagonalizable over the base
// field, then the splitter modulus will be set equal to the original modulus.)
int f2pm_matrix_is_dable(tmatrix<f2_polymod_t> &A, f2_poly_t &rsplitter_modulus,
                         tvector<f2_polymod_t> &reigenvalues);

tvector<f2_polymod_t> ft_vector_from_base_rep(int base_rep, f2_poly_t m, int len);

#endif // F2PMLINALG_H
