// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fp_polymod_t.h"
#include <iomanip>
#include <iostream>

// ----------------------------------------------------------------
fp_polymod_t::fp_polymod_t(fp_poly_t arg_residue, fp_poly_t arg_modulus) {
  this->residue = arg_residue;
  this->modulus = arg_modulus;
  this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
fp_polymod_t::fp_polymod_t(const fp_polymod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
}

// ----------------------------------------------------------------
fp_polymod_t::fp_polymod_t(void) {
  fp_poly_t invalid;
  this->residue = invalid;
  this->modulus = invalid;
}

// ----------------------------------------------------------------
fp_polymod_t::~fp_polymod_t(void) {
  fp_poly_t invalid;
  this->residue = invalid;
  this->modulus = invalid;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::prime_sfld_elt(int v) const {
  fp_poly_t m = this->modulus;
  fp_poly_t r = this->residue.prime_sfld_elt(v);
  return fp_polymod_t(r, m);
}

// ----------------------------------------------------------------
// This is a static method.
fp_polymod_t fp_polymod_t::prime_sfld_elt(int v, fp_poly_t m) {
  return fp_polymod_t(m.prime_sfld_elt(v), m);
}

// ----------------------------------------------------------------
int fp_polymod_t::get_char(void) { return this->residue.get_char(); }

// ----------------------------------------------------------------
fp_polymod_t &fp_polymod_t::operator=(fp_polymod_t that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
  return *this;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::operator+(fp_polymod_t that) {
  this->check_moduli(that);
  fp_polymod_t rv(this->residue + that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::operator-(fp_polymod_t that) {
  this->check_moduli(that);
  fp_polymod_t rv(this->residue - that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::operator-(void) {
  fp_polymod_t rv(-this->residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::operator*(fp_polymod_t that) {
  this->check_moduli(that);
  fp_polymod_t rv(this->residue * that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::operator*(int a) {
  fp_polymod_t rv(*this);
  int p = this->get_char();
  a %= p;
  if (a == 0) {
    rv = rv - rv;
  } else {
    for (int i = 1; i < a; i++)
      rv += *this;
  }
  return rv;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::operator*(spffl::intmath::intmod_t a) {
  fp_polymod_t rv(*this);
  rv.modulus *= a;
  return rv;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::operator/(fp_polymod_t that) {
  this->check_moduli(that);

  fp_polymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "fp_polymod_t::operator/:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this * bi;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::operator%(fp_polymod_t that) {
  this->check_moduli(that);

  fp_polymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "fp_polymod_t::operator%:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this - *this;
}

// ----------------------------------------------------------------
int fp_polymod_t::recip(fp_polymod_t &rinv) {
  fp_poly_t g, a, b;
  g = this->residue.ext_gcd(this->modulus, a, b);

  // Error check:
  if (g.find_degree() != 0) {
    // std::cerr << "fppolymod recip: zero or zero divisor.\n";
    return 0;
  }

  // Ext. GCD actually returns a scalar multiple of 1.  Divide this out.
  spffl::intmath::intmod_t c0i;
  if (!g.get_coeff(0).recip(c0i)) {
    std::cerr << "fp_polymod_t::recip:  zero or zero divisor "
              << " in GCD " << g << ".\n";
    exit(1);
  }
  a *= c0i;
  fp_polymod_t rv(a, this->modulus);
  rinv = rv;
  return 1;
}

// ----------------------------------------------------------------
fp_polymod_t fp_polymod_t::exp(int e) {
  fp_poly_t xp = this->residue;
  fp_polymod_t zero(this->residue.prime_sfld_elt(0), this->modulus);
  fp_polymod_t one(this->residue.prime_sfld_elt(1), this->modulus);
  fp_polymod_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::cerr << "fp_polymod_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::cerr << "fp_polymod_t::exp:  division by zero.\n";
      exit(1);
    }
    if (e == -e) {
      std::cerr << "fp_polymod_t::exp:  can't handle "
                   "MIN_INT.\n";
      exit(1);
    }
    fp_polymod_t inv = one / *this;
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
std::ostream &operator<<(std::ostream &os, const fp_polymod_t &a) {
  int adeg = a.residue.find_degree();
  int rdeg = a.modulus.find_degree() - 1;
  int max = adeg > rdeg ? adeg : rdeg;
  int m = a.residue.get_coeff(0).get_modulus();

  for (int i = max; i >= 0; i--) {
    if (m > 9)
      if (i < max)
        os << ",";
    if (i > adeg)
      os << 0;
    else
      os << a.residue.get_coeff(i).get_residue();
  }

  return os;
}

// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, fp_polymod_t &a) {
  iss >> a.residue; // Modulus must be already set.
  a.residue %= a.modulus;
  return iss;
}

// ----------------------------------------------------------------
int fp_polymod_t::from_string(char *string, fp_poly_t &m) {
  fp_poly_t r;
  int p = m.get_char();
  if (!r.from_string(string, p))
    return 0;
  *this = fp_polymod_t(r, m);
  return 1;
}

// ----------------------------------------------------------------
fp_polymod_t &fp_polymod_t::operator+=(fp_polymod_t that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
fp_polymod_t &fp_polymod_t::operator-=(fp_polymod_t that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
fp_polymod_t &fp_polymod_t::operator*=(fp_polymod_t that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
fp_polymod_t &fp_polymod_t::operator*=(int a) {
  *this = *this * a;
  return *this;
}

// ----------------------------------------------------------------
fp_polymod_t &fp_polymod_t::operator*=(spffl::intmath::intmod_t a) {
  *this = *this * a;
  return *this;
}

// ----------------------------------------------------------------
fp_polymod_t &fp_polymod_t::operator/=(fp_polymod_t that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
fp_polymod_t &fp_polymod_t::operator%=(fp_polymod_t that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
int fp_polymod_t::operator==(fp_polymod_t that) const {
  if (this->residue != that.residue)
    return 0;
  if (this->modulus != that.modulus)
    return 0;
  return 1;
}

// ----------------------------------------------------------------
int fp_polymod_t::operator!=(fp_polymod_t that) const { return !(*this == that); }

// ----------------------------------------------------------------
int fp_polymod_t::operator==(int that) const { return this->residue == that; }

// ----------------------------------------------------------------
int fp_polymod_t::operator!=(int that) const { return this->residue != that; }

// ----------------------------------------------------------------
int fp_polymod_t::operator<(fp_polymod_t that) const {
  this->check_moduli(that);
  return this->residue < that.residue;
}

// ----------------------------------------------------------------
int fp_polymod_t::operator<=(fp_polymod_t that) const {
  this->check_moduli(that);
  return this->residue <= that.residue;
}

// ----------------------------------------------------------------
int fp_polymod_t::operator>(fp_polymod_t that) const {
  this->check_moduli(that);
  return this->residue > that.residue;
}

// ----------------------------------------------------------------
int fp_polymod_t::operator>=(fp_polymod_t that) const {
  this->check_moduli(that);
  return this->residue >= that.residue;
}

// ----------------------------------------------------------------
fp_poly_t fp_polymod_t::get_residue(void) const { return this->residue; }

// ----------------------------------------------------------------
fp_poly_t fp_polymod_t::get_modulus(void) const { return this->modulus; }

// ----------------------------------------------------------------
void fp_polymod_t::check_moduli(fp_polymod_t &that) const {
  if (this->modulus != that.modulus) {
    std::cerr << "fp_polymod_t: mixed moduli " << this->modulus << ", "
              << that.modulus << ".";
    std::cerr << std::endl;
    exit(1);
  }
}
