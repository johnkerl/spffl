// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "isprime.h"
#include "primes16.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

// ----------------------------------------------------------------
int isprime_trial(int n) {
  int d, q;

  if (n == -n)
    return 0;
  else if (n < 0)
    n = -n;

  if (n <= 1)
    return 0;
  else if (n <= 3)
    return 1;
  else if ((n & 1) == 0)
    return 0;

  for (d = 3, q = n; d <= q; d += 2) {
    q = n / d;
    if (n == q * d)
      return 0;
  }

  return 1;
}

// ----------------------------------------------------------------
int isprime_table(int n) {
  int i;
  unsigned un;

  if (n == -n)
    return 0;
  else if (n < 0)
    n = -n;

  if (n <= 1)
    return 0;

  un = (unsigned)n;
  for (i = 0; i < numprimes16; i++) {
    if ((un % primes16[i]) == 0) {
      if (un == primes16[i])
        return 1;
      else
        return 0;
    }
    if (primes16[i] * primes16[i] > un)
      return 1;
  }
  return 1;
}

// ----------------------------------------------------------------
int isprime(int n) {
  // return isprime_trial(n);
  return isprime_table(n);
}

// ----------------------------------------------------------------
int nthprime(int n) {
  if (n > numprimes16) {
    std::cerr << "nthprime:  n=" << n << " past end of table.\n";
    exit(1);
  } else if (n < 1) {
    std::cerr << "nthprime:  n=" << n << " should have been positive.\n";
    exit(1);
  }
  return (int)primes16[n - 1];
}
