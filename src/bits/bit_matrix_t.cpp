// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl_exception.h"
#include "bit_matrix_t.h"
#include "line_scan.h"
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
namespace spffl::bits {

// ----------------------------------------------------------------
bit_matrix_t::bit_matrix_t(int init_num_rows, int init_num_cols) {
  if ((init_num_rows <= 0) || (init_num_cols <= 0)) {
    std::stringstream ss;
    ss << "bit_matrix_t::bit_matrix_t():  Matrix dimensions "
              << "must be >= 0; got " << init_num_rows << " x " << init_num_cols
              << ".  Exiting." << std::endl;
    throw spffl::exception_t(ss.str());
  }

  this->num_rows = init_num_rows;
  this->num_cols = init_num_cols;
  this->rows     = new bit_vector_t[init_num_rows];
  for (int i = 0; i < init_num_rows; i++) {
    this->rows[i] = bit_vector_t(init_num_cols);
  }
}

// ----------------------------------------------------------------
bit_matrix_t::bit_matrix_t(bit_t e, int init_num_rows, int init_num_cols) {
  if ((init_num_rows <= 0) || (init_num_cols <= 0)) {
    std::stringstream ss;
    ss << "bit_matrix_t::bit_matrix_t():  Matrix dimensions "
              << "must be > 0; got " << init_num_rows << " x " << init_num_cols
              << ".  Exiting." << std::endl;
    throw spffl::exception_t(ss.str());
  }
  this->num_rows = init_num_rows;
  this->num_cols = init_num_cols;
  this->rows     = new bit_vector_t[init_num_rows];
  for (int i = 0; i < init_num_rows; i++) {
    this->rows[i] = bit_vector_t(e, init_num_cols);
  }
}

// ----------------------------------------------------------------
bit_matrix_t::bit_matrix_t(int e, int init_num_rows, int init_num_cols) {
  if ((init_num_rows <= 0) || (init_num_cols <= 0)) {
    std::stringstream ss;
    ss << "bit_matrix_t::bit_matrix_t():  Matrix dimensions "
              << "must be > 0; got " << init_num_rows << " x " << init_num_cols
              << ".  Exiting." << std::endl;
    exit(1);
  }
  this->num_rows = init_num_rows;
  this->num_cols = init_num_cols;
  this->rows     = new bit_vector_t[init_num_rows];
  for (int i = 0; i < init_num_rows; i++) {
    this->rows[i] = bit_vector_t(e, init_num_cols);
  }
}
// ----------------------------------------------------------------
bit_matrix_t::bit_matrix_t(void) { this->nullify(); }

// ----------------------------------------------------------------
bit_matrix_t::bit_matrix_t(const bit_matrix_t &that) {
  int i;

  this->num_rows = that.num_rows;
  this->num_cols = that.num_cols;
  this->rows     = new bit_vector_t[that.num_rows];
  for (i = 0; i < that.num_rows; i++) {
    this->rows[i] = that.rows[i];
  }
}

// ----------------------------------------------------------------
bit_matrix_t::~bit_matrix_t(void) { this->mfree(); }

// ----------------------------------------------------------------
bool bit_matrix_t::load_from_file(char *file_name) {
  if ((strcmp(file_name, "-") == 0) || (strcmp(file_name, "@") == 0)) {
    std::cin >> *this;
    if (std::cin.fail()) {
      return false;
    } else {
      return true;
    }
  }

  std::ifstream ifs;
  ifs.open(file_name, std::ifstream::in);

  if (ifs.fail()) {
    std::stringstream ss;
    ss << "bit_matrix_t::load_from_file:  couldn't open \"" << file_name
              << "\"\n";
    return false;
  }

  ifs >> *this;

  if (ifs.fail()) {
    std::stringstream ss;
    ss << "bit_matrix_t::load_from_file:  scan failure "
                 "reading \""
              << file_name << "\"\n";
    ifs.close();
    return false;
  }
  ifs.close();
  return true;
}

// ----------------------------------------------------------------
bit_matrix_t &bit_matrix_t::operator=(const bit_t &scalar) {
  if (this->rows) {
    for (int i = 0; i < this->num_rows; i++) {
      for (int j = 0; j < this->num_cols; j++) {
        this->rows[i].set(j, scalar);
      }
    }
  } else {
    this->num_rows = 1;
    this->num_cols = 1;
    this->rows     = new bit_vector_t[1];
    this->rows[0]  = bit_vector_t(1);
    this->rows[0].set(0, scalar);
  }
  return *this;
}

// ----------------------------------------------------------------
bit_matrix_t &bit_matrix_t::operator=(const bit_matrix_t &that) {
  int i;

  if ((this->num_rows == that.num_rows) && (this->num_cols == that.num_cols)) {
    // Storage is fine as is.
  } else {
    this->mfree();
    this->num_rows = that.num_rows;
    this->num_cols = that.num_cols;
    this->rows     = new bit_vector_t[that.num_rows];
    for (i = 0; i < that.num_rows; i++) {
      this->rows[i] = bit_vector_t(that.num_cols);
    }
  }

  for (i = 0; i < that.num_rows; i++) {
    this->rows[i] = that.rows[i];
  }
  return *this;
}

// ----------------------------------------------------------------
bool bit_matrix_t::operator==(const bit_matrix_t &that) const {
  this->check_dims(that, "operator==");
  for (int i = 0; i < this->num_rows; i++) {
    if (this->rows[i] != that.rows[i]) {
      return false;
    }
  }
  return true;
}

// ----------------------------------------------------------------
bool bit_matrix_t::operator==(const bit_t &e) const {
  for (int i = 0; i < this->num_rows; i++) {
    if (this->rows[i] != e) {
      return false;
    }
  }
  return true;
}

// ----------------------------------------------------------------
bool bit_matrix_t::operator!=(const bit_matrix_t &that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool bit_matrix_t::operator!=(const bit_t &e) const { return !(*this == e); }

// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const bit_matrix_t &m) {
  for (int i = 0; i < m.num_rows; i++) {
    os << m.rows[i] << std::endl;
  }
  return os;
}

// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, bit_matrix_t &m) {
  char line[8192];
  const int init_num_rows = 40;
  const int more_num_rows = 40;
  int alloc_num_rows      = init_num_rows;
  m.rows                  = new bit_vector_t[init_num_rows];

