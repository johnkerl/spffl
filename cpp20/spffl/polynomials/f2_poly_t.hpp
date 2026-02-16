// ================================================================
// Minimal F2[x] (polynomials over F2) with bit-packed storage.
// Models Polynomial_ring_element and Polynomial_with_ext_gcd.
// C++20 port; independent of legacy spffl bits/.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_F2_POLY_T_HPP
#define SPFFL_POLYNOMIALS_F2_POLY_T_HPP

#include "spffl/concepts.hpp"
#include <cstdint>
#include <optional>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <cctype>
#include <vector>

namespace spffl::polynomials {

class f2_poly_t {
public:
  f2_poly_t() = default;

  explicit f2_poly_t(int c0) {
    if (c0 & 1) {
      parts_.push_back(1);
    }
  }

  f2_poly_t(int c1, int c0) {
    std::uint64_t w = (c0 & 1) | (static_cast<std::uint64_t>(c1 & 1) << 1);
    if (w) {
      parts_.push_back(w);
    }
  }

  f2_poly_t(int c2, int c1, int c0) {
    std::uint64_t w = (c0 & 1) | (static_cast<std::uint64_t>(c1 & 1) << 1) |
                      (static_cast<std::uint64_t>(c2 & 1) << 2);
    if (w) {
      parts_.push_back(w);
    }
  }

  int find_degree() const {
    if (parts_.empty()) return 0;
    int w = static_cast<int>(parts_.size()) - 1;
    std::uint64_t v = parts_[static_cast<std::size_t>(w)];
    if (v == 0) return 0;
    int d = w * 64;
    while (v) {
      d++;
      v >>= 1;
    }
    return d - 1;
  }

  int get_coeff(int i) const {
    if (i < 0) return 0;
    std::size_t word = static_cast<std::size_t>(i / 64);
    if (word >= parts_.size()) return 0;
    return (parts_[word] >> (i % 64)) & 1;
  }

  void set_coeff(int i, int c) {
    if (i < 0) return;
    std::size_t word = static_cast<std::size_t>(i / 64);
    if (word >= parts_.size()) {
      parts_.resize(word + 1, 0);
    }
    std::uint64_t mask = std::uint64_t(1) << (i % 64);
    if (c & 1) {
      parts_[word] |= mask;
    } else {
      parts_[word] &= ~mask;
    }
    trim();
  }

  bool is_zero() const {
    return parts_.empty();
  }

  /// Multiplicative identity (for residue_of<f2_poly_t>::exp, etc.).
  static f2_poly_t one(const f2_poly_t&) { return f2_poly_t(1); }

  f2_poly_t operator+(const f2_poly_t& that) const {
    f2_poly_t r;
    std::size_t n = std::max(parts_.size(), that.parts_.size());
    r.parts_.resize(n, 0);
    for (std::size_t i = 0; i < parts_.size(); ++i) r.parts_[i] ^= parts_[i];
    for (std::size_t i = 0; i < that.parts_.size(); ++i) r.parts_[i] ^= that.parts_[i];
    r.trim();
    return r;
  }

  f2_poly_t operator-(const f2_poly_t& that) const { return *this + that; }
  f2_poly_t operator-() const { return *this; }

  f2_poly_t& operator+=(const f2_poly_t& that) { *this = *this + that; return *this; }
  f2_poly_t& operator-=(const f2_poly_t& that) { *this = *this + that; return *this; }

  f2_poly_t operator*(const f2_poly_t& that) const {
    if (is_zero() || that.is_zero()) return f2_poly_t();
    int da = find_degree();
    int db = that.find_degree();
    f2_poly_t r;
    for (int i = 0; i <= da; ++i) {
      if (get_coeff(i)) {
        for (int j = 0; j <= db; ++j) {
          if (that.get_coeff(j)) {
            int k = i + j;
            r.set_coeff(k, r.get_coeff(k) ^ 1);
          }
        }
      }
    }
    return r;
  }

  f2_poly_t& operator*=(const f2_poly_t& that) { *this = *this * that; return *this; }

  void quot_and_rem(const f2_poly_t& that, f2_poly_t& q, f2_poly_t& r) const {
    if (that.is_zero()) {
      throw std::invalid_argument("f2_poly_t::quot_and_rem: division by zero");
    }
    q = f2_poly_t();
    r = *this;
    int dd = that.find_degree();
    while (!r.is_zero() && r.find_degree() >= dd) {
      int dr = r.find_degree();
      int shift = dr - dd;
      q.set_coeff(shift, 1);
      for (int i = 0; i <= dd; ++i) {
        if (that.get_coeff(i)) {
          r.set_coeff(i + shift, r.get_coeff(i + shift) ^ 1);
        }
      }
    }
  }

