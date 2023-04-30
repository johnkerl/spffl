// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "intrat_t.h"
#include "cmps.h"
#include "int_gcd.h"
#include "int_totient.h"
#include <iomanip>
#include <iostream>
#include <stdlib.h>

namespace spffl::rationals {

// ----------------------------------------------------------------
intrat_t::intrat_t(int numerator, int denominator) {
  this->numer = numerator;
  this->denom = denominator;
  this->simplify();
}

// ----------------------------------------------------------------
intrat_t::intrat_t(int numerator) {
  this->numer = numerator;
  this->denom = 1;
  this->simplify();
}

// ----------------------------------------------------------------
intrat_t::intrat_t(const intrat_t &that) {
  this->numer = that.numer;
  this->denom = that.denom;
}

// ----------------------------------------------------------------
intrat_t::intrat_t(void) {
  this->numer = 0;
  this->denom = 1;
}

// ----------------------------------------------------------------
intrat_t::~intrat_t(void) {
  this->numer = 0;
  this->denom = 1;
}

// ----------------------------------------------------------------
intrat_t &intrat_t::operator=(const intrat_t &that) {
  this->numer = that.numer;
  this->denom = that.denom;
  return *this;
}

// ----------------------------------------------------------------
intrat_t &intrat_t::operator=(int numerator) {
  this->numer = numerator;
  this->denom = 1;
  this->simplify();
  return *this;
}

// ----------------------------------------------------------------
//  a     c    ad + bc
// --- + --- = -------
//  b     d      bd

intrat_t intrat_t::operator+(const intrat_t &that) const {
  intrat_t rv;
  rv.numer = this->numer * that.denom + this->denom * that.numer;
  rv.denom = this->denom * that.denom;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
intrat_t intrat_t::operator-(const intrat_t &that) const {
  intrat_t rv;
  rv.numer = this->numer * that.denom - this->denom * that.numer;
  rv.denom = this->denom * that.denom;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
intrat_t intrat_t::operator-(void) const {
  intrat_t rv(*this);
  rv.numer = -rv.numer;
  return rv;
}

// ----------------------------------------------------------------
intrat_t intrat_t::operator*(const intrat_t &that) {
  intrat_t rv;
  rv.numer = this->numer * that.numer;
  rv.denom = this->denom * that.denom;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
intrat_t intrat_t::operator/(const intrat_t &that) {
  intrat_t rv;
  rv.numer = this->numer * that.denom;
  rv.denom = this->denom * that.numer;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
intrat_t intrat_t::operator%(const intrat_t &that) {
  intrat_t rv;
  intrat_t zero = that - that;
  if (that == zero) {
    std::cerr << "intrat_t: Divide by zero.\n";
    exit(1);
  }
  return zero;
}

// ----------------------------------------------------------------
intrat_t intrat_t::exp(int e) {
  intrat_t xp = *this;
  intrat_t zero(0);
  intrat_t one(1);
  intrat_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::cerr << "intrat_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::cerr << "intrat_t::exp:  division by zero.\n";
      exit(1);
    }
    if (e == -e) {
      std::cerr << "intrat_t::exp:  can't handle "
                   "MIN_INT.\n";
      exit(1);
    }
    xp = one / xp;
    e  = -e;
  }

  while (e != 0) {
    if (e & 1) {
      rv *= xp;
    }
    e = (unsigned)e >> 1;
    xp *= xp;
  }

  return rv;
}

// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const intrat_t &a) {
  os << a.numer;
  if (a.denom != 1) {
    os << "/" << a.denom;
  }
  return os;
}

// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, intrat_t &a) {
  // Attempt to skip over whitespace.
  // The istringstream class appears to permit no way to ignore a set of
  // characters.  E.g. if the input is 0, space, tab, space, 1, then the
  // following won't suffice.

  while (is.peek() == ' ') {
    is.ignore(1, ' ');
  }
  while (is.peek() == '\t') {
    is.ignore(1, '\t');
  }
  while (is.peek() == '\n') {
    is.ignore(1, '\n');
  }

  is >> a.numer;
  if (is.eof()) {
    a.denom = 1;
  }
  if (is.peek() == '/') {
    (void)is.get();
    is >> a.denom;
  } else {
    // Clear failure code from not having found the '/'.
    is.clear();
    a.denom = 1;
  }
  a.simplify();
  return is;
}

// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, intrat_t &a) {
  // Attempt to skip over whitespace.
  // The istringstream class appears to permit no way to ignore a set of
  // characters.  E.g. if the input is 0, space, tab, space, 1, then the
  // following won't suffice.

