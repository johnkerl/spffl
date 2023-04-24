// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef SPMINCHAR_H
#define SPMINCHAR_H

#include "f2n_polymod_t.h"
#include "f2_polymod_t.h"
#include "fp_polymod_t.h"

namespace spffl::linalg {

int f2pm_froblen(spffl::polynomials::f2_polymod_t a);
int f2npm_froblen(spffl::polynomials::f2n_polymod_t a);
int fppm_froblen(spffl::polynomials::fp_polymod_t a);

spffl::polynomials::f2_poly_t f2pm_min_poly(spffl::polynomials::f2_polymod_t a);
spffl::polynomials::f2n_poly_t f2npm_min_poly(spffl::polynomials::f2n_polymod_t a);
spffl::polynomials::fp_poly_t fppm_min_poly(spffl::polynomials::fp_polymod_t a);

spffl::polynomials::f2_poly_t f2pm_char_poly(spffl::polynomials::f2_polymod_t a);
spffl::polynomials::f2n_poly_t f2npm_char_poly(spffl::polynomials::f2n_polymod_t a);
spffl::polynomials::fp_poly_t fppm_char_poly(spffl::polynomials::fp_polymod_t a);

} // namespace

#endif // SPMINCHAR_H
