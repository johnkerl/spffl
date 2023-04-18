#include <catch2/catch_test_macros.hpp>

#include "int_power.h"

TEST_CASE("int_power") {
    CHECK(int_power(1, 0) == 1);
    // TODO:FIXME
    // CHECK(int_power(0, 1) == 1);
    CHECK(int_power(2, 3) == 8);
    CHECK(int_power(7, 5) == 16807);

    // TODO: specify handling for negative exponents
}
