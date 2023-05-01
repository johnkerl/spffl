// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/factorization/int_factor.h"
#include "spffl/containers/tfacinfo.h"
#include "spffl/containers/tmatrix.h"
#include "spffl/intmath/primes_16.h"

namespace spffl::factorization {

// ----------------------------------------------------------------
tfacinfo<int> int_factor(int n) {
  tfacinfo<int> finfo;
  if ((-1 <= n) && (n <= 1)) {
    finfo.insert_unit(n);
    return finfo;
  }
  if (n < 0) {
    finfo.insert_unit(-1);
    n = -n; // Breaks at MIN_INT; I don't care.
  }

  for (int i = 0; i < spffl::intmath::numprimes16; i++) {
    int p = spffl::intmath::primes_16[i];
    if (n == 1) {
      return finfo;
    }
    if ((n % p) != 0) {
      continue;
    }
    int count = 0;
    while ((n % p) == 0) {
      count++;
      n /= p;
    }
    finfo.insert_factor(p, count);
  }
  if (n != 1) {
    finfo.insert_factor(n);
  }
  return finfo;
}

} // namespace spffl::factorization
