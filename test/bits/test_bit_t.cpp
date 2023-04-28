#include <catch2/catch_test_macros.hpp>

#include "bit_t.h"

using namespace spffl::bits;

TEST_CASE("spffl::bits::bit_t_1") {
  bit_t a(0);
  bit_t b(0);
  bit_t c(1);
  bit_t d(2);
  bit_t e(3);

  CHECK(a == b);
  CHECK(a != c);
  CHECK(a == d);
}

TEST_CASE("spffl::bits::bit_t_2") {
  bit_t z(0);
  bit_t o(1);

  CHECK(z + z == z);
  CHECK(z + o == o);
  CHECK(o + z == o);
  CHECK(o + o == z);

  CHECK(z - z == z);
  CHECK(z - o == o);
  CHECK(o - z == o);
  CHECK(o - o == z);

  CHECK(z * z == z);
  CHECK(z * o == z);
  CHECK(o * z == z);
  CHECK(o * o == o);

  // TODO check exception CHECK(z / z == z);
  // TODO check exception CHECK(o / z == z);
  CHECK(z / o == z);
  CHECK(o / o == o);

  CHECK(z.exp(0) == z);
  CHECK(z.exp(1) == z);
  CHECK(z.exp(2) == z);
  CHECK(o.exp(0) == o);
  CHECK(o.exp(1) == o);
  CHECK(o.exp(2) == o);
}

TEST_CASE("spffl::bits::bit_t_3") {
  bit_t z(0);
  bit_t o(1);

  CHECK(z <= z);
  CHECK(z <= o);
  CHECK(o <= o);
  CHECK(!(o <= z));

  CHECK(!(z < z));
  CHECK(z < o);
  CHECK(!(o < z));
  CHECK(!(o < o));

}

TEST_CASE("spffl::bits::bit_t_4") {
  bit_t z(0);
  bit_t o(1);

  CHECK(z.get_residue() == 0);
  CHECK(o.get_residue() == 1);

}

// TODO: op=
// TODO: from_string
