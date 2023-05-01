#include <catch2/catch_test_macros.hpp>

#include "spffl/intmath/int_totient.h"

TEST_CASE("spffl::intmath::int_totient") {
  CHECK(spffl::intmath::int_totient(0) == 0);
  CHECK(spffl::intmath::int_totient(1) == 0);
  CHECK(spffl::intmath::int_totient(2) == 1);
  CHECK(spffl::intmath::int_totient(3) == 2);
  CHECK(spffl::intmath::int_totient(4) == 2);
  CHECK(spffl::intmath::int_totient(5) == 4);
  CHECK(spffl::intmath::int_totient(6) == 2);
  CHECK(spffl::intmath::int_totient(7) == 6);
  CHECK(spffl::intmath::int_totient(8) == 4);
  CHECK(spffl::intmath::int_totient(9) == 6);
  CHECK(spffl::intmath::int_totient(10) == 4);

  CHECK(spffl::intmath::int_totient(1728) == 576);
  CHECK(spffl::intmath::int_totient(1729) == 1296);

  // TODO: specify handling for negative arguments
}
