// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPLINALG_H
#define FPLINALG_H

#include "containers/tmatrix.h"
#include "polynomials/fp_poly_t.h"
#if 0
#include "fpn_poly_t.h"
#endif

namespace spffl::linalg {

tvector<spffl::intmath::intmod_t> fp_vector_from_base_rep(
    int base_rep, int p, int len);

spffl::polynomials::fp_poly_t fp_char_poly(
    tmatrix<spffl::intmath::intmod_t> &A);

tmatrix<spffl::intmath::intmod_t> fp_companion_matrix(
    spffl::polynomials::fp_poly_t chpol);

#if 0
spffl::polynomials::fpn_poly_t fp_polymod_min_poly(
	spffl::polynomials::fp_polymod_t a);

spffl::polynomials::fpn_poly_t fp_polymod_char_poly(
	spffl::polynomials::fp_polymod_t a);
#endif

} // namespace spffl::linalg

#endif // FPLINALG_H
