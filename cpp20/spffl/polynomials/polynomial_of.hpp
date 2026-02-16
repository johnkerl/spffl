// ================================================================
// C++20 template sketch: generic polynomial over a coefficient ring.
// This is a header-only implementation intended for the cpp20 port.
// API is modeled after the existing fp_poly_t / f2n_poly_t / fpn_poly_t.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_POLYNOMIAL_OF_HPP
#define SPFFL_POLYNOMIALS_POLYNOMIAL_OF_HPP

#include <vector>
#include <ostream>
#include <istream>
#include <sstream>
#include <stdexcept>

#include "spffl/concepts.hpp"

namespace spffl::polynomials {

template <typename Coeff>
class polynomial_of {
  static_assert(spffl::concepts::Ring_element<Coeff>,
      "Coeff must satisfy Ring_element concept.");

public:
  using coeff_type = Coeff;

  // ------------------------------------------------------------
  // ctors
  // ------------------------------------------------------------

  polynomial_of() : coeffs_{Coeff{}} {}

  explicit polynomial_of(const Coeff &c0) : coeffs_{c0} { trim_degree(); }

  polynomial_of(const Coeff &c1, const Coeff &c0) : coeffs_{c0, c1} {
    trim_degree();
  }

  polynomial_of(const Coeff &c2, const Coeff &c1, const Coeff &c0)
      : coeffs_{c0, c1, c2} {
    trim_degree();
  }

  // Generic constructor from coefficient vector (lowest degree first).
  explicit polynomial_of(std::vector<Coeff> coeffs) : coeffs_(std::move(coeffs)) {
    if (coeffs_.empty()) {
      coeffs_.push_back(Coeff{});
    }
    trim_degree();
  }

  // ------------------------------------------------------------
  // basic queries
  // ------------------------------------------------------------

  int find_degree() const { return static_cast<int>(coeffs_.size()) - 1; }

  const Coeff &get_coeff(int deg) const {
    if (deg < 0 || deg >= static_cast<int>(coeffs_.size())) {
      static const Coeff zero = Coeff{} - Coeff{};
      return zero;
    }
    return coeffs_[static_cast<std::size_t>(deg)];
  }

  void set_coeff(int deg, const Coeff &c) {
    if (deg < 0) {
      throw std::out_of_range("polynomial_of::set_coeff: negative degree");
    }
    auto udeg = static_cast<std::size_t>(deg);
    if (udeg >= coeffs_.size()) {
      coeffs_.resize(udeg + 1, Coeff{} - Coeff{});
    }
    coeffs_[udeg] = c;
    trim_degree();
  }

  // ------------------------------------------------------------
  // arithmetic
  // ------------------------------------------------------------

  polynomial_of operator+(const polynomial_of &that) const {
    std::size_t max_deg = std::max(coeffs_.size(), that.coeffs_.size());
    std::vector<Coeff> out(max_deg, Coeff{} - Coeff{});
    for (std::size_t i = 0; i < max_deg; ++i) {
      Coeff a = (i < coeffs_.size()) ? coeffs_[i] : Coeff{} - Coeff{};
      Coeff b = (i < that.coeffs_.size()) ? that.coeffs_[i] : Coeff{} - Coeff{};
      out[i]  = a + b;
    }
    return polynomial_of(std::move(out));
  }

  polynomial_of operator-(const polynomial_of &that) const {
    std::size_t max_deg = std::max(coeffs_.size(), that.coeffs_.size());
    std::vector<Coeff> out(max_deg, Coeff{} - Coeff{});
    for (std::size_t i = 0; i < max_deg; ++i) {
      Coeff a = (i < coeffs_.size()) ? coeffs_[i] : Coeff{} - Coeff{};
      Coeff b = (i < that.coeffs_.size()) ? that.coeffs_[i] : Coeff{} - Coeff{};
      out[i]  = a - b;
    }
    return polynomial_of(std::move(out));
  }

  polynomial_of operator-() const {
    std::vector<Coeff> out(coeffs_.size());
    for (std::size_t i = 0; i < coeffs_.size(); ++i) {
      out[i] = -coeffs_[i];
    }
    return polynomial_of(std::move(out));
  }

  polynomial_of &operator+=(const polynomial_of &that) {
    *this = *this + that;
    return *this;
  }

  polynomial_of &operator-=(const polynomial_of &that) {
    *this = *this - that;
    return *this;
  }

