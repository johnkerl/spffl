// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2polymod_t.h"
#include <iomanip>
#include <iostream>

// ----------------------------------------------------------------
f2polymod_t::f2polymod_t(f2poly_t arg_residue, f2poly_t arg_modulus) {
  this->residue = arg_residue;
  this->modulus = arg_modulus;
  this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
f2polymod_t::f2polymod_t(const f2polymod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_t::prime_sfld_elt(int v) const {
  f2poly_t m = this->modulus;
  f2poly_t r(v & 1);
  return f2polymod_t(r, m);
}

// ----------------------------------------------------------------
// This is a static method.
f2polymod_t f2polymod_t::prime_sfld_elt(int v, f2poly_t m) {
  f2poly_t r(v & 1);
  return f2polymod_t(r, m);
}

// ----------------------------------------------------------------
int f2polymod_t::get_char(void) { return 2; }

// ----------------------------------------------------------------
f2polymod_t &f2polymod_t::operator=(f2polymod_t that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
  return *this;
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_t::operator+(f2polymod_t that) {
  this->check_moduli(that);
  f2polymod_t rv(this->residue + that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_t::operator-(f2polymod_t that) {
  this->check_moduli(that);
  f2polymod_t rv(this->residue - that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_t::operator-(void) {
  f2polymod_t rv(-this->residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_t::operator*(f2polymod_t that) {
  this->check_moduli(that);
  f2polymod_t rv(this->residue * that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_t::operator*(int a) {
  // Characteristic is 2, so there are two possibilities.
  f2polymod_t rv(*this);
  if (a & 1)
    ;
  else
    rv = rv - rv;
  return rv;
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_t::operator/(f2polymod_t that) {
  this->check_moduli(that);

  f2polymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "f2polymod_t::operator/:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this * bi;
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_t::operator%(f2polymod_t that) {
  this->check_moduli(that);

  f2polymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "f2polymod_t::operator%:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this - *this;
}

// ----------------------------------------------------------------
int f2polymod_t::recip(f2polymod_t &rinv) {
  f2poly_t g, a, b;
  g = this->residue.ext_gcd(this->modulus, a, b);

  // Error check:
  if (g.find_degree() != 0) {
    // std::cerr << "f2polymod recip: zero or zero divisor.\n";
    return 0;
  } else {
    rinv = f2polymod_t(a, this->modulus);
    return 1;
  }
}

// ----------------------------------------------------------------
f2polymod_t f2polymod_t::exp(int e) {
  f2poly_t xp = this->residue;
  f2polymod_t zero(f2poly_t(0), this->modulus);
  f2polymod_t one(f2poly_t(1), this->modulus);
  f2polymod_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::cerr << "f2polymod_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::cerr << "f2polymod_t::exp:  division by zero.\n";
      exit(1);
    }
    if (e == -e) {
      std::cerr << "f2polymod_t::exp:  can't handle "
                   "MIN_INT.\n";
      exit(1);
    }
    f2polymod_t inv = one / *this;
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
std::ostream &operator<<(std::ostream &os, const f2polymod_t &a) {
#if 0
	int rdeg   = a.residue.find_degree();
	int mdeg   = a.modulus.find_degree();
	int maxdeg = rdeg > mdeg ? rdeg : mdeg;
	int nchars = (maxdeg + 3) >> 2;

	std::ios_base::fmtflags svflags = os.flags();
	os.flags(std::ios_base::hex);

	std::cout << std::setw(nchars) << std::setfill('0') << a.residue;

	os.flags(svflags);
#else
  a.residue.dprint(os, a.modulus.find_degree() - 1);
#endif

  return os;
}

// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, f2polymod_t &a) {
  is >> a.residue; // Modulus must be already set.
  a.residue %= a.modulus;
  return is;
}

// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, f2polymod_t &a) {
  iss >> a.residue; // Modulus must be already set.
  a.residue %= a.modulus;
  return iss;
}

// ----------------------------------------------------------------
int f2polymod_t::from_string(char *string, f2poly_t m) {
  f2poly_t r;
  std::istringstream iss(string, std::ios_base::in);
  iss >> r;
  if (iss.fail()) {
    return 0;
  } else {
    *this = f2polymod_t(r, m);
    return 1;
  }
}

// ----------------------------------------------------------------
f2polymod_t &f2polymod_t::operator+=(f2polymod_t that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
f2polymod_t &f2polymod_t::operator-=(f2polymod_t that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
f2polymod_t &f2polymod_t::operator*=(f2polymod_t that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
f2polymod_t &f2polymod_t::operator*=(int a) {
  *this = *this * a;
  return *this;
}

// ----------------------------------------------------------------
f2polymod_t &f2polymod_t::operator/=(f2polymod_t that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
f2polymod_t &f2polymod_t::operator%=(f2polymod_t that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
int f2polymod_t::operator==(f2polymod_t that) const {
  if (this->residue != that.residue)
    return 0;
  if (this->modulus != that.modulus)
    return 0;
  return 1;
}

// ----------------------------------------------------------------
int f2polymod_t::operator!=(f2polymod_t that) const { return !(*this == that); }

// ----------------------------------------------------------------
int f2polymod_t::operator==(int that) const { return this->residue == that; }

// ----------------------------------------------------------------
int f2polymod_t::operator!=(int that) const { return this->residue != that; }

// ----------------------------------------------------------------
int f2polymod_t::operator<(f2polymod_t that) const {
  this->check_moduli(that);
  return this->residue < that.residue;
}

// ----------------------------------------------------------------
int f2polymod_t::operator<=(f2polymod_t that) const {
  this->check_moduli(that);
  return this->residue <= that.residue;
}

// ----------------------------------------------------------------
int f2polymod_t::operator>(f2polymod_t that) const {
  this->check_moduli(that);
  return this->residue > that.residue;
}

// ----------------------------------------------------------------
int f2polymod_t::operator>=(f2polymod_t that) const {
  this->check_moduli(that);
  return this->residue >= that.residue;
}

// ----------------------------------------------------------------
f2poly_t f2polymod_t::get_residue(void) const { return this->residue; }

// ----------------------------------------------------------------
f2poly_t f2polymod_t::get_modulus(void) const { return this->modulus; }

// ----------------------------------------------------------------
void f2polymod_t::change_modulus(f2poly_t new_modulus) {
  this->modulus = new_modulus;
  this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
void f2polymod_t::check_moduli(f2polymod_t &that) const {
  if (this->modulus != that.modulus) {
    std::cerr << "f2polymod_t: mixed moduli " << this->modulus << ", "
              << that.modulus << ".";
    std::cerr << std::endl;
    exit(1);
  }
}
