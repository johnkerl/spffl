// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2_polymod_convert.h"
#include "f2_linear_algebra.h"
#include "f2_polymod_units.h"
#include "f2n_poly_factor.h"

namespace spffl::linalg {

// ----------------------------------------------------------------
int f2polymod_convert_prep(spffl::polynomials::f2_polymod_t g1,
                           spffl::polynomials::f2_poly_t m2,
                           spffl::polynomials::f2_polymod_t &rg2) {
  spffl::polynomials::f2n_poly_t g1_min_poly = f2polymod_min_poly(g1);
  spffl::polynomials::f2n_poly_t g2_min_poly = g1_min_poly;
  g2_min_poly.change_modulus(m2);
  tvector<spffl::polynomials::f2_polymod_t> roots;
  if (!spffl::factorization::f2npoly_roots(g2_min_poly, roots))
    return 0;
  if (roots.get_num_elements() != g2_min_poly.find_degree())
    return 0;
  roots.sort(); // Take the lexically smallest.
  rg2 = roots[0];
  return 1;
}

// ----------------------------------------------------------------
spffl::polynomials::f2_polymod_t
f2polymod_convert_scalar(spffl::polynomials::f2_polymod_t g1,
                         spffl::polynomials::f2_polymod_t g2,
                         spffl::polynomials::f2_polymod_t a1) {
  spffl::polynomials::f2_polymod_t zero1 = g1 - g1;
  spffl::polynomials::f2_polymod_t zero2 = g2 - g2;
  if (a1 == zero1)
    return zero2;
  else
    return g2.exp(spffl::units::f2polymod_log(g1, a1));
}

// ----------------------------------------------------------------
spffl::polynomials::f2n_poly_t
f2polymod_convert_poly(spffl::polynomials::f2_polymod_t g1,
                       spffl::polynomials::f2_polymod_t g2,
                       spffl::polynomials::f2n_poly_t f1) {
  int deg = f1.find_degree();
  spffl::polynomials::f2n_poly_t f2(f1);
  for (int i = 0; i <= deg; i++)
    f2.set_coeff(i, f2polymod_convert_scalar(g1, g2, f1.get_coeff(i)));
  return f2;
}

// ----------------------------------------------------------------
tmatrix<spffl::polynomials::f2_polymod_t>
f2polymod_convert_matrix(spffl::polynomials::f2_polymod_t g1,
                         spffl::polynomials::f2_polymod_t g2,
                         tmatrix<spffl::polynomials::f2_polymod_t> A1) {
  int nr = A1.get_num_rows();
  int nc = A1.get_num_cols();
  tmatrix<spffl::polynomials::f2_polymod_t> A2(nr, nc);
  for (int i = 0; i < nr; i++)
    for (int j = 0; j < nc; j++)
      A2[i][j] = f2polymod_convert_scalar(g1, g2, A1[i][j]);
  return A2;
}

} // namespace spffl::linalg
