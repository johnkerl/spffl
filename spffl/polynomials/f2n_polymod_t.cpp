// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "polynomials/f2n_polymod_t.h"
#include "base/spffl_exception.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

// ----------------------------------------------------------------
f2n_polymod_t::f2n_polymod_t(
    const f2n_poly_t &arg_residue, const f2n_poly_t &arg_modulus) {
  this->residue = arg_residue;
  this->modulus = arg_modulus;
  this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
f2n_polymod_t::f2n_polymod_t(const f2n_polymod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
}

// ----------------------------------------------------------------
f2n_polymod_t::f2n_polymod_t(void) {
  f2n_poly_t invalid;
  this->residue = invalid;
  this->modulus = invalid;
}

// ----------------------------------------------------------------
f2n_polymod_t::~f2n_polymod_t(void) {
  f2n_poly_t invalid;
  this->residue = invalid;
  this->modulus = invalid;
}

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_t::prime_subfield_element(int v) const {
  f2n_poly_t m = this->modulus;
  f2n_poly_t r = this->residue.prime_subfield_element(v);
  return f2n_polymod_t(r, m);
}

// ----------------------------------------------------------------
// This is a static method.
f2n_polymod_t f2n_polymod_t::prime_subfield_element(
    int v, const f2n_poly_t &om) {
  f2_poly_t im = om.get_coeff(0).get_modulus();
  return f2n_polymod_t(f2n_poly_t::prime_subfield_element(v, im), om);
}

// ----------------------------------------------------------------
int f2n_polymod_t::get_characteristic(void) const { return 2; }

// ----------------------------------------------------------------
f2n_polymod_t &f2n_polymod_t::operator=(const f2n_polymod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
  return *this;
}

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_t::operator+(const f2n_polymod_t &that) const {
  this->check_moduli(that);
  f2n_polymod_t rv(this->residue + that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_t::operator-(const f2n_polymod_t &that) const {
  this->check_moduli(that);
  f2n_polymod_t rv(this->residue - that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_t::operator-(void) const {
  f2n_polymod_t rv(-this->residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_t::operator*(const f2n_polymod_t &that) const {
  this->check_moduli(that);
  f2n_polymod_t rv(this->residue * that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_t::operator*(int a) const {
  // Characteristic is 2, so there are two possibilities.
  f2n_polymod_t rv(*this);
  if (a & 1)
    ;
  else {
    rv = rv - rv;
  }
  return rv;
}

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_t::operator/(const f2n_polymod_t &that) const {
  this->check_moduli(that);

  f2n_polymod_t bi;
  if (!that.recip(bi)) {
    std::stringstream ss;
    ss << "f2n_polymod_t::operator/:  zero or zero divisor: " << that.residue
       << " mod " << that.modulus << ".\n";
    throw spffl::exception_t(ss.str());
  }

  return *this * bi;
}

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_t::operator%(const f2n_polymod_t &that) const {
  this->check_moduli(that);

  f2n_polymod_t bi;
  if (!that.recip(bi)) {
    std::stringstream ss;
    ss << "f2n_polymod_t::operator%:  zero or zero divisor: " << that.residue
       << " mod " << that.modulus << ".\n";
    throw spffl::exception_t(ss.str());
  }

  return *this - *this;
}

// ----------------------------------------------------------------
bool f2n_polymod_t::recip(f2n_polymod_t &rinv) const {
  f2n_poly_t g, a, b;
  g = this->residue.ext_gcd(this->modulus, a, b);

  // Error check:
  if (g.find_degree() != 0) {
    return false;
  }

  // Ext. GCD actually returns a scalar multiple of 1.  Divide this out.
  f2_polymod_t c0i;
  if (!g.get_coeff(0).recip(c0i)) {
    std::stringstream ss;
    ss << "f2n_polymod_t::recip:  zero or zero divisor "
       << " in GCD " << g << ".\n";
    throw spffl::exception_t(ss.str());
  }
  a *= c0i;
  f2n_polymod_t rv(a, this->modulus);
  rinv = rv;
  return true;
}

// ----------------------------------------------------------------
f2n_polymod_t f2n_polymod_t::exp(int e) const {
  f2n_poly_t xp = this->residue;
  f2n_polymod_t zero(this->residue.prime_subfield_element(0), this->modulus);
  f2n_polymod_t one(this->residue.prime_subfield_element(1), this->modulus);
  f2n_polymod_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::stringstream ss;
      ss << "f2n_polymod_t::exp:  0 ^ 0 undefined.\n";
      throw spffl::exception_t(ss.str());
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::stringstream ss;
      ss << "f2n_polymod_t::exp:  division by zero.\n";
      throw spffl::exception_t(ss.str());
    }
    if (e == -e) {
      std::stringstream ss;
      ss << "f2n_polymod_t::exp:  can't handle "
            "MIN_INT.\n";
      throw spffl::exception_t(ss.str());
    }
    f2n_polymod_t inv = one / *this;
    xp                = inv.residue;
    e                 = -e;
  }

  while (e != 0) {
    if (e & 1) {
      rv.residue = (rv.residue * xp) % this->modulus;
    }
    e  = (unsigned)e >> 1;
    xp = (xp * xp) % this->modulus;
  }

  return rv;
}

// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const f2n_polymod_t &a) {
  int adeg    = a.residue.find_degree();
  int rdeg    = a.modulus.find_degree() - 1;
  int max     = adeg > rdeg ? adeg : rdeg;
  f2_poly_t m = a.residue.get_coeff(0).get_modulus();

  for (int i = max; i >= 0; i--) {
    if (m > 9) {
      if (i < max) {
        os << ":";
      }
    }
    if (i > adeg) {
      os << 0;
    } else {
      os << a.residue.get_coeff(i).get_residue();
    }
  }

  return os;
}

// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, f2n_polymod_t &a) {
  iss >> a.residue; // Modulus must be already set.
  a.residue %= a.modulus;
  return iss;
}

// ----------------------------------------------------------------
bool f2n_polymod_t::from_string(const std::string &string, f2n_poly_t &m) {
  f2n_poly_t r;
  f2_poly_t mm = m.get_coeff(0).get_modulus();
  if (!r.from_string(string, mm)) {
    return false;
  }
  *this = f2n_polymod_t(r, m);
  return true;
}

// ----------------------------------------------------------------
f2n_polymod_t &f2n_polymod_t::operator+=(const f2n_polymod_t &that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
f2n_polymod_t &f2n_polymod_t::operator-=(const f2n_polymod_t &that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
f2n_polymod_t &f2n_polymod_t::operator*=(const f2n_polymod_t &that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
f2n_polymod_t &f2n_polymod_t::operator*=(int a) {
  *this = *this * a;
  return *this;
}

// ----------------------------------------------------------------
f2n_polymod_t &f2n_polymod_t::operator/=(const f2n_polymod_t &that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
f2n_polymod_t &f2n_polymod_t::operator%=(const f2n_polymod_t &that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
bool f2n_polymod_t::operator==(const f2n_polymod_t &that) const {
  if (this->residue != that.residue) {
    return false;
  }
  if (this->modulus != that.modulus) {
    return false;
  }
  return true;
}

// ----------------------------------------------------------------
bool f2n_polymod_t::operator!=(const f2n_polymod_t &that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool f2n_polymod_t::operator==(int that) const { return this->residue == that; }

// ----------------------------------------------------------------
bool f2n_polymod_t::operator!=(int that) const { return this->residue != that; }

// ----------------------------------------------------------------
bool f2n_polymod_t::operator<(const f2n_polymod_t &that) const {
  this->check_moduli(that);
  return this->residue < that.residue;
}

// ----------------------------------------------------------------
bool f2n_polymod_t::operator<=(const f2n_polymod_t &that) const {
  this->check_moduli(that);
  return this->residue <= that.residue;
}

// ----------------------------------------------------------------
bool f2n_polymod_t::operator>(const f2n_polymod_t &that) const {
  this->check_moduli(that);
  return this->residue > that.residue;
}

// ----------------------------------------------------------------
bool f2n_polymod_t::operator>=(const f2n_polymod_t &that) const {
  this->check_moduli(that);
  return this->residue >= that.residue;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_polymod_t::get_residue(void) const { return this->residue; }

// ----------------------------------------------------------------
f2n_poly_t f2n_polymod_t::get_modulus(void) const { return this->modulus; }

// ----------------------------------------------------------------
void f2n_polymod_t::check_moduli(const f2n_polymod_t &that) const {
  if (this->modulus != that.modulus) {
    std::stringstream ss;
    ss << "f2n_polymod_t: mixed moduli " << this->modulus << ", "
       << that.modulus << ".";
    ss << std::endl;
    throw spffl::exception_t(ss.str());
  }
}

} // namespace spffl::polynomials
