// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2npoly_random.h"
#include "f2polymod_random.h"

// ----------------------------------------------------------------
f2npoly_t f2npoly_random(f2poly_t m, int deg) {
  if (deg < 0) {
    std::cerr << "f2npoly_random:  degree " << deg
              << " should be non-negative.\n";
    exit(1);
  }

  f2poly_t a0(0);
  f2poly_t a1(1);
  f2polymod_t am0(a0, m);
  f2polymod_t am1(a1, m);
  f2npoly_t rv(am0);
  for (int i = deg; i >= 0; i--) {
    f2polymod_t am = f2polymod_random(m);
    if ((i == deg) && (am == am0))
      am = am1;
    rv.set_coeff(i, am);
  }
  return rv;
}
