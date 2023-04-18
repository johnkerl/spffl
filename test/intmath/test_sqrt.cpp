#include <catch2/catch_test_macros.hpp>

#include "int_sqrt.h"
#include "intfc.h"

TEST_CASE("int_sqrt") {

    CHECK(int_sqrt(0, IFLOOR) == 0);
    CHECK(int_sqrt(1, IFLOOR) == 1);
    CHECK(int_sqrt(2, IFLOOR) == 1);
    CHECK(int_sqrt(3, IFLOOR) == 1);
    CHECK(int_sqrt(4, IFLOOR) == 2);
    CHECK(int_sqrt(5, IFLOOR) == 2);
    CHECK(int_sqrt(1048575, IFLOOR) == 1023);
    CHECK(int_sqrt(1048576, IFLOOR) == 1024);
    CHECK(int_sqrt(1048577, IFLOOR) == 1024);

    CHECK(int_sqrt(0, ICEIL) == 0);
    CHECK(int_sqrt(1, ICEIL) == 1);
    CHECK(int_sqrt(2, ICEIL) == 2);
    CHECK(int_sqrt(3, ICEIL) == 2);
    CHECK(int_sqrt(4, ICEIL) == 2);
    CHECK(int_sqrt(5, ICEIL) == 3);
    CHECK(int_sqrt(1048575, ICEIL) == 1024);
    CHECK(int_sqrt(1048576, ICEIL) == 1024);
    CHECK(int_sqrt(1048577, ICEIL) == 1025);

    // TODO: specify handling for negative arguments
}
