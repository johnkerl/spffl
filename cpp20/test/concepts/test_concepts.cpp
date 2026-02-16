// Compile and sanity-check spffl/concepts.hpp and unified euclidean interface

#include <catch2/catch_test_macros.hpp>

#include "spffl/concepts.hpp"
#include "spffl/euclidean.hpp"
#include "spffl/polynomials/aliases.hpp"
#include "spffl/intmath/intmod_t.hpp"

using namespace spffl::concepts;

TEST_CASE("Ring_element: int satisfies ring ops") {
  static_assert(Ring_element<int>);
  int a = 3, b = 5;
  (void)(a + b);
  (void)(a - a);  // zero
}

TEST_CASE("Ring_element: double satisfies (numeric ring)") {
  static_assert(Ring_element<double>);
}

TEST_CASE("Euclidean_domain: int has quot_rem and gcd in spirit (member form not required for int)") {
  // int doesn't have a.quot_and_rem(b, q, r) member; it uses / and %.
  // So int does NOT model Euclidean_domain as written.
  static_assert(!Euclidean_domain<int>);
}

TEST_CASE("Has_gcd_free: can be used for ADL gcd") {
  // Has_gcd_free only requires gcd(a,b) to be callable; no requirement that int models it
  // unless we actually have a gcd(int,int) in scope. So we don't static_assert here.
}

TEST_CASE("Copyable") {
  static_assert(Copyable<int>);
  static_assert(Copyable<double>);
}

TEST_CASE("Ring_element_with_io: int has stream ops") {
  static_assert(Ring_element_with_io<int>);
}

TEST_CASE("has_get_characteristic_v helper") {
  struct WithChar { int get_characteristic() const { return 2; } };
  struct WithoutChar {};
  static_assert(has_get_characteristic_v<WithChar>);
  static_assert(!has_get_characteristic_v<WithoutChar>);
  static_assert(!has_get_characteristic_v<int>);
}

// ---------------------------------------------------------------------------
// Unified euclidean::quot_and_rem and euclidean::gcd (int + Euclidean_domain)
// ---------------------------------------------------------------------------

template <typename E>
E compute_gcd_then_remainder(E const& a, E const& b, E& q, E& r) {
  E g = spffl::euclidean::gcd(a, b);
  spffl::euclidean::quot_and_rem(a, b, q, r);
  return g;
}

TEST_CASE("unified euclidean: int") {
  int q, r;
  int g = compute_gcd_then_remainder(12, 18, q, r);
  CHECK(g == 6);
  CHECK(q == 0);
  CHECK(r == 12);
  CHECK(12 == 18 * q + r);
}

TEST_CASE("unified euclidean: fp_poly_t") {
  using spffl::polynomials::fp_poly_t;
  const int p = 7;
  fp_poly_t one(spffl::intmath::intmod_t(1, p));
  fp_poly_t x(spffl::intmath::intmod_t(1, p), spffl::intmath::intmod_t(0, p));  // x = 0 + 1*x
  fp_poly_t x2 = x * x;
  fp_poly_t a = x2 + one;   // x^2 + 1
  fp_poly_t b = x + one;    // x + 1

  fp_poly_t q, r;
  fp_poly_t g = compute_gcd_then_remainder(a, b, q, r);
  CHECK(g.find_degree() >= 0);
  CHECK(a.find_degree() == 2);
  fp_poly_t recompose = q * b + r;
  CHECK(recompose == a);
}
