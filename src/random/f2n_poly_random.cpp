// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2n_poly_random.h"
#include "f2_polymod_random.h"

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_random(f2_poly_t m, int deg) {
  if (deg < 0) {
    std::cerr << "f2n_poly_random:  degree " << deg
              << " should be non-negative.\n";
    exit(1);
  }

  f2_poly_t a0(0);
  f2_poly_t a1(1);
  f2_polymod_t am0(a0, m);
  f2_polymod_t am1(a1, m);
  f2n_poly_t rv(am0);
  for (int i = deg; i >= 0; i--) {
    f2_polymod_t am = f2_polymod_random(m);
    if ((i == deg) && (am == am0))
      am = am1;
    rv.set_coeff(i, am);
  }
  return rv;
}
