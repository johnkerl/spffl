// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "intmod_t.h"
#include <iomanip>
#include <iostream>

// ----------------------------------------------------------------
intmod_t intmod_t::prime_sfld_elt(int v) const {
  int p = this->get_modulus();
  return intmod_t(v, p);
}

// ----------------------------------------------------------------
intmod_t intmod_t::exp(int e) {
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
    xp = inv.residue;
    e = -e;
  }

  while (e != 0) {
    if (e & 1) {
      rv.residue = (rv.residue * xp) % this->modulus;
    }
    e = (unsigned)e >> 1;
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
#define SEOF -1
std::istream &operator>>(std::istream &is, intmod_t &a) {
  // Skip over whitespace.
  int c = is.peek();
  if (c == SEOF) {
    is.setstate(std::ios::failbit);
    return is;
  }
  while ((c == ' ') || (c == '\t') || (c == '\n')) {
    is.ignore(1, c);
    c = is.peek();
  }
  if (c == SEOF) {
    is.setstate(std::ios::failbit);
    return is;
  }

  a.check_modulus();
  is >> a.residue;
  a.residue %= a.modulus;
  return is;
}

// ----------------------------------------------------------------
int intmod_t::from_string(char *string, int m) {
  int r;
  std::istringstream iss(string, std::ios_base::in);
  iss >> r;
  if (iss.fail()) {
    return 0;
  } else {
    *this = intmod_t(r, m);
    return 1;
  }
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator+=(intmod_t that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator-=(intmod_t that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator*=(intmod_t that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator/=(intmod_t that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
intmod_t &intmod_t::operator%=(intmod_t that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
int intmod_t::operator==(intmod_t that) const {
  this->check_modulus();
  that.check_modulus();
  if (this->residue != that.residue)
    return 0;
  if (this->modulus != that.modulus)
    return 0;
  return 1;
}

// ----------------------------------------------------------------
int intmod_t::operator!=(intmod_t that) const { return !(*this == that); }

// ----------------------------------------------------------------
int intmod_t::operator==(int that) const {
  this->check_modulus();
  return this->residue == that;
}

// ----------------------------------------------------------------
int intmod_t::operator!=(int that) const {
  this->check_modulus();
  return this->residue != that;
}

// ----------------------------------------------------------------
int intmod_t::operator<(intmod_t that) const {
  this->check_moduli(that);
  return this->residue < that.residue;
}

// ----------------------------------------------------------------
int intmod_t::operator<=(intmod_t that) const {
  this->check_moduli(that);
  return this->residue <= that.residue;
}

// ----------------------------------------------------------------
int intmod_t::operator>(intmod_t that) const {
  this->check_moduli(that);
  return this->residue > that.residue;
}

// ----------------------------------------------------------------
int intmod_t::operator>=(intmod_t that) const {
  this->check_moduli(that);
  return this->residue >= that.residue;
}

// ----------------------------------------------------------------
int intmod_t::get_residue(void) const { return this->residue; }

// ----------------------------------------------------------------
int intmod_t::get_modulus(void) const { return this->modulus; }
