// ================================================================
// Generic residue ring over a Euclidean domain E: E/(m).
// E = int (Z/nZ) or E = polynomial type with ext_gcd (e.g. Fp[x]/(m)).
// Models Residue_ring and Residue_ring_with_recip; inversion via euclidean::ext_gcd.
// ================================================================

#ifndef SPFFL_RESIDUE_OF_H
#define SPFFL_RESIDUE_OF_H

#include "spffl/concepts.h"
#include "spffl/euclidean.h"
#include "spffl/polynomials/f2_poly_t.h"
#include <ostream>
#include <stdexcept>
#include <type_traits>

namespace spffl {

/// Residue ring element: residue class of E modulo modulus.
/// E must be int or model Euclidean_domain_with_ext_gcd (e.g. fp_poly_t).
template <typename E>
  requires std::same_as<E, int> || (spffl::concepts::Euclidean_domain<E> &&
                                     spffl::concepts::Euclidean_domain_with_ext_gcd<E>)
class residue_of {
  public:
  residue_of() : residue_{}, modulus_{} {}

  residue_of(E residue, E modulus) : residue_(std::move(residue)), modulus_(std::move(modulus)) {
    reduce();
  }

  E get_residue() const { return residue_; }
  E get_modulus() const { return modulus_; }

  /// Legacy compat: characteristic of the residue ring (2 for F2, p for Z/pZ, etc.).
  int get_characteristic() const {
    if constexpr (std::is_same_v<E, int>) {
      return (modulus_ < 0) ? -modulus_ : modulus_;
    } else if constexpr (std::is_same_v<E, spffl::polynomials::f2_poly_t>) {
      return 2;
    } else {
      return modulus_.get_characteristic();
    }
  }

  residue_of operator+(const residue_of &that) const {
    check_moduli(that);
    return residue_of(add(residue_, that.residue_), modulus_);
  }

  residue_of operator-(const residue_of &that) const {
    check_moduli(that);
    return residue_of(sub(residue_, that.residue_), modulus_);
  }

  residue_of operator-() const { return residue_of(negate(residue_), modulus_); }

  residue_of operator*(const residue_of &that) const {
    check_moduli(that);
    return residue_of(mult(residue_, that.residue_), modulus_);
  }

  residue_of &operator+=(const residue_of &that) {
    *this = *this + that;
    return *this;
  }
  residue_of &operator-=(const residue_of &that) {
    *this = *this - that;
    return *this;
  }
  residue_of &operator*=(const residue_of &that) {
    *this = *this * that;
    return *this;
  }

  bool recip(residue_of &rinv) const {
    if constexpr (std::is_same_v<E, int>) {
      return recip_int(rinv);
    } else if constexpr (std::is_same_v<E, spffl::polynomials::f2_poly_t>) {
      return recip_f2(rinv);
    } else {
      return recip_polynomial(rinv);
    }
  }

  residue_of operator/(const residue_of &that) const {
    residue_of inv;
    if (!that.recip(inv)) {
      throw std::runtime_error("residue_of::operator/: non-invertible divisor");
    }
    return *this * inv;
  }

  residue_of &operator/=(const residue_of &that) {
    *this = *this / that;
    return *this;
  }

  /// Remainder in ring (for CLI compat); in a field, returns zero when divisor is nonzero.
  residue_of operator%(const residue_of &that) const {
    check_moduli(that);
    if (that.residue_ == E{})
      return *this;                   // divisor zero: undefined, return this
    return residue_of(E{}, modulus_); // in field: remainder is zero
  }
  residue_of &operator%=(const residue_of &that) {
    *this = *this % that;
    return *this;
  }

  residue_of exp(int e) const {
    if (e == 0) {
      return residue_of(one_(), modulus_);
    }
    if (e < 0) {
      residue_of inv;
      if (!recip(inv)) {
        throw std::runtime_error("residue_of::exp: negative exponent of non-unit");
      }
      return inv.exp(-e);
    }
    residue_of base(*this);
    residue_of result(one_(), modulus_);
    while (e != 0) {
      if (e & 1) {
        result = result * base;
      }
      e = static_cast<unsigned>(e) >> 1;
      base = base * base;
    }
    return result;
  }

