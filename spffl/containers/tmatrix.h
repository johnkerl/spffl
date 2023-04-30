// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef TMATRIX_H
#define TMATRIX_H

#include "base/line_scan.h"
#include "base/spffl_exception.h"
#include "base/tokenize.h"
#include "intmath/int_gcd.h"
#include "containers/tvector.h"
#include <iostream>
#include <stdlib.h>
#include <string.h>

template <typename element_type> class tmatrix;

template <typename element_type>
static std::ostream &operator<<(
    std::ostream &os, const tmatrix<element_type> &);

template <typename element_type>
static std::istream &operator>>(std::istream &is, tmatrix<element_type> &);

// ================================================================
template <typename element_type> class tmatrix {
public:
  // ================================================================
  // Constructors

  // ----------------------------------------------------------------
  tmatrix(int init_num_rows, int init_num_cols) {
    if ((init_num_rows <= 0) || (init_num_cols <= 0)) {
      std::stringstream ss;
      ss << "tmatrix::tmatrix():  Matrix dimensions must be >= 0; got "
         << init_num_rows << " x " << init_num_cols << ".  Exiting."
         << std::endl;
      throw spffl::exception_t(ss.str());
    }

    this->num_rows = init_num_rows;
    this->num_cols = init_num_cols;
    this->rows     = new tvector<element_type>[init_num_rows];
    for (int i = 0; i < init_num_rows; i++) {
      this->rows[i] = tvector<element_type>(init_num_cols);
    }
  }

  // ----------------------------------------------------------------
  tmatrix(element_type e, int init_num_rows, int init_num_cols) {
    if ((init_num_rows <= 0) || (init_num_cols <= 0)) {
      std::stringstream ss;
      ss << "tmatrix::tmatrix():  Matrix dimensions "
         << "must be > 0; got " << init_num_rows << " x " << init_num_cols
         << ".  Exiting." << std::endl;
      throw spffl::exception_t(ss.str());
    }
    this->num_rows = init_num_rows;
    this->num_cols = init_num_cols;
    this->rows     = new tvector<element_type>[init_num_rows];
    for (int i = 0; i < init_num_rows; i++) {
      this->rows[i] = tvector<element_type>(e, init_num_cols);
    }
  }

  // ----------------------------------------------------------------
  tmatrix(void) { this->nullify(); }

  // ----------------------------------------------------------------
  tmatrix(const tmatrix<element_type> &that) {
    this->num_rows = that.num_rows;
    this->num_cols = that.num_cols;
    this->rows     = new tvector<element_type>[that.num_rows];
    for (int i = 0; i < that.num_rows; i++) {
      this->rows[i] = that.rows[i];
    }
  }

  // ----------------------------------------------------------------
  ~tmatrix(void) { this->mfree(); }

  // ----------------------------------------------------------------
  // Makes sure the (newly scanned-in) matrix isn't ragged.  If it is ragged,
  // zero is returned.  If it is not, one is returned and this->num_cols is set.
  // this->num_rows must be set, and rows must be populated.

  bool check_ragged(void) {
    int min_cols = 0x7fffffff;
    int max_cols = 0;
    for (int i = 0; i < this->num_rows; i++) {
      int cur_cols = this->rows[i].get_num_elements();
      if (cur_cols > max_cols) {
        max_cols = cur_cols;
      }
      if (cur_cols < min_cols) {
        min_cols = cur_cols;
      }
    }
    if (min_cols != max_cols) {
      std::stringstream ss;
      ss << "tmatrix:  ragged input.  # rows = " << this->num_rows
         << " min # cols = " << min_cols << " max # cols = " << max_cols
         << ".\n";
      return false;
    }
    this->num_cols = max_cols;
    return true;
  }

  // ----------------------------------------------------------------
  // The matrix must already contain at least one element.  See the comment
  // above the istream operator.
  bool load_from_file(char *file_name) {
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
      ss << "tmatrix::load_from_file:  couldn't open \"" << file_name << "\"\n";
      return false;
    }

    ifs >> *this;

    if (ifs.fail()) {
      std::stringstream ss;
      ss << "tmatrix::load_from_file:  scan failure reading \"" << file_name
         << "\"\n";
      ifs.close();
      return false;
    }
    ifs.close();
    return true;
  }

  // ----------------------------------------------------------------
  // For this method, the matrix may have the default constructor.
  // The "zero" argument is used to set the modulus for parameterized types.
  bool load_from_file(char *file_name, element_type zero) {
    this->mfree();

    this->num_rows   = 1;
    this->num_cols   = 1;
    this->rows       = new tvector<element_type>[1];
    this->rows[0]    = tvector<element_type>(1);
    this->rows[0][0] = zero;

    return this->load_from_file(file_name);
  }

  // ----------------------------------------------------------------
  // The matrix must already contain at least one element.  See the comment
  // above the istream operator.  The istream input operator expects rows
  // delimited by carriage returns, with each row consisting of elements
  // delimited by whitespace:  for example,
  //
  //   1 2 3
  //   3 4 5
  //   7 2 9
  //
  // The bracket_in() method, by contrast, expects whitespace-delimited
  // elements, surrounded by brackets:  for example,
  //
  //   [[1 2 3] [3 4 5] [7 2 9]]
  //
  // Special case: input of the form
  //
  //   [2 3 4]
  //
  // is treated as an n x 1 matrix (column vector).

  bool bracket_in(char *string) {
    // Make sure the matrix already contains an element.  Remember it,
    // then free the old matrix contents.
    if (!this->rows || (this->num_rows < 1) || (this->num_cols < 1)) {
      std::stringstream ss;
      ss << "tmatrix::bracket_in:  must already have one element.\n";
      return false;
    }
    element_type zero = this->rows[0][0] - this->rows[0][0];
    this->mfree();

    char *copy       = strdup(string);
    char *pouterleft = strchr(copy, '[');
    if (pouterleft == 0) {
      std::stringstream ss;
      ss << "tmatrix::bracket_in:  couldn't find leading left bracket.\n";
      free(copy);
      return false;
    }
    char *pinnerstart = pouterleft + 1;
    while ((*pinnerstart == ' ') || (*pinnerstart == '\t')) {
      pinnerstart++;
    }

    char *pouterright = strrchr(pouterleft, ']');
    if (pouterright == 0) {
      std::stringstream ss;
      ss << "tmatrix::bracket_in:  couldn't find trailing right bracket.\n";
      free(copy);
      return false;
    }
    *pouterright = 0;

    if (strchr(pinnerstart, '[')) {
      // There are nested brackets.
      this->num_rows = spffl::base::count_tokens(pinnerstart, "[");
      this->rows     = new tvector<element_type>[this->num_rows];
      char **stringv = new char *[this->num_rows];
      (void)spffl::base::tokenize(pinnerstart, "[", stringv, this->num_rows);

      for (int i = 0; i < this->num_rows; i++) {
        char *rowcopy = new char[strlen(stringv[i]) + 2];
        strcpy(rowcopy, "[");
        strcat(rowcopy, stringv[i]);
        this->rows[i] = zero;
        if (!this->rows[i].bracket_in(rowcopy)) {
          std::stringstream ss;
          ss << "tmatrix::bracket_in:  couldn't read row " << i << ".\n";
          delete[] rowcopy;
          delete[] stringv;
          free(copy);
          return false;
        }
        delete[] rowcopy;
      }

      // Sets this->num_cols.
      if (!this->check_ragged()) {
        // Error message already printed out.
        delete[] stringv;
        free(copy);
        return false;
      }
      delete[] stringv;
    } else {
      // There are no nested brackets; scan as column vector.
      tvector<element_type> column(zero, 1);
      tvector<element_type> temp(zero, 1);
      std::istringstream iss(pinnerstart, std::ios_base::in);
      iss >> column;
      if (iss.fail()) {
        free(copy);
        return false;
      }

      this->num_rows = column.get_num_elements();
      this->num_cols = 1;

      // Non-void ctor to array new now violates ANSI standard.
      // this->rows = new tvector<element_type>[this->num_rows](zero, 1);
      // for (int i = 0; i < this->num_rows; i++)
      // this->rows[i][0] = column[i];
      this->rows = new tvector<element_type>[this->num_rows];
      for (int i = 0; i < this->num_rows; i++) {
        this->rows[i] = temp;
      }
      for (int i = 0; i < this->num_rows; i++) {
        this->rows[i][0] = column[i];
      }
    }

    free(copy);
    return true;
  }

  // ----------------------------------------------------------------
  bool store_to_file(char *file_name) const {
    if ((strcmp(file_name, "-") == 0) || (strcmp(file_name, "@") == 0)) {
      std::cout << *this;
      return true;
    }

    std::ofstream ofs;
    ofs.open(file_name, std::ofstream::out);

    if (ofs.fail()) {
      std::stringstream ss;
      ss << "tmatrix::store_to_file:  couldn't open \"" << file_name << "\"\n";
      return false;
    }

    ofs << *this;

    if (ofs.fail()) {
      std::stringstream ss;
      ss << "tmatrix::store_to_file:  couldn't write \"" << file_name << "\"\n";
      ofs.close();
      return false;
    }
    ofs.close();
    return true;
  }

  // ----------------------------------------------------------------
  void store_to_file_or_die(char *file_name) const {
    if (!this->store_to_file(file_name)) {
      std::stringstream ss;
      ss << "tmatrix:  couldn't write to \"" << file_name << "\".\n";
      throw spffl::exception_t(ss.str());
    }
  }

  // ================================================================
  // Operators

  // ----------------------------------------------------------------
  tmatrix<element_type> &operator=(const element_type &scalar) {
    if (this->rows) {
      for (int i = 0; i < this->num_rows; i++) {
        for (int j = 0; j < this->num_cols; j++) {
          this->rows[i][j] = scalar;
        }
      }
    } else {
      this->num_rows   = 1;
      this->num_cols   = 1;
      this->rows       = new tvector<element_type>[1];
      this->rows[0]    = tvector<element_type>(1);
      this->rows[0][0] = scalar;
    }
    return *this;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> &operator=(const tmatrix<element_type> &that) {
    int i;

    if ((this->num_rows == that.num_rows) &&
        (this->num_cols == that.num_cols)) {
      // Storage is fine as is.
    } else {
      this->mfree();
      this->num_rows = that.num_rows;
      this->num_cols = that.num_cols;
      this->rows     = new tvector<element_type>[that.num_rows];
      for (i = 0; i < that.num_rows; i++) {
        this->rows[i] = tvector<element_type>(that.num_cols);
      }
    }

    for (i = 0; i < that.num_rows; i++) {
      this->rows[i] = that.rows[i];
    }
    return *this;
  }

  // ----------------------------------------------------------------
  bool operator==(const tmatrix<element_type> &that) const {
    this->check_dims(that, "operator==");
    for (int i = 0; i < this->num_rows; i++) {
      if (this->rows[i] != that.rows[i]) {
        return false;
      }
    }
    return true;
  }

  // ----------------------------------------------------------------
  bool operator==(const element_type &e) const {
    for (int i = 0; i < this->num_rows; i++) {
      if (this->rows[i] != e) {
        return false;
      }
    }
    return true;
  }

  // ----------------------------------------------------------------
  bool operator!=(const tmatrix<element_type> &that) const {
    return !(*this == that);
  }

  // ----------------------------------------------------------------
  bool operator!=(const element_type &e) const { return !(*this == e); }

  // ----------------------------------------------------------------
  tvector<element_type> &operator[](int row_index) const {
    if ((row_index < 0) || (row_index >= this->num_rows)) {
      std::stringstream ss;
      ss << "tmatrix array operator: row index " << row_index
         << " out of bounds " << 0 << ":" << (this->num_rows - 1) << std::endl;
      throw spffl::exception_t(ss.str());
    }
    return this->rows[row_index];
  }

  // ----------------------------------------------------------------
  // Returns a *copy* of the column, *not* a reference to it.
  tvector<element_type> get_column(int col_index) const {
    if ((col_index < 0) || (col_index >= this->num_cols)) {
      std::stringstream ss;
      ss << "tmatrix get_column: col index " << col_index << " out of bounds "
         << 0 << ":" << (this->num_cols - 1) << std::endl;
      throw spffl::exception_t(ss.str());
    }
    tvector<element_type> rv(this->num_rows);
    for (int i = 0; i < this->num_rows; i++) {
      rv[i] = this->rows[i][col_index];
    }
    return rv;
  }

  // ----------------------------------------------------------------
  void put_column(int col_index, tvector<element_type> &v) {
    if ((col_index < 0) || (col_index >= this->num_cols)) {
      std::stringstream ss;
      ss << "tmatrix put_column: col index " << col_index << " out of bounds "
         << 0 << ":" << (this->num_cols - 1) << std::endl;
      throw spffl::exception_t(ss.str());
    }
    if (v.get_num_elements() != this->num_rows) {
      std::stringstream ss;
      ss << "tmatrix::put_column:  matrix is " << this->num_rows << " x "
         << this->num_cols << ", but the vector has height "
         << v.get_num_elements() << ".\n";
      throw spffl::exception_t(ss.str());
    }
    for (int i = 0; i < this->num_rows; i++) {
      this->rows[i][col_index] = v[i];
    }
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> operator+(const tmatrix<element_type> &that) const {
    this->check_dims(that, "operator+");
    tmatrix<element_type> rv(this->num_rows, this->num_cols);
    for (int i = 0; i < this->num_rows; i++) {
      for (int j = 0; j < this->num_cols; j++) {
        rv[i][j] = this->rows[i][j] + that.rows[i][j];
      }
    }
    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> operator-(const tmatrix<element_type> &that) const {
    if ((this->num_rows != that.num_rows) ||
        (this->num_cols != that.num_cols)) {
      std::stringstream ss;
      ss << "tmatrix operator-():  Incompatibly sized "
         << "arguments (" << this->num_rows << "x" << this->num_cols << ", "
         << that.num_rows << "x" << that.num_cols << ")." << std::endl;
      throw spffl::exception_t(ss.str());
    }

    tmatrix<element_type> rv(this->num_rows, this->num_cols);
    for (int i = 0; i < this->num_rows; i++) {
      for (int j = 0; j < this->num_cols; j++) {
        rv[i][j] = this->rows[i][j] - that.rows[i][j];
      }
    }
    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> operator-(void) const {
    tmatrix<element_type> rv(this->num_rows, this->num_cols);
    for (int i = 0; i < this->num_rows; i++) {
      for (int j = 0; j < this->num_cols; j++) {
        rv[i][j] = -this->rows[i][j];
      }
    }
    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> operator+(const element_type &e) const {
    if (!this->is_square()) {
      std::stringstream ss;
      ss << "tmatrix plus scalar:  non-square input.\n";
      throw spffl::exception_t(ss.str());
    }
    tmatrix<element_type> rv(*this);
    for (int i = 0; i < this->num_rows; i++) {
      rv[i][i] += e;
    }
    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> operator-(const element_type &e) const {
    if (!this->is_square()) {
      std::stringstream ss;
      ss << "tmatrix minus scalar:  non-square input.\n";
      throw spffl::exception_t(ss.str());
    }
    tmatrix<element_type> rv(*this);
    for (int i = 0; i < this->num_rows; i++) {
      rv[i][i] -= e;
    }
    return rv;
  }

  // ----------------------------------------------------------------
  // Matrix times (column) vector.

  tvector<element_type> operator*(const tvector<element_type> &v) const {
    int i, j;
    int v_num_elements = v.get_num_elements();

    if (this->num_cols != v_num_elements) {
      std::stringstream ss;
      ss << "tmatrix operator*(): Incompatibly dimensioned "
         << "operands (" << this->num_rows << "x" << this->num_cols << ","
         << v_num_elements << ")." << std::endl;
      throw spffl::exception_t(ss.str());
    }

    tvector<element_type> rv(this->num_rows);
    element_type t00  = this->rows[0][0];
    element_type zero = t00 - t00;
    for (i = 0; i < this->num_rows; i++) {
      rv[i] = zero;
    }

    for (i = 0; i < this->num_rows; i++) {
      for (j = 0; j < this->num_cols; j++) {
        rv[i] += this->rows[i][j] * v[j];
      }
    }

    return rv;
  }

private:
  // ----------------------------------------------------------------
  // This is a private auxiliary function for the exp() method.

  tmatrix<element_type> posexp(
      int power, const tmatrix<element_type> &I) const {
    tmatrix<element_type> a2(*this);
    tmatrix<element_type> apower = I;

    while (power != 0) { // Repeated squaring.
      if (power & 1) {
        apower *= a2;
      }
      power = (unsigned)power >> 1;
      a2 *= a2;
    }
    return apower;
  }

public:
  // ----------------------------------------------------------------
  // * power >=  1:  repeated squaring
  // * power ==  0:
  // * power <= -1:  if singular, ret 0.  else invert & posexp the inverse.

  int exp(int power, tmatrix<element_type> &rout) const {
    if (!this->is_square()) {
      std::stringstream ss;
      ss << "tmatrix::exp():  non-square input.\n";
      throw spffl::exception_t(ss.str());
    }

    element_type zero = this->rows[0][0] - this->rows[0][0];
    element_type one;

    // Zero matrix
    if (!this->find_one(one)) {
      if (power <= 0) {
        std::stringstream ss;
        ss << "tmatrix::exp:  non-postive power of "
           << "zero matrix is undefined.\n";
        throw spffl::exception_t(ss.str());
      } else {
        rout = *this;
        return 1;
      }
    }

    // Non-zero matrix.
    tmatrix<element_type> I = this->make_I(zero, one);
    if (power >= 1) {
      rout = this->posexp(power, I);
      return 1;
    } else {
      tmatrix<element_type> ai;
      if (!this->inverse(ai)) {
        return 0;
      } else if (power == 0) {
        rout = I;
        return 1;
      } else if (power == -power) {
        std::stringstream ss;
        ss << "tmatrix::exp:  can't handle MIN_INT.\n";
        throw spffl::exception_t(ss.str());
      } else {
        rout = ai.posexp(-power, I);
        return 1;
      }
    }
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> operator*(const tmatrix<element_type> &that) const {
    int i, j, k;

    if (this->num_cols != that.num_rows) {
      std::stringstream ss;
      ss << "tmatrix operator*(): Incompatibly dimensioned "
         << "operands (" << this->num_rows << "x" << this->num_cols << ","
         << that.num_rows << "x" << that.num_cols << ")." << std::endl;
      throw spffl::exception_t(ss.str());
    }

    tmatrix<element_type> rv(this->num_rows, that.num_cols);
    element_type t00  = this->rows[0][0];
    element_type zero = t00 - t00;
    for (i = 0; i < this->num_rows; i++) {
      for (j = 0; j < that.num_cols; j++) {
        // rv[i][j] = element_type(0);
        rv[i][j] = zero;
      }
    }

    for (i = 0; i < this->num_rows; i++) {
      for (j = 0; j < that.num_cols; j++) {
        for (k = 0; k < this->num_cols; k++) {
          rv[i][j] += this->rows[i][k] * that.rows[k][j];
        }
      }
    }

    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> operator*(const element_type &e) const {
    tmatrix<element_type> rv(this->num_rows, this->num_cols);

    for (int i = 0; i < this->num_rows; i++) {
      for (int j = 0; j < this->num_cols; j++) {
        rv[i][j] = this->rows[i][j] * e;
      }
    }

    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> &operator+=(const tmatrix<element_type> &that) {
    *this = *this + that;
    return *this;
  }

  tmatrix<element_type> &operator-=(const tmatrix<element_type> &that) {
    *this = *this - that;
    return *this;
  }

  tmatrix<element_type> &operator+=(const element_type &e) {
    *this = *this + e;
    return *this;
  }

  tmatrix<element_type> &operator-=(const element_type &e) {
    *this = *this - e;
    return *this;
  }

  tvector<element_type> &operator*=(const tvector<element_type> &v) {
    *this = *this * v;
    return *this;
  }

  tmatrix<element_type> &operator*=(const tmatrix<element_type> &that) {
    *this = *this * that;
    return *this;
  }

  tmatrix<element_type> &operator*=(const element_type &e) {
    *this = *this * e;
    return *this;
  }

  // ----------------------------------------------------------------
  static tmatrix<element_type> outer(
      const tvector<element_type> &u, const tvector<element_type> &v) {
    int m = u.get_num_elements();
    int n = v.get_num_elements();
    tmatrix<element_type> rv(m, n);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        rv[i][j] = u[i] * v[j];
      }
    }
    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> transpose(void) const {
    tmatrix<element_type> rv(this->num_cols, this->num_rows);
    for (int i = 0; i < this->num_rows; i++) {
      for (int j = 0; j < this->num_cols; j++) {
        rv.rows[j][i] = this->rows[i][j];
      }
    }
    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> flip_horiz(void) const {
    tmatrix<element_type> rv(this->num_rows, this->num_cols);
    int nr = this->num_rows;
    int nc = this->num_cols;
    for (int i = 0; i < nr; i++) {
      for (int j = 0; j < nc; j++) {
        rv.rows[i][j] = this->rows[i][nc - j - 1];
      }
    }
    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> flip_vert(void) const {
    tmatrix<element_type> rv(this->num_rows, this->num_cols);
    int nr = this->num_rows;
    int nc = this->num_cols;
    for (int i = 0; i < nr; i++) {
      for (int j = 0; j < nc; j++) {
        rv.rows[i][j] = this->rows[nr - i - 1][j];
      }
    }
    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> flip_horiz_vert(void) const {
    tmatrix<element_type> rv(this->num_rows, this->num_cols);
    int nr = this->num_rows;
    int nc = this->num_cols;
    for (int i = 0; i < nr; i++) {
      for (int j = 0; j < nc; j++) {
        rv.rows[i][j] = this->rows[nr - i - 1][nc - j - 1];
      }
    }
    return rv;
  }

  // ----------------------------------------------------------------
  bool find_row(tvector<element_type> &v, int &row_index) const {
    for (int i = 0; i < this->num_rows; i++) {
      if (this->rows[i] == v) {
        row_index = i;
        return true;
      }
    }
    return false;
  }

  // ----------------------------------------------------------------
  // In a template class, we don't know a priori what form the additive or
  // multiplicative identities will take.  We can't assume that element_type
  // has a constructor from a single int -- e.g. for any mod type, we don't
  // know the modulus.  However, we can *compute* what 0 and 1 are:  0 is
  // any matrix element minus itself.  If there is any non-zero element, then
  // 1 is that element divided by itself.

  bool find_one(element_type &rone) const {
    element_type a    = this->rows[0][0];
    element_type zero = a - a;
    for (int i = 0; i < this->num_rows; i++) {
      for (int j = 0; j < this->num_cols; j++) {
        if (this->rows[i][j] != zero) {
          a    = this->rows[i][j];
          rone = a / a;
          return true;
        }
      }
    }
    return false;
  }

  // ----------------------------------------------------------------
  // Makes an identity matrix with the same dimensions as *this has.

  tmatrix<element_type> make_I(element_type zero, element_type one) const {
    if (!this->is_square()) {
      std::stringstream ss;
      ss << "tmatrix::make_I():  non-square input.\n";
      throw spffl::exception_t(ss.str());
    }

    tmatrix<element_type> rv(*this);
    for (int i = 0; i < this->num_rows; i++) {
      for (int j = 0; j < this->num_cols; j++) {
        if (i == j) {
          rv.rows[i][j] = one;
        } else {
          rv.rows[i][j] = zero;
        }
      }
    }
    return rv;
  }

  // ----------------------------------------------------------------
  bool is_zero(void) const {
    element_type one;
    if (this->find_one(one)) {
      return false;
    } else {
      return true;
    }
  }

  // ----------------------------------------------------------------
  bool is_square(void) const {
    if (this->num_rows == this->num_cols) {
      return true;
    } else {
      return false;
    }
  }

  // ----------------------------------------------------------------
  bool is_I(void) const {
    int i, j;

    if (!this->is_square()) {
      return false;
    }

    element_type a    = this->rows[0][0];
    element_type zero = a - a;
    element_type one;
    if (!this->find_one(one)) {
      return false;
    }
    for (i = 0; i < this->num_rows; i++) {
      if (this->rows[i][i] != one) {
        return false;
      }
    }
    for (i = 0; i < this->num_rows; i++) {
      for (j = 0; j < this->num_cols; j++) {
        if (i != j) {
          if (this->rows[i][j] != zero) {
            return false;
          }
        }
      }
    }
    return true;
  }

  // ----------------------------------------------------------------
  void swap(int arow, int brow) { this->rows[arow].ptrswap(this->rows[brow]); }

  // ----------------------------------------------------------------
  // This is a general row-reduction method.  It operates on the matrix
  // in-place.
  //
  // The "scalar" argument is used for computation of the determinant.
  // When the determinant is not desired, this scalar is tracked anyway; the
  // overhead is minimal.  Let A and B be the input and output, respectively.
  // The scalar s is such that det(A) = s det(B).
  //
  // The determinant is the unique n-linear alternating form such that det(I)
  // = 1. This means (letting u, v, w be row vectors of a sample 3x3 matrix):
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
  //   B = (au+bv,v,w) s = 1/a. s det(B) = (1/a)*(a det(au,v,w) + b
  //   det(v,v,w))=d

  void row_reduce_below_with_scalar(element_type &s) {
    int top_row, left_column, cur_row;
    element_type zero = this->rows[0][0] - this->rows[0][0];
    element_type one;
    element_type minus_one;

    if (!this->find_one(one)) {
      s = zero;
      return; // Zero matrix; already done.
    }
    element_type **ptrs = this->expose();
    element_type *temp;

    minus_one = zero - one;
    s         = one;
    for (top_row = 0, left_column = 0;
         (top_row < this->num_rows) && (left_column < this->num_cols);
        /* increment in loop body */) {
      // Find the nearest row with a non-zero value in this column;
      // exchange that row with this one.
      int pivot_row        = top_row;
      int pivot_successful = 0;
      while (!pivot_successful && (pivot_row < this->num_rows)) {
        // if (this->rows[pivot_row][left_column] != zero)
        if (ptrs[pivot_row][left_column] != zero) {
          if (top_row != pivot_row) {
            this->swap(top_row, pivot_row);
            temp            = ptrs[top_row];
            ptrs[top_row]   = ptrs[pivot_row];
            ptrs[pivot_row] = temp;
            s *= minus_one;
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

      // We can have a zero leading element in this row if it's
      // the last row and full of zeroes.
      // element_type top_row_lead = this->rows[top_row][left_column];
      element_type top_row_lead = ptrs[top_row][left_column];
      if (top_row_lead != zero) {
        // Normalize this row.
        element_type inv = one / top_row_lead;
        this->rows[top_row].mult_by(inv);
        s *= top_row_lead;

        // Clear this column.
        top_row_lead = ptrs[top_row][left_column];
        for (cur_row = top_row + 1; cur_row < this->num_rows; cur_row++) {
          element_type current_row_lead = ptrs[cur_row][left_column];

          // this->rows[cur_row] =
          //	this->rows[cur_row] * top_row_lead -
          //	this->rows[top_row] * current_row_lead;
          this->rows[cur_row].accum_row_mul(
              top_row_lead, current_row_lead, this->rows[top_row]);

          s /= top_row_lead;
        }
      }
      left_column++;
      top_row++;
    }
    delete[] ptrs;
  }

  // ----------------------------------------------------------------
  // Operates on the matrix in-place.

  void row_reduce_below(void) {
    element_type ignored;
    this->row_reduce_below_with_scalar(ignored);
  }

  // ----------------------------------------------------------------
  // Operates on the matrix in-place.

  void row_echelon_form(void) {
    this->row_reduce_below();

    element_type zero = this->rows[0][0] - this->rows[0][0];
    int row, row2, row2_leader_pos;
    element_type row_clear_val, row2_leader_val, mul;

    for (row = 0; row < this->num_rows; row++) {
      for (row2 = row + 1; row2 < this->num_rows; row2++) {
        if (!this->rows[row2].find_leader_pos(zero, row2_leader_pos)) {
          break;
        }
        row2_leader_val = this->rows[row2][row2_leader_pos];
        row_clear_val   = this->rows[row][row2_leader_pos];
        if (row_clear_val == zero) {
          continue;
        }

        mul = row_clear_val / row2_leader_val;
        this->rows[row] -= this->rows[row2] * mul;
      }
    }
  }

  bool get_rr_non_zero_rows(tmatrix<element_type> &rrnz) {
    tmatrix<element_type> rr(*this);
    rr.row_reduce_below();
    int rank = rr.get_rank_rr();
    if (rank == 0) {
      // I don't support zero-row matrices.
      return false;
    } else {
      rrnz          = rr;
      rrnz.num_rows = rank;
      return true;
    }
  }

  bool get_rech_non_zero_rows(tmatrix<element_type> &rechnz) {
    tmatrix<element_type> rech(*this);
    rech.row_echelon_form();
    int rank = rech.get_rank_rr();
    if (rank == 0) {
      // I don't support zero-row matrices.
      return false;
    } else {
      rechnz          = rech;
      rechnz.num_rows = rank;
      return true;
    }
  }

  // ----------------------------------------------------------------
  // This method makes a copy of the matrix and row-reduces it.  To save
  // CPU cycles, use get_rank_rr() if the matrix is already row-reduced.
  int get_rank(void) const {
    tmatrix<element_type> rr(*this);
    rr.row_reduce_below();
    return rr.get_rank_rr();
  }

  // This method assumes the matrix is already row-reduced.  If not,
  // use get_rank() instead.
  int get_rank_rr(void) const {
    int rank          = 0;
    element_type zero = this->rows[0][0] - this->rows[0][0];

    for (int i = 0; i < this->num_rows; i++) {
      bool row_is_zero = true;
      for (int j = 0; j < this->num_cols; j++) {
        if (this->rows[i][j] != zero) {
          row_is_zero = false;
          break;
        }
      }
      if (!row_is_zero) {
        rank++;
      }
    }
    return rank;
  }

  // ----------------------------------------------------------------
  bool get_kernel_basis(tmatrix<element_type> &rbas, const element_type &zero,
      const element_type &one) const {
    int i, j;
    tmatrix<element_type> rr(*this);
    rr.row_echelon_form();
    int rank   = rr.get_rank_rr();
    int dimker = rr.num_cols - rank;
    if (dimker == 0) {
      return false;
    }

    tmatrix<element_type> basis(dimker, rr.num_cols);

    for (i = 0; i < dimker; i++) {
      for (j = 0; j < rr.num_cols; j++) {
        basis[i][j] = zero;
      }
    }

    unsigned char *free_flags = new unsigned char[this->num_cols];
    int *free_indices         = new int[this->num_cols];
    int nfree                 = 0; // == dimker but I'll compute it anyway
    int dep_pos               = 0;

    for (i = 0; i < this->num_cols; i++) {
      free_flags[i] = 1;
    }

    for (i = 0; i < rank; i++) {
      if (rr.rows[i].find_leader_pos(zero, dep_pos)) {
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
      basis.rows[i][free_indices[i]] = one;

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
        if (rr.rows[j][free_indices[i]] == zero) {
          continue;
        }

        (void)rr.rows[j].find_leader_pos(zero, dep_pos);
        basis.rows[i][dep_pos] = -rr.rows[j][free_indices[i]];
      }
    }

#ifdef KERBAS_DEBUG
    std::cout << "start check:\n";
    std::cout << "A  =\n" << *this << "\n";
    std::cout << "rr =\n" << rr << "\n";

    for (i = 0; i < dimker; i++) {
      std::cout << "v  = " << basis.rows[i] << "\n";
    }
    std::cout << "\n";
    for (i = 0; i < dimker; i++) {
      tvector<element_type> Av = *this * basis.rows[i];
      std::cout << "Av = " << Av << "\n";
    }
    std::cout << "end check.\n";
    std::cout << "\n";
#endif // KERBAS_DEBUG

    delete[] free_flags;
    delete[] free_indices;

    rbas = basis;
    return true;
  }

  // ----------------------------------------------------------------
  void check_kernel_basis(const tmatrix<element_type> &kerbas) const {
    element_type zero = this->rows[0][0] - this->rows[0][0];
    int i;
    int dimker = kerbas.num_rows;

    for (i = 0; i < dimker; i++) {
      tvector<element_type> Av = *this * kerbas.rows[i];
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
        throw spffl::exception_t(ss.str());
      }
    }
  }

  // ----------------------------------------------------------------
  // A x = b
  // A is m x n, i.e. A: F^n -> F^m
  // * If rank(A) < rank(A|b):     no solution.
  // * If rank(A) = rank(A|b) = n: unique solution.
  // * If rank(A) = rank(A|b) < n: non-unique solutions.

  // n > m:
  // +-----------n-----------+   +-+   +-+  Unique solution impossible.
  // |                       |   | |   | |
  // |           A           |   |x|   |b|
  // m                       | * | | = | |
  // +-----------------------+   | n   | m
  // |///////////////////////|   | |   | |
  // +-----------------------+   | |   +-+
  //                             | |
  //                             | |
  //                             +-+

  // n = m:
  // +-----n-----+   +-+   +-+
  // |           |   | |   | |
  // |     A     |   |x|   |b|
  // |           | * | | = | |
  // m           |   | n   | m
  // |\\\\\\\\\\\|   | |   | |
  // +-----------+   +-+   +-+

  // n < m:
  // +-----n-----+   +-+   +-+   Just rech & take the first n entries in the
  // |           |   | |   | |   last column of A|b.
  // |     A     |   |x|   |b|   Make sure to check ranks of A and aug first.
  // |           | * | | = | |
  // m           |   | n   | m
  // |\\\\\\\\\\\|   | |   | |
  // +-----------+   +-+   | |
  // |///////////|         | |
  // |///////////|         | |
  // |///////////|         | |
  // +-----------+         +-+

  // The solve_unique method checks that the matrix has full rank (i.e. rank=n).
  // For efficiency, if the matrix is already known to have full rank, invoke
  // solve_unique_full_rank.
  bool solve_unique(tvector<element_type> &x, // Output
      const tvector<element_type> &b,         // Input
      const element_type &zero, const element_type &one) const {
    int indim  = this->get_num_cols();
    int outdim = this->get_num_rows();
    //  A linear transformation from a higher-dimensional space to a
    //  lower-dimensional space cannot be injective, hence there can be no
    //  unique solution.
    if (indim > outdim) {
      std::stringstream ss;
      ss << "tmatrix::solve_unique:  matrix cannot have full rank.\n";
      return false;
    }
    int A_rank = this->get_rank();
    if (A_rank != indim) {
      std::stringstream ss;
      ss << "tmatrix::solve_unique:  matrix does not have full rank.\n";
      return false;
    }

    return this->solve_unique_full_rank(x, b, zero, one);
  }

  // The solve_unique_full_rank method assumes the matrix is already known to
  // have full rank (rank=n).  If this is not known, please invoke solve_unique
  // instead.
  bool solve_unique_full_rank(tvector<element_type> &x, // Output
      const tvector<element_type> &b,                   // Input
      const element_type &zero, const element_type &one) const {
    int indim                   = this->get_num_cols();
    tmatrix<element_type> Ab_rr = this->paste_vector(b);
    Ab_rr.row_echelon_form();
    int Ab_rank = Ab_rr.get_rank_rr();
    if (Ab_rank != indim) {
      std::stringstream ss;
      ss << "tmatrix::solve_unique_full_rank:  augmented matrix does "
            "not have full rank.\n";
      return false;
    }

    x = tvector<element_type>(indim);
    for (int i = 0; i < indim; i++) {
      x[i] = Ab_rr.rows[i][indim];
    }
    return true;
  }

  // n < m:
  // +-----n-----+   +-+   +-+   6 3 1 5 1 2 0 4  1 0 0 0 0 0 0 5
  // |           |   | |   | |   7 4 0 7 7 2 3 5  0 1 0 0 0 0 0 2
  // |     A     |   |x|   |b|   1 4 4 5 4 4 5 2  0 0 1 0 0 0 0 4
  // |           | * | | = | |   6 4 7 3 6 4 6 7  0 0 0 1 0 0 0 3
  // m           |   | n   | m   7 6 3 5 5 1 1 5  0 0 0 0 1 0 0 4
  // |\\\\\\\\\\\|   | |   | |   1 0 0 0 0 0 0 5  0 0 0 0 0 1 0 7
  // +-----------+   +-+   | |   0 1 0 0 0 0 0 2  0 0 0 0 0 0 1 2
  // |///////////|         | |   0 0 1 0 0 0 0 4  0 0 0 0 0 0 0 0
  // |///////////|         | |   0 0 0 1 0 0 0 3  0 0 0 0 0 0 0 0
  // |///////////|         | |   0 0 0 0 1 0 0 4  0 0 0 0 0 0 0 0
  // +-----------+         +-+   0 0 0 0 0 1 0 7  0 0 0 0 0 0 0 0
  //                             0 0 0 0 0 0 1 2  0 0 0 0 0 0 0 0

  // ----------------------------------------------------------------
  tmatrix<element_type> paste(const tmatrix<element_type> &that) const {
    if (this->num_rows != that.num_rows) {
      std::stringstream ss;
      ss << "tmatrix::paste:  differing number of rows (" << this->num_rows
         << " vs. " << that.num_rows << ")\n";
      throw spffl::exception_t(ss.str());
    }

    tmatrix<element_type> rv(this->num_rows, this->num_cols + that.num_cols);
    int i, j;

    for (i = 0; i < this->num_rows; i++) {
      for (j = 0; j < this->num_cols; j++) {
        rv.rows[i][j] = this->rows[i][j];
      }
    }
    for (i = 0; i < this->num_rows; i++) {
      for (j = 0; j < that.num_cols; j++) {
        rv.rows[i][this->num_rows + j] = that.rows[i][j];
      }
    }

    return rv;
  }

  // ----------------------------------------------------------------
  tmatrix<element_type> paste_vector(const tvector<element_type> &v) const {
    int vne = v.get_num_elements();
    if (this->num_rows != vne) {
      std::stringstream ss;
      ss << "tmatrix::paste_vector:  differing number of rows ("
         << this->num_rows << " vs. " << vne << ")\n";
      throw spffl::exception_t(ss.str());
    }

    tmatrix<element_type> rv(this->num_rows, this->num_cols + 1);
    int i, j;
    for (i = 0; i < this->num_rows; i++) {
      for (j = 0; j < this->num_cols; j++) {
        rv.rows[i][j] = this->rows[i][j];
      }
    }
    for (i = 0; i < this->num_rows; i++) {
      rv.rows[i][this->num_cols] = v[i];
    }

    return rv;
  }

  // ----------------------------------------------------------------
  void split(tmatrix<element_type> &rleft, tmatrix<element_type> &rright,
      int split_column) const {
    if ((split_column < 0) || (split_column >= this->num_cols)) {
      std::stringstream ss;
      ss << "tmatrix::split:  split column " << split_column
         << " out of bounds 0:" << this->num_rows - 1 << ".\n";
      throw spffl::exception_t(ss.str());
    }

    rleft = tmatrix<element_type>(this->num_rows, split_column);
    rright =
        tmatrix<element_type>(this->num_rows, this->num_cols - split_column);

    int i, j;

    for (i = 0; i < this->num_rows; i++) {
      for (j = 0; j < split_column; j++) {
        rleft.rows[i][j] = this->rows[i][j];
      }
    }

    for (i = 0; i < this->num_rows; i++) {
      for (j = split_column; j < this->num_cols; j++) {
        rright.rows[i][j - split_column] = this->rows[i][j];
      }
    }
  }

  // ----------------------------------------------------------------
  bool inverse(tmatrix<element_type> &rinv) const {
    element_type zero = this->rows[0][0] - this->rows[0][0];
    element_type one;

    if (!this->is_square()) {
      std::stringstream ss;
      ss << "tmatrix::inverse():  non-square input.\n";
      throw spffl::exception_t(ss.str());
    }

    if (!this->find_one(one)) {
      return false;
    }

    tmatrix<element_type> I    = this->make_I(zero, one);
    tmatrix<element_type> pair = this->paste(I);
    pair.row_echelon_form();

    pair.split(I, rinv, this->num_cols);
    return I.is_I();
  }

  // ----------------------------------------------------------------
  void check_inverse(tmatrix<element_type> &rinv) const {
    tmatrix<element_type> AB = *this * rinv;
    tmatrix<element_type> BA = rinv * *this;
    if (!AB.is_I() || !BA.is_I()) {
      std::stringstream ss;
      ss << "coding error:  not really inverses.\n";
      throw spffl::exception_t(ss.str());
    }
  }

  // ----------------------------------------------------------------
  element_type det(void) const {
    if (!this->is_square()) {
      std::stringstream ss;
      ss << "tmatrix::det():  non-square input.\n";
      throw spffl::exception_t(ss.str());
    }
    tmatrix<element_type> rr(*this);
    element_type d;
    rr.row_reduce_below_with_scalar(d);
    for (int i = 0; i < this->num_rows; i++) {
      d *= rr.rows[i][i];
    }
    return d;
  }

  // ----------------------------------------------------------------
  void ed_row_reduce_below_with_scalar(
      element_type &snumer, element_type &sdenom) {
    int top_row, left_column, cur_row;
    element_type zero = this->rows[0][0] - this->rows[0][0];
    element_type one;

    if (!this->find_one(one)) {
      snumer = zero;
      return; // Zero matrix; already done.
    }
    snumer = one;
    sdenom = one;

    for (top_row = 0, left_column = 0;
         (top_row < this->num_rows) && (left_column < this->num_cols);
        /* increment in loop body */) {
      // Find the nearest row with a non-zero value in this column; exchange
      // that row with this one.
      int pivot_row        = top_row;
      int pivot_successful = 0;
      while (!pivot_successful && (pivot_row < this->num_rows)) {
        if (this->rows[pivot_row][left_column] != zero) {
          if (top_row != pivot_row) {
            this->swap(top_row, pivot_row);
            snumer = zero - snumer;
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

      // We can have a zero leading element in this row if it's
      // the last row and full of zeroes.

      // Normalize this row.
      element_type g = this->rows[top_row].vgcd();
      if (g != zero) {
        this->rows[top_row] /= g;
        snumer *= g;
      }
      element_type top_row_lead = this->rows[top_row][left_column];

      if (top_row_lead != zero) {
        // Clear this column.
        for (cur_row = top_row + 1; cur_row < this->num_rows; cur_row++) {

          g = this->rows[cur_row].vgcd();
          if (g != zero) {
            this->rows[cur_row] /= g;
            snumer *= g;
          }
          element_type current_row_lead = this->rows[cur_row][left_column];

          element_type lead_gcd = gcd(top_row_lead, current_row_lead);
          element_type top_mul  = current_row_lead / lead_gcd;
          element_type cur_mul  = top_row_lead / lead_gcd;
          this->rows[cur_row].accum_row_mul(
              cur_mul, top_mul, this->rows[top_row]);
          sdenom *= cur_mul;

          g = this->rows[cur_row].vgcd();
          if (g != zero) {
            this->rows[cur_row] /= g;
            snumer *= g;
          }

          g = gcd(snumer, sdenom);
          if (g != zero) {
            snumer /= g;
            sdenom /= g;
          }
        }
      }
      left_column++;
      top_row++;
    }
  }

  // ----------------------------------------------------------------
  void ed_row_reduce_below(void) {
    element_type ignored_numer, ignored_denom;
    this->ed_row_reduce_below_with_scalar(ignored_numer, ignored_denom);
  }

  // ----------------------------------------------------------------
  element_type ed_det(void) const {
    if (!this->is_square()) {
      std::stringstream ss;
      ss << "tmatrix::ed_det():  non-square input.\n";
      throw spffl::exception_t(ss.str());
    }
    tmatrix<element_type> rr(*this);
    element_type dn, dd;
    rr.ed_row_reduce_below_with_scalar(dn, dd);
    for (int i = 0; i < this->num_rows; i++) {
      dn *= rr.rows[i][i];
    }

    // Sanity check: dd must divide dn.
    element_type zero = dn - dn;
    element_type rem  = dn % dd;
    element_type quot = dn / dd;
    if (rem != zero) {
      std::stringstream ss;
      ss << "tmatrix::ed_det:  coding error:  dd must divide dn.\n";
      ss << "Got " << dn << "% " << dd << " = " << rem << "\n";
      throw spffl::exception_t(ss.str());
    }
    return quot;
  }

  // ----------------------------------------------------------------
  // Operates on the matrix in-place.

  // 3 5 3 1 7 4
  // 0 2 2 4 9 8
  // 0 0 4 2 8 1
  // 0 0 0 3 0 b

  void ed_row_echelon_form(void) {
    this->ed_row_reduce_below();

    element_type zero = this->rows[0][0] - this->rows[0][0];
    int row, row2, row2_leader_pos;
    element_type row_clear_val, row2_leader_val;

    for (row = 0; row < this->num_rows; row++) {
      for (row2 = row + 1; row2 < this->num_rows; row2++) {
        if (!this->rows[row2].find_leader_pos(zero, row2_leader_pos)) {
          break;
        }
        row2_leader_val = this->rows[row2][row2_leader_pos];
        row_clear_val   = this->rows[row][row2_leader_pos];
        if (row_clear_val == zero) {
          continue;
        }

        this->rows[row].accum_row_mul(
            row2_leader_val, row_clear_val, this->rows[row2]);

        element_type g = this->rows[row].vgcd();
        if (g != zero) {
          this->rows[row] /= g;
        }
      }
    }
  }

  // ----------------------------------------------------------------
  bool ed_inverse(tmatrix<element_type> &rinv) const {
    element_type zero = this->rows[0][0] - this->rows[0][0];
    element_type one;

    if (!this->is_square()) {
      std::stringstream ss;
      ss << "tmatrix::ed_inverse():  non-square input.\n";
      throw spffl::exception_t(ss.str());
    }

    if (!this->find_one(one)) {
      return false;
    }

    tmatrix<element_type> I    = this->make_I(zero, one);
    tmatrix<element_type> pair = this->paste(I);
    pair.ed_row_echelon_form();

    pair.split(I, rinv, this->num_cols);
    return I.is_I();
  }

  // ----------------------------------------------------------------
  void trim_num_rows(int new_num_rows) {
    if ((new_num_rows < 1) || (new_num_rows > this->num_rows)) {
      std::stringstream ss;
      ss << "tmatrix trim_num_rows: new count " << new_num_rows
         << " out of bounds " << 1 << ":" << this->num_rows << std::endl;
      throw spffl::exception_t(ss.str());
    }
    this->num_rows = new_num_rows;
  }

  // ----------------------------------------------------------------
  // The caller must delete [] the return value.
  element_type **expose(void) const {
    element_type **rv = new element_type *[this->num_rows];
    for (int i = 0; i < this->num_rows; i++) {
      rv[i] = this->rows[i].expose();
    }
    return rv;
  }

  // ----------------------------------------------------------------
  int get_num_rows(void) const { return this->num_rows; }

  // ----------------------------------------------------------------
  int get_num_cols(void) const { return this->num_cols; }

  // ================================================================
private:
  tvector<element_type> *rows;
  int num_rows;
  int num_cols;

  // ----------------------------------------------------------------
  void mfree(void) {
    if (this->rows != 0) {
      delete[] this->rows;
    }
    this->nullify();
  }

  // ----------------------------------------------------------------
  void nullify(void) {
    this->rows     = 0;
    this->num_rows = 0;
    this->num_cols = 0;
  }

  // ----------------------------------------------------------------
  void check_dims(
      const tmatrix<element_type> &that, const std::string &msg) const {
    if ((this->num_rows != that.num_rows) ||
        (this->num_cols != that.num_cols)) {
      std::stringstream ss;
      ss << "tmatrix " << msg << ":  Incompatibly sized arguments ("
         << this->num_rows << "x" << this->num_cols << ", " << that.num_rows
         << "x" << that.num_cols << ")." << std::endl;
      throw spffl::exception_t(ss.str());
    }
  }

  // ----------------------------------------------------------------
  friend std::ostream &operator<< <>(
      std::ostream &os, const tmatrix<element_type> &m);

  friend std::istream &operator>><>(std::istream &is, tmatrix<element_type> &m);
};

// ================================================================
template <typename element_type>
static std::ostream &operator<<(
    std::ostream &os, const tmatrix<element_type> &m) {
  for (int i = 0; i < m.num_rows; i++) {
    os << m.rows[i] << std::endl;
  }
  return os;
}

// ================================================================
// The matrix must already contain at least one element, even though it
// will be discarded.  I know no other way to set the modulus for mod types,
// other than requiring all input data to have moduli for each and every
// element (yuk).
template <typename element_type>
static std::istream &operator>>(std::istream &is, tmatrix<element_type> &m) {
  const int tmx_buf_size = 65536;
  char *line             = new char[tmx_buf_size];
  char *pline            = line;

  // Make sure the matrix already contains an element.  Remember it,
  // then free the old matrix contents.
  if (!m.rows || (m.num_rows < 1) || (m.num_cols < 1)) {
    is.setstate(std::ios::badbit);
    std::stringstream ss;
    ss << "tmatrix >>:  must already have one element.\n";
    delete[] line;
    return is;
  }
  element_type zero = m.rows[0][0] - m.rows[0][0];
  m.mfree();

  const int init_num_rows = 10;
  const int more_num_rows = 10;
  int alloc_num_rows      = init_num_rows;
  m.rows                  = new tvector<element_type>[init_num_rows];

  while (1) {
    if (is.eof()) {
      break;
    }

    if (m.num_rows >= alloc_num_rows) {
      alloc_num_rows += more_num_rows;
      tvector<element_type> *ptemp = new tvector<element_type>[alloc_num_rows];
      for (int i = 0; i < m.num_rows; i++) {
        ptemp[i] = m.rows[i];
      }
      delete[] m.rows;
      m.rows = ptemp;
    }

    // Read a line of text.
    is.getline(pline, tmx_buf_size);
    if (is.eof()) {
      is.clear();
      break;
    } else if (is.fail()) {
      break;
    }

    // Allow comments.
    char *phash = strstr(pline, "#");
    if (phash) {
      *phash = 0;
    }

    // Strip leading whitespace.
    while (isspace(pline[0])) {
      pline++;
    }

    // Strip trailing whitespace.
    int len = strlen(pline);
    while ((len > 0) && isspace(pline[len - 1])) {
      pline[len - 1] = 0;
      len--;
    }

    // Allow multiple matrices in the same stream, delimited by
    // carriage returns.
    if (spffl::base::is_whitespace_line(pline)) {
      if (m.num_rows == 0) {
        continue;
      } else {
        break;
      }
    }

    // E.g. set modulus.
    m.rows[m.num_rows] = zero;

    // Use tvector istringstream >> to scan the line of text as a
    // row vector.
    std::istringstream iss(pline, std::ios_base::in);
    iss >> m.rows[m.num_rows];
    if (iss.fail()) {
      is.setstate(std::ios::failbit);
      std::stringstream ss;
      ss << "tmatrix scan failure: \"" << pline << "\"\n";
      delete[] line;
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
    ss << "tmatrix >>:  zero-row matrix.\n";
    delete[] line;
    return is;
  }

  // Sets num_cols too.
  if (!m.check_ragged()) {
    is.setstate(std::ios::badbit);
    delete[] line;
    return is;
  }

  delete[] line;
  return is;
}

#endif // TMATRIX_H
