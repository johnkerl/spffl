// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// How to compute the order of the unit group of a residue class ring over
// F_q[x], i.e. the totient function of a polynomial in F_q[x].  Let the prime
// factorization of f(x) be
//
//   f(x) = \prod_{i=1}^m {f_i}^{e_i}
//
// The CRT says
//
//   \F_q[x]/<{f(x)}> \cong \oplus_{i=1}^m \F_q[x]/\pig{{f_i}^{e_i}}
//
// as a ring isomorphism, and likewise for the multiplicative group (units).
// So the question reduces to, what is the totient function of ${f_i}^{e_i}$.
// Let $d_i = \deg(f_i)$.  Then a \emph{non}-unit in the residue class ring is
// is any multiple of $f_i$.  The $i$th factor ring has order $q^{d_i e_i}$.
// Any non-zero poly of degree less than $d_i$ is necessarily relatively prime
// to $f_i$, since $f_i$ is prime.  Letting the zero poly have degree 0, there
// are $q^{d_i e_i - d_i}$ multiples of $f_i$.  Then the number of units in
// the $i$th factor ring is
//
//   q^{d_i e_i} - q^{d_i e_i-d_i } = q^{d_i (e_i-1)}(q^{d_i} -1)
//
// and so the order of the multiplicative group is
//
//   \prod_{i=1}^m q^{d_i (e_i-1)}(q^{d_i} -1)
//
// In the irreducible case, $m=1$, $d_1=n$, $e_1=1$, whence
//
//   q^{n (1-1)}(q^{n} -1) = q^{n-1}

// which recovers the special case for finite fields.

#include "factorization/f2_poly_totient.h"
#include "factorization/f2_poly_factor.h"

namespace spffl::factorization {

int f2_poly_totient(const spffl::polynomials::f2_poly_t &f) {
  int rv                                        = 1;
  tfacinfo<spffl::polynomials::f2_poly_t> finfo = f2_poly_factor(f);
  int nf                                        = finfo.get_num_distinct();

  for (int i = 0; i < nf; i++) {
    spffl::polynomials::f2_poly_t fi = finfo.get_ith_factor(i);
    int ei                           = finfo.get_ith_count(i);
    int di                           = fi.find_degree();
    rv *= (1 << (di * (ei - 1))) * ((1 << di) - 1);
  }

  return rv;
}

} // namespace spffl::factorization
