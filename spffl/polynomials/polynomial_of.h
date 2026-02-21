// ================================================================
// C++20 template sketch: generic polynomial over a coefficient ring.
// This is a header-only implementation intended for the cpp20 port.
// API is modeled after the existing fp_poly_t / f2n_poly_t / fpn_poly_t.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_POLYNOMIAL_OF_H
#define SPFFL_POLYNOMIALS_POLYNOMIAL_OF_H

#include <vector>
#include <ostream>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

#include "spffl/concepts.h"
#include "spffl/intmath/intmod_t.h"

namespace spffl::polynomials {

template <typename Coeff> class polynomial_of {
  static_assert(spffl::concepts::Ring_element<Coeff>, "Coeff must satisfy Ring_element concept.");

  public:
  using coeff_type = Coeff;

  // ------------------------------------------------------------
  // ctors
  // ------------------------------------------------------------

  polynomial_of() : coeffs_{Coeff{}} {}

  explicit polynomial_of(const Coeff &c0) : coeffs_{c0} { trim_degree(); }

  polynomial_of(const Coeff &c1, const Coeff &c0) : coeffs_{c0, c1} { trim_degree(); }

  polynomial_of(const Coeff &c2, const Coeff &c1, const Coeff &c0) : coeffs_{c0, c1, c2} {
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

  Coeff get_coeff(int deg) const {
    if (deg < 0 || deg >= static_cast<int>(coeffs_.size())) {
      return zero_coeff();
    }
    return coeffs_[static_cast<std::size_t>(deg)];
  }

  void set_coeff(int deg, const Coeff &c) {
    if (deg < 0) {
      throw std::out_of_range("polynomial_of::set_coeff: negative degree");
    }
    auto udeg = static_cast<std::size_t>(deg);
    if (udeg >= coeffs_.size()) {
      coeffs_.resize(udeg + 1, zero_coeff());
    }
    coeffs_[udeg] = c;
    trim_degree();
  }

  // Legacy compat: characteristic of coefficient ring.
  // When Coeff has get_modulus() returning int (e.g. intmod_t).
  int get_characteristic() const
    requires spffl::concepts::has_get_modulus_v<Coeff> &&
             std::convertible_to<decltype(std::declval<Coeff const &>().get_modulus()), int>
  {
    return coeffs_[0].get_modulus();
  }

  // When Coeff has get_characteristic() (e.g. fp_polymod_t, residue_of<f2_poly_t>).
  int get_characteristic() const
    requires spffl::concepts::has_get_characteristic_v<Coeff>
  {
    return coeffs_[0].get_characteristic();
  }

  // Legacy compat: constant polynomial with single coefficient v in prime subfield.
  polynomial_of prime_subfield_element(int v) const
    requires spffl::concepts::Field_element<Coeff> && spffl::concepts::has_get_modulus_v<Coeff>
  {
    return polynomial_of(Coeff(v, get_characteristic()));
  }

  // When Coeff is e.g. fp_polymod_t: construct from (intmod_t(v,p), modulus).
  polynomial_of prime_subfield_element(int v) const
    requires spffl::concepts::Field_element<Coeff> &&
             spffl::concepts::has_get_characteristic_v<Coeff> &&
             spffl::concepts::has_get_modulus_v<Coeff> &&
             std::constructible_from<Coeff, spffl::intmath::intmod_t,
               decltype(std::declval<Coeff const &>().get_modulus())>
  {
    return polynomial_of(
      Coeff(spffl::intmath::intmod_t(v, get_characteristic()), coeffs_[0].get_modulus()));
  }

  // ------------------------------------------------------------
  // arithmetic
  // ------------------------------------------------------------

  polynomial_of operator+(const polynomial_of &that) const {
    Coeff z = zero_coeff();
    std::size_t max_deg = std::max(coeffs_.size(), that.coeffs_.size());
    std::vector<Coeff> out(max_deg, z);
    for (std::size_t i = 0; i < max_deg; ++i) {
      Coeff a = (i < coeffs_.size()) ? coeffs_[i] : z;
      Coeff b = (i < that.coeffs_.size()) ? that.coeffs_[i] : z;
      out[i] = a + b;
    }
    return polynomial_of(std::move(out));
  }

  polynomial_of operator-(const polynomial_of &that) const {
    Coeff z = zero_coeff();
    std::size_t max_deg = std::max(coeffs_.size(), that.coeffs_.size());
    std::vector<Coeff> out(max_deg, z);
    for (std::size_t i = 0; i < max_deg; ++i) {
      Coeff a = (i < coeffs_.size()) ? coeffs_[i] : z;
      Coeff b = (i < that.coeffs_.size()) ? that.coeffs_[i] : z;
      out[i] = a - b;
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
    Coeff z = zero_coeff();
    if (((deg_a == 0) && (coeffs_[0] == z)) || ((deg_b == 0) && (that.coeffs_[0] == z))) {
      return polynomial_of(std::vector<Coeff>{z});
    }

    std::size_t out_deg = static_cast<std::size_t>(deg_a + deg_b);
    std::vector<Coeff> out(out_deg + 1, z);

    for (int i = 0; i <= deg_a; ++i) {
      for (int j = 0; j <= deg_b; ++j) {
        out[static_cast<std::size_t>(i + j)] +=
          coeffs_[static_cast<std::size_t>(i)] * that.coeffs_[static_cast<std::size_t>(j)];
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

  /// Scalar division (multiply by inverse of s). Legacy compat.
  polynomial_of &operator/=(const Coeff &s)
    requires spffl::concepts::Field_element<Coeff>
  {
    Coeff inv;
    if (!s.recip(inv)) {
      throw std::runtime_error("polynomial_of::operator/=: non-invertible scalar");
    }
    return *this *= inv;
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
      if (coeffs_[static_cast<std::size_t>(i)] != that.coeffs_[static_cast<std::size_t>(i)]) {
        return false;
      }
    }
    return true;
  }

  bool operator!=(const polynomial_of &that) const { return !(*this == that); }

  /// Legacy compat: compare to constant polynomial (int as residue mod get_characteristic()).
  bool operator==(int v) const
    requires spffl::concepts::has_get_modulus_v<Coeff>
  {
    return find_degree() == 0 && get_coeff(0) == Coeff(v, get_characteristic());
  }
  bool operator!=(int v) const
    requires spffl::concepts::has_get_modulus_v<Coeff>
  {
    return !(*this == v);
  }

  /// Compare to constant polynomial (single coefficient).
  bool operator==(const Coeff &c) const { return find_degree() == 0 && get_coeff(0) == c; }
  bool operator!=(const Coeff &c) const { return !(*this == c); }

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

  template <typename X> X eval(const X &x) const {
    // Horner's method.
    int d = find_degree();
    if (d < 0) {
      return X{}; // shouldn't happen; degree >= 0 by construction.
    }
    X result = static_cast<X>(coeffs_[static_cast<std::size_t>(d)]);
    for (int i = d - 1; i >= 0; --i) {
      result = result * x + static_cast<X>(coeffs_[static_cast<std::size_t>(i)]);
    }
    return result;
  }

  // ------------------------------------------------------------
  // Euclidean-division-style operations
  // (only for coefficient types modeling Field_element)
  // ------------------------------------------------------------

  bool is_zero() const {
    Coeff z = zero_coeff();
    return find_degree() == 0 && coeffs_[0] == z;
  }

  void quot_and_rem(const polynomial_of &that, polynomial_of &rquot, polynomial_of &rrem) const
    requires spffl::concepts::Field_element<Coeff>
  {
    Coeff zero = zero_coeff();

    if (that.is_zero()) {
      throw std::runtime_error("polynomial_of::quot_and_rem: division by zero");
    }
    if (this->is_zero()) {
      rquot = polynomial_of(zero);
      rrem = *this;
      return;
    }

    int dividend_degree = this->find_degree();
    int divisor_degree = that.find_degree();

    if (dividend_degree < divisor_degree) {
      rquot = polynomial_of(zero);
      rrem = *this;
      return;
    }

    polynomial_of quot;
    quot.coeffs_.assign(static_cast<std::size_t>(dividend_degree - divisor_degree + 1), zero);

    polynomial_of rem(*this);

    int max_shift = dividend_degree - divisor_degree;
    Coeff divisor_leader = that.coeffs_[static_cast<std::size_t>(divisor_degree)];
    Coeff dlinv;
    if (!divisor_leader.recip(dlinv)) {
      std::ostringstream oss;
      oss << "polynomial_of::quot_and_rem: non-invertible leading coefficient";
      throw std::runtime_error(oss.str());
    }

    for (int shift = max_shift; shift >= 0; --shift) {
      Coeff rem_leader = rem.coeffs_[static_cast<std::size_t>(shift + divisor_degree)];
      Coeff multiplier = rem_leader * dlinv;

      quot.coeffs_[static_cast<std::size_t>(shift)] = multiplier;

      for (int i = 0; i <= divisor_degree; ++i) {
        rem.coeffs_[static_cast<std::size_t>(i + shift)] -=
          that.coeffs_[static_cast<std::size_t>(i)] * multiplier;
      }
      rem.trim_degree();
    }

    quot.trim_degree();
    rem.trim_degree();

    rquot = quot;
    rrem = rem;
  }

  polynomial_of gcd(const polynomial_of &that) const
    requires spffl::concepts::Field_element<Coeff>
  {
    polynomial_of z(zero_coeff());

    if (this->is_zero()) {
      return that;
    }
    if (that.is_zero()) {
      return *this;
    }

    polynomial_of c(*this);
    polynomial_of d(that);
    polynomial_of q, r;

    while (true) {
      c.quot_and_rem(d, q, r);
      if (r.is_zero()) {
        break;
      }
      c = d;
      d = r;
    }
    return d;
  }

  // Extended GCD: returns g = gcd(*this, that), and rm, rn with this*rm + that*rn = g.
  polynomial_of ext_gcd(const polynomial_of &that, polynomial_of &rm, polynomial_of &rn) const
    requires spffl::concepts::Field_element<Coeff>
  {
    polynomial_of mprime = polynomial_of(one_coeff());
    rn = polynomial_of(one_coeff());
    rm = polynomial_of(zero_coeff());
    polynomial_of nprime = polynomial_of(zero_coeff());
    polynomial_of c(*this), d(that), q, r, t, qm, qn;

    while (true) {
      c.quot_and_rem(d, q, r);
      if (r.is_zero()) {
        break;
      }
      c = d;
      d = r;

      t = mprime;
      mprime = rm;
      qm = q * rm;
      rm = t - qm;

      t = nprime;
      nprime = rn;
      qn = q * rn;
      rn = t - qn;
    }
    return d;
  }

  // Scalar exponentiation: (*this)^e (e >= 0).
  polynomial_of exp(int e) const
    requires spffl::concepts::Field_element<Coeff>
  {
    Coeff z = zero_coeff();
    Coeff one = one_coeff();
    polynomial_of zero_poly(z);
    polynomial_of one_poly(one);

    if (*this == zero_poly) {
      if (e == 0) {
        throw std::runtime_error("polynomial_of::exp: 0^0 undefined");
      }
      if (e < 0) {
        throw std::runtime_error("polynomial_of::exp: negative exponent of zero");
      }
      return zero_poly;
    }
    if (e == 0) {
      return one_poly;
    }
    if (e < 0) {
      throw std::runtime_error("polynomial_of::exp: negative exponent not implemented");
    }

    polynomial_of base(*this);
    polynomial_of result(one_poly);
    while (e != 0) {
      if (e & 1) {
        result = result * base;
      }
      e = (unsigned)e >> 1;
      base = base * base;
    }
    return result;
  }

  // Formal derivative: d/dx (sum c_i x^i) = sum i*c_i x^{i-1}.
  // Requires Coeff to have get_modulus() and Coeff(i, modulus) for scalar i.
  polynomial_of deriv() const
    requires spffl::concepts::Field_element<Coeff> && spffl::concepts::has_get_modulus_v<Coeff>
  {
    int d = find_degree();
    Coeff z = zero_coeff();
    if (d <= 0) {
      return polynomial_of(z);
    }
    auto m = coeffs_[0].get_modulus();
    std::vector<Coeff> out(static_cast<std::size_t>(d), z);
    for (int i = 1; i <= d; ++i) {
      out[static_cast<std::size_t>(i - 1)] = coeffs_[static_cast<std::size_t>(i)] * Coeff(i, m);
    }
    return polynomial_of(std::move(out));
  }

  polynomial_of operator/(const polynomial_of &that) const
    requires spffl::concepts::Field_element<Coeff>
  {
    polynomial_of q, r;
    this->quot_and_rem(that, q, r);
    return q;
  }

  polynomial_of operator%(const polynomial_of &that) const
    requires spffl::concepts::Field_element<Coeff>
  {
    polynomial_of q, r;
    this->quot_and_rem(that, q, r);
    return r;
  }

  polynomial_of &operator/=(const polynomial_of &that)
    requires spffl::concepts::Field_element<Coeff>
  {
    *this = *this / that;
    return *this;
  }

  polynomial_of &operator%=(const polynomial_of &that)
    requires spffl::concepts::Field_element<Coeff>
  {
    *this = *this % that;
    return *this;
  }

  /// p-th root in characteristic p: keep only coefficients at indices 0, p, 2p, ... Return false if
  /// not a p-th power.
  bool pth_root(polynomial_of &rroot) const
    requires spffl::concepts::Field_element<Coeff> && spffl::concepts::has_get_modulus_v<Coeff>
  {
    int p = get_characteristic();
    Coeff z = zero_coeff();
    int d = find_degree();
    std::vector<Coeff> out;
    for (int si = 0, di = 0; si <= d; si += p, ++di) {
      out.push_back(coeffs_[static_cast<std::size_t>(si)]);
      for (int j = 1; j < p && si + j <= d; ++j) {
        if (coeffs_[static_cast<std::size_t>(si + j)] != z) {
          return false;
        }
      }
    }
    if (out.empty())
      out.push_back(z);
    rroot = polynomial_of(std::move(out));
    return true;
  }

  // Free-function-style helper for templates (ADL-friendly).
  friend polynomial_of gcd(const polynomial_of &a, const polynomial_of &b)
    requires spffl::concepts::Field_element<Coeff>
  {
    return a.gcd(b);
  }

  /// Legacy compat: add 1 to constant term with carry (increment in lex order).
  void increment()
    requires spffl::concepts::Field_element<Coeff> && spffl::concepts::has_get_modulus_v<Coeff>
  {
    int p = get_characteristic();
    Coeff z = zero_coeff();
    Coeff one = Coeff(1, p);
    for (int i = 0; i <= find_degree(); ++i) {
      Coeff c = coeffs_[static_cast<std::size_t>(i)];
      Coeff c_plus_one = c + one;
      if (c_plus_one != z) {
        coeffs_[static_cast<std::size_t>(i)] = c_plus_one;
        return;
      }
      coeffs_[static_cast<std::size_t>(i)] = z;
    }
    set_coeff(find_degree() + 1, one);
  }

  // ------------------------------------------------------------
  // I/O helpers (very simple; not matching legacy syntax yet)
  // ------------------------------------------------------------

  friend std::ostream &operator<<(std::ostream &os, const polynomial_of &p) {
    int d = p.find_degree();
    Coeff z = p.zero_coeff();
    bool first = true;
    for (int i = d; i >= 0; --i) {
      const auto &c = p.coeffs_[static_cast<std::size_t>(i)];
      if (c == z) {
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
      os << z;
    }
    return os;
  }

  private:
  std::vector<Coeff> coeffs_; // coeffs_[i] is coefficient of x^i

  Coeff zero_coeff() const { return coeffs_[0] - coeffs_[0]; }

  /// Multiplicative identity in the coefficient ring (requires Field_element).
  Coeff one_coeff() const
    requires spffl::concepts::Field_element<Coeff>
  {
    Coeff z = zero_coeff();
    for (const auto &c : coeffs_) {
      if (c != z) {
        Coeff inv;
        if (c.recip(inv)) {
          return c * inv;
        }
      }
    }
    return z; // zero polynomial: no multiplicative identity
  }

  public:
  /// Constant polynomial 1 (convenience for residue rings etc.).
  static polynomial_of one(const polynomial_of &p)
    requires spffl::concepts::Field_element<Coeff>
  {
    return polynomial_of(p.one_coeff());
  }

  private:
  void trim_degree() {
    Coeff z = zero_coeff();
    while (coeffs_.size() > 1 && coeffs_.back() == z) {
      coeffs_.pop_back();
    }
  }
};

} // namespace spffl::polynomials

#endif // SPFFL_POLYNOMIALS_POLYNOMIAL_OF_H
