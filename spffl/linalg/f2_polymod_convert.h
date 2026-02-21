// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYMOD_CONVERT_H
#define F2POLYMOD_CONVERT_H
#include "spffl/containers/tmatrix.h"
#include "spffl/polynomials/f2_polymod_t.h"
#include "spffl/polynomials/f2n_poly_t.h"

namespace spffl::linalg {

bool f2_polymod_convert_prep(spffl::polynomials::f2_polymod_t g1, spffl::polynomials::f2_poly_t m2,
  spffl::polynomials::f2_polymod_t &rg2);

spffl::polynomials::f2_polymod_t f2_polymod_convert_scalar(spffl::polynomials::f2_polymod_t g1,
  spffl::polynomials::f2_polymod_t g2, spffl::polynomials::f2_polymod_t a1);

spffl::polynomials::f2n_poly_t f2_polymod_convert_poly(spffl::polynomials::f2_polymod_t g1,
  spffl::polynomials::f2_polymod_t g2, spffl::polynomials::f2n_poly_t f1);

tmatrix<spffl::polynomials::f2_polymod_t> f2_polymod_convert_matrix(
  spffl::polynomials::f2_polymod_t g1, spffl::polynomials::f2_polymod_t g2,
  tmatrix<spffl::polynomials::f2_polymod_t> A1);

} // namespace spffl::linalg

#endif // F2POLYMOD_CONVERT_H
