// Computation of cyclotomic polynomials:
//
// x^n - 1 = product over d dividing n of Phi_d(n).
// E.g. x^8 - 1 = Phi_1(x) * Phi_2(x) * Phi_4(x) * Phi_8(x).
// So, Phi_n(x) = (x^n - 1) / product over d dividing n and d<n of Phi_d(n).
// E.g.  Phi_8(x) = (x^8 - 1) / (Phi_1(x) * Phi_2(x) * Phi_4(x)).

#include <iostream>
#include <string>

#include "base/spffl_exception.h"
#include "q_cyclotomic/cyclo_poly.h"
#include "q_cyclotomic/qff.h"

namespace spffl::q_cyclotomic {

#define CYCLO_MEMO_MAX 16
static int memo_flags[CYCLO_MEMO_MAX + 1] = {0};
static spffl::rationals::q_poly_t memo_data[CYCLO_MEMO_MAX + 1];

// ----------------------------------------------------------------
spffl::rationals::q_poly_t get_cyclo_qpoly(int n) {
  int d;
  spffl::rationals::q_poly_t rv;
  spffl::rationals::q_poly_t dth;
  spffl::rationals::q_poly_t rem;
  spffl::rationals::q_poly_t zero(0);

  if (n < 1) {
    std::stringstream ss;
    ss << "get_cyclo_qpoly: argument must be positive; got " << n << ".\n";
    throw spffl::exception_t(ss.str());
  }

  if ((n <= CYCLO_MEMO_MAX) && (memo_flags[n])) {
    return memo_data[n];
  }

  if (n == 1) {
    rv = spffl::rationals::q_poly_t(1, -1);
    if (n <= CYCLO_MEMO_MAX) {
      memo_data[n]  = rv;
      memo_flags[n] = 1;
    }
    return rv;
  }

  // x^n - 1
  rv = spffl::rationals::q_poly_t::binomial(
      spffl::rationals::intrat_t(1), n, spffl::rationals::intrat_t(-1), 0);

  for (d = 1; d < n; d++) {
    if ((n % d) != 0) {
      continue;
    }

    if ((d <= CYCLO_MEMO_MAX) && (memo_flags[d])) {
      dth = memo_data[d];
    } else {
      dth = get_cyclo_qpoly(d);
    }

    rv.quot_and_rem(dth, rv, rem);
    if (rem != zero) {
      std::stringstream ss;
      ss << "get_cyclo_qpoly: internal error.\n";
      throw spffl::exception_t(ss.str());
    }
  }

  if (n <= CYCLO_MEMO_MAX) {
    memo_data[n]  = rv;
    memo_flags[n] = 1;
  }

  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::f2_poly_t get_cyclo_f2_poly(int n) {
  spffl::rationals::q_poly_t q      = get_cyclo_qpoly(n);
  spffl::polynomials::f2_poly_t rv = f2_poly_from_q_poly(q);
  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::fp_poly_t get_cyclo_fp_poly(int n, int p) {
  spffl::rationals::q_poly_t q      = get_cyclo_qpoly(n);
  spffl::polynomials::fp_poly_t rv = fp_poly_from_qpoly(q, p);
  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::f2n_poly_t get_cyclo_f2n_poly(
    int n, const spffl::polynomials::f2_poly_t &im) {
  spffl::rationals::q_poly_t q       = get_cyclo_qpoly(n);
  spffl::polynomials::f2n_poly_t rv = f2n_poly_from_qpoly(q, im);
  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::fpn_poly_t get_cyclo_fpn_poly(
    int n, const spffl::polynomials::fp_poly_t &im) {
  spffl::rationals::q_poly_t q       = get_cyclo_qpoly(n);
  spffl::polynomials::fpn_poly_t rv = fpn_poly_from_qpoly(q, im);
  return rv;
}

// ----------------------------------------------------------------
#ifdef CYCLOPOLY_TEST
int main(void) {
  int p    = 3;
  int nmax = 30;
  spffl::polynomials::f2_poly_t m2 =
      spffl::polynomials::f2_poly_t::from_base_rep(0x13);
  spffl::polynomials::fp_poly_t mp(spffl::intmath::intmod_t(1, 3),
      spffl::intmath::intmod_t(0, 3), spffl::intmath::intmod_t(2, 3),
      spffl::intmath::intmod_t(1, 3));

  for (int n = 1; n < nmax; n++) {
    std::cout << n << ": " << get_cyclo_qpoly(n) << "\n";
  }
  std::cout << "\n";

  for (int n = 1; n < nmax; n++) {
    std::cout << n << ": " << get_cyclo_f2_poly(n) << "\n";
  }
  std::cout << "\n";

  for (int n = 1; n < nmax; n++) {
    std::cout << n << ": " << get_cyclo_fp_poly(n, p) << "\n";
  }
  std::cout << "\n";

  for (int n = 1; n < nmax; n++) {
    std::cout << n << ": " << get_cyclo_f2n_poly(n, m2) << "\n";
  }
  std::cout << "\n";

  for (int n = 1; n < nmax; n++) {
    std::cout << n << ": " << get_cyclo_fpn_poly(n, mp) << "\n";
  }
  std::cout << "\n";

  return 0;
}
#endif

} // namespace spffl::q_cyclotomic
