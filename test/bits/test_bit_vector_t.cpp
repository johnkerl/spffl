#include <catch2/catch_test_macros.hpp>

#include "bit_vector_t.h"

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
//  friend std::istringstream &operator>>(std::istringstream &is, bit_vector_t &v);
//  void sqzout(std::ostream &os);
//  void crout(std::ostream &os);

//  bit_t get(int index) {
//    if ((index < 0) || (index >= this->num_bits))
//      this->bounds_check(index);
//    return bit_t(GET_BIT(this->words, index));
//  }
//
//  void set(int index, bit_t value) {
//    if ((index < 0) || (index >= this->num_bits))
//      this->bounds_check(index);
//    if (value.get_residue())
//      SET_BIT(this->words, index);
//    else
//      CLEAR_BIT(this->words, index);
//  }
//
//  void set(int index, int value) {
//    if ((index < 0) || (index >= this->num_bits))
//      this->bounds_check(index);
//    if (value & 1)
//      SET_BIT(this->words, index);
//    else
//      CLEAR_BIT(this->words, index);
//  }
//
//  void toggle_element(int index);

//  bit_vector_t operator+(bit_vector_t that);
//  bit_vector_t operator-(bit_vector_t that);
//  bit_vector_t operator*(bit_t s);
//
//  // This is componentwise multiplication (u * v), useful for
//  // implementing direct products of rings.
//  //
//  // Use dot() (e.g. u.dot(v)) for inner product, or bit_matrix_t's
//  // outer() (e.g.  bit_matrix_t::outer(u, v)) for outer product.
//  bit_vector_t operator*(bit_vector_t that);
//  bit_t dot(bit_vector_t that);
//
//  // Componentwise division.
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

//  // Warning:  trusts the caller to remain in bounds!
//  int get_bit(int index) { return GET_BIT(this->words, index); }
//
//  void accum_row(bit_vector_t &that);
//  int get_num_elements(void);
//  bool find_leader_pos(int &rpos);