  while (1) {
    if (is.eof()) {
      break;
    }

    if (m.num_rows >= alloc_num_rows) {
      alloc_num_rows += more_num_rows;
      bit_vector_t *ptemp = new bit_vector_t[alloc_num_rows];
      for (int i = 0; i < m.num_rows; i++) {
        ptemp[i] = m.rows[i];
      }
      delete[] m.rows;
      m.rows = ptemp;
    }

    // Read a line of text.
    is.getline(line, sizeof(line));
    if (is.eof()) {
      is.clear();
      break;
    } else if (is.fail()) {
      break;
    }

    // Allow comments.
    char *phash = strstr(line, "#");
    if (phash) {
      *phash = 0;
    }

    // Allow multiple matrices in the same stream, delimited by
    // carriage returns.
    if (spffl::base::is_whitespace_line(line)) {
      if (m.num_rows == 0) {
        continue;
      } else {
        break;
      }
    }

    // Use bit_vector_t istringstream >> to scan the line of text
    // as a row vector.
    std::istringstream iss(line, std::ios_base::in);
    iss >> m.rows[m.num_rows];
    if (iss.fail()) {
      is.setstate(std::ios::failbit);
      std::stringstream ss;
      ss << "bit_matrix_t scan failure: \"" << line << "\"\n";
      return is;
    }

    m.num_rows++;
  }

  if (is.peek() == EOF) {
    is.setstate(std::ios::eofbit);
  }

  if (m.num_rows == 0) {
    is.setstate(std::ios::badbit);
    std::stringstream ss;
    ss << "bit_matrix_t >>:  zero-row matrix.\n";
    return is;
  }

  int min_cols = 0x7fffffff;
  int max_cols = 0;
  for (int i = 0; i < m.num_rows; i++) {
    int cur_cols = m.rows[i].get_num_elements();
    if (cur_cols > max_cols) {
      max_cols = cur_cols;
    }
    if (cur_cols < min_cols) {
      min_cols = cur_cols;
    }
  }
  if (min_cols != max_cols) {
    is.setstate(std::ios::badbit);
    std::stringstream ss;
    ss << "bit_matrix_t >>:  ragged input.  # rows = " << m.num_rows
              << " min # cols = " << min_cols << " max # cols = " << max_cols
              << ".\n";
    return is;
  }
  m.num_cols = max_cols;

  return is;
}

