// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/moebius.h"
#include "spffl/int_factor.h"

// ----------------------------------------------------------------
int calc_moebius(int n) {
  int rv = 1;
  tfacinfo<int> finfo = int_factor(n);

  for (int i = 0; i < finfo.get_num_distinct(); i++) {
    if (finfo.get_ith_count(i) > 1)
      return 0;
    rv *= -1;
  }
  return rv;
}
