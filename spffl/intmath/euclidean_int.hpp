// ================================================================
// Euclidean domain operations for int (free functions).
// Enables generic algorithms to treat int and polynomial types
// uniformly via overloads: use quot_and_rem(a, b, q, r) and gcd(a, b).
// ================================================================

#ifndef SPFFL_INTMATH_EUCLIDEAN_INT_HPP
#define SPFFL_INTMATH_EUCLIDEAN_INT_HPP

#include <numeric>
#include <stdexcept>

namespace spffl::intmath {

// Euclidean quotient and remainder: a = b*q + r with 0 <= r < |b| (b != 0).
// Truncation semantics: q = a/b (C++ integer division), r = a - b*q.
inline void quot_and_rem(int a, int b, int& q, int& r) {
  if (b == 0) {
    throw std::invalid_argument("euclidean_int: division by zero");
  }
  q = a / b;
  r = a - b * q;
}

// GCD (non-negative result). Delegates to std::gcd (C++17).
inline int gcd(int a, int b) {
  a = a < 0 ? -a : a;
  b = b < 0 ? -b : b;
  return static_cast<int>(std::gcd(static_cast<unsigned>(a),
                                   static_cast<unsigned>(b)));
}

// Extended GCD: returns g = gcd(a,b) and sets m, n such that a*m + b*n = g.
inline int ext_gcd(int a, int b, int& m, int& n) {
  if (b == 0) {
    m = (a < 0) ? -1 : 1;
    n = 0;
    return (a < 0) ? -a : a;
  }
  int m1 = 0, n1 = 1;
  m = 1;
  n = 0;
  int c = a, d = b;
  while (d != 0) {
    int q = c / d;
    int r = c - q * d;
    c = d;
    d = r;
    int t = m1;
    m1 = m - q * m1;
    m = t;
    t = n1;
    n1 = n - q * n1;
    n = t;
  }
  if (c < 0) {
    c = -c;
    m = -m;
    n = -n;
  }
  return c;
}

}  // namespace spffl::intmath

#endif  // SPFFL_INTMATH_EUCLIDEAN_INT_HPP