// ----------------------------------------------------------------
bit_vector_t &bit_matrix_t::operator[](int row_index) {
  if ((row_index < 0) || (row_index >= this->num_rows)) {
    std::stringstream ss;
    ss << "bit_matrix_t array operator: row index " << row_index
              << " out of bounds " << 0 << ":" << (this->num_rows - 1)
              << std::endl;
    exit(1);
  }
  return this->rows[row_index];
}

// ----------------------------------------------------------------
bit_matrix_t bit_matrix_t::operator+(const bit_matrix_t &that) const {
  this->check_dims(that, "operator+");
  bit_matrix_t rv(this->num_rows, this->num_cols);
  for (int i = 0; i < this->num_rows; i++) {
    rv[i] = this->rows[i] + that.rows[i];
  }
  return rv;
}

// ----------------------------------------------------------------
bit_matrix_t bit_matrix_t::operator-(const bit_matrix_t &that) const {
  if ((this->num_rows != that.num_rows) || (this->num_cols != that.num_cols)) {
    std::stringstream ss;
    ss << "bit_matrix_t operator-():  Incompatibly sized "
              << "arguments (" << this->num_rows << "x" << this->num_cols
              << ", " << that.num_rows << "x" << that.num_cols << ")."
              << std::endl;
    exit(1);
  }

  bit_matrix_t rv(this->num_rows, this->num_cols);
  for (int i = 0; i < this->num_rows; i++) {
    rv[i] = this->rows[i] - that.rows[i];
  }
  return rv;
}

// ----------------------------------------------------------------
bit_matrix_t bit_matrix_t::operator-(void) const {
  return *this; // Characteristic 2.
}

// ----------------------------------------------------------------
bit_matrix_t bit_matrix_t::operator+(const bit_t &e) const {
  if (!this->is_square()) {
    std::stringstream ss;
    ss << "bit_matrix_t plus scalar:  non-square input.\n";
    exit(1);
  }
  bit_matrix_t rv(*this);
  if (e == bit_t(1)) {
    for (int i = 0; i < this->num_rows; i++) {
      rv[i].toggle_element(i);
    }
  }
  return rv;
}

// ----------------------------------------------------------------
bit_matrix_t bit_matrix_t::operator-(const bit_t &e) const {
  if (!this->is_square()) {
    std::stringstream ss;
    ss << "bit_matrix_t minus scalar:  non-square input.\n";
    exit(1);
  }
  bit_matrix_t rv(*this);
  if (e == bit_t(1)) {
    for (int i = 0; i < this->num_rows; i++) {
      rv[i].toggle_element(i);
    }
  }
  return rv;
}

// ----------------------------------------------------------------
bit_vector_t bit_matrix_t::operator*(const bit_vector_t &v) const {
  int i, j;
  int v_num_elements = v.get_num_elements();

  if (this->num_cols != v_num_elements) {
    std::stringstream ss;
    ss << "bit_matrix_t operator*(): Incompatibly dimensioned "
              << "operands (" << this->num_rows << "x" << this->num_cols << ","
              << v_num_elements << ")." << std::endl;
    exit(1);
  }

  bit_t zero(0);
  bit_vector_t rv(zero, this->num_rows);
  for (i = 0; i < this->num_rows; i++) {
    for (j = 0; j < this->num_cols; j++) {
      rv.set(i, rv.get(i) + this->rows[i].get(j) * v.get(j));
    }
  }

  return rv;
}

// ----------------------------------------------------------------
// This is a private auxiliary function for the exp() method.

bit_matrix_t bit_matrix_t::posexp(int power, bit_matrix_t &I) const {
  bit_matrix_t a2(*this);
  bit_matrix_t apower = I;

  while (power != 0) { // Repeated squaring.
    if (power & 1) {
      apower *= a2;
    }
    power = (uint64_t)power >> 1;
    a2 *= a2;
  }
  return apower;
}

// ----------------------------------------------------------------
// * power >=  1:  repeated squaring
// * power ==  0:
// * power <= -1:  if singular, ret 0.  else invert & posexp the inverse.

int bit_matrix_t::exp(int power, bit_matrix_t &rout) const {
  if (!this->is_square()) {
    std::stringstream ss;
    ss << "bit_matrix_t::exp():  non-square input.\n";
    exit(1);
  }

  bit_matrix_t I = this->make_I();
  if (power >= 1) {
    rout = this->posexp(power, I);
    return 1;
  } else {
    bit_matrix_t ai;
    if (!this->inverse(ai)) {
      return 0;
    } else if (power == 0) {
      rout = I;
      return 1;
    } else if (power == -power) {
      std::stringstream ss;
      ss << "bit_matrix_t::exp:  can't handle "
                << "MIN_INT.\n";
      exit(1);
    } else {
      rout = ai.posexp(-power, I);
      return 1;
    }
  }
}

