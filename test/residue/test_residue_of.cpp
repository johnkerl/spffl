// Tests for generic residue_of<E>: Z/nZ and Fp[x]/(m).

#include <catch2/catch_test_macros.hpp>

#include "spffl/concepts.h"
#include "spffl/residue_of.h"
#include "spffl/polynomials/aliases.h"
#include "spffl/polynomials/fp_polymod_t.h"
#include "spffl/polynomials/f2_poly_t.h"

using spffl::residue_of;
using spffl::polynomials::fp_poly_t;
using spffl::polynomials::f2_poly_t;
using spffl::intmath::intmod_t;

// ---------------------------------------------------------------------------
// Concepts
// ---------------------------------------------------------------------------

TEST_CASE("residue_of<int> models Residue_ring and Residue_ring_with_recip") {
  static_assert(spffl::concepts::Residue_ring<residue_of<int>>);
  static_assert(spffl::concepts::Residue_ring_with_recip<residue_of<int>>);
}

TEST_CASE("residue_of<fp_poly_t> models Residue_ring and Residue_ring_with_recip") {
  static_assert(spffl::concepts::Residue_ring<residue_of<fp_poly_t>>);
  static_assert(spffl::concepts::Residue_ring_with_recip<residue_of<fp_poly_t>>);
}

TEST_CASE("residue_of<f2_poly_t> models Residue_ring and Residue_ring_with_recip") {
  static_assert(spffl::concepts::Residue_ring<residue_of<f2_poly_t>>);
  static_assert(spffl::concepts::Residue_ring_with_recip<residue_of<f2_poly_t>>);
}

// ---------------------------------------------------------------------------
// residue_of<int>: Z/nZ
// ---------------------------------------------------------------------------

TEST_CASE("residue_of<int>: basic ring ops (Z/7)") {
  residue_of<int> a(3, 7);
  residue_of<int> b(5, 7);

  CHECK((a + b).get_residue() == 1);   // 3+5=8 ≡ 1
  CHECK((a - b).get_residue() == 5);   // 3-5=-2 ≡ 5
  CHECK((a * b).get_residue() == 1);   // 15 ≡ 1
  CHECK((-a).get_residue() == 4);      // -3 ≡ 4
}

TEST_CASE("residue_of<int>: inverse and division") {
  residue_of<int> a(3, 7);
  residue_of<int> inv;
  REQUIRE(a.recip(inv));
  CHECK((a * inv).get_residue() == 1);

  residue_of<int> b(5, 7);
  residue_of<int> one_over_b;
  REQUIRE(b.recip(one_over_b));
  CHECK((one_over_b * b).get_residue() == 1);
}

TEST_CASE("residue_of<int>: exp") {
  residue_of<int> a(2, 7);
  auto a3 = a.exp(3);
  CHECK(a3.get_residue() == 1);  // 2^3 = 8 ≡ 1
}

// ---------------------------------------------------------------------------
// residue_of<fp_poly_t>: Fp[x]/(m)
// ---------------------------------------------------------------------------

TEST_CASE("residue_of<fp_poly_t>: F7[x]/(x^2+1) ring and inverse") {
  int p = 7;
  fp_poly_t modulus(intmod_t(1, p), intmod_t(0, p), intmod_t(1, p));  // x^2+1
  fp_poly_t x_poly(intmod_t(0, p), intmod_t(1, p));                   // x
  fp_poly_t one_poly(intmod_t(1, p));

  residue_of<fp_poly_t> x_mod(x_poly, modulus);
  residue_of<fp_poly_t> one_mod(one_poly, modulus);

  auto x_sq = x_mod * x_mod;
  CHECK(x_sq.get_residue().find_degree() == 0);  // x^2 ≡ constant (e.g. -1 or 6 in F7)

  residue_of<fp_poly_t> x_inv;
  REQUIRE(x_mod.recip(x_inv));
  CHECK((x_mod * x_inv).get_residue().find_degree() == 0);
  CHECK((x_mod * x_inv).get_residue().get_coeff(0).get_residue() == 1);
}

// ---------------------------------------------------------------------------
// residue_of<f2_poly_t>: F2[x]/(m) — legacy f2_poly_t has bit_at(), not get_coeff()
// ---------------------------------------------------------------------------

TEST_CASE("residue_of<f2_poly_t>: F2[x]/(x^2+x+1) ring and inverse") {
  f2_poly_t modulus(1, 1, 1);   // x^2 + x + 1
  f2_poly_t x_poly(1, 0);       // x
  f2_poly_t one_poly(1);

  residue_of<f2_poly_t> x_mod(x_poly, modulus);
  residue_of<f2_poly_t> one_mod(one_poly, modulus);

  auto x_sq = x_mod * x_mod;
  CHECK(x_sq.get_residue().find_degree() <= 1);  // reduced mod x^2+x+1

  residue_of<f2_poly_t> x_inv;
  REQUIRE(x_mod.recip(x_inv));
  CHECK((x_mod * x_inv).get_residue().find_degree() == 0);
  CHECK((x_mod * x_inv).get_residue() == f2_poly_t(1));
}
