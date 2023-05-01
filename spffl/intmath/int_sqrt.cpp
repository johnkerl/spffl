// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "intmath/int_sqrt.h"
#include "base/spffl_exception.h"
#include <iostream>
#include <stdlib.h>

namespace spffl::intmath {

static int int_sqrt(int nsigned, bool want_ceil) {
  unsigned n = (unsigned)nsigned;
  unsigned nsv, half_log;
  unsigned lower, upper, diff;
  unsigned half_diff, middle, middle_sq;

  if (nsigned < 0) {
    std::stringstream ss;
    ss << "int_sqrt:  Can't handle negative input " << nsigned << "\n";
    throw spffl::exception_t(ss.str());
  }

  if (nsigned == 0) {
    return 0;
  }

  for (nsv = n, half_log = 0; nsv != 0; nsv >>= 2, half_log++)
    ;
  half_log--;
  lower = 1 << half_log;
  upper = lower << 1;
  diff  = upper - lower;

  while (diff > 0) {
    half_diff = diff >> 1;
    middle    = lower + half_diff;
    middle_sq = middle * middle;
    if (middle_sq == n) {
      return middle;
    } else if (middle_sq < n) {
      lower += half_diff;
    } else {
      upper -= half_diff;
    }
    diff = half_diff;
  }
  if (want_ceil) {
    return upper;
  } else {
    return lower;
  }
}

int int_sqrt_ceil(int nsigned) { return int_sqrt(nsigned, true); }

int int_sqrt_floor(int nsigned) { return int_sqrt(nsigned, false); }

} // namespace spffl::intmath
