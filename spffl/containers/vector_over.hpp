// ================================================================
// STL-based vector over a ring element. Satisfies Vector_over<V, T>.
// Minimal C++20 version for cpp20 port.
// ================================================================

#ifndef SPFFL_CONTAINERS_VECTOR_OVER_HPP
#define SPFFL_CONTAINERS_VECTOR_OVER_HPP

#include "spffl/concepts.hpp"
#include <vector>
#include <stdexcept>
#include <ostream>

namespace spffl::containers {

template <typename T>
  requires spffl::concepts::Ring_element<T>
class vector_over {
public:
  using element_type = T;

  vector_over() = default;

  explicit vector_over(int n) : data_(static_cast<std::size_t>(n)) {
    if (n < 0) {
      throw std::invalid_argument("vector_over: negative size");
    }
  }

  vector_over(int n, const T& value) : data_(static_cast<std::size_t>(n), value) {
    if (n < 0) {
      throw std::invalid_argument("vector_over: negative size");
    }
  }

  template <typename It>
  vector_over(It first, It last) : data_(first, last) {}

  T& operator[](int i) {
    bounds_check(i);
    return data_[static_cast<std::size_t>(i)];
  }

  const T& operator[](int i) const {
    bounds_check(i);
    return data_[static_cast<std::size_t>(i)];
  }

  int get_num_elements() const {
    return static_cast<int>(data_.size());
  }

  vector_over operator+(const vector_over& that) const {
    check_equal_lengths(that);
    vector_over out(get_num_elements());
    for (int i = 0; i < get_num_elements(); ++i) {
      out[i] = (*this)[i] + that[i];
    }
    return out;
  }

  vector_over operator-(const vector_over& that) const {
    check_equal_lengths(that);
    vector_over out(get_num_elements());
    for (int i = 0; i < get_num_elements(); ++i) {
      out[i] = (*this)[i] - that[i];
    }
    return out;
  }

  vector_over operator-() const {
    vector_over out(get_num_elements());
    for (int i = 0; i < get_num_elements(); ++i) {
      out[i] = -(*this)[i];
    }
    return out;
  }

  vector_over operator*(const T& s) const {
    vector_over out(get_num_elements());
    for (int i = 0; i < get_num_elements(); ++i) {
      out[i] = (*this)[i] * s;
    }
    return out;
  }

  T dot(const vector_over& that) const {
    check_equal_lengths(that);
    if (get_num_elements() == 0) {
      throw std::runtime_error("vector_over::dot: zero length");
    }
    T acc = (*this)[0] - (*this)[0];  // zero
    for (int i = 0; i < get_num_elements(); ++i) {
      acc = acc + (*this)[i] * that[i];
    }
    return acc;
  }

  bool operator==(const vector_over& that) const {
    if (get_num_elements() != that.get_num_elements()) {
      return false;
    }
    for (int i = 0; i < get_num_elements(); ++i) {
      if ((*this)[i] != that[i]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const vector_over& that) const {
    return !(*this == that);
  }

  friend std::ostream& operator<<(std::ostream& os, const vector_over& v) {
    for (int i = 0; i < v.get_num_elements(); ++i) {
      if (i > 0) os << " ";
      os << v[i];
    }
    return os;
  }

private:
  std::vector<T> data_;

  void bounds_check(int i) const {
    if (i < 0 || i >= get_num_elements()) {
      throw std::out_of_range("vector_over: index out of range");
    }
  }

  void check_equal_lengths(const vector_over& that) const {
    if (get_num_elements() != that.get_num_elements()) {
      throw std::invalid_argument("vector_over: size mismatch");
    }
  }
};

}  // namespace spffl::containers

#endif  // SPFFL_CONTAINERS_VECTOR_OVER_HPP
