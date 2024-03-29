// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/random/f2n_poly_random.h"
#include "spffl/base/spffl_exception.h"
#include "spffl/random/f2_polymod_random.h"

namespace spffl::random {

// ----------------------------------------------------------------
spffl::polynomials::f2n_poly_t f2n_poly_random(
    const spffl::polynomials::f2_poly_t &m, int deg) {
  if (deg < 0) {
    std::stringstream ss;
    ss << "f2n_poly_random:  degree " << deg << " should be non-negative.\n";
    throw spffl::exception_t(ss.str());
  }

  spffl::polynomials::f2_poly_t a0(0);
  spffl::polynomials::f2_poly_t a1(1);
  spffl::polynomials::f2_polymod_t am0(a0, m);
  spffl::polynomials::f2_polymod_t am1(a1, m);
  spffl::polynomials::f2n_poly_t rv(am0);
  for (int i = deg; i >= 0; i--) {
    spffl::polynomials::f2_polymod_t am = f2_polymod_random(m);
    if ((i == deg) && (am == am0)) {
      am = am1;
    }
    rv.set_coeff(i, am);
  }
  return rv;
}

} // namespace spffl::random
