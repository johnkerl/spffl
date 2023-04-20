// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fp_linear_algebra.h"
#include "fppoly_t.h"

// ----------------------------------------------------------------
tvector<intmod_t> fp_vector_from_base_rep(int base_rep, int p, int len) {
  tvector<intmod_t> v(len);
  int i;

  for (i = len - 1; i >= 0; i--) {
    v[i] = intmod_t(base_rep % p, p);
    base_rep /= p;
  }
  return v;
}

// ----------------------------------------------------------------
fppoly_t fp_char_poly(tmatrix<intmod_t> &A) {
  if (!A.is_square()) {
    std::cerr << "fp_char_poly():  non-square input.\n";
    exit(1);
  }

  int i, j;
  int n = A.get_num_rows();
  tmatrix<fppoly_t> tI_A(n, n);
  int p = A[0][0].get_modulus();
  intmod_t c1(1, p);
  intmod_t c0(0, p);
  fppoly_t t(c1, c0);
  fppoly_t det;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      tI_A[i][j] = -fppoly_t(A[i][j]);
      if (i == j)
        tI_A[i][j] += t;
    }
  }

  det = tI_A.ed_det();
  return det;
}

// ----------------------------------------------------------------
tmatrix<intmod_t> fp_companion_matrix(fppoly_t chpol) {
  int n = chpol.find_degree();
  int p = chpol.get_char();
  tmatrix<intmod_t> rv(n, n);
  int i;

  // chpol = 10011
  // 0 0 1 1
  // 1 0 0 0
  // 0 1 0 0
  // 0 0 1 0

  rv = intmod_t(0, p);
  for (i = 1; i < n; i++)
    rv[i][i - 1] = intmod_t(1, p);
  for (i = 0; i < n; i++)
    rv[0][n - 1 - i] = -chpol.get_coeff(i);

  return rv;
}

#if 0
// ----------------------------------------------------------------
static fpnpoly_t fppolymod_char_or_min_poly(
	fppolymod_t a,
	bool do_min)
{
	fppoly_t m = a.get_modulus();
	int p = m.get_char();
	int d = m.find_degree();
	fppoly_t r1(intmod_t(1, p));
	fppolymod_t one(r1, m);
	fpnpoly_t rv = one;
	fppolymod_t ap = a;

	for (int i = 0; i < d; i++) {
		fpnpoly_t factor(one, ap);
		rv *= factor;
		ap = ap.exp(p); // Frobenius
		if (do_min && (ap == a))
			break;
	}

	return rv;
}

// ----------------------------------------------------------------
fpnpoly_t fppolymod_char_poly(
	fppolymod_t a)
{
	return fppolymod_char_or_min_poly(a, 0);
}

// ----------------------------------------------------------------
fpnpoly_t fppolymod_min_poly(
	fppolymod_t a)
{
	return fppolymod_char_or_min_poly(a, 1);
}
#endif
