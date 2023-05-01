// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef SPMINCHAR_H
#define SPMINCHAR_H

#include "spffl/polynomials/f2_polymod_t.h"
#include "spffl/polynomials/f2n_polymod_t.h"
#include "spffl/polynomials/fp_polymod_t.h"

namespace spffl::linalg {

int f2_polymod_frobenius_length(spffl::polynomials::f2_polymod_t a);
int f2npm_froblen(spffl::polynomials::f2n_polymod_t a);
int fp_polymod_frobenius_length(spffl::polynomials::fp_polymod_t a);

spffl::polynomials::f2_poly_t f2_polymod_minimal_polynomial(
    spffl::polynomials::f2_polymod_t a);
spffl::polynomials::f2n_poly_t f2npm_min_poly(
    spffl::polynomials::f2n_polymod_t a);
spffl::polynomials::fp_poly_t fp_polymod_minimal_polynomial(
    spffl::polynomials::fp_polymod_t a);

spffl::polynomials::f2_poly_t f2_polymod_characteristic_polynomial(
    spffl::polynomials::f2_polymod_t a);
spffl::polynomials::f2n_poly_t f2npm_char_poly(
    spffl::polynomials::f2n_polymod_t a);
spffl::polynomials::fp_poly_t fp_polymod_characteristic_polynomial(
    spffl::polynomials::fp_polymod_t a);

} // namespace spffl::linalg

#endif // SPMINCHAR_H
