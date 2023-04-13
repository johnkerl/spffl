#include <catch2/catch_test_macros.hpp>

#include "log10.h"
#include "intfc.h"

TEST_CASE("calc_log10_unsigned") {
    CHECK(calc_log10_unsigned(0, IFLOOR) == 0);
    CHECK(calc_log10_unsigned(1, IFLOOR) == 0);
    CHECK(calc_log10_unsigned(2, IFLOOR) == 0);
    CHECK(calc_log10_unsigned(3, IFLOOR) == 0);
    CHECK(calc_log10_unsigned(4, IFLOOR) == 0);
    CHECK(calc_log10_unsigned(5, IFLOOR) == 0);

    CHECK(calc_log10_unsigned(9,  IFLOOR) == 0);
    CHECK(calc_log10_unsigned(10, IFLOOR) == 1);
    CHECK(calc_log10_unsigned(11, IFLOOR) == 1);

    CHECK(calc_log10_unsigned(99,  IFLOOR) == 1);
    CHECK(calc_log10_unsigned(100, IFLOOR) == 2);
    CHECK(calc_log10_unsigned(101, IFLOOR) == 2);

    CHECK(calc_log10_unsigned(999,  IFLOOR) == 2);
    CHECK(calc_log10_unsigned(1000, IFLOOR) == 3);
    CHECK(calc_log10_unsigned(1001, IFLOOR) == 3);

    // TODO: test log10 with ICEIL once that's implemented
}
