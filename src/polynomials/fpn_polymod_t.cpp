// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fpn_polymod_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

// ----------------------------------------------------------------
fpn_polymod_t::fpn_polymod_t(fpn_poly_t arg_residue, fpn_poly_t arg_modulus) {
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
fpn_polymod_t fpn_polymod_t::prime_sfld_elt(int v) const {
  fpn_poly_t m = this->modulus;
  fpn_poly_t r = this->residue.prime_sfld_elt(v);
  return fpn_polymod_t(r, m);
}

// ----------------------------------------------------------------
// This is a static method.
fpn_polymod_t fpn_polymod_t::prime_sfld_elt(int v, fpn_poly_t om) {
  fp_poly_t im = om.get_coeff(0).get_modulus();
  return fpn_polymod_t(fpn_poly_t::prime_sfld_elt(v, im), om);
}

// ----------------------------------------------------------------
int fpn_polymod_t::get_characteristic(void) { return this->residue.get_characteristic(); }

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator=(fpn_polymod_t that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator+(fpn_polymod_t that) {
  this->check_moduli(that);
  fpn_polymod_t rv(this->residue + that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator-(fpn_polymod_t that) {
  this->check_moduli(that);
  fpn_polymod_t rv(this->residue - that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator-(void) {
  fpn_polymod_t rv(-this->residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator*(fpn_polymod_t that) {
  this->check_moduli(that);
  fpn_polymod_t rv(this->residue * that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator*(int a) {
  // xxx get the characteristic and reduce a mod that.
  fpn_polymod_t rv = *this - *this;
  for (int i = 0; i < a; i++)
    rv += *this;
  return rv;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator/(fpn_polymod_t that) {
  this->check_moduli(that);

  fpn_polymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "fpn_polymod_t::operator/:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this * bi;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::operator%(fpn_polymod_t that) {
  this->check_moduli(that);

  fpn_polymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "fpn_polymod_t::operator%:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this - *this;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::recip(fpn_polymod_t &rinv) {
  fpn_poly_t g, a, b;
  g = this->residue.ext_gcd(this->modulus, a, b);

  // Error check:
  if (g.find_degree() != 0) {
    // std::cerr << "fpn_polymod recip: zero or zero divisor.\n";
    return false;
  }

  // Ext. GCD actually returns a scalar multiple of 1.  Divide this out.
  fp_polymod_t c0i;
  if (!g.get_coeff(0).recip(c0i)) {
    std::cerr << "fpn_polymod_t::recip:  zero or zero divisor "
              << " in GCD " << g << ".\n";
    exit(1);
  }
  a *= c0i;
  fpn_polymod_t rv(a, this->modulus);
  rinv = rv;
  return true;
}

// ----------------------------------------------------------------
fpn_polymod_t fpn_polymod_t::exp(int e) {
  fpn_poly_t xp = this->residue;
  fpn_polymod_t zero(this->residue.prime_sfld_elt(0), this->modulus);
  fpn_polymod_t one(this->residue.prime_sfld_elt(1), this->modulus);
  fpn_polymod_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::cerr << "fpn_polymod_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::cerr << "fpn_polymod_t::exp:  division by zero.\n";
      exit(1);
    }
    if (e == -e) {
      std::cerr << "fpn_polymod_t::exp:  can't handle "
                   "MIN_INT.\n";
      exit(1);
    }
    fpn_polymod_t inv = one / *this;
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
std::ostream &operator<<(std::ostream &os, const fpn_polymod_t &a) {
  int adeg = a.residue.find_degree();
  int rdeg = a.modulus.find_degree() - 1;
  int max = adeg > rdeg ? adeg : rdeg;
  fp_poly_t m = a.residue.get_coeff(0).get_modulus();

  for (int i = max; i >= 0; i--) {
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
std::istringstream &operator>>(std::istringstream &iss, fpn_polymod_t &a) {
  iss >> a.residue; // Modulus must be already set.
  a.residue %= a.modulus;
  return iss;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::from_string(char *string, fpn_poly_t &m) {
  fpn_poly_t r;
  fp_poly_t mm = m.get_coeff(0).get_modulus();
  if (!r.from_string(string, mm))
    return false;
  *this = fpn_polymod_t(r, m);
  return true;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator+=(fpn_polymod_t that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator-=(fpn_polymod_t that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator*=(fpn_polymod_t that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator*=(int a) {
  *this = *this * a;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator/=(fpn_polymod_t that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
fpn_polymod_t &fpn_polymod_t::operator%=(fpn_polymod_t that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator==(fpn_polymod_t that) const {
  if (this->residue != that.residue)
    return false;
  if (this->modulus != that.modulus)
    return false;
  return true;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator!=(fpn_polymod_t that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator==(int that) const { return this->residue == that; }

// ----------------------------------------------------------------
bool fpn_polymod_t::operator!=(int that) const { return this->residue != that; }

// ----------------------------------------------------------------
bool fpn_polymod_t::operator<(fpn_polymod_t that) const {
  this->check_moduli(that);
  return this->residue < that.residue;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator<=(fpn_polymod_t that) const {
  this->check_moduli(that);
  return this->residue <= that.residue;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator>(fpn_polymod_t that) const {
  this->check_moduli(that);
  return this->residue > that.residue;
}

// ----------------------------------------------------------------
bool fpn_polymod_t::operator>=(fpn_polymod_t that) const {
  this->check_moduli(that);
  return this->residue >= that.residue;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_polymod_t::get_residue(void) const { return this->residue; }

// ----------------------------------------------------------------
fpn_poly_t fpn_polymod_t::get_modulus(void) const { return this->modulus; }

// ----------------------------------------------------------------
void fpn_polymod_t::check_moduli(fpn_polymod_t &that) const {
  if (this->modulus != that.modulus) {
    std::cerr << "fpn_polymod_t: mixed moduli " << this->modulus << ", "
              << that.modulus << ".";
    std::cerr << std::endl;
    exit(1);
  }
}

} // namespace spffl::polynomials
