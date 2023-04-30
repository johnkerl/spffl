// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "random/f2_polymod_random.h"
#include "base/spffl_exception.h"
#include "random/f2_poly_random.h"
#include "random/int_random.h"

namespace spffl::random {

// ----------------------------------------------------------------
spffl::polynomials::f2_polymod_t f2_polymod_random(
    const spffl::polynomials::f2_poly_t &m) {
  int deg = m.find_degree();
  if (deg < 1) {
    std::stringstream ss;
    ss << "f2_polymod_random:  degree (" << deg << ") of " << m
       << " should be >= 1.\n";
    throw spffl::exception_t(ss.str());
  }

  return spffl::polynomials::f2_polymod_t(f2_poly_random(deg), m);
}

} // namespace spffl::random
