// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2_polymod_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

// ----------------------------------------------------------------
f2_polymod_t::f2_polymod_t(f2_poly_t arg_residue, f2_poly_t arg_modulus) {
  this->residue = arg_residue;
  this->modulus = arg_modulus;
  this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
f2_polymod_t::f2_polymod_t(const f2_polymod_t &that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
}

// ----------------------------------------------------------------
f2_polymod_t f2_polymod_t::prime_sfld_elt(int v) const {
  f2_poly_t m = this->modulus;
  f2_poly_t r(v & 1);
  return f2_polymod_t(r, m);
}

// ----------------------------------------------------------------
// This is a static method.
f2_polymod_t f2_polymod_t::prime_sfld_elt(int v, f2_poly_t m) {
  f2_poly_t r(v & 1);
  return f2_polymod_t(r, m);
}

// ----------------------------------------------------------------
int f2_polymod_t::get_characteristic(void) { return 2; }

// ----------------------------------------------------------------
f2_polymod_t &f2_polymod_t::operator=(f2_polymod_t that) {
  this->residue = that.residue;
  this->modulus = that.modulus;
  return *this;
}

// ----------------------------------------------------------------
f2_polymod_t f2_polymod_t::operator+(f2_polymod_t that) {
  this->check_moduli(that);
  f2_polymod_t rv(this->residue + that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2_polymod_t f2_polymod_t::operator-(f2_polymod_t that) {
  this->check_moduli(that);
  f2_polymod_t rv(this->residue - that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2_polymod_t f2_polymod_t::operator-(void) {
  f2_polymod_t rv(-this->residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2_polymod_t f2_polymod_t::operator*(f2_polymod_t that) {
  this->check_moduli(that);
  f2_polymod_t rv(this->residue * that.residue, this->modulus);
  return rv;
}

// ----------------------------------------------------------------
f2_polymod_t f2_polymod_t::operator*(int a) {
  // Characteristic is 2, so there are two possibilities.
  f2_polymod_t rv(*this);
  if (a & 1)
    ;
  else
    rv = rv - rv;
  return rv;
}

// ----------------------------------------------------------------
f2_polymod_t f2_polymod_t::operator/(f2_polymod_t that) {
  this->check_moduli(that);

  f2_polymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "f2_polymod_t::operator/:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this * bi;
}

// ----------------------------------------------------------------
f2_polymod_t f2_polymod_t::operator%(f2_polymod_t that) {
  this->check_moduli(that);

  f2_polymod_t bi;
  if (!that.recip(bi)) {
    std::cerr << "f2_polymod_t::operator%:  zero or zero divisor: "
              << that.residue << " mod " << that.modulus << ".\n";
    exit(1);
  }

  return *this - *this;
}

// ----------------------------------------------------------------
bool f2_polymod_t::recip(f2_polymod_t &rinv) {
  f2_poly_t g, a, b;
  g = this->residue.ext_gcd(this->modulus, a, b);

  // Error check:
  if (g.find_degree() != 0) {
    // std::cerr << "f2_polymod recip: zero or zero divisor.\n";
    return false;
  } else {
    rinv = f2_polymod_t(a, this->modulus);
    return true;
  }
}

// ----------------------------------------------------------------
f2_polymod_t f2_polymod_t::exp(int e) {
  f2_poly_t xp = this->residue;
  f2_polymod_t zero(f2_poly_t(0), this->modulus);
  f2_polymod_t one(f2_poly_t(1), this->modulus);
  f2_polymod_t rv = one;

  if (e == 0) {
    if (*this == zero) {
      std::cerr << "f2_polymod_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    }
    return one;
  } else if (e < 0) {
    if (*this == zero) {
      std::cerr << "f2_polymod_t::exp:  division by zero.\n";
      exit(1);
    }
    if (e == -e) {
      std::cerr << "f2_polymod_t::exp:  can't handle "
                   "MIN_INT.\n";
      exit(1);
    }
    f2_polymod_t inv = one / *this;
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
std::ostream &operator<<(std::ostream &os, const f2_polymod_t &a) {
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
std::istream &operator>>(std::istream &is, f2_polymod_t &a) {
  is >> a.residue; // Modulus must be already set.
  a.residue %= a.modulus;
  return is;
}

// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, f2_polymod_t &a) {
  iss >> a.residue; // Modulus must be already set.
  a.residue %= a.modulus;
  return iss;
}

// ----------------------------------------------------------------
bool f2_polymod_t::from_string(const char *string, f2_poly_t m) {
  f2_poly_t r;
  std::istringstream iss(string, std::ios_base::in);
  iss >> r;
  if (iss.fail()) {
    return false;
  } else {
    *this = f2_polymod_t(r, m);
    return true;
  }
}

// ----------------------------------------------------------------
f2_polymod_t &f2_polymod_t::operator+=(f2_polymod_t that) {
  *this = *this + that;
  return *this;
}

// ----------------------------------------------------------------
f2_polymod_t &f2_polymod_t::operator-=(f2_polymod_t that) {
  *this = *this - that;
  return *this;
}

// ----------------------------------------------------------------
f2_polymod_t &f2_polymod_t::operator*=(f2_polymod_t that) {
  *this = *this * that;
  return *this;
}

// ----------------------------------------------------------------
f2_polymod_t &f2_polymod_t::operator*=(int a) {
  *this = *this * a;
  return *this;
}

// ----------------------------------------------------------------
f2_polymod_t &f2_polymod_t::operator/=(f2_polymod_t that) {
  *this = *this / that;
  return *this;
}

// ----------------------------------------------------------------
f2_polymod_t &f2_polymod_t::operator%=(f2_polymod_t that) {
  *this = *this % that;
  return *this;
}

// ----------------------------------------------------------------
bool f2_polymod_t::operator==(f2_polymod_t that) const {
  if (this->residue != that.residue)
    return false;
  if (this->modulus != that.modulus)
    return false;
  return true;
}

// ----------------------------------------------------------------
bool f2_polymod_t::operator!=(f2_polymod_t that) const {
  return !(*this == that);
}

// ----------------------------------------------------------------
bool f2_polymod_t::operator==(int that) const { return this->residue == that; }

// ----------------------------------------------------------------
bool f2_polymod_t::operator!=(int that) const { return this->residue != that; }

// ----------------------------------------------------------------
bool f2_polymod_t::operator<(f2_polymod_t that) const {
  this->check_moduli(that);
  return this->residue < that.residue;
}

// ----------------------------------------------------------------
bool f2_polymod_t::operator<=(f2_polymod_t that) const {
  this->check_moduli(that);
  return this->residue <= that.residue;
}

// ----------------------------------------------------------------
bool f2_polymod_t::operator>(f2_polymod_t that) const {
  this->check_moduli(that);
  return this->residue > that.residue;
}

// ----------------------------------------------------------------
bool f2_polymod_t::operator>=(f2_polymod_t that) const {
  this->check_moduli(that);
  return this->residue >= that.residue;
}

// ----------------------------------------------------------------
f2_poly_t f2_polymod_t::get_residue(void) const { return this->residue; }

// ----------------------------------------------------------------
f2_poly_t f2_polymod_t::get_modulus(void) const { return this->modulus; }

// ----------------------------------------------------------------
void f2_polymod_t::change_modulus(f2_poly_t new_modulus) {
  this->modulus = new_modulus;
  this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
void f2_polymod_t::check_moduli(f2_polymod_t &that) const {
  if (this->modulus != that.modulus) {
    std::cerr << "f2_polymod_t: mixed moduli " << this->modulus << ", "
              << that.modulus << ".";
    std::cerr << std::endl;
    exit(1);
  }
}

} // namespace spffl::polynomials
