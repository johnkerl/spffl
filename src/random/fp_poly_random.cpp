// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fp_poly_random.h"
#include "intmod_random.h"

// ----------------------------------------------------------------
fp_poly_t fp_poly_random(int p, int deg) {
  if (deg < 0) {
    std::cerr << "fp_poly_random:  degree " << deg << " must be non-negative.\n";
    exit(1);
  }

  intmod_t zero(0, p);
  intmod_t one(1, p);
  fp_poly_t rv(zero);
  for (int i = deg; i >= 0; i--) {
    intmod_t c = intmod_random(p);
    if ((i == deg) && (c == zero))
      c = one;
    rv.set_coeff(i, c);
  }
  return rv;
}
