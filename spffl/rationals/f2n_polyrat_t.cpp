// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/rationals/f2n_polyrat_t.h"
#include "spffl/base/cmps.h"
#include "spffl/base/spffl_exception.h"
#include <iomanip>
#include <iostream>

namespace spffl::rationals {

// ----------------------------------------------------------------
f2n_polyrat_t::f2n_polyrat_t(const spffl::polynomials::f2n_poly_t &numerator,
    const spffl::polynomials::f2n_poly_t &denominator) {
  this->numer = numerator;
  this->denom = denominator;
  this->simplify();
}

// ----------------------------------------------------------------
f2n_polyrat_t::f2n_polyrat_t(const spffl::polynomials::f2n_poly_t &numerator) {
  this->numer = numerator;
  this->denom = numerator.prime_subfield_element(1);
  this->simplify();
}

// ----------------------------------------------------------------
f2n_polyrat_t::f2n_polyrat_t(const f2n_polyrat_t &that) {
  this->numer = that.numer;
  this->denom = that.denom;
}

// ----------------------------------------------------------------
f2n_polyrat_t::f2n_polyrat_t(void) {}

// ----------------------------------------------------------------
f2n_polyrat_t::~f2n_polyrat_t(void) {}

// ----------------------------------------------------------------
f2n_polyrat_t f2n_polyrat_t::prime_subfield_element(int v) const {
  spffl::polynomials::f2n_poly_t a = this->numer.prime_subfield_element(v);
  return f2n_polyrat_t(a);
}

// ----------------------------------------------------------------
// This is a static method.
f2n_polyrat_t f2n_polyrat_t::prime_subfield_element(
    int v, const spffl::polynomials::f2_poly_t &m) {
  return f2n_polyrat_t(
      spffl::polynomials::f2n_poly_t::prime_subfield_element(v, m));
}

// ----------------------------------------------------------------
int f2n_polyrat_t::get_characteristic(void) const { return 2; }

// ----------------------------------------------------------------
f2n_polyrat_t &f2n_polyrat_t::operator=(const f2n_polyrat_t &that) {
  this->numer = that.numer;
  this->denom = that.denom;
  return *this;
}

// ----------------------------------------------------------------
f2n_polyrat_t &f2n_polyrat_t::operator=(
    const spffl::polynomials::f2n_poly_t &numerator) {
  this->numer = numerator;
  this->denom = numerator.prime_subfield_element(1);
  this->simplify();
  return *this;
}

// ----------------------------------------------------------------
//  a     c    ad + bc
// --- + --- = -------
//  b     d      bd

f2n_polyrat_t f2n_polyrat_t::operator+(const f2n_polyrat_t &that) const {
  f2n_polyrat_t rv;
  rv.numer = this->numer * that.denom + this->denom * that.numer;
  rv.denom = this->denom * that.denom;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
f2n_polyrat_t f2n_polyrat_t::operator-(const f2n_polyrat_t &that) const {
  f2n_polyrat_t rv;
  rv.numer = this->numer * that.denom - this->denom * that.numer;
  rv.denom = this->denom * that.denom;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
f2n_polyrat_t f2n_polyrat_t::operator-(void) const {
  f2n_polyrat_t rv;
  rv.numer = -this->numer;
  rv.denom = this->denom;
  return rv;
}

// ----------------------------------------------------------------
f2n_polyrat_t f2n_polyrat_t::operator*(const f2n_polyrat_t &that) {
  f2n_polyrat_t rv;
  rv.numer = this->numer * that.numer;
  rv.denom = this->denom * that.denom;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
f2n_polyrat_t f2n_polyrat_t::operator/(const f2n_polyrat_t &that) {
  f2n_polyrat_t rv;
  rv.numer = this->numer * that.denom;
  rv.denom = this->denom * that.numer;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
f2n_polyrat_t f2n_polyrat_t::operator%(const f2n_polyrat_t &that) {
  f2n_polyrat_t rv;
  f2n_polyrat_t zero = that - that;
  if (that == zero) {
    std::stringstream ss;
    ss << "f2n_polyrat_t: Divide by zero.\n";
    throw spffl::exception_t(ss.str());
  }
  return zero;
}

// ----------------------------------------------------------------
f2n_polyrat_t f2n_polyrat_t::exp(int e) const {
  f2n_polyrat_t xp = *this;
  f2n_polyrat_t zero(this->numer.prime_subfield_element(0));
  f2n_polyrat_t one(this->numer.prime_subfield_element(1));
  f2n_polyrat_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::stringstream ss;
      ss << "f2n_polyrat_t::exp:  0 ^ 0 undefined.\n";
      throw spffl::exception_t(ss.str());
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::stringstream ss;
      ss << "f2n_polyrat_t::exp:  division by zero.\n";
      throw spffl::exception_t(ss.str());
    }
    if (e == -e) {
      std::stringstream ss;
      ss << "f2n_polyrat_t::exp:  can't handle "
            "MIN_F2NPOLY.\n";
      throw spffl::exception_t(ss.str());
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
std::ostream &operator<<(std::ostream &os, const f2n_polyrat_t &a) {
  os << a.numer;
  if (a.denom != 1) {
    os << "/" << a.denom;
  }
  return os;
}

// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, f2n_polyrat_t &a) {
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
    a.denom = a.numer.prime_subfield_element(1);
  }
  if (is.peek() == '/') {
    (void)is.get();
    is >> a.denom;
  } else {
    // Clear failure code from not having found the '/'.
    is.clear();
    a.denom = a.numer.prime_subfield_element(1);
  }
  a.simplify();
  return is;
}

// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, f2n_polyrat_t &a) {
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
    a.denom = a.numer.prime_subfield_element(1);
  } else if (iss.peek() == '/') {
    (void)iss.get();
    iss >> a.denom;
  } else {
    // Clear failure code from not having found the '/'.
    iss.clear();
    a.denom = a.numer.prime_subfield_element(1);
  }
  a.simplify();
  return iss;
}

// ----------------------------------------------------------------
bool f2n_polyrat_t::from_string(
    const std::string &string, spffl::polynomials::f2_poly_t m) {
  this->numer = spffl::polynomials::f2n_poly_t(
      spffl::polynomials::f2_polymod_t(spffl::polynomials::f2_poly_t(0), m));
  this->denom = spffl::polynomials::f2n_poly_t(
      spffl::polynomials::f2_polymod_t(spffl::polynomials::f2_poly_t(1), m));
  std::istringstream iss(string, std::ios_base::in);
  iss >> *this;
  return iss.fail() ? false : true;
}

// ----------------------------------------------------------------
f2n_polyrat_t &f2n_polyrat_t::operator+=(const f2n_polyrat_t &that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
f2n_polyrat_t &f2n_polyrat_t::operator-=(const f2n_polyrat_t &that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
f2n_polyrat_t &f2n_polyrat_t::operator*=(const f2n_polyrat_t &that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
f2n_polyrat_t &f2n_polyrat_t::operator/=(const f2n_polyrat_t &that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
f2n_polyrat_t &f2n_polyrat_t::operator%=(const f2n_polyrat_t &that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
bool f2n_polyrat_t::operator==(const f2n_polyrat_t &that) const {
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
bool f2n_polyrat_t::operator!=(const f2n_polyrat_t &that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool f2n_polyrat_t::operator==(spffl::polynomials::f2n_poly_t that) const {
  if (this->denom != this->numer.prime_subfield_element(1)) {
    return false;
  }
  return this->numer == that;
}

// ----------------------------------------------------------------
bool f2n_polyrat_t::operator!=(spffl::polynomials::f2n_poly_t that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool f2n_polyrat_t::operator<(const f2n_polyrat_t &that) const {
  return ((this->numer * that.denom) < (this->denom * that.numer));
}

// ----------------------------------------------------------------
bool f2n_polyrat_t::operator<=(const f2n_polyrat_t &that) const {
  return ((this->numer * that.denom) <= (this->denom * that.numer));
}

// ----------------------------------------------------------------
bool f2n_polyrat_t::operator>(const f2n_polyrat_t &that) const {
  return ((this->numer * that.denom) > (this->denom * that.numer));
}

// ----------------------------------------------------------------
bool f2n_polyrat_t::operator>=(const f2n_polyrat_t &that) const {
  return ((this->numer * that.denom) >= (this->denom * that.numer));
}

// ----------------------------------------------------------------
spffl::polynomials::f2n_poly_t f2n_polyrat_t::get_numerator(void) const {
  return this->numer;
}

// ----------------------------------------------------------------
spffl::polynomials::f2n_poly_t f2n_polyrat_t::get_denominator(void) const {
  return this->denom;
}

// ----------------------------------------------------------------
// * Check denominator != 0
// * Divide numerator and denominator by their GCD

void f2n_polyrat_t::simplify(void) {
  spffl::polynomials::f2n_poly_t g;
  if (this->denom == 0) {
    std::stringstream ss;
    ss << "rat: Divide by zero.\n";
    throw spffl::exception_t(ss.str());
  }
  g = this->numer.gcd(this->denom);
  this->numer /= g;
  this->denom /= g;
}

} // namespace spffl::rationals
