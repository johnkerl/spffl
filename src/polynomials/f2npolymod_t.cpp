// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2npolymod_t.h"
#include <iomanip>
#include <iostream>

// ----------------------------------------------------------------
f2npolymod_t::f2npolymod_t(f2npoly_t arg_residue, f2npoly_t arg_modulus) {
  this->residue = arg_residue;
  this->modulus = arg_modulus;
  this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
f2npolymod_t::f2npolymod_t(const f2npolymod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
}

// ----------------------------------------------------------------
f2npolymod_t::f2npolymod_t(void) {
  f2npoly_t invalid;
  this->residue = invalid;
  this->modulus = invalid;
}

// ----------------------------------------------------------------
f2npolymod_t::~f2npolymod_t(void) {
  f2npoly_t invalid;
  this->residue = invalid;
  this->modulus = invalid;
}

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_t::prime_sfld_elt(int v) const {
  f2npoly_t m = this->modulus;
  f2npoly_t r = this->residue.prime_sfld_elt(v);
  return f2npolymod_t(r, m);
}

// ----------------------------------------------------------------
// This is a static method.
f2npolymod_t f2npolymod_t::prime_sfld_elt(int v, f2npoly_t om) {
  f2poly_t im = om.get_coeff(0).get_modulus();
  return f2npolymod_t(f2npoly_t::prime_sfld_elt(v, im), om);
}

// ----------------------------------------------------------------
int f2npolymod_t::get_char(void) { return 2; }

// ----------------------------------------------------------------
f2npolymod_t &f2npolymod_t::operator=(f2npolymod_t that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
  return *this;
}

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_t::operator+(f2npolymod_t that) {
  this->check_moduli(that);
  f2npolymod_t rv(this->residue + that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_t::operator-(f2npolymod_t that) {
  this->check_moduli(that);
  f2npolymod_t rv(this->residue - that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_t::operator-(void) {
  f2npolymod_t rv(-this->residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_t::operator*(f2npolymod_t that) {
  this->check_moduli(that);
  f2npolymod_t rv(this->residue * that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_t::operator*(int a) {
  // Characteristic is 2, so there are two possibilities.
  f2npolymod_t rv(*this);
  if (a & 1)
    ;
  else
    rv = rv - rv;
  return rv;
}

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_t::operator/(f2npolymod_t that) {
  this->check_moduli(that);

  f2npolymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "f2npolymod_t::operator/:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this * bi;
}

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_t::operator%(f2npolymod_t that) {
  this->check_moduli(that);

  f2npolymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "f2npolymod_t::operator%:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this - *this;
}

// ----------------------------------------------------------------
int f2npolymod_t::recip(f2npolymod_t &rinv) {
  f2npoly_t g, a, b;
  g = this->residue.ext_gcd(this->modulus, a, b);

  // Error check:
  if (g.find_degree() != 0) {
    // std::cerr << "f2npolymod recip: zero or zero divisor.\n";
    return 0;
  }

  // Ext. GCD actually returns a scalar multiple of 1.  Divide this out.
  f2polymod_t c0i;
  if (!g.get_coeff(0).recip(c0i)) {
    std::cerr << "f2npolymod_t::recip:  zero or zero divisor "
              << " in GCD " << g << ".\n";
    exit(1);
  }
  a *= c0i;
  f2npolymod_t rv(a, this->modulus);
  rinv = rv;
  return 1;
}

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_t::exp(int e) {
  f2npoly_t xp = this->residue;
  f2npolymod_t zero(this->residue.prime_sfld_elt(0), this->modulus);
  f2npolymod_t one(this->residue.prime_sfld_elt(1), this->modulus);
  f2npolymod_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::cerr << "f2npolymod_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::cerr << "f2npolymod_t::exp:  division by zero.\n";
      exit(1);
    }
    if (e == -e) {
      std::cerr << "f2npolymod_t::exp:  can't handle "
                   "MIN_INT.\n";
      exit(1);
    }
    f2npolymod_t inv = one / *this;
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
std::ostream &operator<<(std::ostream &os, const f2npolymod_t &a) {
  int adeg = a.residue.find_degree();
  int rdeg = a.modulus.find_degree() - 1;
  int max = adeg > rdeg ? adeg : rdeg;
  f2poly_t m = a.residue.get_coeff(0).get_modulus();

  for (int i = max; i >= 0; i--) {
    if (m > 9)
      if (i < max)
        os << ":";
    if (i > adeg)
      os << 0;
    else
      os << a.residue.get_coeff(i).get_residue();
  }

  return os;
}

// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, f2npolymod_t &a) {
  iss >> a.residue; // Modulus must be already set.
  a.residue %= a.modulus;
  return iss;
}

// ----------------------------------------------------------------
int f2npolymod_t::from_string(char *string, f2npoly_t &m) {
  f2npoly_t r;
  f2poly_t mm = m.get_coeff(0).get_modulus();
  if (!r.from_string(string, mm))
    return 0;
  *this = f2npolymod_t(r, m);
  return 1;
}

// ----------------------------------------------------------------
f2npolymod_t &f2npolymod_t::operator+=(f2npolymod_t that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
f2npolymod_t &f2npolymod_t::operator-=(f2npolymod_t that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
f2npolymod_t &f2npolymod_t::operator*=(f2npolymod_t that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
f2npolymod_t &f2npolymod_t::operator*=(int a) {
  *this = *this * a;
  return *this;
}

// ----------------------------------------------------------------
f2npolymod_t &f2npolymod_t::operator/=(f2npolymod_t that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
f2npolymod_t &f2npolymod_t::operator%=(f2npolymod_t that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
int f2npolymod_t::operator==(f2npolymod_t that) const {
  if (this->residue != that.residue)
    return 0;
  if (this->modulus != that.modulus)
    return 0;
  return 1;
}

// ----------------------------------------------------------------
int f2npolymod_t::operator!=(f2npolymod_t that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
int f2npolymod_t::operator==(int that) const { return this->residue == that; }

// ----------------------------------------------------------------
int f2npolymod_t::operator!=(int that) const { return this->residue != that; }

// ----------------------------------------------------------------
int f2npolymod_t::operator<(f2npolymod_t that) const {
  this->check_moduli(that);
  return this->residue < that.residue;
}

// ----------------------------------------------------------------
int f2npolymod_t::operator<=(f2npolymod_t that) const {
  this->check_moduli(that);
  return this->residue <= that.residue;
}

// ----------------------------------------------------------------
int f2npolymod_t::operator>(f2npolymod_t that) const {
  this->check_moduli(that);
  return this->residue > that.residue;
}

// ----------------------------------------------------------------
int f2npolymod_t::operator>=(f2npolymod_t that) const {
  this->check_moduli(that);
  return this->residue >= that.residue;
}

// ----------------------------------------------------------------
f2npoly_t f2npolymod_t::get_residue(void) const { return this->residue; }

// ----------------------------------------------------------------
f2npoly_t f2npolymod_t::get_modulus(void) const { return this->modulus; }

// ----------------------------------------------------------------
void f2npolymod_t::check_moduli(f2npolymod_t &that) const {
  if (this->modulus != that.modulus) {
    std::cerr << "f2npolymod_t: mixed moduli " << this->modulus << ", "
              << that.modulus << ".";
    std::cerr << std::endl;
    exit(1);
  }
}
