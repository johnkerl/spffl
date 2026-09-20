// ================================================================
// intmod_t: Z/nZ (residue classes). Header-only C++20.
// Replaces former intmod_t.h + intmod_t.cpp. Models Residue_ring_with_recip.
// ================================================================

#ifndef INTMOD_T_H
#define INTMOD_T_H

#include <stdexcept>
#include <ostream>
#include <istream>
#include <sstream>
#include <string>

namespace spffl::intmath {

class intmod_t {
  public:
  intmod_t() : residue_(0), modulus_(0) {}
  intmod_t(int residue, int modulus) : residue_(0), modulus_(modulus) { normalize(residue); }

  intmod_t prime_subfield_element(int v) const {
    check_modulus();
    return intmod_t(v, modulus_);
  }

  // basic ring ops
  intmod_t operator+(const intmod_t &that) const {
    check_moduli(that);
    return intmod_t(residue_ + that.residue_, modulus_);
  }
  intmod_t operator-(const intmod_t &that) const {
    check_moduli(that);
    return intmod_t(residue_ - that.residue_, modulus_);
  }
  intmod_t operator-() const { return intmod_t(-residue_, modulus_); }
  intmod_t operator*(const intmod_t &that) const {
    check_moduli(that);
    return intmod_t(residue_ * that.residue_, modulus_);
  }

  intmod_t operator+(int a) const {
    check_modulus();
    return intmod_t(residue_ + a, modulus_);
  }
  intmod_t operator-(int a) const {
    check_modulus();
    return intmod_t(residue_ - a, modulus_);
  }
  intmod_t operator*(int a) const {
    check_modulus();
    return intmod_t(residue_ * a, modulus_);
  }

  intmod_t &operator+=(const intmod_t &that) {
    *this = *this + that;
    return *this;
  }
  intmod_t &operator-=(const intmod_t &that) {
    *this = *this - that;
    return *this;
  }
  intmod_t &operator*=(const intmod_t &that) {
    *this = *this * that;
    return *this;
  }

  // multiplicative inverse and division
  bool recip(intmod_t &rinv) const {
    check_modulus();
    if (residue_ == 0) {
      return false;
    }
    int a = residue_;
    int m = modulus_;
    int t0 = 0, t1 = 1;
    int r0 = m, r1 = a;

    while (r1 != 0) {
      int q = r0 / r1;
      int r2 = r0 - q * r1;
      int t2 = t0 - q * t1;
      r0 = r1;
      r1 = r2;
      t0 = t1;
      t1 = t2;
    }
    if (r0 != 1) {
      return false; // not a unit
    }
    intinv_normalize(t0, m);
    rinv = intmod_t(t0, m);
    return true;
  }

  intmod_t operator/(const intmod_t &that) const {
    intmod_t inv;
    if (!that.recip(inv)) {
      throw std::runtime_error("intmod_t: division by non-invertible element");
    }
    return *this * inv;
  }

  intmod_t &operator/=(const intmod_t &that) {
    *this = *this / that;
    return *this;
  }

  // Legacy: operator% (zero in a field). Kept for API compatibility.
  intmod_t operator%(const intmod_t &that) const {
    check_moduli(that);
    intmod_t inv;
    if (!that.recip(inv)) {
      throw std::runtime_error("intmod_t: operator% with non-invertible divisor");
    }
    return intmod_t(0, modulus_);
  }

  intmod_t &operator%=(const intmod_t &that) {
    *this = *this % that;
    return *this;
  }

  /// Exponentiation: a^e (e >= 0). For e < 0, returns inverse^|e| when invertible.
  intmod_t exp(int e) const {
    check_modulus();
    if (e == 0) {
      return intmod_t(1, modulus_);
    }
    if (e < 0) {
      intmod_t inv;
      if (!recip(inv)) {
        throw std::runtime_error("intmod_t::exp: negative exponent of non-unit");
      }
      return inv.exp(-e);
    }
    intmod_t base(*this);
    intmod_t result(1, modulus_);
    while (e != 0) {
      if (e & 1) {
        result = result * base;
      }
      e = static_cast<unsigned>(e) >> 1;
      base = base * base;
    }
    return result;
  }

  // comparisons
  bool operator==(const intmod_t &that) const {
    check_moduli(that);
    return residue_ == that.residue_;
  }
  bool operator!=(const intmod_t &that) const { return !(*this == that); }
  bool operator==(int that) const {
    check_modulus();
    int r = that % modulus_;
    if (r < 0)
      r += modulus_;
    return residue_ == r;
  }
  bool operator!=(int that) const { return !(*this == that); }
  bool operator<(const intmod_t &that) const {
    check_moduli(that);
    return residue_ < that.residue_;
  }
  bool operator>(const intmod_t &that) const {
    check_moduli(that);
    return residue_ > that.residue_;
  }
  bool operator<=(const intmod_t &that) const {
    check_moduli(that);
    return residue_ <= that.residue_;
  }
  bool operator>=(const intmod_t &that) const {
    check_moduli(that);
    return residue_ >= that.residue_;
  }

  int get_residue() const { return residue_; }
  int get_modulus() const { return modulus_; }

  bool from_string(const std::string &s, int m) {
    int r;
    std::istringstream iss(s);
    iss >> r;
    if (iss.fail()) {
      return false;
    }
    *this = intmod_t(r, m);
    return true;
  }

  friend std::ostream &operator<<(std::ostream &os, const intmod_t &a) {
    a.check_modulus();
    os << a.residue_;
    return os;
  }

  friend std::istream &operator>>(std::istream &is, intmod_t &a) {
    int c = is.peek();
    if (c == EOF) {
      is.setstate(std::ios::failbit);
      return is;
    }
    while (c == ' ' || c == '\t' || c == '\n') {
      is.ignore(1);
      c = is.peek();
    }
    if (c == EOF) {
      is.setstate(std::ios::failbit);
      return is;
    }
    a.check_modulus();
    is >> a.residue_;
    a.residue_ %= a.modulus_;
    if (a.residue_ < 0) {
      a.residue_ += a.modulus_;
    }
    return is;
  }

  private:
  int residue_;
  int modulus_;

  void normalize(int x) {
    if (modulus_ == 0) {
      throw std::runtime_error("intmod_t: modulus is zero");
    }
    int m = modulus_;
    int r = x % m;
    if (r < 0) {
      r += m;
    }
    residue_ = r;
  }

  static void intinv_normalize(int &x, int m) {
    x %= m;
    if (x < 0) {
      x += m;
    }
  }

  void check_modulus() const {
    if (modulus_ == 0) {
      throw std::runtime_error("intmod_t: modulus not set");
    }
  }

  void check_moduli(const intmod_t &that) const {
    if (modulus_ != that.modulus_) {
      throw std::runtime_error("intmod_t: mismatched moduli");
    }
  }
};

} // namespace spffl::intmath

#endif // INTMOD_T_H
