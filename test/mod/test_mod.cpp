#include <catch2/catch_test_macros.hpp>

#include "spffl/mod/foo.h"

TEST_CASE("spffl::mod::foo") {
  CHECK(foo(2, 3) == 5);
}
