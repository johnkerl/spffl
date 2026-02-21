// ================================================================
// Unified Euclidean domain operations: quot_and_rem, gcd, ext_gcd.
// Use this so generic code can treat int and polynomial types
// (e.g. fp_poly_t) uniformly for GCD and residue-ring inversion.
// ================================================================

#ifndef SPFFL_EUCLIDEAN_H
#define SPFFL_EUCLIDEAN_H

#include "spffl/concepts.h"
#include "spffl/intmath/euclidean_int.h"
#include <stdexcept>

namespace spffl::euclidean {

// ----- int (delegate to intmath) -----
inline void quot_and_rem(int a, int b, int& q, int& r) {
  intmath::quot_and_rem(a, b, q, r);
}

inline int gcd(int a, int b) {
  return intmath::gcd(a, b);
}

inline int ext_gcd(int a, int b, int& m, int& n) {
  return intmath::ext_gcd(a, b, m, n);
}

// ----- Any type that models Euclidean_domain (e.g. polynomial_of<...>) -----
template <typename E>
  requires spffl::concepts::Euclidean_domain<E>
void quot_and_rem(E const& a, E const& b, E& q, E& r) {
  a.quot_and_rem(b, q, r);
}

template <typename E>
  requires spffl::concepts::Euclidean_domain<E>
E gcd(E const& a, E const& b) {
  return a.gcd(b);
}

// ----- ext_gcd for types that model Euclidean_domain_with_ext_gcd -----
template <typename E>
  requires spffl::concepts::Euclidean_domain_with_ext_gcd<E>
E ext_gcd(E const& a, E const& b, E& m, E& n) {
  return a.ext_gcd(b, m, n);
}

}  // namespace spffl::euclidean

#endif  // SPFFL_EUCLIDEAN_H
