// Tests for cpp20 intmod_t (header-only version).

#include <catch2/catch_test_macros.hpp>

#include "spffl/intmath/intmod_t.h"

using spffl::intmath::intmod_t;

TEST_CASE("intmod_t: basic ring operations") {
  intmod_t a(3, 7);
  intmod_t b(5, 7);

  CHECK((a + b).get_residue() == 1); // 3+5=8 ≡ 1 mod 7
  CHECK((a - b).get_residue() == 5); // 3-5=-2 ≡ 5 mod 7
  CHECK((a * b).get_residue() == 1); // 3*5=15 ≡ 1 mod 7
}

TEST_CASE("intmod_t: inverse and division") {
  intmod_t a(3, 7);
  intmod_t inv(0, 7);

  REQUIRE(a.recip(inv));
  CHECK((a * inv).get_residue() == 1);

  intmod_t one_over_a = intmod_t(1, 7) / a;
  CHECK((one_over_a * a).get_residue() == 1);
}

TEST_CASE("intmod_t: negative residue normalizes to 0..modulus-1") {
  intmod_t a(-1, 7);
  CHECK(a.get_residue() == 6); // -1 ≡ 6 (mod 7)
}
