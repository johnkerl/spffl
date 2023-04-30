// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "base/spffl_exception.h"
#include "intmath/intmod_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::intmath {

// ----------------------------------------------------------------
intmod_t intmod_t::prime_subfield_element(int v) const {
  int p = this->get_modulus();
  return intmod_t(v, p);
}

// ----------------------------------------------------------------
intmod_t intmod_t::exp(int e) const {
  this->check_modulus();

  int xp = this->residue;
  intmod_t zero(0, this->modulus);
  intmod_t one(1, this->modulus);
  intmod_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::stringstream ss;
      ss << "intmod_t::exp:  0 ^ 0 undefined.";
      throw spffl::exception_t(ss.str());
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::stringstream ss;
      ss << "intmod_t::exp:  division by zero.\n";
      throw spffl::exception_t(ss.str());
    }
    if (e == -e) {
      std::stringstream ss;
      ss << "intmod_t::exp:  can't handle "
            "MIN_INT.\n";
      throw spffl::exception_t(ss.str());
    }
    intmod_t inv = one / *this;
    xp           = inv.residue;
    e            = -e;
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
std::ostream &operator<<(std::ostream &os, const intmod_t &a) {
  a.check_modulus();
  os << a.residue;
  return os;
}

// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, intmod_t &a) {
  // Skip over whitespace.
  int c = is.peek();
  if (c == EOF) {
    is.setstate(std::ios::failbit);
    return is;
  }
  while ((c == ' ') || (c == '\t') || (c == '\n')) {
    is.ignore(1, c);
    c = is.peek();
  }
  if (c == EOF) {
    is.setstate(std::ios::failbit);
    return is;
  }

  a.check_modulus();
  is >> a.residue;
  a.residue %= a.modulus;
  return is;
}

