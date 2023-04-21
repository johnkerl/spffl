// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2n_polymod_random.h"
#include "f2n_poly_random.h"

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_random(f2_poly_t im, f2n_poly_t om) {
  int deg = om.find_degree();
  f2n_poly_t r = f2n_poly_random(im, deg);
  return f2n_polymod_t(r, om);
}
