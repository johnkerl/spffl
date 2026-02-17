// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLYRAT_T_H
#define FPPOLYRAT_T_H

#include "spffl/polynomials/fp_poly_t.h"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace spffl::rationals {

class fp_polyrat_t {
public:
  fp_polyrat_t(const spffl::polynomials::fp_poly_t &numerator,
      const spffl::polynomials::fp_poly_t &denominator);
  fp_polyrat_t(const spffl::polynomials::fp_poly_t &numerator);
  fp_polyrat_t(void);
  fp_polyrat_t(const fp_polyrat_t &that);
  ~fp_polyrat_t(void);

  fp_polyrat_t prime_subfield_element(int v) const;
  static fp_polyrat_t prime_subfield_element(int v, int p);
  int get_characteristic(void) const;

  fp_polyrat_t &operator=(const fp_polyrat_t &that);
  fp_polyrat_t &operator=(spffl::polynomials::fp_poly_t numer);
  fp_polyrat_t operator+(const fp_polyrat_t &that) const;
  fp_polyrat_t operator-(const fp_polyrat_t &that) const;
  fp_polyrat_t operator-(void) const;
  fp_polyrat_t operator*(const fp_polyrat_t &that) const;
  fp_polyrat_t operator/(const fp_polyrat_t &that);
  fp_polyrat_t operator%(const fp_polyrat_t &that);
  fp_polyrat_t exp(int e) const;
  friend std::ostream &operator<<(std::ostream &os, const fp_polyrat_t &a);
  friend std::istream &operator>>(std::istream &is, fp_polyrat_t &a);
  friend std::istringstream &operator>>(
      std::istringstream &iss, fp_polyrat_t &a);
  bool from_string(const std::string &string, int p);

  fp_polyrat_t &operator+=(const fp_polyrat_t &that);
  fp_polyrat_t &operator-=(const fp_polyrat_t &that);
  fp_polyrat_t &operator*=(const fp_polyrat_t &that);
  fp_polyrat_t &operator/=(const fp_polyrat_t &that);
  fp_polyrat_t &operator%=(const fp_polyrat_t &that);

  bool operator==(const fp_polyrat_t &that) const;
  bool operator!=(const fp_polyrat_t &that) const;
  bool operator==(spffl::polynomials::fp_poly_t that) const;
  bool operator!=(spffl::polynomials::fp_poly_t that) const;

  bool operator<(const fp_polyrat_t &that) const;
  bool operator>(const fp_polyrat_t &that) const;
  bool operator<=(const fp_polyrat_t &that) const;
  bool operator>=(const fp_polyrat_t &that) const;

  spffl::polynomials::fp_poly_t get_numerator(void) const;
  spffl::polynomials::fp_poly_t get_denominator(void) const;

private:
  spffl::polynomials::fp_poly_t numer;
  spffl::polynomials::fp_poly_t denom;

  void simplify();
};

} // namespace spffl::rationals

#endif // FPPOLYRAT_T_H
