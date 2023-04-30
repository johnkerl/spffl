// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "intmod_t.h"
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
      std::cerr << "intmod_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::cerr << "intmod_t::exp:  division by zero.\n";
      exit(1);
    }
    if (e == -e) {
      std::cerr << "intmod_t::exp:  can't handle "
                   "MIN_INT.\n";
      exit(1);
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
bool intmod_t::from_string(const char *string, int m) {
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
bool intmod_t::operator!=(const intmod_t &that) const { return !(*this == that); }

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

} // namespace spffl::intmath
