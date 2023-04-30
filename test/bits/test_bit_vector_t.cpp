#include <catch2/catch_test_macros.hpp>

#include "bits/bit_vector_t.h"

using namespace spffl::bits;

TEST_CASE("spffl::bits::bit_vector_0") {
  bit_vector_t v;
  CHECK(v.get_num_elements() == 0);
  CHECK(v.is_zero());
}

TEST_CASE("spffl::bits::bit_vector_1") {
  bit_vector_t v(100);
  CHECK(v.get_num_elements() == 100);
  CHECK(v.is_zero());
}

TEST_CASE("spffl::bits::bit_vector_2") {
  bit_vector_t v(bit_t(0), 100);
  CHECK(v.get_num_elements() == 100);
  CHECK(v.is_zero());

  bit_vector_t w(bit_t(1), 100);
  CHECK(w.get_num_elements() == 100);
  CHECK(!w.is_zero());
}

TEST_CASE("spffl::bits::bit_vector_3") {
  bit_vector_t a(bit_t(0), 100);
  bit_vector_t b(bit_t(0), 100);
  bit_vector_t c(bit_t(1), 100);
  bit_vector_t d(bit_t(1), 100);
  CHECK(a == b);
  CHECK(c == d);
  CHECK(a != c);
  CHECK(b != d);
}

// TODO: test:
//  friend std::ostream &operator<<(std::ostream &os, const bit_vector_t &v);
//  friend std::istream &operator>>(std::istream &is, bit_vector_t &v);
//  friend std::istringstream &operator>>(std::istringstream &is, bit_vector_t
//  &v); void sqzout(std::ostream &os); void crout(std::ostream &os);

TEST_CASE("spffl::bits::bit_vector_10") {
  bit_vector_t v(100);
  v.set(43, 1);
  v.set(44, 0);
  v.set(97, 1);

  for (int i = 0; i < 100; i++) {
    if (i == 43 || i == 97) {
      CHECK(v.get(i) == 1);
    } else {
      CHECK(v.get(i) == 0);
    }
  }

  v.toggle_element(55);

  for (int i = 0; i < 100; i++) {
    if (i == 43 || i == 97 || i == 55) {
      CHECK(v.get(i) == 1);
    } else {
      CHECK(v.get(i) == 0);
    }
  }
}

TEST_CASE("spffl::bits::bit_vector_11") {
  bit_vector_t u(100);
  bit_vector_t v(100);

  u.set(43, 1);
  u.set(97, 1);

  v.set(0, 1);
  v.set(43, 1);
  v.set(96, 1);

  bit_vector_t w = u + v;

  for (int i = 0; i < 100; i++) {
    if (i == 0 || i == 96 || i == 97) {
      CHECK(w.get(i) == 1);
    } else {
      CHECK(w.get(i) == 0);
    }
  }

  w = u - v;

  for (int i = 0; i < 100; i++) {
    if (i == 0 || i == 96 || i == 97) {
      CHECK(w.get(i) == 1);
    } else {
      CHECK(w.get(i) == 0);
    }
  }

  w = u * v;

  for (int i = 0; i < 100; i++) {
    if (i == 43) {
      CHECK(w.get(i) == 1);
    } else {
      CHECK(w.get(i) == 0);
    }
  }

  w = u * bit_t(1);

  CHECK(w == u);

  w = u * bit_t(0);

  for (int i = 0; i < 100; i++) {
    CHECK(w.get(i) == 0);
  }

  bit_t b = u.dot(v);
  CHECK(b == 1);
}

// TODO:
//  bit_vector_t operator/(bit_vector_t that);
//  bit_vector_t operator+=(bit_vector_t that);
//  bit_vector_t operator-=(bit_vector_t that);
//  bit_vector_t operator*=(bit_t scalar);
//  bit_vector_t operator*=(bit_vector_t that);
//
//  bool operator==(bit_vector_t &that);
//  bool operator!=(bit_vector_t &that);
//  bool operator==(bit_t scalar);
//  bool operator!=(bit_t scalar);

//  void accum_row(bit_vector_t &that);

TEST_CASE("spffl::bits::bit_vector_20") {
  bit_vector_t z(100);
  bit_vector_t u(100);

  u.set(43, 1);
  u.set(97, 1);

  int rpos = 999;
  CHECK(z.find_leader_pos(rpos) == false);
  CHECK(u.find_leader_pos(rpos) == true);
  CHECK(rpos == 43);
}