  while (iss.peek() == ' ') {
    iss.ignore(1, ' ');
  }
  while (iss.peek() == '\t') {
    iss.ignore(1, '\t');
  }
  while (iss.peek() == '\n') {
    iss.ignore(1, '\n');
  }

  iss >> a.numer;
  if (iss.eof()) {
    a.denom = 1;
  } else if (iss.peek() == '/') {
    (void)iss.get();
    iss >> a.denom;
  } else {
    // Clear failure code from not having found the '/'.
    iss.clear();
    a.denom = 1;
  }
  a.simplify();
  return iss;
}

// ----------------------------------------------------------------
bool intrat_t::from_string(const std::string &string) {
  std::istringstream iss(string, std::ios_base::in);
  iss >> *this;
  return iss.fail() ? false : true;
}

// ----------------------------------------------------------------
intrat_t &intrat_t::operator+=(const intrat_t &that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
intrat_t &intrat_t::operator-=(const intrat_t &that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
intrat_t &intrat_t::operator*=(const intrat_t &that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
intrat_t &intrat_t::operator/=(const intrat_t &that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
intrat_t &intrat_t::operator%=(const intrat_t &that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
bool intrat_t::operator==(const intrat_t &that) const {
  // Our constructor ensures both *this and that are already in
  // canonical form.
  if (this->numer != that.numer) {
    return false;
  }
  if (this->denom != that.denom) {
    return false;
  }
  return true;
}

// ----------------------------------------------------------------
bool intrat_t::operator!=(const intrat_t &that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool intrat_t::operator==(int that) const {
  if (this->denom != 1) {
    return false;
  }
  return this->numer == that;
}

// ----------------------------------------------------------------
bool intrat_t::operator!=(int that) const { return !(*this == that); }

// ----------------------------------------------------------------
bool intrat_t::operator<(const intrat_t &that) const {
  return ((this->numer * that.denom) < (this->denom * that.numer));
}

// ----------------------------------------------------------------
bool intrat_t::operator<=(const intrat_t &that) const {
  return ((this->numer * that.denom) <= (this->denom * that.numer));
}

// ----------------------------------------------------------------
bool intrat_t::operator>(const intrat_t &that) const {
  return ((this->numer * that.denom) > (this->denom * that.numer));
}

// ----------------------------------------------------------------
bool intrat_t::operator>=(const intrat_t &that) const {
  return ((this->numer * that.denom) >= (this->denom * that.numer));
}

// ----------------------------------------------------------------
int intrat_t::get_numerator(void) const { return this->numer; }

// ----------------------------------------------------------------
int intrat_t::get_denominator(void) const { return this->denom; }

// ----------------------------------------------------------------
// * Check denominator != 0
// * Make denominator positive
// * Divide numerator and denominator by their GCD

void intrat_t::simplify(void) {
  int g;
  if (this->denom == 0) {
    std::cerr << "rat: Divide by zero.\n";
    exit(1);
  }
  if (this->denom < 0) {
    this->numer = -this->numer;
    this->denom = -this->denom;
  }
  g = spffl::intmath::int_gcd(this->numer, this->denom);
  this->numer /= g;
  this->denom /= g;
}

} // namespace spffl::rationals
