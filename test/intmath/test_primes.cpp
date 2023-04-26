#include <catch2/catch_test_macros.hpp>

#include "is_prime.h"

TEST_CASE("spffl::intmath::is_prime") {

  CHECK(spffl::intmath::is_prime(0) == false);
  CHECK(spffl::intmath::is_prime(1) == false);
  CHECK(spffl::intmath::is_prime(2) == true);
  CHECK(spffl::intmath::is_prime(3) == true);
  CHECK(spffl::intmath::is_prime(4) == false);
  CHECK(spffl::intmath::is_prime(5) == true);
  CHECK(spffl::intmath::is_prime(127) == true);
  CHECK(spffl::intmath::is_prime(2047) == false);

  // TODO: specify handling for negative arguments
  // TODO: check handling for numbers >= 2**32
}

TEST_CASE("spffl::intmath::nth_prime") {

  CHECK(spffl::intmath::nth_prime(1) == 2);
  CHECK(spffl::intmath::nth_prime(2) == 3);
  CHECK(spffl::intmath::nth_prime(3) == 5);
  CHECK(spffl::intmath::nth_prime(4) == 7);
  CHECK(spffl::intmath::nth_prime(5) == 11);
  CHECK(spffl::intmath::nth_prime(6) == 13);
  CHECK(spffl::intmath::nth_prime(127) == 709);
  CHECK(spffl::intmath::nth_prime(2047) == 17851);

  // TODO: specify handling for non-positive arguments
}
