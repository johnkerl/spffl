// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/random/intmod_random.h"
#include "spffl/base/spffl_exception.h"
#include "spffl/random/int_random.h"

namespace spffl::random {

// ----------------------------------------------------------------
spffl::intmath::intmod_t intmod_random(int m) {
  if (m < 2) {
    std::stringstream ss;
    ss << "intmod_random:  modulus " << m << " should be >= 2.\n";
    throw spffl::exception_t(ss.str());
  }
  return spffl::intmath::intmod_t(get_random_int(), m);
}

} // namespace spffl::random
