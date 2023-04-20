// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPLINALG_H
#define FPLINALG_H

#include "fppoly_t.h"
#include "tmatrix.h"
#if 0
#include "fpnpoly_t.h"
#endif

tvector<intmod_t> fp_vector_from_base_rep(int base_rep, int p, int len);

fppoly_t fp_char_poly(tmatrix<intmod_t> &A);

tmatrix<intmod_t> fp_companion_matrix(fppoly_t chpol);

#if 0
fpnpoly_t fppolymod_min_poly(
	fppolymod_t a);

fpnpoly_t fppolymod_char_poly(
	fppolymod_t a);
#endif

#endif // FPLINALG_H
