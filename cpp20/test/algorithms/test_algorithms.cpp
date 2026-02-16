// Tests for generic algorithms (optional_inverse, optional_solve_ax_eq_b).
// Types that model Residue_ring_with_recip (recip + exp): intmod_t, residue_of<int>, fp_polymod_t, residue_of<f2_poly_t>.

#include <catch2/catch_test_macros.hpp>

#include "spffl/algorithms/optional_inverse.hpp"
#include "spffl/algorithms/optional_solve_2x2.hpp"
#include "spffl/containers/matrix_over.hpp"
#include "spffl/containers/vector_over.hpp"
#include "spffl/residue_of.hpp"
#include "spffl/polynomials/aliases.hpp"
#include "spffl/polynomials/fp_polymod_t.hpp"
#include "spffl/polynomials/f2_poly_t.hpp"
#include "spffl/intmath/intmod_t.hpp"

using spffl::algorithms::optional_inverse;
using spffl::algorithms::optional_solve_ax_eq_b;
using spffl::algorithms::optional_solve_2x2;
using spffl::containers::matrix_over;
using spffl::containers::vector_over;
using spffl::residue_of;
using spffl::polynomials::fp_poly_t;
using spffl::polynomials::fp_polymod_t;
using spffl::polynomials::f2_poly_t;
using spffl::intmath::intmod_t;

TEST_CASE("optional_inverse: intmod_t") {
  intmod_t a(3, 7);
  auto inv = optional_inverse(a);
  REQUIRE(inv.has_value());
  CHECK((a * *inv).get_residue() == 1);

  intmod_t zero(0, 7);
  CHECK(!optional_inverse(zero).has_value());
}

TEST_CASE("optional_inverse: residue_of<int>") {
  residue_of<int> a(3, 7);
  auto inv = optional_inverse(a);
  REQUIRE(inv.has_value());
  CHECK((a * *inv).get_residue() == 1);

  residue_of<int> zero(0, 7);
  CHECK(!optional_inverse(zero).has_value());
}

TEST_CASE("optional_solve_ax_eq_b: residue_of<int>") {
  residue_of<int> a(3, 7);
  residue_of<int> b(5, 7);
  auto x = optional_solve_ax_eq_b(a, b);
  REQUIRE(x.has_value());
  CHECK((a * *x).get_residue() == b.get_residue());
}

TEST_CASE("optional_solve_ax_eq_b: intmod_t") {
  intmod_t a(3, 7);
  intmod_t b(5, 7);
  auto x = optional_solve_ax_eq_b(a, b);
  REQUIRE(x.has_value());
  CHECK((a * *x).get_residue() == b.get_residue());
}

TEST_CASE("optional_inverse: fp_polymod_t") {
  int p = 7;
  fp_poly_t mod(intmod_t(1, p), intmod_t(0, p), intmod_t(1, p));
  fp_poly_t x_poly(intmod_t(0, p), intmod_t(1, p));
  fp_polymod_t x_mod(x_poly, mod);
  auto inv = optional_inverse(x_mod);
  REQUIRE(inv.has_value());
  CHECK((x_mod * *inv).get_residue().find_degree() == 0);
  CHECK((x_mod * *inv).get_residue().get_coeff(0).get_residue() == 1);
}

TEST_CASE("optional_inverse: residue_of<f2_poly_t>") {
  f2_poly_t mod(1, 1, 1);   // x^2+x+1
  f2_poly_t x_poly(1, 0);    // x
  residue_of<f2_poly_t> x_mod(x_poly, mod);
  auto inv = optional_inverse(x_mod);
  REQUIRE(inv.has_value());
  CHECK((x_mod * *inv).get_residue().find_degree() == 0);
  CHECK((x_mod * *inv).get_residue().get_coeff(0) == 1);
}

TEST_CASE("optional_solve_2x2: matrix_over<intmod_t> A*x = b") {
  using R = intmod_t;
  int m = 7;
  matrix_over<R> A(2, 2);
  A[0][0] = R(1, m);
  A[0][1] = R(2, m);
  A[1][0] = R(1, m);
  A[1][1] = R(3, m);
  vector_over<R> b(2);
  b[0] = R(1, m);
  b[1] = R(0, m);

  auto x_opt = optional_solve_2x2(A, b);
  REQUIRE(x_opt.has_value());
  vector_over<R> Ax = A * *x_opt;
  CHECK(Ax[0].get_residue() == b[0].get_residue());
  CHECK(Ax[1].get_residue() == b[1].get_residue());
}

TEST_CASE("optional_solve_2x2: matrix_over<residue_of<int>> A*x = b") {
  using R = residue_of<int>;
  int m = 7;
  matrix_over<R> A(2, 2);
  A[0][0] = R(1, m);
  A[0][1] = R(2, m);
  A[1][0] = R(1, m);
  A[1][1] = R(3, m);
  vector_over<R> b(2);
  b[0] = R(1, m);
  b[1] = R(0, m);

  auto x_opt = optional_solve_2x2(A, b);
  REQUIRE(x_opt.has_value());
  vector_over<R> Ax = A * *x_opt;
  CHECK(Ax[0].get_residue() == b[0].get_residue());
  CHECK(Ax[1].get_residue() == b[1].get_residue());
}
