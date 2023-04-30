// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2_polymod_random.h"
#include "f2_poly_random.h"
#include "int_random.h"
#include "spffl_exception.h"

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
