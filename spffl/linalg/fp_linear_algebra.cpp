// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "base/spffl_exception.h"
#include "polynomials/fp_poly_t.h"
#include "linalg/fp_linear_algebra.h"

namespace spffl::linalg {

// ----------------------------------------------------------------
tvector<spffl::intmath::intmod_t> fp_vector_from_base_rep(
    int base_rep, int p, int len) {
  tvector<spffl::intmath::intmod_t> v(len);
  int i;

  for (i = len - 1; i >= 0; i--) {
    v[i] = spffl::intmath::intmod_t(base_rep % p, p);
    base_rep /= p;
  }
  return v;
}

// ----------------------------------------------------------------
spffl::polynomials::fp_poly_t fp_char_poly(
    tmatrix<spffl::intmath::intmod_t> &A) {
  if (!A.is_square()) {
    std::stringstream ss;
    ss << "fp_char_poly():  non-square input.\n";
    throw spffl::exception_t(ss.str());
  }

  int i, j;
  int n = A.get_num_rows();
  tmatrix<spffl::polynomials::fp_poly_t> tI_A(n, n);
  int p = A[0][0].get_modulus();
  spffl::intmath::intmod_t c1(1, p);
  spffl::intmath::intmod_t c0(0, p);
  spffl::polynomials::fp_poly_t t(c1, c0);
  spffl::polynomials::fp_poly_t det;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      tI_A[i][j] = -spffl::polynomials::fp_poly_t(A[i][j]);
      if (i == j) {
        tI_A[i][j] += t;
      }
    }
  }

  det = tI_A.ed_det();
  return det;
}

// ----------------------------------------------------------------
tmatrix<spffl::intmath::intmod_t> fp_companion_matrix(
    spffl::polynomials::fp_poly_t chpol) {
  int n = chpol.find_degree();
  int p = chpol.get_characteristic();
  tmatrix<spffl::intmath::intmod_t> rv(n, n);
  int i;

  // chpol = 10011
  // 0 0 1 1
  // 1 0 0 0
  // 0 1 0 0
  // 0 0 1 0

  rv = spffl::intmath::intmod_t(0, p);
  for (i = 1; i < n; i++) {
    rv[i][i - 1] = spffl::intmath::intmod_t(1, p);
  }
  for (i = 0; i < n; i++) {
    rv[0][n - 1 - i] = -chpol.get_coeff(i);
  }

  return rv;
}

#if 0
// ----------------------------------------------------------------
static spffl::polynomials::fpn_poly_t fp_polymod_char_or_min_poly(
	spffl::polynomials::fp_polymod_t a,
	bool do_min)
{
	spffl::polynomials::fp_poly_t m = a.get_modulus();
	int p = m.get_characteristic();
	int d = m.find_degree();
	spffl::polynomials::fp_poly_t r1(spffl::intmath::intmod_t(1, p));
	spffl::polynomials::fp_polymod_t one(r1, m);
	spffl::polynomials::fpn_poly_t rv = one;
	spffl::polynomials::fp_polymod_t ap = a;

	for (int i = 0; i < d; i++) {
		spffl::polynomials::fpn_poly_t factor(one, ap);
		rv *= factor;
		ap = ap.exp(p); // Frobenius
		if (do_min && (ap == a))
			break;
	}

	return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::fpn_poly_t fp_polymod_char_poly(
	spffl::polynomials::fp_polymod_t a)
{
	return fp_polymod_char_or_min_poly(a, 0);
}

// ----------------------------------------------------------------
spffl::polynomials::fpn_poly_t fp_polymod_min_poly(
	spffl::polynomials::fp_polymod_t a)
{
	return fp_polymod_char_or_min_poly(a, 1);
}
#endif

} // namespace spffl::linalg
