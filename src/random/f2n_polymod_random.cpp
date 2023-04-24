// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2n_polymod_random.h"
#include "f2n_poly_random.h"

// ----------------------------------------------------------------
spffl::polynomials::f2n_polymod_t f2n_polymod_random(spffl::polynomials::f2_poly_t im, spffl::polynomials::f2n_poly_t om) {
  int deg = om.find_degree();
  spffl::polynomials::f2n_poly_t r = f2n_poly_random(im, deg);
  return spffl::polynomials::f2n_polymod_t(r, om);
}