// ----------------------------------------------------------------
bool intmod_t::from_string(const std::string &string, int m) {
  int r;
  std::istringstream iss(string, std::ios_base::in);
  iss >> r;
  if (iss.fail()) {
    return false;
  } else {
    *this = intmod_t(r, m);
    return true;
  }
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator+=(const intmod_t &that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator-=(const intmod_t &that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator*=(const intmod_t &that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator/=(const intmod_t &that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator%=(const intmod_t &that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
bool intmod_t::operator==(const intmod_t &that) const {
  this->check_modulus();
  that.check_modulus();
  if (this->residue != that.residue) {
    return false;
  }
  if (this->modulus != that.modulus) {
    return false;
  }
  return true;
}

// ----------------------------------------------------------------
bool intmod_t::operator!=(const intmod_t &that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool intmod_t::operator==(int that) const {
  this->check_modulus();
  return this->residue == that;
}

// ----------------------------------------------------------------
bool intmod_t::operator!=(int that) const {
  this->check_modulus();
  return this->residue != that;
}

// ----------------------------------------------------------------
bool intmod_t::operator<(const intmod_t &that) const {
  this->check_moduli(that);
  return this->residue < that.residue;
}

// ----------------------------------------------------------------
bool intmod_t::operator<=(const intmod_t &that) const {
  this->check_moduli(that);
  return this->residue <= that.residue;
}

// ----------------------------------------------------------------
bool intmod_t::operator>(const intmod_t &that) const {
  this->check_moduli(that);
  return this->residue > that.residue;
}

// ----------------------------------------------------------------
bool intmod_t::operator>=(const intmod_t &that) const {
  this->check_moduli(that);
  return this->residue >= that.residue;
}

// ----------------------------------------------------------------
int intmod_t::get_residue(void) const { return this->residue; }

// ----------------------------------------------------------------
int intmod_t::get_modulus(void) const { return this->modulus; }

// ----------------------------------------------------------------
intmod_t::intmod_t(int arg_residue, int arg_modulus) {
  if (arg_modulus <= 0) {
    std::stringstream ss;
    ss << "intmod_t: non-positive modulus " << arg_modulus << " disallowed.";
    ss << std::endl;
    throw spffl::exception_t(ss.str());
  }
  this->residue = arg_residue;
  this->modulus = arg_modulus;
  this->residue = this->residue % this->modulus;
  if (this->residue < 0) { // Wacky C mod operator.
    this->residue += this->modulus;
  }
}

// ----------------------------------------------------------------
intmod_t::intmod_t(const intmod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
}

// ----------------------------------------------------------------
intmod_t::intmod_t(void) {
  this->residue = -1;
  this->modulus = 0;
}

// ----------------------------------------------------------------
intmod_t::~intmod_t(void) {}

// ----------------------------------------------------------------
void intmod_t::check_moduli(const intmod_t &that) const {
  this->check_modulus();
  that.check_modulus();
  if (this->modulus != that.modulus) {
    std::stringstream ss;
    ss << "intmod_t: mixed moduli " << this->modulus << ", " << that.modulus
       << ".";
    ss << std::endl;
    throw spffl::exception_t(ss.str());
  }
}

// ----------------------------------------------------------------
// Unfortunately a default ctor is sometimes necessary (e.g. for matrices
// and vectors): the modulus must sometimes be specified *after* construction.
// Yet we don't want such data being used for arithmetic.
void intmod_t::check_modulus(void) const {
  if (this->modulus == 0) {
    std::stringstream ss;
    ss << "intmod_t: unspecified modulus.\n";
    throw spffl::exception_t(ss.str());
  }
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator=(const intmod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
  return *this;
}

// ----------------------------------------------------------------
intmod_t intmod_t::operator+(const intmod_t &that) const {
  this->check_moduli(that);
  intmod_t rv(this->residue + that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
intmod_t intmod_t::operator-(const intmod_t &that) const {
  this->check_moduli(that);
  intmod_t rv(this->modulus + this->residue - that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
intmod_t intmod_t::operator-(void) const {
  this->check_modulus();
  intmod_t rv(this->modulus - this->residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
intmod_t intmod_t::operator*(const intmod_t &that) const {
  this->check_moduli(that);
  intmod_t rv(this->residue * that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
intmod_t intmod_t::operator+(int a) const {
  intmod_t rv(this->residue + a, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
intmod_t intmod_t::operator-(int a) const {
  intmod_t rv(this->modulus + this->residue - a, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
intmod_t intmod_t::operator*(int a) const {
  intmod_t rv(this->residue * a, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
intmod_t intmod_t::operator/(const intmod_t &that) const {
  this->check_moduli(that);

  intmod_t bi;
  if (!that.recip(bi)) {
    std::stringstream ss;
    ss << "intmod_t::operator/:  zero or zero divisor: " << that.residue
       << " mod " << that.modulus << ".";
    throw spffl::exception_t(ss.str());
  }

  return *this * bi;
}

// ----------------------------------------------------------------
intmod_t intmod_t::operator%(const intmod_t &that) const {
  this->check_moduli(that);

  intmod_t bi;
  if (!that.recip(bi)) {
    std::stringstream ss;
    ss << "intmod_t::operator%:  zero or zero divisor: " << that.residue
       << " mod " << that.modulus << ".\n";
    throw spffl::exception_t(ss.str());
  }

  return *this - *this;
}

// ----------------------------------------------------------------
bool intmod_t::recip(intmod_t &rinv) const {
  this->check_modulus();

  if (this->modulus == 2) {
    if (this->residue == 0) {
      return false;
    } else {
      rinv = *this;
      return true;
    }
  }

  static int mlast = 2;
  static int phi   = 1;
  if (this->modulus != mlast) { // Cache
    mlast = this->modulus;
    phi   = int_totient(this->modulus);
  }

  intmod_t rv = this->exp(phi - 1);
  int check   = (this->residue * rv.residue) % this->modulus;
  if (check != 1) {
    return false;
  } else {
    rinv = rv;
    return true;
  }
}

} // namespace spffl::intmath
