// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "int_factor.h"
#include "primes_16.h"
#include "tfacinfo.h"
#include "tmatrix.h"

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

  for (int i = 0; i < numprimes16; i++) {
    int p = primes_16[i];
    if (n == 1)
      return finfo;
    if ((n % p) != 0)
      continue;
    int count = 0;
    while ((n % p) == 0) {
      count++;
      n /= p;
    }
    finfo.insert_factor(p, count);
  }
  if (n != 1)
    finfo.insert_factor(n);
  return finfo;
}
