// ================================================================
// Residue ring Fp[x]/(m): elements are polynomials mod m.
// Minimal C++20 version for cpp20 port. Uses fp_poly_t = polynomial_of<intmod_t>.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_FP_POLYMOD_T_HPP
#define SPFFL_POLYNOMIALS_FP_POLYMOD_T_HPP

#include "spffl/polynomials/aliases.hpp"
#include "spffl/concepts.hpp"
#include <ostream>
#include <stdexcept>

namespace spffl::polynomials {

/// Element of Fp[x]/(m): residue class represented by a reduced polynomial.
class fp_polymod_t {
public:
  fp_polymod_t() = default;

  fp_polymod_t(const fp_poly_t &residue, const fp_poly_t &modulus)
      : residue_(residue), modulus_(modulus) {
    reduce();
  }

  fp_poly_t get_residue() const { return residue_; }
  fp_poly_t get_modulus() const { return modulus_; }

  fp_polymod_t operator+(const fp_polymod_t &that) const {
    check_moduli(that);
    return fp_polymod_t(residue_ + that.residue_, modulus_);
  }

  fp_polymod_t operator-(const fp_polymod_t &that) const {
    check_moduli(that);
    return fp_polymod_t(residue_ - that.residue_, modulus_);
  }

  fp_polymod_t operator-() const {
    return fp_polymod_t(-residue_, modulus_);
  }

  fp_polymod_t operator*(const fp_polymod_t &that) const {
    check_moduli(that);
    return fp_polymod_t(residue_ * that.residue_, modulus_);
  }

  fp_polymod_t &operator+=(const fp_polymod_t &that) {
    *this = *this + that;
    return *this;
  }
  fp_polymod_t &operator-=(const fp_polymod_t &that) {
    *this = *this - that;
    return *this;
  }
  fp_polymod_t &operator*=(const fp_polymod_t &that) {
    *this = *this * that;
    return *this;
  }

  bool recip(fp_polymod_t &rinv) const {
    if (modulus_.is_zero()) {
      return false;
    }
    fp_poly_t m, n;
    fp_poly_t g = residue_.ext_gcd(modulus_, m, n);
    if (g.find_degree() != 0 || g.is_zero()) {
      return false;  // not a unit
    }
    // residue_ * m + modulus_ * n = g (g constant). So residue_ * m ≡ g (mod modulus_).
    // Inverse of residue_ is m / g (coefficient-wise), then reduced.
    fp_poly_t g_inv = g;  // need 1/g in coeff ring: g is constant, so g.get_coeff(0).recip
    using Coeff = spffl::intmath::intmod_t;
    Coeff g0 = g.get_coeff(0);
    Coeff g0_inv;
    if (!g0.recip(g0_inv)) {
      return false;
    }
    fp_poly_t minv = m * g0_inv;  // scalar multiply polynomial by 1/g
    fp_poly_t q, r;
    minv.quot_and_rem(modulus_, q, r);
    rinv = fp_polymod_t(r, modulus_);
    return true;
  }

  fp_polymod_t operator/(const fp_polymod_t &that) const {
    fp_polymod_t inv;
    if (!that.recip(inv)) {
      throw std::runtime_error("fp_polymod_t::operator/: non-invertible divisor");
    }
    return *this * inv;
  }

  fp_polymod_t &operator/=(const fp_polymod_t &that) {
    *this = *this / that;
    return *this;
  }

  fp_polymod_t exp(int e) const {
    if (e == 0) {
      return fp_polymod_t(fp_poly_t::one(residue_), modulus_);
    }
    if (e < 0) {
      fp_polymod_t inv;
      if (!recip(inv)) {
        throw std::runtime_error("fp_polymod_t::exp: negative exponent of non-unit");
      }
      return inv.exp(-e);
    }
    fp_polymod_t base(*this);
    fp_polymod_t result(fp_poly_t::one(residue_), modulus_);
    while (e != 0) {
      if (e & 1) {
        result = result * base;
      }
      e = (unsigned)e >> 1;
      base = base * base;
    }
    return result;
  }

  bool operator==(const fp_polymod_t &that) const {
    check_moduli(that);
    return residue_ == that.residue_;
  }
  bool operator!=(const fp_polymod_t &that) const { return !(*this == that); }
  bool operator<(const fp_polymod_t &that) const {
    check_moduli(that);
    return residue_ < that.residue_;
  }

  friend std::ostream &operator<<(std::ostream &os, const fp_polymod_t &a) {
    os << a.residue_;
    return os;
  }

private:
  fp_poly_t residue_;
  fp_poly_t modulus_;

  void reduce() {
    if (modulus_.is_zero()) {
      return;
    }
    fp_poly_t q, r;
    residue_.quot_and_rem(modulus_, q, r);
    residue_ = r;
  }

  void check_moduli(const fp_polymod_t &that) const {
    if (modulus_ != that.modulus_) {
      throw std::runtime_error("fp_polymod_t: mismatched moduli");
    }
  }
};

}  // namespace spffl::polynomials

#endif  // SPFFL_POLYNOMIALS_FP_POLYMOD_T_HPP
