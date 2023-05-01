#include <catch2/catch_test_macros.hpp>

#include "spffl/bits/count_bits.h"

TEST_CASE("spffl::bits::line_scan::tokenize_0") {
  unsigned char c[4] = {0x00, 0xff, 0x0a, 0x10};

  CHECK(spffl::bits::count_one_bits(&c[0], 0) == 0);

  CHECK(spffl::bits::count_one_bits(&c[0], 1) == 0);
  CHECK(spffl::bits::count_one_bits(&c[1], 1) == 8);
  CHECK(spffl::bits::count_one_bits(&c[2], 1) == 2);
  CHECK(spffl::bits::count_one_bits(&c[3], 1) == 1);

  CHECK(spffl::bits::count_one_bits(&c[0], 2) == 8);
  CHECK(spffl::bits::count_one_bits(&c[1], 2) == 10);
  CHECK(spffl::bits::count_one_bits(&c[2], 2) == 3);

  CHECK(spffl::bits::count_one_bits(&c[0], 3) == 10);
  CHECK(spffl::bits::count_one_bits(&c[1], 3) == 11);

  CHECK(spffl::bits::count_one_bits(&c[0], 4) == 11);
}
