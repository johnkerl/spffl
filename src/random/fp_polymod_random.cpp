// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fp_polymod_random.h"
#include "fp_poly_random.h"
#include "spffl_exception.h"

namespace spffl::random {

// ----------------------------------------------------------------
spffl::polynomials::fp_polymod_t fp_polymod_random(
    const spffl::polynomials::fp_poly_t &m) {
  int deg = m.find_degree();
  if (deg < 1) {
    std::stringstream ss;
    ss << "fp_polymod_random:  degree (" << deg << ") of " << m
       << " should be >= 1.\n";
    throw spffl::exception_t(ss.str());
  }
  int p = m.get_characteristic();
  return spffl::polynomials::fp_polymod_t(fp_poly_random(p, deg), m);
}

} // namespace spffl::random
