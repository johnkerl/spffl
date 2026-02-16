// ================================================================
// STL-based matrix over a ring element. Satisfies Matrix_over<M, T>.
// Rows are vector_over<T>; A[i] is row i.
// ================================================================

#ifndef SPFFL_CONTAINERS_MATRIX_OVER_HPP
#define SPFFL_CONTAINERS_MATRIX_OVER_HPP

#include "spffl/concepts.hpp"
#include "spffl/containers/vector_over.hpp"
#include <vector>
#include <stdexcept>
#include <ostream>

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

#endif  // SPFFL_CONTAINERS_MATRIX_OVER_HPP
