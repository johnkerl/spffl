// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

namespace spffl::intmath {
#include "int_power.h"

// ----------------------------------------------------------------
int int_power(int b, int e) {
  int b2 = b;
  int rv = 1;

  while (e != 0) {
    if (e & 1) {
      rv = rv * b2;
    }
    e  = (unsigned)e >> 1;
    b2 = b2 * b2;
  }
  return rv;
}

} // namespace spffl::intmath