  polynomial_of operator*(const polynomial_of &that) const {
    int deg_a = find_degree();
    int deg_b = that.find_degree();
    if ((deg_a == 0) && (coeffs_[0] == Coeff{} - Coeff{}) ||
        (deg_b == 0) && (that.coeffs_[0] == Coeff{} - Coeff{})) {
      return polynomial_of{}; // zero
    }

    std::size_t out_deg = static_cast<std::size_t>(deg_a + deg_b);
    std::vector<Coeff> out(out_deg + 1, Coeff{} - Coeff{});

    for (int i = 0; i <= deg_a; ++i) {
      for (int j = 0; j <= deg_b; ++j) {
        out[static_cast<std::size_t>(i + j)] +=
            coeffs_[static_cast<std::size_t>(i)] *
            that.coeffs_[static_cast<std::size_t>(j)];
      }
    }
    return polynomial_of(std::move(out));
  }

  polynomial_of &operator*=(const polynomial_of &that) {
    *this = *this * that;
    return *this;
  }

  // scalar multiply (Coeff)
  polynomial_of operator*(const Coeff &s) const {
    std::vector<Coeff> out(coeffs_.size());
    for (std::size_t i = 0; i < coeffs_.size(); ++i) {
      out[i] = coeffs_[i] * s;
    }
    return polynomial_of(std::move(out));
  }

  polynomial_of &operator*=(const Coeff &s) {
    for (auto &c : coeffs_) {
      c *= s;
    }
    trim_degree();
    return *this;
  }

  // ------------------------------------------------------------
  // comparison (lexicographic on degree, then coefficients)
  // ------------------------------------------------------------

  bool operator==(const polynomial_of &that) const {
    if (find_degree() != that.find_degree()) {
      return false;
    }
    int d = find_degree();
    for (int i = 0; i <= d; ++i) {
      if (coeffs_[static_cast<std::size_t>(i)] !=
          that.coeffs_[static_cast<std::size_t>(i)]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const polynomial_of &that) const { return !(*this == that); }

  // Simple lex order on coefficient vector (useful for maps/sorting).
  bool operator<(const polynomial_of &that) const {
    int da = find_degree();
    int db = that.find_degree();
    if (da != db) {
      return da < db;
    }
    for (int i = db; i >= 0; --i) {
      const auto &a = coeffs_[static_cast<std::size_t>(i)];
      const auto &b = that.coeffs_[static_cast<std::size_t>(i)];
      if (a < b) {
        return true;
      } else if (b < a) {
        return false;
      }
    }
    return false;
  }

  bool operator>(const polynomial_of &that) const { return that < *this; }
  bool operator<=(const polynomial_of &that) const { return !(*this > that); }
  bool operator>=(const polynomial_of &that) const { return !(*this < that); }

  // ------------------------------------------------------------
  // evaluation
  // ------------------------------------------------------------

  template <typename X>
  X eval(const X &x) const {
    // Horner's method.
    int d = find_degree();
    if (d < 0) {
      return X{}; // shouldn't happen; degree >= 0 by construction.
    }
    X result = static_cast<X>(coeffs_[static_cast<std::size_t>(d)]);
    for (int i = d - 1; i >= 0; --i) {
      result = result * x +
               static_cast<X>(coeffs_[static_cast<std::size_t>(i)]);
    }
    return result;
  }

  // ------------------------------------------------------------
  // I/O helpers (very simple; not matching legacy syntax yet)
  // ------------------------------------------------------------

  friend std::ostream &operator<<(std::ostream &os, const polynomial_of &p) {
    int d = p.find_degree();
    bool first = true;
    for (int i = d; i >= 0; --i) {
      const auto &c = p.coeffs_[static_cast<std::size_t>(i)];
      if (c == (Coeff{} - Coeff{})) {
        continue;
      }
      if (!first) {
        os << " + ";
      }
      first = false;
      os << c;
      if (i > 0) {
        os << "*x";
        if (i > 1) {
          os << "^" << i;
        }
      }
    }
    if (first) {
      // All coefficients were zero.
      os << (Coeff{} - Coeff{});
    }
    return os;
  }

private:
  std::vector<Coeff> coeffs_; // coeffs_[i] is coefficient of x^i

  void trim_degree() {
    Coeff zero = Coeff{} - Coeff{};
    while (coeffs_.size() > 1 &&
           coeffs_.back() == zero) {
      coeffs_.pop_back();
    }
  }
};

} // namespace spffl::polynomials

#endif // SPFFL_POLYNOMIALS_POLYNOMIAL_OF_HPP

