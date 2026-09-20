// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYRAT_T_H
#define F2POLYRAT_T_H

#include "spffl/polynomials/f2_poly_t.h"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace spffl::rationals {

class f2_polyrat_t {
  public:
  f2_polyrat_t(const spffl::polynomials::f2_poly_t &numerator,
    const spffl::polynomials::f2_poly_t &denominator);
  f2_polyrat_t(const spffl::polynomials::f2_poly_t &numerator);
  f2_polyrat_t(int inumer);
  f2_polyrat_t(void);
  f2_polyrat_t(const f2_polyrat_t &that);
  ~f2_polyrat_t(void);

  f2_polyrat_t prime_subfield_element(int v) const;
  int get_characteristic(void) const;

  f2_polyrat_t &operator=(const f2_polyrat_t &that);
  f2_polyrat_t &operator=(const spffl::polynomials::f2_poly_t &numer);
  f2_polyrat_t operator+(const f2_polyrat_t &that) const;
  f2_polyrat_t operator-(const f2_polyrat_t &that) const;
  f2_polyrat_t operator-(void) const;
  f2_polyrat_t operator*(const f2_polyrat_t &that) const;
  f2_polyrat_t operator/(const f2_polyrat_t &that);
  f2_polyrat_t operator%(const f2_polyrat_t &that);
  f2_polyrat_t exp(int e) const;
  friend std::ostream &operator<<(std::ostream &os, const f2_polyrat_t &a);
  friend std::istream &operator>>(std::istream &is, f2_polyrat_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss, f2_polyrat_t &a);
  bool from_string(const std::string &string);

  f2_polyrat_t &operator+=(const f2_polyrat_t &that);
  f2_polyrat_t &operator-=(const f2_polyrat_t &that);
  f2_polyrat_t &operator*=(const f2_polyrat_t &that);
  f2_polyrat_t &operator/=(const f2_polyrat_t &that);
  f2_polyrat_t &operator%=(const f2_polyrat_t &that);

  bool operator==(const f2_polyrat_t &that) const;
  bool operator!=(const f2_polyrat_t &that) const;
  bool operator==(spffl::polynomials::f2_poly_t that) const;
  bool operator!=(spffl::polynomials::f2_poly_t that) const;

  bool operator<(const f2_polyrat_t &that) const;
  bool operator>(const f2_polyrat_t &that) const;
  bool operator<=(const f2_polyrat_t &that) const;
  bool operator>=(const f2_polyrat_t &that) const;

  spffl::polynomials::f2_poly_t get_numerator(void) const;
  spffl::polynomials::f2_poly_t get_denominator(void) const;

  private:
  spffl::polynomials::f2_poly_t numer;
  spffl::polynomials::f2_poly_t denom;

  void simplify();
};

} // namespace spffl::rationals

#endif // F2POLYRAT_T_H
