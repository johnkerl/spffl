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

namespace spffl::units {

int f2polymod_convert_prep(spffl::polynomials::f2_polymod_t g1, spffl::polynomials::f2_poly_t m2, spffl::polynomials::f2_polymod_t &rg2);

spffl::polynomials::f2_polymod_t f2polymod_convert_scalar(spffl::polynomials::f2_polymod_t g1, spffl::polynomials::f2_polymod_t g2,
                                     spffl::polynomials::f2_polymod_t a1);

spffl::polynomials::f2n_poly_t f2polymod_convert_poly(spffl::polynomials::f2_polymod_t g1, spffl::polynomials::f2_polymod_t g2, spffl::polynomials::f2n_poly_t f1);

tmatrix<spffl::polynomials::f2_polymod_t> f2polymod_convert_matrix(spffl::polynomials::f2_polymod_t g1, spffl::polynomials::f2_polymod_t g2,
                                              tmatrix<spffl::polynomials::f2_polymod_t> A1);

} // namespace

#endif // F2POLYMOD_CONVERT_H
