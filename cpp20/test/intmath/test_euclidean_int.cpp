// Tests for spffl::intmath::quot_and_rem and gcd (int).

#include <catch2/catch_test_macros.hpp>

#include "spffl/intmath/euclidean_int.hpp"

using spffl::intmath::quot_and_rem;
using spffl::intmath::gcd;

TEST_CASE("quot_and_rem(int): basic") {
  int q, r;
  quot_and_rem(17, 5, q, r);
  CHECK(q == 3);
  CHECK(r == 2);
  CHECK(17 == 5 * q + r);

  quot_and_rem(-17, 5, q, r);
  CHECK(q == -3);
  CHECK(r == -2);
  quot_and_rem(17, -5, q, r);
  CHECK(q == -3);
  CHECK(r == 2);
}

TEST_CASE("gcd(int)") {
  CHECK(gcd(12, 18) == 6);
  CHECK(gcd(18, 12) == 6);
  CHECK(gcd(-12, 18) == 6);
  CHECK(gcd(7, 11) == 1);
  CHECK(gcd(0, 5) == 5);
  CHECK(gcd(5, 0) == 5);
}

TEST_CASE("quot_and_rem division by zero throws") {
  int q, r;
  REQUIRE_THROWS_AS(quot_and_rem(1, 0, q, r), std::invalid_argument);
}