// ----------------------------------------------------------------
bit_matrix_t bit_matrix_t::operator*(const bit_matrix_t &that) const {
  int i, j;

  if (this->num_cols != that.num_rows) {
    std::stringstream ss;
    ss << "bit_matrix_t operator*(): Incompatibly "
              << "dimensioned operands (" << this->num_rows << "x"
              << this->num_cols << "," << that.num_rows << "x" << that.num_cols
              << ")." << std::endl;
    exit(1);
  }

  bit_t zero(0);
  bit_t one(1);
  bit_matrix_t rv(zero, this->num_rows, that.num_cols);
  bit_matrix_t thatt = that.transpose();

  for (i = 0; i < this->num_rows; i++) {
    for (j = 0; j < thatt.num_rows; j++) {
      bit_t dot = this->rows[i].dot(thatt.rows[j]);
      if (dot == one) {
        rv[i].set(j, 1);
      }
    }
  }
  return rv;
}

// ----------------------------------------------------------------
bit_matrix_t &bit_matrix_t::operator+=(const bit_matrix_t &that) {
  *this = *this + that;
  return *this;
}

bit_matrix_t &bit_matrix_t::operator-=(const bit_matrix_t &that) {
  *this = *this - that;
  return *this;
}

bit_matrix_t &bit_matrix_t::operator+=(const bit_t &e) {
  *this = *this + e;
  return *this;
}

bit_matrix_t &bit_matrix_t::operator-=(const bit_t &e) {
  *this = *this - e;
  return *this;
}

bit_matrix_t &bit_matrix_t::operator*=(const bit_matrix_t &that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
// This is a static method.
bit_matrix_t bit_matrix_t::outer(const bit_vector_t &u, const bit_vector_t &v) {
  int m = u.get_num_elements();
  int n = v.get_num_elements();
  bit_matrix_t rv;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      rv[i].set(j, u.get(i) * v.get(j));
    }
  }
  return rv;
}

// ----------------------------------------------------------------
bit_matrix_t bit_matrix_t::transpose(void) const {
  bit_matrix_t rv(this->num_cols, this->num_rows);
  for (int i = 0; i < this->num_rows; i++) {
    for (int j = 0; j < this->num_cols; j++) {
      rv.rows[j].set(i, this->rows[i].get(j));
    }
  }
  return rv;
}

// ----------------------------------------------------------------
// Makes an identity matrix with the same dimensions as *this has.

bit_matrix_t bit_matrix_t::make_I(void) const {
  if (!this->is_square()) {
    std::stringstream ss;
    ss << "bit_matrix_t::make_I():  non-square input.\n";
    exit(1);
  }

  bit_matrix_t rv(*this);
  for (int i = 0; i < this->num_rows; i++) {
    for (int j = 0; j < this->num_cols; j++) {
      if (i == j) {
        rv.rows[i].set(j, 1);
      } else {
        rv.rows[i].set(j, 0);
      }
    }
  }
  return rv;
}

// ----------------------------------------------------------------
bool bit_matrix_t::is_zero(void) const {
  for (int i = 0; i < this->num_rows; i++) {
    if (!this->rows[i].is_zero()) {
      return false;
    }
  }
  return true;
}

// ----------------------------------------------------------------
bool bit_matrix_t::is_square(void) const {
  if (this->num_rows == this->num_cols) {
    return true;
  } else {
    return false;
  }
}

// ----------------------------------------------------------------
bool bit_matrix_t::is_I(void) const {
  int i, j;

  if (!this->is_square()) {
    return false;
  }

  for (i = 0; i < this->num_rows; i++) {
    if (this->rows[i].get(i) != 1) {
      return false;
    }
  }
  for (i = 0; i < this->num_rows; i++) {
    for (j = 0; j < i; j++) {
      if (this->rows[i].get(j) != 0) {
        return false;
      }
    }
    for (j = i + 1; j < this->num_cols; j++) {
      if (this->rows[i].get(j) != 0) {
        return false;
      }
    }
  }
  return true;
}

