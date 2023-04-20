// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "int_gcd.h"

// ----------------------------------------------------------------
int int_gcd(int a, int b) {
  int r;

  if (a == 0)
    return b;
  if (b == 0)
    return a;

  if (a < 0) // Breaks for most negative int (-2^31); I don't care.
    a = -a;
  if (b < 0)
    b = -b;

  while (1) {
    r = a % b;
    if (r == 0)
      break;
    a = b;
    b = r;
  }

  return b;
}

// ----------------------------------------------------------------
int int_ext_gcd(int a, int b, int *pm, int *pn) {
  int mprime, nprime, c, q, r, t, qm, qn;
  int d; // Return value.

  // Initialize
  mprime = 1;
  *pn = 1;
  *pm = 0;
  nprime = 0;
  c = a;
  d = b;

  while (1) {

    // Divide
    q = c / d;
    r = c % d;
    // Note:  now c = qd + r and 0 <= r < d

    // Remainder zero?
    if (r == 0)
      break;

    // Recycle
    c = d;
    d = r;

    t = mprime;
    mprime = *pm;
    qm = q * *pm;
    *pm = t - qm;

    t = nprime;
    nprime = *pn;
    qn = q * *pn;
    *pn = t - qn;
  }
  return d;
}

// ----------------------------------------------------------------
int int_lcm(int a, int b) { return (a * b) / int_gcd(a, b); }

// ----------------------------------------------------------------
int gcd(int a, int b) { return int_gcd(a, b); }
