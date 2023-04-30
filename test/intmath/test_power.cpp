#include <catch2/catch_test_macros.hpp>

#include "intmath/int_power.h"

TEST_CASE("spffl::intmath::int_power") {
  CHECK(spffl::intmath::int_power(1, 0) == 1);
  // TODO:FIXME
  // CHECK(spffl::intmath::int_power(0, 1) == 1);
  CHECK(spffl::intmath::int_power(2, 3) == 8);
  CHECK(spffl::intmath::int_power(7, 5) == 16807);

  // TODO: specify handling for negative exponents
}