// ----------------------------------------------------------------
uint64_t **bit_matrix_t::expose(void) const {
  uint64_t **ptrs = new uint64_t *[this->num_rows];
  for (int i = 0; i < this->num_rows; i++) {
    ptrs[i] = this->rows[i].expose();
  }
  return ptrs;
}

// ----------------------------------------------------------------
void bit_matrix_t::swap(int arow, int brow) {
  this->rows[arow].ptrswap(this->rows[brow]);
}

// ----------------------------------------------------------------
// This is a general row-reduction method.  It operates on the matrix in-place.
//
// The "scalar" argument is used for computation of the determinant.
// When the determinant is not desired, this scalar is tracked anyway; the
// overhead is minimal.  Let A and B be the input and output, respectively.
// The scalar s is such that det(A) = s det(B).
//
// The determinant is the unique n-linear alternating form such that det(I) = 1.
// This means (letting u, v, w be row vectors of a sample 3x3 matrix):
//
// * det(u,v,w)     = - det(v,u,w)                (alternating)
// * det(au,v,w)    = a det(u,v,w)                (n-linear)
// * det(u+v,v,w)   =   det(u,v,w) + det(v,v,w)   (n-linear)
//
// From this definition, the following results apply:
//
// * det(0,v,w)     =   det(0 u,v,w) = 0 det(u,v,w) = 0
//   (Zero row => zero determinant).
//
// * det(v,v,w)     =   det(v,v,w)
//   det(v,v,w)     = - det(v,v,w) (row swap)
//   (Duplicate row => zero determinant).
//
// The following operations occur during row-reduction:
//
// * Swap rows.
//   A = (u,v,w)                det(A) = d
//   B = (v,u,w)     s = -1 . s det(B) = d
//
// * Divide by leading elements.
//   A = ( u ,v,w)              det(A) = d
//   B = (u/a,v,w)   s = a  . s det(B) = a * (1/a) * d = d
//
// * Replace u with au+bv.
//   A = (  u ,v,w)             det(A) = d
//   B = (au+bv,v,w) s = 1/a. s det(B) = (1/a)*(a det(au,v,w) + b det(v,v,w))=d

void bit_matrix_t::row_reduce_below_with_scalar(bit_t &s) {
  int top_row, left_column, row;
  uint64_t **ptrs = this->expose();
  uint64_t *temp;

  s = 1;
  for (top_row = 0, left_column = 0;
       (top_row < this->num_rows) && (left_column < this->num_cols);
      /* increment in loop body */) {
    // Find the nearest row with a non-zero value in this column;
    // exchange that row with this one.  If this is the last row,
    // there are no rows below to pivot into place, so don't
    // bother.
    if (top_row < this->num_rows - 1) {
      int pivot_row        = top_row;
      int pivot_successful = 0;
      while (!pivot_successful && (pivot_row < this->num_rows)) {
        // if (this->rows[pivot_row].get_bit(left_column) != 0) {
        if (GET_BIT(ptrs[pivot_row], left_column)) {
          if (top_row != pivot_row) {
            this->swap(top_row, pivot_row);
            temp            = ptrs[top_row];
            ptrs[top_row]   = ptrs[pivot_row];
            ptrs[pivot_row] = temp;
          }
          pivot_successful = 1;
        } else {
          pivot_row++;
        }
      }
      if (!pivot_successful) {
        left_column++;
        continue; // Work on the next column.
      }
    }

    // We can have a zero leading element in this row if it's
    // the last row and full of zeroes.
    // int top_row_lead = this->rows[top_row].get_bit(left_column);
    int top_row_lead = GET_BIT(ptrs[top_row], left_column);
    if (top_row_lead != 0) {

      // Clear this column.
      for (row = top_row + 1; row < this->num_rows; row++) {
        // int current_row_lead = this->rows[row].get_bit(left_column);
        int current_row_lead = GET_BIT(ptrs[row], left_column);
        if (current_row_lead) {
          this->rows[row].accum_row(this->rows[top_row]);
        }
      }
    }
    left_column++;
    top_row++;
  }
}

// ----------------------------------------------------------------
// Operates on the matrix in-place.

void bit_matrix_t::row_reduce_below(void) {
  bit_t ignored;
  this->row_reduce_below_with_scalar(ignored);
}

// ----------------------------------------------------------------
// Operates on the matrix in-place.

