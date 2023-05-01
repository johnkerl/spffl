// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/random/f2_poly_random.h"
#include "spffl/base/spffl_exception.h"
#include "spffl/random/int_random.h"

namespace spffl::random {

// ----------------------------------------------------------------
spffl::polynomials::f2_poly_t f2_poly_random(int deg) {
  if (deg < 0) {
    std::stringstream ss;
    ss << "f2_poly_random:  degree " << deg << " should be non-negative.\n";
    throw spffl::exception_t(ss.str());
  }

  spffl::polynomials::f2_poly_t rv(0);
  rv.set_bit(deg);
  for (int i = deg - 1; i >= 0; i--) {
    int bit = (get_random_uint32() >> 17) & 1;
    if (bit) {
      rv.set_bit(i);
    }
  }
  return rv;
}

} // namespace spffl::random
