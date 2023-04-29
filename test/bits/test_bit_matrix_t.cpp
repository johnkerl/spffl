#include <catch2/catch_test_macros.hpp>

#include "bit_matrix_t.h"

using namespace spffl::bits;

// ----------------------------------------------------------------
TEST_CASE("spffl::bits::bit_matrix_0") {
  bit_matrix_t A(44, 99);
  CHECK(A.get_num_rows() == 44);
  CHECK(A.get_num_cols() == 99);

  bit_matrix_t B(bit_t(1), 44, 99);
  CHECK(B.get_num_rows() == 44);
  CHECK(B.get_num_cols() == 99);

  bit_matrix_t C(55, 55);

  CHECK(A == A);
  CHECK(B == B);
  CHECK(A != B);
  // Check exception -- or have it not abend
  // CHECK(A != C);

  CHECK(A == bit_t(0));
  CHECK(B == bit_t(1));
  CHECK(C == bit_t(0));

  CHECK(A.is_zero());
  CHECK(!B.is_zero());
  CHECK(C.is_zero());

  CHECK(!A.is_square());
  CHECK(!B.is_square());
  CHECK(C.is_square());

  bit_matrix_t T = A.transpose();
  CHECK(T.get_num_rows() == 99);
  CHECK(T.get_num_cols() == 44);

  bit_matrix_t Z;
  CHECK(Z.get_num_rows() == 0);
  CHECK(Z.get_num_cols() == 0);

  // TODO: check exception on non-square
  // bit_matrix_t I = A.make_I();

  bit_matrix_t I = C.make_I();
  for (int i = 0; i < 55; i++) {
    for (int j = 0; j < 55; j++) {
      CHECK(I[i].get(j) == bit_t(i == j));
    }
  }

  CHECK(!A.is_I());
  CHECK(!B.is_I());
  CHECK(!C.is_I());
  CHECK(I.is_I());

  A = bit_t(1);
  CHECK(A.get_num_rows() == 44);
  CHECK(A.get_num_cols() == 99);
  CHECK(!A.is_zero());

  A = bit_t(0);
  CHECK(A.get_num_rows() == 44);
  CHECK(A.get_num_cols() == 99);
  CHECK(A.is_zero());
}

// TODO:
//  bool load_from_file(char *file_name);

// TODO:
//  friend std::ostream &operator<<(std::ostream &os, const bit_matrix_t &m);
//  friend std::istream &operator>>(std::istream &is, bit_matrix_t &m);

//  bit_vector_t &operator[](int row_index);
//  bit_matrix_t operator+(const bit_matrix_t that) const;
//  bit_matrix_t operator-(const bit_matrix_t that) const;
//  bit_matrix_t operator-(void) const;
//  bit_matrix_t operator+(bit_t e) const;
//  bit_matrix_t operator-(bit_t e) const;
//  bit_vector_t operator*(bit_vector_t v) const;
//  bit_matrix_t operator*(const bit_matrix_t &that);

//  // Return value is 1 for success, 0 for failure (i.e. non-positive
//  // exponent of a singular matrix).
//  int exp(int power, bit_matrix_t &rout);

// TODO:
//  bit_matrix_t &operator+=(bit_matrix_t that);
//  bit_matrix_t &operator-=(bit_matrix_t that);
//  bit_matrix_t &operator+=(bit_t e);
//  bit_matrix_t &operator-=(bit_t e);
//  bit_matrix_t &operator*=(bit_matrix_t that);

//  void row_reduce_below_with_scalar(bit_t &s);
//  void row_reduce_below(void);
//  void row_echelon_form(void);
//
//  // This method makes a copy of the matrix and row-reduces it.  To save
//  // CPU cycles, use get_rank_rr() if the matrix is already row-reduced.
//  int get_rank(void);
//
//  // This method assumes the matrix is already row-reduced.  If not,
//  // use get_rank() instead.
//  int get_rank_rr(void);
//
//  bool get_kernel_basis(bit_matrix_t &rbas);
//  void check_kernel_basis(bit_matrix_t &kerbas);
//  bit_matrix_t paste(bit_matrix_t &that);
//
//  void split(bit_matrix_t &rleft, bit_matrix_t &rright, int split_column);
//
//  bool inverse(bit_matrix_t &rinv);
//  void check_inverse(bit_matrix_t &rinv);
//  bit_t det(void);
