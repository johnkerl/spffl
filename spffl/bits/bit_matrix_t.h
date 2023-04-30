// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef BIT_MATRIX_T_H
#define BIT_MATRIX_T_H

#include "bits/bit_vector_t.h"
#include <cstdint>
#include <iostream>
namespace spffl::bits {

class bit_matrix_t {
public:
  bit_matrix_t(int init_num_rows, int init_num_cols);
  bit_matrix_t(bit_t e, int init_num_rows, int init_num_cols);
  bit_matrix_t(int e, int init_num_rows, int init_num_cols);
  bit_matrix_t(void);
  bit_matrix_t(const bit_matrix_t &that);
  ~bit_matrix_t(void);

  bool load_from_file(char *file_name);

  bit_matrix_t &operator=(const bit_t &scalar);
  bit_matrix_t &operator=(const bit_matrix_t &that);
  bool operator==(const bit_matrix_t &that) const;
  bool operator==(const bit_t &e) const;
  bool operator!=(const bit_matrix_t &that) const;
  bool operator!=(const bit_t &e) const;

  friend std::ostream &operator<<(std::ostream &os, const bit_matrix_t &m);

  friend std::istream &operator>>(std::istream &is, bit_matrix_t &m);

  // For this class, since bits aren't individually addressable, please
  // use A[i].set(j, x) and x = A[i].get(j) in place of A[i][j].
  bit_vector_t &operator[](int row_index);
  bit_matrix_t operator+(const bit_matrix_t &that) const;
  bit_matrix_t operator-(const bit_matrix_t &that) const;
  bit_matrix_t operator-(void) const;
  bit_matrix_t operator+(const bit_t &e) const;
  bit_matrix_t operator-(const bit_t &e) const;
  bit_vector_t operator*(const bit_vector_t &v) const;
  bit_matrix_t operator*(const bit_matrix_t &that) const;

  // Return value is 1 for success, 0 for failure (i.e. non-positive
  // exponent of a singular matrix).
  int exp(int power, bit_matrix_t &rout) const;

  bit_matrix_t &operator+=(const bit_matrix_t &that);
  bit_matrix_t &operator-=(const bit_matrix_t &that);
  bit_matrix_t &operator+=(const bit_t &e);
  bit_matrix_t &operator-=(const bit_t &e);
  bit_matrix_t &operator*=(const bit_matrix_t &that);

  static bit_matrix_t outer(const bit_vector_t &u, const bit_vector_t &v);
  bit_matrix_t transpose(void) const;

  // Makes an identity matrix with the same dimensions as *this has.
  bit_matrix_t make_I(void) const;
  bool is_zero(void) const;
  bool is_square(void) const;
  bool is_I(void) const;
  uint64_t **expose(void) const;
  void swap(int arow, int brow);

  // This is a general row-reduction method.  It operates on the matrix
  // in-place.
  //
  // The "scalar" argument is used for computation of the determinant.
  // When the determinant is not desired, this scalar is tracked anyway;
  // the overhead is minimal.  Let A and B be the input and output,
  // respectively.  The scalar s is such that det(A) = s det(B).
  void row_reduce_below_with_scalar(bit_t &s);

  // Operates on the matrix in-place.
  void row_reduce_below(void);

  // Operates on the matrix in-place.
  void row_echelon_form(void);

  // This method makes a copy of the matrix and row-reduces it.  To save
  // CPU cycles, use get_rank_rr() if the matrix is already row-reduced.
  int get_rank(void) const;

  // This method assumes the matrix is already row-reduced.  If not,
  // use get_rank() instead.
  int get_rank_rr(void) const;

  bool get_kernel_basis(bit_matrix_t &rbas) const;
  void check_kernel_basis(bit_matrix_t &kerbas) const;
  bit_matrix_t paste(bit_matrix_t &that) const;

  void split(bit_matrix_t &rleft, bit_matrix_t &rright, int split_column) const;

  bool inverse(bit_matrix_t &rinv) const;
  void check_inverse(bit_matrix_t &rinv) const;
  bit_t det(void) const;
  int get_num_rows(void) const;
  int get_num_cols(void) const;

  // ----------------------------------------------------------------
private:
  bit_vector_t *rows;
  int num_rows;
  int num_cols;

  void mfree(void);
  void nullify(void);
  void check_dims(const bit_matrix_t that, const std::string &msg) const;

  // This is a private auxiliary function for the exp() method.
  bit_matrix_t posexp(int power, bit_matrix_t &I) const;
};

} // namespace spffl::bits

#endif // BIT_MATRIX_T_H
