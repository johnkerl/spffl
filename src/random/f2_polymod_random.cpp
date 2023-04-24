// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2_polymod_random.h"
#include "f2_poly_random.h"
#include "int_random.h"

namespace spffl::random {

// ----------------------------------------------------------------
spffl::polynomials::f2_polymod_t f2_polymod_random(spffl::polynomials::f2_poly_t m) {
  int deg = m.find_degree();
  if (deg < 1) {
    std::cerr << "f2_polymod_random:  degree (" << deg << ") of " << m
              << " should be >= 1.\n";
    exit(1);
  }

  return spffl::polynomials::f2_polymod_t(f2_poly_random(deg), m);
}

} // namespace