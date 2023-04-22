// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPLINALG_H
#define FPLINALG_H

#include "fp_poly_t.h"
#include "tmatrix.h"
#if 0
#include "fpn_poly_t.h"
#endif

tvector<spffl::intmath::intmod_t> fp_vector_from_base_rep(int base_rep, int p, int len);

fp_poly_t fp_char_poly(tmatrix<spffl::intmath::intmod_t> &A);

tmatrix<spffl::intmath::intmod_t> fp_companion_matrix(fp_poly_t chpol);

#if 0
fpn_poly_t fppolymod_min_poly(
	fp_polymod_t a);

fpn_poly_t fppolymod_char_poly(
	fp_polymod_t a);
#endif

#endif // FPLINALG_H
