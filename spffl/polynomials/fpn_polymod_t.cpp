// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/polynomials/fpn_polymod_t.h"
#include "spffl/base/spffl_exception.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

// ----------------------------------------------------------------
fpn_polymod_t::fpn_polymod_t(
    const fpn_poly_t &arg_residue, const fpn_poly_t &arg_modulus) {
  this->residue = arg_residue;
  this->modulus = arg_modulus;
  this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
fpn_polymod_t::fpn_polymod_t(const fpn_polymod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
}

// ----------------------------------------------------------------
fpn_polymod_t::fpn_polymod_t(void) {
  fpn_poly_t invalid;
  this->residue = invalid;
  this->modulus = invalid;
}

// ----------------------------------------------------------------
fpn_polymod_t::~fpn_polymod_t(void) {
  fpn_poly_t invalid;
  this->residue = invalid;
  this->modulus = invalid;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::prime_subfield_element(int v) const {
  fpn_poly_t m = this->modulus;
  fpn_poly_t r = this->residue.prime_subfield_element(v);
  return fpn_polymod_t(r, m);
}

// ----------------------------------------------------------------
// This is a static method.
fpn_polymod_t fpn_polymod_t::prime_subfield_element(
    int v, const fpn_poly_t &om) {
  fp_poly_t im = om.get_coeff(0).get_modulus();
  return fpn_polymod_t(fpn_poly_t::prime_subfield_element(v, im), om);
}

// ----------------------------------------------------------------
int fpn_polymod_t::get_characteristic(void) const {
  return this->residue.get_characteristic();
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator=(const fpn_polymod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator+(const fpn_polymod_t &that) const {
  this->check_moduli(that);
  fpn_polymod_t rv(this->residue + that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator-(const fpn_polymod_t &that) const {
  this->check_moduli(that);
  fpn_polymod_t rv(this->residue - that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator-(void) const {
  fpn_polymod_t rv(-this->residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator*(const fpn_polymod_t &that) const {
  this->check_moduli(that);
  fpn_polymod_t rv(this->residue * that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator*(int a) const {
  // xxx get the characteristic and reduce a mod that.
  fpn_polymod_t rv = *this - *this;
  for (int i = 0; i < a; i++) {
    rv += *this;
  }
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator/(const fpn_polymod_t &that) const {
  this->check_moduli(that);

  fpn_polymod_t bi;
  if (!that.recip(bi)) {
    std::stringstream ss;
    ss << "fpn_polymod_t::operator/:  zero or zero divisor: " << that.residue
       << " mod " << that.modulus << ".\n";
    throw spffl::exception_t(ss.str());
  }

  return *this * bi;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator%(const fpn_polymod_t &that) const {
  this->check_moduli(that);

  fpn_polymod_t bi;
  if (!that.recip(bi)) {
    std::stringstream ss;
    ss << "fpn_polymod_t::operator%:  zero or zero divisor: " << that.residue
       << " mod " << that.modulus << ".\n";
    throw spffl::exception_t(ss.str());
  }

  return *this - *this;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::recip(fpn_polymod_t &rinv) const {
  fpn_poly_t g, a, b;
  g = this->residue.ext_gcd(this->modulus, a, b);

  // Error check:
  if (g.find_degree() != 0) {
    return false;
  }

  // Ext. GCD actually returns a scalar multiple of 1.  Divide this out.
  fp_polymod_t c0i;
  if (!g.get_coeff(0).recip(c0i)) {
    std::stringstream ss;
    ss << "fpn_polymod_t::recip:  zero or zero divisor "
       << " in GCD " << g << ".\n";
    throw spffl::exception_t(ss.str());
  }
  a *= c0i;
  fpn_polymod_t rv(a, this->modulus);
  rinv = rv;
  return true;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::exp(int e) const {
  fpn_poly_t xp = this->residue;
  fpn_polymod_t zero(this->residue.prime_subfield_element(0), this->modulus);
  fpn_polymod_t one(this->residue.prime_subfield_element(1), this->modulus);
  fpn_polymod_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::stringstream ss;
      ss << "fpn_polymod_t::exp:  0 ^ 0 undefined.\n";
      throw spffl::exception_t(ss.str());
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::stringstream ss;
      ss << "fpn_polymod_t::exp:  division by zero.\n";
      throw spffl::exception_t(ss.str());
    }
    if (e == -e) {
      std::stringstream ss;
      ss << "fpn_polymod_t::exp:  can't handle "
            "MIN_INT.\n";
      throw spffl::exception_t(ss.str());
    }
    fpn_polymod_t inv = one / *this;
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
std::ostream &operator<<(std::ostream &os, const fpn_polymod_t &a) {
  int adeg    = a.residue.find_degree();
  int rdeg    = a.modulus.find_degree() - 1;
  int max     = adeg > rdeg ? adeg : rdeg;
  fp_poly_t m = a.residue.get_coeff(0).get_modulus();

  for (int i = max; i >= 0; i--) {
    if (i < max) {
      os << ":";
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
std::istringstream &operator>>(std::istringstream &iss, fpn_polymod_t &a) {
  iss >> a.residue; // Modulus must be already set.
  a.residue %= a.modulus;
  return iss;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::from_string(const std::string &string, fpn_poly_t &m) {
  fpn_poly_t r;
  fp_poly_t mm = m.get_coeff(0).get_modulus();
  if (!r.from_string(string, mm)) {
    return false;
  }
  *this = fpn_polymod_t(r, m);
  return true;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator+=(const fpn_polymod_t &that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator-=(const fpn_polymod_t &that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator*=(const fpn_polymod_t &that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator*=(int a) {
  *this = *this * a;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator/=(const fpn_polymod_t &that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator%=(const fpn_polymod_t &that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator==(const fpn_polymod_t &that) const {
  if (this->residue != that.residue) {
    return false;
  }
  if (this->modulus != that.modulus) {
    return false;
  }
  return true;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator!=(const fpn_polymod_t &that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator==(int that) const { return this->residue == that; }

// ----------------------------------------------------------------
bool fpn_polymod_t::operator!=(int that) const { return this->residue != that; }

// ----------------------------------------------------------------
bool fpn_polymod_t::operator<(const fpn_polymod_t &that) const {
  this->check_moduli(that);
  return this->residue < that.residue;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator<=(const fpn_polymod_t &that) const {
  this->check_moduli(that);
  return this->residue <= that.residue;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator>(const fpn_polymod_t &that) const {
  this->check_moduli(that);
  return this->residue > that.residue;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator>=(const fpn_polymod_t &that) const {
  this->check_moduli(that);
  return this->residue >= that.residue;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_polymod_t::get_residue(void) const { return this->residue; }

// ----------------------------------------------------------------
fpn_poly_t fpn_polymod_t::get_modulus(void) const { return this->modulus; }

// ----------------------------------------------------------------
void fpn_polymod_t::check_moduli(const fpn_polymod_t &that) const {
  if (this->modulus != that.modulus) {
    std::stringstream ss;
    ss << "fpn_polymod_t: mixed moduli " << this->modulus << ", "
       << that.modulus << ".";
    ss << std::endl;
    throw spffl::exception_t(ss.str());
  }
}

} // namespace spffl::polynomials
