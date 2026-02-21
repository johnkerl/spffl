// ================================================================
// STL-based matrix over a ring element. Satisfies Matrix_over<M, T>.
// Rows are vector_over<T>; A[i] is row i.
// ================================================================

#ifndef SPFFL_CONTAINERS_MATRIX_OVER_H
#define SPFFL_CONTAINERS_MATRIX_OVER_H

#include "spffl/concepts.h"
#include "spffl/containers/vector_over.h"
#include "spffl/containers/tmatrix.h"
#include "spffl/base/read_element.h"
#include "spffl/base/tokenize.h"
#include <vector>
#include <stdexcept>
#include <ostream>
#include <istream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>

namespace spffl::containers {

template <typename T>
  requires spffl::concepts::Ring_element<T>
class matrix_over {
public:
  using element_type = T;
  using row_type = vector_over<T>;

  matrix_over() : rows_(0), cols_(0) {}

  matrix_over(int num_rows, int num_cols)
      : cols_(num_cols) {
    if (num_rows < 0 || num_cols < 0) {
      throw std::invalid_argument("matrix_over: negative dimensions");
    }
    rows_.reserve(static_cast<std::size_t>(num_rows));
    for (int i = 0; i < num_rows; ++i) {
      rows_.emplace_back(num_cols);
    }
  }

  matrix_over(int num_rows, int num_cols, const T& fill)
      : cols_(num_cols) {
    if (num_rows < 0 || num_cols < 0) {
      throw std::invalid_argument("matrix_over: negative dimensions");
    }
    rows_.reserve(static_cast<std::size_t>(num_rows));
    for (int i = 0; i < num_rows; ++i) {
      rows_.emplace_back(num_cols, fill);
    }
  }

  row_type& operator[](std::size_t i) {
    if (i >= static_cast<std::size_t>(get_num_rows())) {
      throw std::out_of_range("matrix_over: row index out of range");
    }
    return rows_[i];
  }

  const row_type& operator[](std::size_t i) const {
    if (i >= static_cast<std::size_t>(get_num_rows())) {
      throw std::out_of_range("matrix_over: row index out of range");
    }
    return rows_[i];
  }

  int get_num_rows() const { return static_cast<int>(rows_.size()); }
  int get_num_cols() const { return cols_; }

  matrix_over operator+(const matrix_over& B) const {
    check_same_shape(B);
    matrix_over out(get_num_rows(), get_num_cols());
    for (int i = 0; i < get_num_rows(); ++i) {
      out.rows_[static_cast<std::size_t>(i)] =
          (*this)[static_cast<std::size_t>(i)] + B[static_cast<std::size_t>(i)];
    }
    return out;
  }

  matrix_over operator-(const matrix_over& B) const {
    check_same_shape(B);
    matrix_over out(get_num_rows(), get_num_cols());
    for (int i = 0; i < get_num_rows(); ++i) {
      out.rows_[static_cast<std::size_t>(i)] =
          (*this)[static_cast<std::size_t>(i)] - B[static_cast<std::size_t>(i)];
    }
    return out;
  }

  matrix_over operator-() const {
    matrix_over out(get_num_rows(), get_num_cols());
    for (int i = 0; i < get_num_rows(); ++i) {
      out.rows_[static_cast<std::size_t>(i)] =
          -(*this)[static_cast<std::size_t>(i)];
    }
    return out;
  }