  f2_poly_t gcd(const f2_poly_t& that) const {
    if (is_zero()) return that;
    if (that.is_zero()) return *this;
    f2_poly_t a(*this), b(that);
    f2_poly_t q, r;
    while (true) {
      a.quot_and_rem(b, q, r);
      if (r.is_zero()) return b;
      a = b;
      b = r;
    }
  }

  f2_poly_t ext_gcd(const f2_poly_t& that, f2_poly_t& rm, f2_poly_t& rn) const {
    if (that.is_zero()) {
      rm = f2_poly_t(1);
      rn = f2_poly_t();
      return *this;
    }
    f2_poly_t q, r;
    quot_and_rem(that, q, r);
    if (r.is_zero()) {
      rm = f2_poly_t();
      rn = f2_poly_t(1);
      return that;
    }
    f2_poly_t m1, n1;
    f2_poly_t g = that.ext_gcd(r, m1, n1);
    rm = n1;
    rn = m1 + q * n1;
    return g;
  }

  f2_poly_t exp(int e) const {
    if (e < 0) {
      throw std::invalid_argument("f2_poly_t::exp: negative exponent");
    }
    if (e == 0) return f2_poly_t(1);
    f2_poly_t base(*this);
    f2_poly_t result(1);
    while (e) {
      if (e & 1) result = result * base;
      e = static_cast<unsigned>(e) >> 1;
      base = base * base;
    }
    return result;
  }

  f2_poly_t deriv() const {
    f2_poly_t r;
    int d = find_degree();
    for (int i = 1; i <= d; ++i) {
      if (i & 1) r.set_coeff(i - 1, get_coeff(i));
    }
    return r;
  }

  bool operator==(const f2_poly_t& that) const { return parts_ == that.parts_; }
  bool operator!=(const f2_poly_t& that) const { return !(*this == that); }

  bool operator<(const f2_poly_t& that) const {
    int da = find_degree(), db = that.find_degree();
    if (da != db) return da < db;
    for (int i = da; i >= 0; --i) {
      int a = get_coeff(i), b = that.get_coeff(i);
      if (a != b) return a < b;
    }
    return false;
  }

  friend std::ostream& operator<<(std::ostream& os, const f2_poly_t& p) {
    int d = p.find_degree();
    if (d == 0 && p.get_coeff(0) == 0) { os << "0"; return os; }
    for (int i = d; i >= 0; --i) {
      if (p.get_coeff(i)) {
        if (i < d) os << "+";
        if (i == 0) os << "1";
        else if (i == 1) os << "x";
        else os << "x^" << i;
      }
    }
    return os;
  }

  /// Parse comma-separated 0/1 (leading coefficient first). Returns nullopt on error.
  static std::optional<f2_poly_t> from_string(const std::string& s) {
    std::istringstream iss(s);
    std::string token;
    std::vector<int> coeffs;
    while (std::getline(iss, token, ',')) {
      while (!token.empty() && std::isspace(static_cast<unsigned char>(token.front())))
        token.erase(0, 1);
      while (!token.empty() && std::isspace(static_cast<unsigned char>(token.back())))
        token.pop_back();
      if (token.empty()) return std::nullopt;
      if (token.size() != 1 || (token[0] != '0' && token[0] != '1'))
        return std::nullopt;
      coeffs.push_back(token[0] - '0');
    }
    if (coeffs.empty()) return std::nullopt;
    int degree = static_cast<int>(coeffs.size()) - 1;
    f2_poly_t p;
    for (int i = 0; i <= degree; ++i)
      p.set_coeff(degree - i, coeffs[static_cast<std::size_t>(i)]);
    return p;
  }

  friend std::istream& operator>>(std::istream& is, f2_poly_t& p) {
    std::string line;
    if (!std::getline(is, line)) return is;
    auto opt = f2_poly_t::from_string(line);
    if (!opt) {
      is.setstate(std::ios::failbit);
      return is;
    }
    p = std::move(*opt);
    return is;
  }

private:
  std::vector<std::uint64_t> parts_;

  void trim() {
    while (!parts_.empty() && parts_.back() == 0) {
      parts_.pop_back();
    }
  }
};

}  // namespace spffl::polynomials

#endif  // SPFFL_POLYNOMIALS_F2_POLY_T_HPP
