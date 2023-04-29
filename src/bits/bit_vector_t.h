// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef BIT_VECTOR_T_H
#define BIT_VECTOR_T_H

#include "bit_t.h"
#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>

namespace spffl::bits {

const uint64_t BITS_PER_WORD = 64;
const uint64_t BITS_SHIFT    = 6;
const uint64_t WORD_MASK     = BITS_PER_WORD - 1;
const uint64_t UONE          = 1;

static inline uint64_t WORD_INDEX_FROM_BIT_INDEX(uint64_t bi) {
  return bi >> BITS_SHIFT;
}

static inline uint64_t WORD_POS_FROM_BIT_INDEX(uint64_t bi) {
  return 63 - (bi & WORD_MASK);
}

static uint64_t GET_BIT(uint64_t *wordptr, uint64_t bi) {
  return (wordptr[WORD_INDEX_FROM_BIT_INDEX(bi)] >>
          WORD_POS_FROM_BIT_INDEX(bi)) &
         UONE;
}

static void SET_BIT(uint64_t *wordptr, uint64_t bi) {
  wordptr[WORD_INDEX_FROM_BIT_INDEX(bi)] |=
      (UONE << WORD_POS_FROM_BIT_INDEX(bi));
}

static void CLEAR_BIT(uint64_t *wordptr, uint64_t bi) {
  wordptr[WORD_INDEX_FROM_BIT_INDEX(bi)] &=
      ~(UONE << WORD_POS_FROM_BIT_INDEX(bi));
}

static void TOGGLE_BIT(uint64_t *wordptr, uint64_t bi) {
  wordptr[WORD_INDEX_FROM_BIT_INDEX(bi)] ^=
      (UONE << WORD_POS_FROM_BIT_INDEX(bi));
}

static uint64_t NWORDS_FROM_NBITS(uint64_t nb) {
  return ((nb) + BITS_PER_WORD - UONE) >> BITS_SHIFT;
}

class bit_vector_t {
public:
  bit_vector_t(void);
  bit_vector_t(int init_num_elements);
  bit_vector_t(bit_t scalar, int init_num_elements);
  bit_vector_t(int scalar, int init_num_elements);
  bit_vector_t(const bit_vector_t &that);
  ~bit_vector_t(void);

  bit_vector_t &operator=(bit_vector_t that);
  bit_vector_t &operator=(const bit_t scalar);

  // I/O format:  all elements on one line, delimited by whitespace.
  friend std::ostream &operator<<(std::ostream &os, const bit_vector_t &v);

  friend std::istream &operator>>(std::istream &is, bit_vector_t &v);

  friend std::istringstream &operator>>(std::istringstream &is,
                                        bit_vector_t &v);

  // No spaces between elements.  (Instead, perhaps I could implement a
  // derived iomanip, and then just use ostream <<.)
  void sqzout(std::ostream &os);

  // Carriage return between elements.
  void crout(std::ostream &os);

  bit_t get(int index) const {
    if ((index < 0) || (index >= this->num_bits)) {
      this->bounds_check(index);
    }
    return bit_t(GET_BIT(this->words, index));
  }

  int get_int(int index) const {
    if ((index < 0) || (index >= this->num_bits)) {
      this->bounds_check(index);
    }
    return GET_BIT(this->words, index);
  }

  void set(int index, bit_t value) {
    if ((index < 0) || (index >= this->num_bits)) {
      this->bounds_check(index);
    }

    if (value.get_residue()) {
      SET_BIT(this->words, index);
    } else {
      CLEAR_BIT(this->words, index);
    }
  }

  void set(int index, int value) {
    if ((index < 0) || (index >= this->num_bits)) {
      this->bounds_check(index);
    }
    if (value & 1) {
      SET_BIT(this->words, index);
    } else {
      CLEAR_BIT(this->words, index);
    }
  }

  void toggle_element(int index);
  bool is_zero(void) const;

  bit_vector_t operator+(bit_vector_t that);
  bit_vector_t operator-(bit_vector_t that);
  bit_vector_t operator*(bit_t s);

  // This is componentwise multiplication (u * v), useful for
  // implementing direct products of rings.
  //
  // Use dot() (e.g. u.dot(v)) for inner product, or bit_matrix_t's
  // outer() (e.g.  bit_matrix_t::outer(u, v)) for outer product.
  bit_vector_t operator*(bit_vector_t that);
  bit_t dot(bit_vector_t that);

  // Componentwise division.
  bit_vector_t operator/(bit_vector_t that);
  bit_vector_t operator+=(bit_vector_t that);
  bit_vector_t operator-=(bit_vector_t that);
  bit_vector_t operator*=(bit_t scalar);
  bit_vector_t operator*=(bit_vector_t that);

  bool operator==(const bit_vector_t &that) const;
  bool operator!=(const bit_vector_t &that) const;
  bool operator==(const bit_t &scalar) const;
  bool operator!=(const bit_t &scalar) const;

  // Warning:  trusts the caller to remain in bounds!
  int get_bit(int index) { return GET_BIT(this->words, index); }

  void accum_row(bit_vector_t &that);
  int get_num_elements(void) const;
  void ptrswap(bit_vector_t &that);
  bool find_leader_pos(int &rpos);

  uint64_t *expose() { return this->words; }

  // ----------------------------------------------------------------
private:
  uint64_t *words;
  int num_words;
  int num_bits;

  // Return value:  True/false.  rpos:  index, if found.
  void check_equal_lengths(bit_vector_t &that);
  void bounds_check(int index) const;
  void trim(void);
};

} // namespace spffl::bits

#endif // BIT_VECTOR_T_H
