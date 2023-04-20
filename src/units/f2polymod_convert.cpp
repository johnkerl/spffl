// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2polymod_convert.h"
#include "f2_linear_algebra.h"
#include "f2npoly_factor.h"
#include "f2polymod_units.h"

// ----------------------------------------------------------------
int f2polymod_convert_prep(f2polymod_t g1, f2poly_t m2, f2polymod_t &rg2) {
  f2npoly_t g1_min_poly = f2polymod_min_poly(g1);
  f2npoly_t g2_min_poly = g1_min_poly;
  g2_min_poly.change_modulus(m2);
  tvector<f2polymod_t> roots;
  if (!f2npoly_roots(g2_min_poly, roots))
    return 0;
  if (roots.get_num_elements() != g2_min_poly.find_degree())
    return 0;
  roots.sort(); // Take the lexically smallest.
  rg2 = roots[0];
  return 1;
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_convert_scalar(f2polymod_t g1, f2polymod_t g2,
                                     f2polymod_t a1) {
  f2polymod_t zero1 = g1 - g1;
  f2polymod_t zero2 = g2 - g2;
  if (a1 == zero1)
    return zero2;
  else
    return g2.exp(f2polymod_log(g1, a1));
}

// ----------------------------------------------------------------
f2npoly_t f2polymod_convert_poly(f2polymod_t g1, f2polymod_t g2, f2npoly_t f1) {
  int deg = f1.find_degree();
  f2npoly_t f2(f1);
  for (int i = 0; i <= deg; i++)
    f2.set_coeff(i, f2polymod_convert_scalar(g1, g2, f1.get_coeff(i)));
  return f2;
}

// ----------------------------------------------------------------
tmatrix<f2polymod_t> f2polymod_convert_matrix(f2polymod_t g1, f2polymod_t g2,
                                              tmatrix<f2polymod_t> A1) {
  int nr = A1.get_num_rows();
  int nc = A1.get_num_cols();
  tmatrix<f2polymod_t> A2(nr, nc);
  for (int i = 0; i < nr; i++)
    for (int j = 0; j < nc; j++)
      A2[i][j] = f2polymod_convert_scalar(g1, g2, A1[i][j]);
  return A2;
}
