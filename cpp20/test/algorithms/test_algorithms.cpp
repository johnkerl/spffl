// Tests for generic algorithms (optional_inverse, optional_solve_ax_eq_b).
// Only types that model Residue_ring_with_recip (recip + exp) work; e.g. residue_of<int>, fp_polymod_t.

#include <catch2/catch_test_macros.hpp>

#include "spffl/algorithms/optional_inverse.hpp"
#include "spffl/residue_of.hpp"
#include "spffl/polynomials/aliases.hpp"
#include "spffl/polynomials/fp_polymod_t.hpp"
#include "spffl/intmath/intmod_t.hpp"

using spffl::algorithms::optional_inverse;
using spffl::algorithms::optional_solve_ax_eq_b;
using spffl::residue_of;
using spffl::polynomials::fp_poly_t;
using spffl::polynomials::fp_polymod_t;
using spffl::intmath::intmod_t;

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
