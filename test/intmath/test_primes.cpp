#include <catch2/catch_test_macros.hpp>

#include "isprime.h"

TEST_CASE("isprime") {

  CHECK(isprime(0) == 0);
  CHECK(isprime(1) == 0);
  CHECK(isprime(2) == 1);
  CHECK(isprime(3) == 1);
  CHECK(isprime(4) == 0);
  CHECK(isprime(5) == 1);
  CHECK(isprime(127) == 1);
  CHECK(isprime(2047) == 0);

  // TODO: specify handling for negative arguments
  // TODO: check handling for numbers >= 2**32
}

TEST_CASE("nthprime") {

  CHECK(nthprime(1) == 2);
  CHECK(nthprime(2) == 3);
  CHECK(nthprime(3) == 5);
  CHECK(nthprime(4) == 7);
  CHECK(nthprime(5) == 11);
  CHECK(nthprime(6) == 13);
  CHECK(nthprime(127) == 709);
  CHECK(nthprime(2047) == 17851);

  // TODO: specify handling for non-positive arguments
}
