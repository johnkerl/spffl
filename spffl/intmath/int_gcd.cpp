// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/intmath/int_gcd.h"

namespace spffl::intmath {

// ----------------------------------------------------------------
int int_gcd(int a, int b) {
  int r;

  if (a == 0) {
    return b;
  }
  if (b == 0) {
    return a;
  }

  if (a < 0) { // Breaks for most negative int (-2^63); I don't care.
    a = -a;
  }
  if (b < 0) {
    b = -b;
  }

  while (1) {
    r = a % b;
    if (r == 0) {
      break;
    }
    a = b;
    b = r;
  }

  return b;
}

// ----------------------------------------------------------------
int int_ext_gcd(int a, int b, int &m, int &n) {
  int mprime, nprime, c, q, r, t, qm, qn;
  int d; // Return value.

  // Initialize
  mprime = 1;
  n = 1;
  m = 0;
  nprime = 0;
  c = a;
  d = b;

  while (1) {

    // Divide
    q = c / d;
    r = c % d;
    // Note:  now c = qd + r and 0 <= r < d

    // Remainder zero?
    if (r == 0) {
      break;
    }

    // Recycle
    c = d;
    d = r;

    t = mprime;
    mprime = m;
    qm = q * m;
    m = t - qm;

    t = nprime;
    nprime = n;
    qn = q * n;
    n = t - qn;
  }
  return d;
}

// ----------------------------------------------------------------
int int_lcm(int a, int b) { return (a * b) / int_gcd(a, b); }

// ----------------------------------------------------------------
int gcd(const int a, const int b) { return int_gcd(a, b); }

} // namespace spffl::intmath
