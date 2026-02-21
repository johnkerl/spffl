// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/rationals/f2n_polyrat_t.h"
#include "spffl/polynomials/fpn_f2n_io.h"
#include "spffl/base/cmps.h"
#include "spffl/base/spffl_exception.h"
#include <iomanip>
#include <iostream>
#include <optional>

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
  this->denom = spffl::polynomials::prime_subfield_element(
      1, numerator.get_coeff(0).get_modulus());
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
  spffl::polynomials::f2n_poly_t a = spffl::polynomials::prime_subfield_element(
      v, this->numer.get_coeff(0).get_modulus());
  return f2n_polyrat_t(a);
}

// ----------------------------------------------------------------
// This is a static method.
f2n_polyrat_t f2n_polyrat_t::prime_subfield_element(
    int v, const spffl::polynomials::f2_poly_t &m) {
  return f2n_polyrat_t(spffl::polynomials::prime_subfield_element(v, m));
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
f2n_polyrat_t f2n_polyrat_t::operator*(const f2n_polyrat_t &that) const {
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
  auto m = get_denominator().get_coeff(0).get_modulus();
  f2n_polyrat_t xp = *this;
  f2n_polyrat_t zero(
      spffl::polynomials::prime_subfield_element(0, m));
  f2n_polyrat_t one(
      spffl::polynomials::prime_subfield_element(1, m));
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
  auto m = a.get_modulus();
  if (!read_f2n_polyrat(is, m, a)) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, f2n_polyrat_t &a) {
  auto m = a.get_modulus();
  if (!read_f2n_polyrat(iss, m, a)) {
    iss.setstate(std::ios::failbit);
  }
  return iss;
}

// ----------------------------------------------------------------
// Read rational from stream; modulus m is required (explicit API).
bool read_f2n_polyrat(std::istream& is, const spffl::polynomials::f2_poly_t& m,
                      f2n_polyrat_t& a) {
  while (is.peek() == ' ' || is.peek() == '\t' || is.peek() == '\n') {
    is.ignore(1);
  }
  std::string line;
  if (!std::getline(is, line)) return false;
  auto opt = f2n_polyrat_from_string(line, m);
  if (!opt) return false;
  a = std::move(*opt);
  return true;
}

bool read_f2n_polyrat(std::istringstream& iss,
                      const spffl::polynomials::f2_poly_t& m, f2n_polyrat_t& a) {
  while (iss.peek() == ' ' || iss.peek() == '\t' || iss.peek() == '\n') {
    iss.ignore(1);
  }
  std::string line;
  if (!std::getline(iss, line)) return false;
  auto opt = f2n_polyrat_from_string(line, m);
  if (!opt) return false;
  a = std::move(*opt);
  return true;
}

// ----------------------------------------------------------------
std::optional<f2n_polyrat_t> f2n_polyrat_from_string(
    const std::string& s, const spffl::polynomials::f2_poly_t& m) {
  std::string num_str, denom_str;
  std::size_t slash = s.find('/');
  if (slash != std::string::npos) {
    num_str = s.substr(0, slash);
    denom_str = s.substr(slash + 1);
  } else {
    num_str = s;
    denom_str.clear();
  }
  auto num_opt = spffl::polynomials::f2n_poly_from_string(num_str, m);
  if (!num_opt) return std::nullopt;
  spffl::polynomials::f2n_poly_t denom;
  if (denom_str.empty()) {
    denom = spffl::polynomials::prime_subfield_element(1, m);
  } else {
    auto denom_opt = spffl::polynomials::f2n_poly_from_string(denom_str, m);
    if (!denom_opt) return std::nullopt;
    denom = *denom_opt;
  }
  return f2n_polyrat_t(*num_opt, denom);
}

// ----------------------------------------------------------------
bool f2n_polyrat_t::from_string(
    const std::string &string, spffl::polynomials::f2_poly_t m) {
  auto opt = f2n_polyrat_from_string(string, m);
  if (!opt) return false;
  *this = std::move(*opt);
  return true;
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
  if (this->denom != spffl::polynomials::prime_subfield_element(
                         1, this->numer.get_coeff(0).get_modulus())) {
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
spffl::polynomials::f2_poly_t f2n_polyrat_t::get_modulus(void) const {
  return this->denom.get_coeff(0).get_modulus();
}

// ----------------------------------------------------------------
// * Check denominator != 0
// * Divide numerator and denominator by their GCD

void f2n_polyrat_t::simplify(void) {
  spffl::polynomials::f2n_poly_t g;
  if (this->denom.is_zero()) {
    std::stringstream ss;
    ss << "rat: Divide by zero.\n";
    throw spffl::exception_t(ss.str());
  }
  g = this->numer.gcd(this->denom);
  this->numer /= g;
  this->denom /= g;
}

// ----------------------------------------------------------------
void read_element(std::istringstream& iss, const f2n_polyrat_t& zero,
                  f2n_polyrat_t& out) {
  if (!read_f2n_polyrat(iss, zero.get_modulus(), out)) {
    iss.setstate(std::ios::failbit);
  }
}

}  // namespace spffl::rationals
