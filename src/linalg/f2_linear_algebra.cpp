// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2_linear_algebra.h"
#include "f2_poly_t.h"

// ----------------------------------------------------------------
tvector<spffl::bits::bit_t> f2_vector_from_base_rep(int base_rep, int len) {
  tvector<spffl::bits::bit_t> v(len);
  for (int i = len - 1; i >= 0; i--) {
    v[i] = spffl::bits::bit_t(base_rep & 1);
    base_rep >>= 1;
  }
  return v;
}

// ----------------------------------------------------------------
tmatrix<spffl::bits::bit_t> f2_matrix_from_base_rep(int base_rep, int num_rows,
                                       int num_cols) {
  tmatrix<spffl::bits::bit_t> A(num_rows, num_cols);
  for (int i = num_rows - 1; i >= 0; i--) {
    for (int j = num_cols - 1; j >= 0; j--) {
      A[i][j] = spffl::bits::bit_t(base_rep & 1);
      base_rep >>= 1;
    }
  }
  return A;
}

// ----------------------------------------------------------------
f2_poly_t f2_char_poly(tmatrix<spffl::bits::bit_t> &A) {
  if (!A.is_square()) {
    std::cerr << "f2_char_poly():  non-square input.\n";
    exit(1);
  }

  int i, j;
  int n = A.get_num_rows();
  tmatrix<f2_poly_t> A_lI(n, n);
  f2_poly_t lambda(f2_poly_t(1, 0));
  f2_poly_t det;

  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      A_lI[i][j] = f2_poly_t(A[i][j].get_residue());
      if (i == j)
        A_lI[i][j] -= lambda;
    }
  }

  det = A_lI.ed_det();

  return det;
}

// ----------------------------------------------------------------
tmatrix<spffl::bits::bit_t> f2_companion_matrix(f2_poly_t chpol) {
  int n = chpol.find_degree();
  tmatrix<spffl::bits::bit_t> rv(n, n);
  int i;

  // chpol = 13 = 10011
  // 0 0 1 1
  // 1 0 0 0
  // 0 1 0 0
  // 0 0 1 0

  rv = spffl::bits::bit_t(0);
  for (i = 1; i < n; i++)
    rv[i][i - 1] = spffl::bits::bit_t(1);
  for (i = 0; i < n; i++)
    if (chpol.bit_at(i))
      rv[0][n - 1 - i] = spffl::bits::bit_t(1);

  return rv;
}

// ----------------------------------------------------------------
static f2n_poly_t f2polymod_char_or_min_poly(f2_polymod_t a, bool do_min) {
  f2_poly_t m = a.get_modulus();
  int d = m.find_degree();
  f2_poly_t r1(1);
  f2_polymod_t one(r1, m);
  f2n_poly_t rv = one;
  f2_polymod_t ap = a;

  for (int i = 0; i < d; i++) {
    f2n_poly_t factor(one, ap);
    rv *= factor;
    ap = ap * ap; // Frobenius
    if (do_min && (ap == a))
      break;
  }

  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t f2polymod_char_poly(f2_polymod_t a) {
  return f2polymod_char_or_min_poly(a, 0);
}

// ----------------------------------------------------------------
f2n_poly_t f2polymod_min_poly(f2_polymod_t a) {
  return f2polymod_char_or_min_poly(a, 1);
}
