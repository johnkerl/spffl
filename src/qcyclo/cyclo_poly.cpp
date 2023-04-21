// Computation of cyclotomic polynomials:
//
// x^n - 1 = product over d dividing n of Phi_d(n).
// E.g. x^8 - 1 = Phi_1(x) * Phi_2(x) * Phi_4(x) * Phi_8(x).
// So, Phi_n(x) = (x^n - 1) / product over d dividing n and d<n of Phi_d(n).
// E.g.  Phi_8(x) = (x^8 - 1) / (Phi_1(x) * Phi_2(x) * Phi_4(x)).

#include <iostream>
#include <string>

#include "cyclo_poly.h"
#include "qff.h"

#define CYCLO_MEMO_MAX 16
static int memo_flags[CYCLO_MEMO_MAX + 1] = {0};
static qpoly_t memo_data[CYCLO_MEMO_MAX + 1];

// ----------------------------------------------------------------
qpoly_t get_cyclo_qpoly(int n) {
  int d;
  qpoly_t rv;
  qpoly_t dth;
  qpoly_t rem;
  qpoly_t zero(0);

  if (n < 1) {
    std::cerr << "get_cyclo_qpoly: argument must be positive; got " << n
              << ".\n";
    exit(1);
  }

  if ((n <= CYCLO_MEMO_MAX) && (memo_flags[n]))
    return memo_data[n];

  if (n == 1) {
    rv = qpoly_t(1, -1);
    if (n <= CYCLO_MEMO_MAX) {
      memo_data[n] = rv;
      memo_flags[n] = 1;
    }
    return rv;
  }

  // x^n - 1
  rv = qpoly_t::binomial(intrat_t(1), n, intrat_t(-1), 0);

  for (d = 1; d < n; d++) {
    if ((n % d) != 0)
      continue;

    if ((d <= CYCLO_MEMO_MAX) && (memo_flags[d]))
      dth = memo_data[d];
    else
      dth = get_cyclo_qpoly(d);

    rv.quot_and_rem(dth, rv, rem);
    if (rem != zero) {
      std::cerr << "get_cyclo_qpoly: internal error.\n";
      exit(1);
    }
  }

  if (n <= CYCLO_MEMO_MAX) {
    memo_data[n] = rv;
    memo_flags[n] = 1;
  }

  return rv;
}

// ----------------------------------------------------------------
f2_poly_t get_cyclo_f2poly(int n) {
  qpoly_t q = get_cyclo_qpoly(n);
  f2_poly_t rv = f2poly_from_qpoly(q);
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t get_cyclo_fppoly(int n, int p) {
  qpoly_t q = get_cyclo_qpoly(n);
  fp_poly_t rv = fppoly_from_qpoly(q, p);
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t get_cyclo_f2npoly(int n, f2_poly_t im) {
  qpoly_t q = get_cyclo_qpoly(n);
  f2n_poly_t rv = f2npoly_from_qpoly(q, im);
  return rv;
}

// ----------------------------------------------------------------
fpn_poly_t get_cyclo_fpnpoly(int n, fp_poly_t im) {
  qpoly_t q = get_cyclo_qpoly(n);
  fpn_poly_t rv = fpnpoly_from_qpoly(q, im);
  return rv;
}

// ----------------------------------------------------------------
#ifdef CYCLOPOLY_TEST
int main(void) {
  int p = 3;
  int nmax = 30;
  f2_poly_t m2 = f2_poly_t::from_base_rep(0x13);
  fp_poly_t mp(intmod_t(1, 3), intmod_t(0, 3), intmod_t(2, 3), intmod_t(1, 3));

  for (int n = 1; n < nmax; n++)
    std::cout << n << ": " << get_cyclo_qpoly(n) << "\n";
  std::cout << "\n";

  for (int n = 1; n < nmax; n++)
    std::cout << n << ": " << get_cyclo_f2poly(n) << "\n";
  std::cout << "\n";

  for (int n = 1; n < nmax; n++)
    std::cout << n << ": " << get_cyclo_fppoly(n, p) << "\n";
  std::cout << "\n";

  for (int n = 1; n < nmax; n++)
    std::cout << n << ": " << get_cyclo_f2npoly(n, m2) << "\n";
  std::cout << "\n";

  for (int n = 1; n < nmax; n++)
    std::cout << n << ": " << get_cyclo_fpnpoly(n, mp) << "\n";
  std::cout << "\n";

  return 0;
}
#endif
