#include <catch2/catch_test_macros.hpp>

#include "intmath/int_sqrt.h"

TEST_CASE("spffl::intmath::int_sqrt") {

  CHECK(spffl::intmath::int_sqrt_floor(0) == 0);
  CHECK(spffl::intmath::int_sqrt_floor(1) == 1);
  CHECK(spffl::intmath::int_sqrt_floor(2) == 1);
  CHECK(spffl::intmath::int_sqrt_floor(3) == 1);
  CHECK(spffl::intmath::int_sqrt_floor(4) == 2);
  CHECK(spffl::intmath::int_sqrt_floor(5) == 2);
  CHECK(spffl::intmath::int_sqrt_floor(1048575) == 1023);
  CHECK(spffl::intmath::int_sqrt_floor(1048576) == 1024);
  CHECK(spffl::intmath::int_sqrt_floor(1048577) == 1024);

  CHECK(spffl::intmath::int_sqrt_ceil(0) == 0);
  CHECK(spffl::intmath::int_sqrt_ceil(1) == 1);
  CHECK(spffl::intmath::int_sqrt_ceil(2) == 2);
  CHECK(spffl::intmath::int_sqrt_ceil(3) == 2);
  CHECK(spffl::intmath::int_sqrt_ceil(4) == 2);
  CHECK(spffl::intmath::int_sqrt_ceil(5) == 3);
  CHECK(spffl::intmath::int_sqrt_ceil(1048575) == 1024);
  CHECK(spffl::intmath::int_sqrt_ceil(1048576) == 1024);
  CHECK(spffl::intmath::int_sqrt_ceil(1048577) == 1025);

  // TODO: specify handling for negative arguments
}