void bit_matrix_t::row_echelon_form(void) {
  this->row_reduce_below();

  int row, row2, row2_leader_pos;
  bit_t row_leader_val, row2_leader_val, mul;

  for (row = 0; row < this->num_rows; row++) {
    for (row2 = row + 1; row2 < this->num_rows; row2++) {
      if (!this->rows[row2].find_leader_pos(row2_leader_pos)) {
        break;
      }
      row2_leader_val = this->rows[row2].get(row2_leader_pos);
      row_leader_val  = this->rows[row].get(row2_leader_pos);
      if (row_leader_val == 0) {
        continue;
      }

      mul = row_leader_val / row2_leader_val;
      this->rows[row] -= this->rows[row2] * mul;
    }
  }
}

// ----------------------------------------------------------------
// This method makes a copy of the matrix and row-reduces it.  To save
// CPU cycles, use get_rank_rr() if the matrix is already row-reduced.
int bit_matrix_t::get_rank(void) const {
  bit_matrix_t rr(*this);
  rr.row_reduce_below();
  return rr.get_rank_rr();
}

// This method assumes the matrix is already row-reduced.  If not,
// use get_rank() instead.
int bit_matrix_t::get_rank_rr(void) const {
  int rank = 0;
  for (int i = 0; i < this->num_rows; i++) {
    if (this->rows[i].is_zero()) {
      break;
    } else {
      rank++;
    }
  }
  return rank;
}

// ----------------------------------------------------------------
bool bit_matrix_t::get_kernel_basis(bit_matrix_t &rbas) const {
  int i, j;
  bit_matrix_t rr(*this);
  rr.row_echelon_form();
  int rank   = rr.get_rank_rr();
  int dimker = rr.num_cols - rank;
  if (dimker == 0) {
    return false;
  }

  bit_matrix_t basis(bit_t(0), dimker, rr.num_cols);

  unsigned char *free_flags = new unsigned char[this->num_cols];
  int *free_indices         = new int[this->num_cols];
  int nfree                 = 0; // == dimker but I'll compute it anyway
  int dep_pos;

  for (i = 0; i < this->num_cols; i++) {
    free_flags[i] = 1;
  }

  for (i = 0; i < rank; i++) {
    if (rr.rows[i].find_leader_pos(dep_pos)) {
      free_flags[dep_pos] = 0;
    }
  }

  for (i = 0; i < this->num_cols; i++) {
    if (free_flags[i]) {
      free_indices[nfree++] = i;
    }
  }

  // For each free coefficient:
  //   Let that free coefficient be 1 and the rest be zero.
  //   Also set any dependent coefficients which depend on that
  //   free coefficient.
  for (i = 0; i < dimker; i++) {
    basis.rows[i].set(free_indices[i], 1);

    // Matrix in row echelon form:
    //
    // 0210     c0 = ??      c0 = 1  c0 = 0
    // 1000     c1 = -2 c2   c1 = 0  c1 = 5
    // 0000     c2 = ??      c2 = 0  c2 = 1
    // 0000     c3 = 0       c3 = 0  c3 = 0

    // j  = 0,1
    // fi = 0,2

    // i = 0:
    //   j = 0  row 0 fi 0 = row 0 c0 = 0
    //   j = 1  row 1 fi 0 = row 1 c0 = 0
    // i = 1:
    //   j = 0  row 0 fi 1 = row 0 c2 = 2 dep_pos = 1
    //   j = 1  row 1 fi 1 = row 1 c2 = 0

    // 0001
    // 01?0

    for (j = 0; j < rank; j++) {
      if (rr.rows[j].get(free_indices[i]) == 0) {
        continue;
      }

      (void)rr.rows[j].find_leader_pos(dep_pos);
      basis.rows[i].set(dep_pos, rr.rows[j].get(free_indices[i]));
    }
  }

  delete[] free_flags;
  delete[] free_indices;

  rbas = basis;
  return true;
}

// ----------------------------------------------------------------
void bit_matrix_t::check_kernel_basis(bit_matrix_t &kerbas) const {
  bit_t zero(0);
  int i;
  int dimker = kerbas.num_rows;

  for (i = 0; i < dimker; i++) {
    bit_vector_t Av = *this * kerbas.rows[i];
    if (Av != zero) {
      std::stringstream ss;
      ss << "Coding error in kernel basis.\n";
      ss << "Matrix =\n";
      ss << *this;
      ss << "Vector =\n";
      ss << kerbas.rows[i] << "\n";
      ss << "Product =\n";
      ss << Av << "\n";
      ss << "Zero scalar = " << zero << "\n";
      exit(1);
    }
  }
}

