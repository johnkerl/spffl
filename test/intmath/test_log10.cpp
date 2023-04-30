#include <catch2/catch_test_macros.hpp>

#include "intmath/log10.h"

TEST_CASE("calc_log10_unsigned") {
  CHECK(spffl::intmath::calc_log10_unsigned_floor(0) == 0);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(1) == 0);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(2) == 0);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(3) == 0);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(4) == 0);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(5) == 0);

  CHECK(spffl::intmath::calc_log10_unsigned_floor(9) == 0);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(10) == 1);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(11) == 1);

  CHECK(spffl::intmath::calc_log10_unsigned_floor(99) == 1);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(100) == 2);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(101) == 2);

  CHECK(spffl::intmath::calc_log10_unsigned_floor(999) == 2);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(1000) == 3);
  CHECK(spffl::intmath::calc_log10_unsigned_floor(1001) == 3);

  // TODO: test log10 with ICEIL once that's implemented
}
