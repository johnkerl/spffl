// Compile and sanity-check spffl/concepts.hpp

#include <catch2/catch_test_macros.hpp>

#include "spffl/concepts.hpp"

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