  bool operator==(const residue_of &that) const {
    check_moduli(that);
    return residue_ == that.residue_;
  }
  bool operator!=(const residue_of &that) const { return !(*this == that); }
  bool operator<(const residue_of &that) const {
    check_moduli(that);
    return residue_ < that.residue_;
  }
  bool operator>(const residue_of &that) const {
    check_moduli(that);
    return residue_ > that.residue_;
  }
  bool operator<=(const residue_of &that) const { return !(*this > that); }
  bool operator>=(const residue_of &that) const { return !(*this < that); }

  friend std::ostream &operator<<(std::ostream &os, const residue_of &a) {
    os << a.residue_;
    return os;
  }

  private:
  E residue_;
  E modulus_;

  void reduce() {
    if (is_zero_modulus())
      return;
    E q{}, r{};
    spffl::euclidean::quot_and_rem(residue_, modulus_, q, r);
    residue_ = r;
    if constexpr (std::is_same_v<E, int>) {
      int m = modulus_;
      int mod_abs = (m < 0) ? -m : m;
      if (mod_abs != 0 && residue_ < 0) {
        residue_ = residue_ % mod_abs;
        if (residue_ < 0)
          residue_ += mod_abs;
      }
    }
  }

  static bool is_zero_poly(const E &e) {
    if constexpr (std::is_same_v<E, int>) {
      return e == 0;
    } else if constexpr (std::is_same_v<E, spffl::polynomials::f2_poly_t>) {
      return e == 0;
    } else {
      return e.is_zero();
    }
  }

  bool is_zero_modulus() const {
    if constexpr (std::is_same_v<E, int>) {
      return modulus_ == 0;
    } else {
      return is_zero_poly(modulus_);
    }
  }

  void check_moduli(const residue_of &that) const {
    if (modulus_ != that.modulus_) {
      throw std::runtime_error("residue_of: mismatched moduli");
    }
  }

  static E add(const E &a, const E &b) { return a + b; }
  static E sub(const E &a, const E &b) { return a - b; }
  static E negate(const E &a) { return -a; }
  static E mult(const E &a, const E &b) { return a * b; }

  E one_() const {
    if constexpr (std::is_same_v<E, int>) {
      return 1;
    } else if constexpr (std::is_same_v<E, spffl::polynomials::f2_poly_t>) {
      return E(1);
    } else {
      return E::one(modulus_);
    }
  }

  bool recip_int(residue_of &rinv) const {
    if (modulus_ == 0)
      return false;
    int a = residue_;
    int m = modulus_;
    int bez_m = 0, bez_n = 0;
    int g = spffl::euclidean::ext_gcd(a, m, bez_m, bez_n);
    if (g != 1)
      return false;
    int r = bez_m;
    int mod_abs = (m < 0) ? -m : m;
    r = r % mod_abs;
    if (r < 0)
      r += mod_abs;
    rinv = residue_of(r, modulus_);
    return true;
  }

  bool recip_f2(residue_of &rinv) const {
    if (is_zero_poly(modulus_))
      return false;
    E m, n;
    E g = spffl::euclidean::ext_gcd(residue_, modulus_, m, n);
    if (g.find_degree() != 0 || is_zero_poly(g))
      return false;
    E q, r;
    spffl::euclidean::quot_and_rem(m, modulus_, q, r);
    rinv = residue_of(r, modulus_);
    return true;
  }

  bool recip_polynomial(residue_of &rinv) const {
    if (modulus_.is_zero())
      return false;
    E m, n;
    E g = spffl::euclidean::ext_gcd(residue_, modulus_, m, n);
    if (g.find_degree() != 0 || g.is_zero())
      return false;
    typename E::coeff_type g0 = g.get_coeff(0);
    typename E::coeff_type g0_inv;
    if (!g0.recip(g0_inv))
      return false;
    E minv = m * g0_inv;
    E q, r;
    spffl::euclidean::quot_and_rem(minv, modulus_, q, r);
    rinv = residue_of(r, modulus_);
    return true;
  }
};

} // namespace spffl

#endif // SPFFL_RESIDUE_OF_H
