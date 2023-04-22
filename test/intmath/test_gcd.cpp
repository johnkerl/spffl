#include <catch2/catch_test_macros.hpp>

#include "int_gcd.h"

TEST_CASE("spffl::intmath::int_gcd") {
  CHECK(spffl::intmath::int_gcd(1, 1) == 1);
  CHECK(spffl::intmath::int_gcd(2, 1) == 1);
  CHECK(spffl::intmath::int_gcd(2, 2) == 2);
  CHECK(spffl::intmath::int_gcd(4, 8) == 4);
  CHECK(spffl::intmath::int_gcd(4, 6) == 2);
  CHECK(spffl::intmath::int_gcd(1296, 1728) == 432);

  CHECK(spffl::intmath::int_gcd(0, 0) == 0);
  CHECK(spffl::intmath::int_gcd(0, 123) == 123);
  CHECK(spffl::intmath::int_gcd(123, 0) == 123);
}

TEST_CASE("spffl::intmath::int_ext_gcd") {
  int a, b, m, n, g;

  a = 1;
  b = 1;
  g = spffl::intmath::int_ext_gcd(a, b, m, n);
  CHECK(g == 1);
  CHECK(a * m + b * n == g);

  a = 2;
  b = 1;
  g = spffl::intmath::int_ext_gcd(a, b, m, n);
  CHECK(g == 1);
  CHECK(a * m + b * n == g);

  a = 4;
  b = 8;
  g = spffl::intmath::int_ext_gcd(a, b, m, n);
  CHECK(g == 4);
  CHECK(a * m + b * n == g);

  a = 4;
  b = 6;
  g = spffl::intmath::int_ext_gcd(a, b, m, n);
  CHECK(g == 2);
  CHECK(a * m + b * n == g);

  a = 1296;
  b = 1728;
  g = spffl::intmath::int_ext_gcd(a, b, m, n);
  CHECK(g == 432);
  CHECK(a * m + b * n == g);

  // TODO:FIXME
  // CHECK(spffl::intmath::int_ext_gcd(0, 0, m, n) == 0);
  // CHECK(spffl::intmath::int_ext_gcd(0, 123, m, n) == 123);
  // CHECK(spffl::intmath::int_ext_gcd(123, 0, m, n) == 123);
}

TEST_CASE("spffl::intmath::int_lcm") {
  CHECK(spffl::intmath::int_lcm(1, 1) == 1);
  CHECK(spffl::intmath::int_lcm(2, 1) == 2);
  CHECK(spffl::intmath::int_lcm(2, 2) == 2);
  CHECK(spffl::intmath::int_lcm(4, 8) == 8);
  CHECK(spffl::intmath::int_lcm(4, 6) == 12);
  CHECK(spffl::intmath::int_lcm(1296, 1728) == 5184);

  // TODO:FIXME
  // CHECK(spffl::intmath::int_lcm(0, 0) == 0);
  CHECK(spffl::intmath::int_lcm(0, 123) == 0);
  CHECK(spffl::intmath::int_lcm(123, 0) == 0);
}