  matrix_over operator*(const matrix_over& B) const {
    if (get_num_cols() != B.get_num_rows()) {
      throw std::invalid_argument("matrix_over: incompatible dimensions for multiply");
    }
    const int n = get_num_rows();
    const int m = get_num_cols();
    const int p = B.get_num_cols();
    matrix_over out(n, p);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < p; ++j) {
        T sum = (*this)[static_cast<std::size_t>(i)][0] - (*this)[static_cast<std::size_t>(i)][0];  // zero
        for (int k = 0; k < m; ++k) {
          sum = sum + (*this)[static_cast<std::size_t>(i)][k] * B[static_cast<std::size_t>(k)][j];
        }
        out.rows_[static_cast<std::size_t>(i)][j] = sum;
      }
    }
    return out;
  }

  row_type operator*(const row_type& x) const {
    if (x.get_num_elements() != get_num_cols()) {
      throw std::invalid_argument("matrix_over: vector length must match num_cols");
    }
    row_type out(get_num_rows());
    for (int i = 0; i < get_num_rows(); ++i) {
      out[i] = (*this)[static_cast<std::size_t>(i)].dot(x);
    }
    return out;
  }

  bool operator==(const matrix_over& B) const {
    if (get_num_rows() != B.get_num_rows() || get_num_cols() != B.get_num_cols()) {
      return false;
    }
    for (int i = 0; i < get_num_rows(); ++i) {
      if ((*this)[static_cast<std::size_t>(i)] != B[static_cast<std::size_t>(i)]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const matrix_over& B) const { return !(*this == B); }

  bool is_square() const {
    return get_num_rows() == get_num_cols();
  }

  bool find_one(T& rone) const {
    const int nr = get_num_rows();
    const int nc = get_num_cols();
    if (nr == 0 || nc == 0) return false;
    T zero = (*this)[0][0] - (*this)[0][0];
    for (int i = 0; i < nr; ++i) {
      for (int j = 0; j < nc; ++j) {
        if ((*this)[static_cast<std::size_t>(i)][j] != zero) {
          T a = (*this)[static_cast<std::size_t>(i)][j];
          rone = a / a;
          return true;
        }
      }
    }
    return false;
  }

  matrix_over make_I(const T& zero, const T& one) const {
    if (!is_square()) {
      throw std::invalid_argument("matrix_over::make_I: non-square matrix");
    }
    const int n = get_num_rows();
    matrix_over rv(n, n);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        rv.rows_[static_cast<std::size_t>(i)][j] = (i == j) ? one : zero;
      }
    }
    return rv;
  }

  bool is_I() const {
    if (!is_square()) return false;
    T zero, one;
    zero = (*this)[0][0] - (*this)[0][0];
    if (!find_one(one)) return false;
    const int n = get_num_rows();
    for (int i = 0; i < n; ++i) {
      if ((*this)[static_cast<std::size_t>(i)][i] != one) return false;
    }
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i != j && (*this)[static_cast<std::size_t>(i)][j] != zero) return false;
      }
    }
    return true;
  }

  void swap_rows(int arow, int brow) {
    if (arow < 0 || arow >= get_num_rows() || brow < 0 || brow >= get_num_rows()) {
      throw std::out_of_range("matrix_over::swap_rows: index out of range");
    }
    std::swap(rows_[static_cast<std::size_t>(arow)], rows_[static_cast<std::size_t>(brow)]);
  }

  void row_reduce_below() {
    T zero = (*this)[0][0] - (*this)[0][0];
    T one;
    if (!find_one(one)) return;
    const int nr = get_num_rows();
    const int nc = get_num_cols();
    int top_row = 0, left_column = 0;
    while (top_row < nr && left_column < nc) {
      int pivot_row = top_row;
      while (pivot_row < nr && (*this)[static_cast<std::size_t>(pivot_row)][left_column] == zero) {
        ++pivot_row;
      }
      if (pivot_row >= nr) {
        ++left_column;
        continue;
      }
      if (pivot_row != top_row) {
        swap_rows(top_row, pivot_row);
      }
      T top_row_lead = (*this)[static_cast<std::size_t>(top_row)][left_column];
      if (top_row_lead != zero) {
        T inv = one / top_row_lead;
        (*this)[static_cast<std::size_t>(top_row)].mult_by(inv);
        for (int cur_row = top_row + 1; cur_row < nr; ++cur_row) {
          T cur_lead = (*this)[static_cast<std::size_t>(cur_row)][left_column];
          if (cur_lead != zero) {
            (*this)[static_cast<std::size_t>(cur_row)].accum_row_mul(top_row_lead, cur_lead, (*this)[static_cast<std::size_t>(top_row)]);
          }
        }
      }
      ++left_column;
      ++top_row;
    }
  }

  void row_echelon_form() {
    row_reduce_below();
    T zero = (*this)[0][0] - (*this)[0][0];
    T one;
    if (!find_one(one)) return;
    const int nr = get_num_rows();
    for (int row = 0; row < nr; ++row) {
      for (int row2 = row + 1; row2 < nr; ++row2) {
        int row2_leader_pos;
        if (!(*this)[static_cast<std::size_t>(row2)].find_leader_pos(zero, row2_leader_pos)) break;
        T row2_leader_val = (*this)[static_cast<std::size_t>(row2)][row2_leader_pos];
        T row_clear_val = (*this)[static_cast<std::size_t>(row)][row2_leader_pos];
        if (row_clear_val == zero) continue;
        T mul = row_clear_val / row2_leader_val;
        (*this)[static_cast<std::size_t>(row)].accum_row_mul(one, mul, (*this)[static_cast<std::size_t>(row2)]);
      }
    }
  }

  int get_rank_rr() const {
    T zero = (*this)[0][0] - (*this)[0][0];
    int rank = 0;
    for (int i = 0; i < get_num_rows(); ++i) {
      bool row_is_zero = true;
      for (int j = 0; j < get_num_cols(); ++j) {
        if ((*this)[static_cast<std::size_t>(i)][j] != zero) {
          row_is_zero = false;
          break;
        }
      }
      if (!row_is_zero) ++rank;
    }
    return rank;
  }

  int get_rank() const {
    matrix_over copy(*this);
    copy.row_reduce_below();
    return copy.get_rank_rr();
  }

  bool get_kernel_basis(matrix_over& rbas, const T& zero, const T& one) const {
    matrix_over rr(*this);
    rr.row_echelon_form();
    int rank = rr.get_rank_rr();
    int dimker = get_num_cols() - rank;
    if (dimker == 0) return false;
    rbas = matrix_over(dimker, get_num_cols());
    std::vector<int> free_indices;
    std::vector<bool> free_flags(static_cast<std::size_t>(get_num_cols()), true);
    for (int i = 0; i < rank; ++i) {
      int dep_pos;
      if (rr[static_cast<std::size_t>(i)].find_leader_pos(zero, dep_pos)) {
        free_flags[static_cast<std::size_t>(dep_pos)] = false;
      }
    }
    for (int i = 0; i < get_num_cols(); ++i) {
      if (free_flags[static_cast<std::size_t>(i)]) free_indices.push_back(i);
    }
    for (int i = 0; i < dimker; ++i) {
      rbas[static_cast<std::size_t>(i)][free_indices[static_cast<std::size_t>(i)]] = one;
      for (int j = 0; j < rank; ++j) {
        if (rr[static_cast<std::size_t>(j)][free_indices[static_cast<std::size_t>(i)]] == zero) continue;
        int dep_pos;
        (void)rr[static_cast<std::size_t>(j)].find_leader_pos(zero, dep_pos);
        T val = rr[static_cast<std::size_t>(j)][free_indices[static_cast<std::size_t>(i)]];
        rbas[static_cast<std::size_t>(i)][dep_pos] = zero - val;
      }
    }
    return true;
  }

  matrix_over paste(const matrix_over& B) const {
    if (get_num_rows() != B.get_num_rows()) {
      throw std::invalid_argument("matrix_over::paste: row count mismatch");
    }
    matrix_over rv(get_num_rows(), get_num_cols() + B.get_num_cols());
    for (int i = 0; i < get_num_rows(); ++i) {
      for (int j = 0; j < get_num_cols(); ++j) {
        rv.rows_[static_cast<std::size_t>(i)][j] = (*this)[static_cast<std::size_t>(i)][j];
      }
      for (int j = 0; j < B.get_num_cols(); ++j) {
        rv.rows_[static_cast<std::size_t>(i)][get_num_cols() + j] = B[static_cast<std::size_t>(i)][j];
      }
    }
    return rv;
  }

  matrix_over paste_vector(const row_type& v) const {
    if (get_num_rows() != v.get_num_elements()) {
      throw std::invalid_argument("matrix_over::paste_vector: row count mismatch");
    }
    matrix_over rv(get_num_rows(), get_num_cols() + 1);
    for (int i = 0; i < get_num_rows(); ++i) {
      for (int j = 0; j < get_num_cols(); ++j) {
        rv.rows_[static_cast<std::size_t>(i)][j] = (*this)[static_cast<std::size_t>(i)][j];
      }
      rv.rows_[static_cast<std::size_t>(i)][get_num_cols()] = v[i];
    }
    return rv;
  }

  void split(matrix_over& rleft, matrix_over& rright, int split_column) const {
    if (split_column < 0 || split_column >= get_num_cols()) {
      throw std::out_of_range("matrix_over::split: split column out of range");
    }
    rleft = matrix_over(get_num_rows(), split_column);
    rright = matrix_over(get_num_rows(), get_num_cols() - split_column);
    for (int i = 0; i < get_num_rows(); ++i) {
      for (int j = 0; j < split_column; ++j) {
        rleft.rows_[static_cast<std::size_t>(i)][j] = (*this)[static_cast<std::size_t>(i)][j];
      }
      for (int j = split_column; j < get_num_cols(); ++j) {
        rright.rows_[static_cast<std::size_t>(i)][j - split_column] = (*this)[static_cast<std::size_t>(i)][j];
      }
    }
  }

  bool inverse(matrix_over& rinv) const {
    if (!is_square()) {
      throw std::invalid_argument("matrix_over::inverse: non-square matrix");
    }
    T zero = (*this)[0][0] - (*this)[0][0];
    T one;
    if (!find_one(one)) return false;
    matrix_over I = make_I(zero, one);
    matrix_over pair = paste(I);
    pair.row_echelon_form();
    matrix_over I_out, rinv_out;
    pair.split(I_out, rinv_out, get_num_cols());
    rinv = rinv_out;
    return I_out.is_I();
  }

  int exp(int power, matrix_over& rout) const {
    if (!is_square()) {
      throw std::invalid_argument("matrix_over::exp: non-square matrix");
    }
    T zero = (*this)[0][0] - (*this)[0][0];
    T one;
    if (!find_one(one)) {
      if (power <= 0) {
        throw std::invalid_argument("matrix_over::exp: non-positive power of zero matrix");
      }
      rout = *this;
      return 1;
    }
    matrix_over I = make_I(zero, one);
    if (power >= 1) {
      matrix_over apower = I;
      matrix_over a2 = *this;
      while (power != 0) {
        if (power & 1) apower = apower * a2;
        power = (unsigned)power >> 1;
        a2 = a2 * a2;
      }
      rout = apower;
      return 1;
    }
    matrix_over ai;
    if (!inverse(ai)) return 0;
    if (power == 0) {
      rout = I;
      return 1;
    }
    if (power == -power) throw std::invalid_argument("matrix_over::exp: can't handle INT_MIN");
    matrix_over apower = I;
    matrix_over a2 = ai;
    int p = -power;
    while (p != 0) {
      if (p & 1) apower = apower * a2;
      p = (unsigned)p >> 1;
      a2 = a2 * a2;
    }
    rout = apower;
    return 1;
  }

  bool solve_unique_full_rank(row_type& x, const row_type& b, const T& zero, const T& one) const {
    int indim = get_num_cols();
    if (get_num_rows() != b.get_num_elements()) {
      return false;
    }
    matrix_over Ab = paste_vector(b);
    Ab.row_echelon_form();
    int Ab_rank = Ab.get_rank_rr();
    if (Ab_rank != indim) return false;
    x = row_type(indim);
    for (int i = 0; i < indim; ++i) {
      x[i] = Ab[static_cast<std::size_t>(i)][indim];
    }
    return true;
  }

  bool solve_unique(row_type& x, const row_type& b, const T& zero, const T& one) const {
    int indim = get_num_cols();
    int outdim = get_num_rows();
    if (indim > outdim) return false;
    if (get_rank() != indim) return false;
    return solve_unique_full_rank(x, b, zero, one);
  }

  matrix_over transpose() const {
    matrix_over rv(get_num_cols(), get_num_rows());
    for (int i = 0; i < get_num_rows(); ++i) {
      for (int j = 0; j < get_num_cols(); ++j) {
        rv.rows_[static_cast<std::size_t>(j)][i] = (*this)[static_cast<std::size_t>(i)][j];
      }
    }
    return rv;
  }

  /// Construct from tmatrix (e.g. companion matrix from linalg).
  matrix_over(const tmatrix<T>& other) : cols_(other.get_num_cols()) {
    int nr = other.get_num_rows();
    rows_.reserve(static_cast<std::size_t>(nr));
    for (int i = 0; i < nr; ++i) {
      row_type row(other.get_num_cols());
      for (int j = 0; j < other.get_num_cols(); ++j) {
        row[j] = other[i][j];
      }
      rows_.push_back(std::move(row));
    }
  }

  /// Assign from tmatrix.
  matrix_over& operator=(const tmatrix<T>& other) {
    cols_ = other.get_num_cols();
    rows_.clear();
    int nr = other.get_num_rows();
    rows_.reserve(static_cast<std::size_t>(nr));
    for (int i = 0; i < nr; ++i) {
      row_type row(other.get_num_cols());
      for (int j = 0; j < other.get_num_cols(); ++j) {
        row[j] = other[i][j];
      }
      rows_.push_back(std::move(row));
    }
    return *this;
  }

  /// Fill with scalar (e.g. set modulus). Sets to 1x1 matrix.
  matrix_over& operator=(const T& scalar) {
    rows_.clear();
    rows_.emplace_back(1, scalar);
    cols_ = 1;
    return *this;
  }

  /// Determinant (field elements). Row-reduces and tracks product of pivots and sign.
  T det() const {
    if (!is_square()) {
      throw std::invalid_argument("matrix_over::det: non-square matrix");
    }
    T zero = (*this)[0][0] - (*this)[0][0];
    T one;
    if (!find_one(one)) return zero;
    matrix_over rr(*this);
    T d = one;
    const int nr = rr.get_num_rows();
    const int nc = rr.get_num_cols();
    int top_row = 0, left_col = 0;
    while (top_row < nr && left_col < nc) {
      int pivot_row = top_row;
      while (pivot_row < nr && rr[static_cast<std::size_t>(pivot_row)][left_col] == zero) ++pivot_row;
      if (pivot_row >= nr) { ++left_col; continue; }
      if (pivot_row != top_row) {
        rr.swap_rows(top_row, pivot_row);
        d = zero - d;
      }
      T pivot = rr[static_cast<std::size_t>(top_row)][left_col];
      if (pivot != zero) {
        d = d * pivot;
        T inv = one / pivot;
        rr[static_cast<std::size_t>(top_row)].mult_by(inv);
        for (int r = top_row + 1; r < nr; ++r) {
          T cur = rr[static_cast<std::size_t>(r)][left_col];
          if (cur != zero) {
            rr[static_cast<std::size_t>(r)].accum_row_mul(pivot, cur, rr[static_cast<std::size_t>(top_row)]);
          }
        }
      }
      ++left_col;
      ++top_row;
    }
    return d;
  }

  /// Scalar operations: add/subtract scalar to diagonal (square matrices only).
  matrix_over operator+(const T& e) const {
    if (!is_square()) {
      throw std::invalid_argument("matrix_over plus scalar: non-square matrix");
    }
    matrix_over rv(*this);
    for (int i = 0; i < get_num_rows(); ++i) {
      rv.rows_[static_cast<std::size_t>(i)][i] = rv.rows_[static_cast<std::size_t>(i)][i] + e;
    }
    return rv;
  }

  matrix_over operator-(const T& e) const {
    if (!is_square()) {
      throw std::invalid_argument("matrix_over minus scalar: non-square matrix");
    }
    matrix_over rv(*this);
    for (int i = 0; i < get_num_rows(); ++i) {
      rv.rows_[static_cast<std::size_t>(i)][i] = rv.rows_[static_cast<std::size_t>(i)][i] - e;
    }
    return rv;
  }

  /// Scalar multiplication: multiply all elements by scalar.
  matrix_over operator*(const T& e) const {
    matrix_over rv(get_num_rows(), get_num_cols());
    for (int i = 0; i < get_num_rows(); ++i) {
      for (int j = 0; j < get_num_cols(); ++j) {
        rv.rows_[static_cast<std::size_t>(i)][j] = (*this)[static_cast<std::size_t>(i)][j] * e;
      }
    }
    return rv;
  }

  matrix_over& operator+=(const T& e) {
    *this = *this + e;
    return *this;
  }

  matrix_over& operator-=(const T& e) {
    *this = *this - e;
    return *this;
  }

  matrix_over& operator*=(const T& e) {
    *this = *this * e;
    return *this;
  }

  /// Euclidean-domain row reduction below diagonal; updates scalar numerator/denominator.
  /// For use with element types satisfying Euclidean_domain (e.g. polynomial rings).
  void ed_row_reduce_below_with_scalar(T& snumer, T& sdenom) {
    T zero = (*this)[0][0] - (*this)[0][0];
    T one;
    if (!find_one(one)) {
      snumer = zero;
      return;
    }
    snumer = one;
    sdenom = one;
    const int nr = get_num_rows();
    const int nc = get_num_cols();
    int top_row = 0, left_column = 0;
    while (top_row < nr && left_column < nc) {
      int pivot_row = top_row;
      int pivot_successful = 0;
      while (!pivot_successful && pivot_row < nr) {
        if ((*this)[static_cast<std::size_t>(pivot_row)][left_column] != zero) {
          if (top_row != pivot_row) {
            swap_rows(top_row, pivot_row);
            snumer = zero - snumer;
          }
          pivot_successful = 1;
        } else {
          ++pivot_row;
        }
      }
      if (!pivot_successful) {
        ++left_column;
        continue;
      }
      row_type& top_row_vec = rows_[static_cast<std::size_t>(top_row)];
      T g = top_row_vec.vgcd();
      if (g != zero) {
        top_row_vec.div_by(g);
        snumer = snumer * g;
      }
      T top_row_lead = top_row_vec[left_column];
      if (top_row_lead != zero) {
        for (int cur_row = top_row + 1; cur_row < nr; ++cur_row) {
          row_type& cur_row_vec = rows_[static_cast<std::size_t>(cur_row)];
          g = cur_row_vec.vgcd();
          if (g != zero) {
            cur_row_vec.div_by(g);
            snumer = snumer * g;
          }
          T current_row_lead = cur_row_vec[left_column];
          T lead_gcd = gcd(top_row_lead, current_row_lead);
          T top_mul = current_row_lead / lead_gcd;
          T cur_mul = top_row_lead / lead_gcd;
          cur_row_vec.accum_row_mul(cur_mul, top_mul, top_row_vec);
          sdenom = sdenom * cur_mul;
          g = cur_row_vec.vgcd();
          if (g != zero) {
            cur_row_vec.div_by(g);
            snumer = snumer * g;
          }
          g = gcd(snumer, sdenom);
          if (g != zero) {
            snumer = snumer / g;
            sdenom = sdenom / g;
          }
        }
      }
      ++left_column;
      ++top_row;
    }
  }

  /// Determinant for Euclidean-domain element types (e.g. polynomial matrices).
  /// Uses fraction-free row reduction; requires T to support gcd, /, %.
  T ed_det() const {
    if (!is_square()) {
      throw std::invalid_argument("matrix_over::ed_det: non-square matrix");
    }
    matrix_over rr(*this);
    T dn, dd;
    rr.ed_row_reduce_below_with_scalar(dn, dd);
    for (int i = 0; i < get_num_rows(); ++i) {
      dn = dn * rr[static_cast<std::size_t>(i)][i];
    }
    T zero = dn - dn;
    T rem = dn % dd;
    T quot = dn / dd;
    if (rem != zero) {
      std::stringstream ss;
      ss << "matrix_over::ed_det: coding error: dd must divide dn. Got " << dn << " % " << dd << " = " << rem;
      throw std::runtime_error(ss.str());
    }
    return quot;
  }

  /// Parse "[[r1] [r2] ...]" or "[c1 c2 ...]". *this must already have one element.
  bool bracket_in(char* string) {
    if (rows_.empty() || cols_ < 1) return false;
    T zero = rows_[0][0] - rows_[0][0];
    char* copy = strdup(string);
    char* pouterleft = strchr(copy, '[');
    if (!pouterleft) { free(copy); return false; }
    char* pinner = pouterleft + 1;
    while (*pinner == ' ' || *pinner == '\t') ++pinner;
    char* pouterright = strrchr(pouterleft, ']');
    if (!pouterright) { free(copy); return false; }
    *pouterright = '\0';

    if (strchr(pinner, '[')) {
      int num_rows = spffl::base::count_tokens(pinner, "[");
      if (num_rows <= 0) { free(copy); return false; }
      std::vector<char*> row_strs(static_cast<std::size_t>(num_rows), nullptr);
      if (spffl::base::tokenize(pinner, "[", row_strs.data(), num_rows) != num_rows) { free(copy); return false; }
      rows_.clear();
      cols_ = 0;
      for (int i = 0; i < num_rows; ++i) {
        char rowcopy[2048];
        std::snprintf(rowcopy, sizeof(rowcopy), "[%s]", row_strs[static_cast<std::size_t>(i)]);
        row_type row(1, zero);
        if (!row.bracket_in(rowcopy)) { free(copy); return false; }
        if (i == 0) cols_ = row.get_num_elements();
        else if (row.get_num_elements() != cols_) { free(copy); return false; }
        rows_.push_back(std::move(row));
      }
    } else {
      row_type col(1, zero);
      std::istringstream iss(pinner, std::ios_base::in);
      iss >> col;
      if (iss.fail() || col.get_num_elements() == 0) { free(copy); return false; }
      rows_.clear();
      cols_ = 1;
      for (int i = 0; i < col.get_num_elements(); ++i) {
        rows_.emplace_back(1);
        rows_.back()[0] = col[i];
      }
    }
    free(copy);
    return true;
  }

  bool load_from_file(char* file_name) {
    if (strcmp(file_name, "-") == 0 || strcmp(file_name, "@") == 0) {
      if (rows_.empty()) return false;
      std::cin >> *this;
      return !std::cin.fail();
    }
    std::ifstream ifs(file_name);
    if (!ifs) return false;
    if (rows_.empty()) return false;
    T zero = rows_[0][0] - rows_[0][0];
    rows_.clear();
    cols_ = 0;
    std::string line;
    while (std::getline(ifs, line)) {
      char* phash = strchr(const_cast<char*>(line.c_str()), '#');
      if (phash) *phash = '\0';
      while (!line.empty() && (line.back() == ' ' || line.back() == '\t')) line.pop_back();
      size_t start = line.find_first_not_of(" \t");
      if (start == std::string::npos) {
        if (rows_.empty()) continue;
        break;
      }
      line = line.substr(start);
      if (line.empty() && !rows_.empty()) break;
      row_type row(1, zero);
      std::istringstream iss(line, std::ios_base::in);
      iss >> row;
      if (iss.fail()) { ifs.close(); return false; }
      if (cols_ == 0) cols_ = row.get_num_elements();
      else if (row.get_num_elements() != cols_) { ifs.close(); return false; }
      rows_.push_back(std::move(row));
    }
    ifs.close();
    return !rows_.empty();
  }

  bool load_from_file(char* file_name, const T& zero) {
    rows_.clear();
    rows_.emplace_back(1, zero);
    cols_ = 1;
    return load_from_file(file_name);
  }

  void check_inverse(matrix_over& rinv) const {
    matrix_over AB = *this * rinv;
    matrix_over BA = rinv * *this;
    if (!AB.is_I() || !BA.is_I()) {
      throw std::runtime_error("matrix_over::check_inverse: not really inverses");
    }
  }

  void check_kernel_basis(const matrix_over& kerbas) const {
    T zero = (*this)[0][0] - (*this)[0][0];
    row_type zerov(get_num_rows(), zero);
    for (int i = 0; i < kerbas.get_num_rows(); ++i) {
      row_type Av = (*this) * kerbas[static_cast<std::size_t>(i)];
      if (Av != zerov) {
        throw std::runtime_error("matrix_over::check_kernel_basis: coding error in kernel basis");
      }
    }
  }

  matrix_over flip_horiz() const {
    matrix_over rv(get_num_rows(), get_num_cols());
    int nc = get_num_cols();
    for (int i = 0; i < get_num_rows(); ++i) {
      for (int j = 0; j < nc; ++j) {
        rv.rows_[static_cast<std::size_t>(i)][j] = (*this)[static_cast<std::size_t>(i)][nc - 1 - j];
      }
    }
    return rv;
  }

  matrix_over flip_horiz_vert() const {
    matrix_over rv(get_num_rows(), get_num_cols());
    int nr = get_num_rows();
    int nc = get_num_cols();
    for (int i = 0; i < nr; ++i) {
      for (int j = 0; j < nc; ++j) {
        rv.rows_[static_cast<std::size_t>(i)][j] = (*this)[static_cast<std::size_t>(nr - 1 - i)][nc - 1 - j];
      }
    }
    return rv;
  }

  bool get_rr_non_zero_rows(matrix_over& rrnz) const {
    matrix_over rr(*this);
    rr.row_reduce_below();
    int rank = rr.get_rank_rr();
    if (rank == 0) return false;
    rrnz = matrix_over(rank, get_num_cols());
    for (int i = 0; i < rank; ++i) {
      rrnz.rows_[static_cast<std::size_t>(i)] = rr.rows_[static_cast<std::size_t>(i)];
    }
    return true;
  }

  bool get_rech_non_zero_rows(matrix_over& rechnz) const {
    matrix_over rech(*this);
    rech.row_echelon_form();
    int rank = rech.get_rank_rr();
    if (rank == 0) return false;
    rechnz = matrix_over(rank, get_num_cols());
    for (int i = 0; i < rank; ++i) {
      rechnz.rows_[static_cast<std::size_t>(i)] = rech.rows_[static_cast<std::size_t>(i)];
    }
    return true;
  }

  friend std::ostream& operator<<(std::ostream& os, const matrix_over& A) {
    for (int i = 0; i < A.get_num_rows(); ++i) {
      for (int j = 0; j < A.get_num_cols(); ++j) {
        if (j > 0) os << " ";
        os << A[static_cast<std::size_t>(i)][j];
      }
      if (i + 1 < A.get_num_rows()) os << "\n";
    }
    return os;
  }

  friend std::istream& operator>>(std::istream& is, matrix_over& A) {
    if (A.rows_.empty() || A.cols_ < 1) { is.setstate(std::ios::failbit); return is; }
    T zero = A.rows_[0][0] - A.rows_[0][0];
    A.rows_.clear();
    A.cols_ = 0;
    std::string line;
    while (std::getline(is, line)) {
      char* phash = strchr(const_cast<char*>(line.c_str()), '#');
      if (phash) *phash = '\0';
      while (!line.empty() && (line.back() == ' ' || line.back() == '\t')) line.pop_back();
      size_t start = line.find_first_not_of(" \t");
      if (start == std::string::npos) {
        if (A.rows_.empty()) continue;
        break;
      }
      line = line.substr(start);
      if (line.empty() && !A.rows_.empty()) break;
      row_type row(1, zero);
      std::istringstream iss(line, std::ios_base::in);
      iss >> row;
      if (iss.fail()) { is.setstate(std::ios::failbit); return is; }
      if (A.cols_ == 0) A.cols_ = row.get_num_elements();
      else if (row.get_num_elements() != A.cols_) { is.setstate(std::ios::failbit); return is; }
      A.rows_.push_back(std::move(row));
    }
    return is;
  }

private:
  std::vector<row_type> rows_;
  int cols_;

  void check_same_shape(const matrix_over& B) const {
    if (get_num_rows() != B.get_num_rows() || get_num_cols() != B.get_num_cols()) {
      throw std::invalid_argument("matrix_over: shape mismatch");
    }
  }
};

}  // namespace spffl::containers

#endif  // SPFFL_CONTAINERS_MATRIX_OVER_H
