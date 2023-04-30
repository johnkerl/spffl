// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fp_polyrat_t.h"
#include "cmps.h"
#include <iomanip>
#include <iostream>

namespace spffl::rationals {

// ----------------------------------------------------------------
fp_polyrat_t::fp_polyrat_t(const spffl::polynomials::fp_poly_t &numerator,
    const spffl::polynomials::fp_poly_t &denominator) {
  this->numer = numerator;
  this->denom = denominator;
  this->simplify();
}

// ----------------------------------------------------------------
fp_polyrat_t::fp_polyrat_t(const spffl::polynomials::fp_poly_t &numerator) {
  this->numer = numerator;
  this->denom = numerator.prime_sfld_elt(1);
  this->simplify();
}

// ----------------------------------------------------------------
fp_polyrat_t::fp_polyrat_t(const fp_polyrat_t &that) {
  this->numer = that.numer;
  this->denom = that.denom;
}

// ----------------------------------------------------------------
fp_polyrat_t::fp_polyrat_t(void) {}

// ----------------------------------------------------------------
fp_polyrat_t::~fp_polyrat_t(void) {}

// ----------------------------------------------------------------
fp_polyrat_t fp_polyrat_t::prime_sfld_elt(int v) const {
  spffl::polynomials::fp_poly_t a = this->numer.prime_sfld_elt(v);
  return fp_polyrat_t(a);
}

// ----------------------------------------------------------------
// This is a static method.
fp_polyrat_t fp_polyrat_t::prime_sfld_elt(int v, int p) {
  return fp_polyrat_t(
      spffl::polynomials::fp_poly_t(spffl::intmath::intmod_t(v, p)));
}

// ----------------------------------------------------------------
int fp_polyrat_t::get_characteristic(void) const {
  return this->numer.get_characteristic();
}

// ----------------------------------------------------------------
fp_polyrat_t &fp_polyrat_t::operator=(const fp_polyrat_t &that) {
  this->numer = that.numer;
  this->denom = that.denom;
  return *this;
}

// ----------------------------------------------------------------
fp_polyrat_t &fp_polyrat_t::operator=(spffl::polynomials::fp_poly_t numerator) {
  this->numer = numerator;
  this->denom = numerator.prime_sfld_elt(1);
  this->simplify();
  return *this;
}

// ----------------------------------------------------------------
//  a     c    ad + bc
// --- + --- = -------
//  b     d      bd

fp_polyrat_t fp_polyrat_t::operator+(const fp_polyrat_t &that) const {
  fp_polyrat_t rv;
  rv.numer = this->numer * that.denom + this->denom * that.numer;
  rv.denom = this->denom * that.denom;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
fp_polyrat_t fp_polyrat_t::operator-(const fp_polyrat_t &that) const {
  fp_polyrat_t rv;
  rv.numer = this->numer * that.denom - this->denom * that.numer;
  rv.denom = this->denom * that.denom;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
fp_polyrat_t fp_polyrat_t::operator-(void) const {
  fp_polyrat_t rv;
  rv.numer = -this->numer;
  rv.denom = this->denom;
  return rv;
}

// ----------------------------------------------------------------
fp_polyrat_t fp_polyrat_t::operator*(const fp_polyrat_t &that) {
  fp_polyrat_t rv;
  rv.numer = this->numer * that.numer;
  rv.denom = this->denom * that.denom;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
fp_polyrat_t fp_polyrat_t::operator/(const fp_polyrat_t &that) {
  fp_polyrat_t rv;
  rv.numer = this->numer * that.denom;
  rv.denom = this->denom * that.numer;
  rv.simplify();
  return rv;
}

// ----------------------------------------------------------------
fp_polyrat_t fp_polyrat_t::operator%(const fp_polyrat_t &that) {
  fp_polyrat_t rv;
  fp_polyrat_t zero = that - that;
  if (that == zero) {
    std::cerr << "fp_polyrat_t: Divide by zero.\n";
    exit(1);
  }
  return zero;
}

// ----------------------------------------------------------------
fp_polyrat_t fp_polyrat_t::exp(int e) const {
  fp_polyrat_t xp = *this;
  fp_polyrat_t zero(this->numer.prime_sfld_elt(0));
  fp_polyrat_t one(this->numer.prime_sfld_elt(1));
  fp_polyrat_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::cerr << "fp_polyrat_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::cerr << "fp_polyrat_t::exp:  division by zero.\n";
      exit(1);
    }
    if (e == -e) {
      std::cerr << "fp_polyrat_t::exp:  can't handle "
                   "MIN_FPPOLY.\n";
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
std::ostream &operator<<(std::ostream &os, const fp_polyrat_t &a) {
  os << a.numer;
  if (a.denom != 1) {
    os << "/" << a.denom;
  }
  return os;
}

// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, fp_polyrat_t &a) {
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
    a.denom = a.numer.prime_sfld_elt(1);
  }
  if (is.peek() == '/') {
    (void)is.get();
    is >> a.denom;
  } else {
    // Clear failure code from not having found the '/'.
    is.clear();
    a.denom = a.numer.prime_sfld_elt(1);
  }
  a.simplify();
  return is;
}

// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, fp_polyrat_t &a) {
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
    a.denom = a.numer.prime_sfld_elt(1);
  } else if (iss.peek() == '/') {
    (void)iss.get();
    iss >> a.denom;
  } else {
    // Clear failure code from not having found the '/'.
    iss.clear();
    a.denom = a.numer.prime_sfld_elt(1);
  }
  a.simplify();
  return iss;
}

// ----------------------------------------------------------------
bool fp_polyrat_t::from_string(const char *string, int p) {
  this->numer = spffl::polynomials::fp_poly_t(spffl::intmath::intmod_t(0, p));
  this->denom = spffl::polynomials::fp_poly_t(spffl::intmath::intmod_t(1, p));
  std::istringstream iss(string, std::ios_base::in);
  iss >> *this;
  return iss.fail() ? false : true;
}

// ----------------------------------------------------------------
fp_polyrat_t &fp_polyrat_t::operator+=(const fp_polyrat_t &that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
fp_polyrat_t &fp_polyrat_t::operator-=(const fp_polyrat_t &that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
fp_polyrat_t &fp_polyrat_t::operator*=(const fp_polyrat_t &that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
fp_polyrat_t &fp_polyrat_t::operator/=(const fp_polyrat_t &that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
fp_polyrat_t &fp_polyrat_t::operator%=(const fp_polyrat_t &that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
bool fp_polyrat_t::operator==(const fp_polyrat_t &that) const {
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
bool fp_polyrat_t::operator!=(const fp_polyrat_t &that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool fp_polyrat_t::operator==(spffl::polynomials::fp_poly_t that) const {
  if (this->denom != this->numer.prime_sfld_elt(1)) {
    return false;
  }
  return this->numer == that;
}

// ----------------------------------------------------------------
bool fp_polyrat_t::operator!=(spffl::polynomials::fp_poly_t that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool fp_polyrat_t::operator<(const fp_polyrat_t &that) const {
  return ((this->numer * that.denom) < (this->denom * that.numer));
}

// ----------------------------------------------------------------
bool fp_polyrat_t::operator<=(const fp_polyrat_t &that) const {
  return ((this->numer * that.denom) <= (this->denom * that.numer));
}

// ----------------------------------------------------------------
bool fp_polyrat_t::operator>(const fp_polyrat_t &that) const {
  return ((this->numer * that.denom) > (this->denom * that.numer));
}

// ----------------------------------------------------------------
bool fp_polyrat_t::operator>=(const fp_polyrat_t &that) const {
  return ((this->numer * that.denom) >= (this->denom * that.numer));
}

// ----------------------------------------------------------------
spffl::polynomials::fp_poly_t fp_polyrat_t::get_numerator(void) const {
  return this->numer;
}

// ----------------------------------------------------------------
spffl::polynomials::fp_poly_t fp_polyrat_t::get_denominator(void) const {
  return this->denom;
}

// ----------------------------------------------------------------
// * Check denominator != 0
// * Divide numerator and denominator by their GCD

void fp_polyrat_t::simplify(void) {
  spffl::polynomials::fp_poly_t g;
  if (this->denom == 0) {
    std::cerr << "rat: Divide by zero.\n";
    exit(1);
  }
  g = this->numer.gcd(this->denom);
  this->numer /= g;
  this->denom /= g;
}

} // namespace spffl::rationals
