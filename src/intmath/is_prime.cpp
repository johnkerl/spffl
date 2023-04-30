// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl_exception.h"
#include "is_prime.h"
#include "primes_16.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

namespace spffl::intmath {

// ----------------------------------------------------------------
bool isprime_trial(int n) {
  int d, q;

  if (n == -n) {
    return false;
  } else if (n < 0) {
    n = -n;
  }

  if (n <= 1) {
    return false;
  } else if (n <= 3) {
    return true;
  } else if ((n & 1) == 0) {
    return false;
  }

  for (d = 3, q = n; d <= q; d += 2) {
    q = n / d;
    if (n == q * d) {
      return false;
    }
  }

  return true;
}

// ----------------------------------------------------------------
bool isprime_table(int n) {
  int i;
  unsigned un;

  if (n == -n) {
    return false;
  } else if (n < 0) {
    n = -n;
  }

  if (n <= 1) {
    return false;
  }

  un = (unsigned)n;
  for (i = 0; i < numprimes16; i++) {
    if ((un % primes_16[i]) == 0) {
      if (un == primes_16[i]) {
        return true;
      } else {
        return false;
      }
    }
    if (primes_16[i] * primes_16[i] > un) {
      return true;
    }
  }
  return true;
}

// ----------------------------------------------------------------
bool is_prime(int n) {
  // return isprime_trial(n);
  return isprime_table(n);
}

// ----------------------------------------------------------------
int nth_prime(int n) {
  if (n > numprimes16) {
    std::stringstream ss;
    ss << "nth_prime:  n=" << n << " past end of table.\n";
    exit(1);
  } else if (n < 1) {
    std::stringstream ss;
    ss << "nth_prime:  n=" << n << " should have been positive.\n";
    exit(1);
  }
  return (int)primes_16[n - 1];
}

} // namespace spffl::intmath