// ----------------------------------------------------------------
bit_matrix_t bit_matrix_t::paste(bit_matrix_t &that) const {
  if (this->num_rows != that.num_rows) {
    std::stringstream ss;
    ss << "bit_matrix_t::paste:  differing number of rows ("
              << this->num_rows << " vs. " << that.num_rows << ")\n";
    exit(1);
  }

  bit_matrix_t rv(this->num_rows, this->num_cols + that.num_cols);
  int i, j;

  for (i = 0; i < this->num_rows; i++) {
    rv.rows[i] = this->rows[i];
  }
  for (i = 0; i < this->num_rows; i++) {
    for (j = 0; j < that.num_cols; j++) {
      rv.rows[i].set(this->num_rows + j, that.rows[i].get(j));
    }
  }

  return rv;
}

// ----------------------------------------------------------------
void bit_matrix_t::split(
    bit_matrix_t &rleft, bit_matrix_t &rright, int split_column) const {
  if ((split_column < 0) || (split_column >= this->num_cols)) {
    std::stringstream ss;
    ss << "bit_matrix_t::split:  split column " << split_column
              << " out of bounds 0:" << this->num_rows - 1 << ".\n";
    exit(1);
  }

  rleft  = bit_matrix_t(this->num_rows, split_column);
  rright = bit_matrix_t(this->num_rows, this->num_cols - split_column);

  int i, j;

  for (i = 0; i < this->num_rows; i++) {
    for (j = 0; j < split_column; j++) {
      rleft.rows[i].set(j, this->rows[i].get(j));
    }
  }

  for (i = 0; i < this->num_rows; i++) {
    for (j = split_column; j < this->num_cols; j++) {
      rright.rows[i].set(j - split_column, this->rows[i].get(j));
    }
  }
}

// ----------------------------------------------------------------
bool bit_matrix_t::inverse(bit_matrix_t &rinv) const {
  if (!this->is_square()) {
    std::stringstream ss;
    ss << "bit_matrix_t::inverse():  non-square input.\n";
    exit(1);
  }

  bit_matrix_t I    = this->make_I();
  bit_matrix_t pair = this->paste(I);
  pair.row_echelon_form();

  pair.split(I, rinv, this->num_cols);
  return I.is_I();
}

// ----------------------------------------------------------------
void bit_matrix_t::check_inverse(bit_matrix_t &rinv) const {
  bit_matrix_t AB = *this * rinv;
  bit_matrix_t BA = rinv * *this;
  if (!AB.is_I() || !BA.is_I()) {
    std::stringstream ss;
    ss << "coding error:  not really inverses.\n";
    exit(1);
  }
}

// ----------------------------------------------------------------
bit_t bit_matrix_t::det(void) const {
  if (!this->is_square()) {
    std::stringstream ss;
    ss << "bit_matrix_t::det():  non-square input.\n";
    exit(1);
  }
  bit_matrix_t rr(*this);
  bit_t d(1);
  rr.row_reduce_below_with_scalar(d);
  for (int i = 0; i < this->num_rows; i++) {
    if (rr.rows[i].get(i) == 0) {
      d = 0;
      break;
    }
  }
  return d;
}

// ----------------------------------------------------------------
int bit_matrix_t::get_num_rows(void) const { return this->num_rows; }

// ----------------------------------------------------------------
int bit_matrix_t::get_num_cols(void) const { return this->num_cols; }

// ----------------------------------------------------------------
void bit_matrix_t::mfree(void) {
  if (this->rows != 0) {
    delete[] this->rows;
  }
  this->nullify();
}

// ----------------------------------------------------------------
void bit_matrix_t::nullify(void) {
  this->rows     = 0;
  this->num_rows = 0;
  this->num_cols = 0;
}

// ----------------------------------------------------------------
void bit_matrix_t::check_dims(
    const bit_matrix_t that, const std::string &msg) const {
  if ((this->num_rows != that.num_rows) || (this->num_cols != that.num_cols)) {
    std::stringstream ss;
    ss << "bit_matrix_t " << msg << ":  Incompatibly sized arguments ("
              << this->num_rows << "x" << this->num_cols << ", "
              << that.num_rows << "x" << that.num_cols << ")." << std::endl;
    exit(1);
  }
}

} // namespace spffl::bits
