// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLYRAT_T_H
#define F2NPOLYRAT_T_H

#include "f2n_poly_t.h"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace spffl::rationals {

class f2n_polyrat_t {
public:
  f2n_polyrat_t(const spffl::polynomials::f2n_poly_t &numerator,
      const spffl::polynomials::f2n_poly_t &denominator);
  f2n_polyrat_t(const spffl::polynomials::f2n_poly_t &numerator);
  f2n_polyrat_t(void);
  f2n_polyrat_t(const f2n_polyrat_t &that);
  ~f2n_polyrat_t(void);

  f2n_polyrat_t prime_subfield_element(int v) const;
  static f2n_polyrat_t prime_subfield_element(int v, const spffl::polynomials::f2_poly_t &m);
  int get_characteristic(void) const;

  f2n_polyrat_t &operator=(const f2n_polyrat_t &that);
  f2n_polyrat_t &operator=(const spffl::polynomials::f2n_poly_t &numer);
  f2n_polyrat_t operator+(const f2n_polyrat_t &that) const;
  f2n_polyrat_t operator-(const f2n_polyrat_t &that) const;
  f2n_polyrat_t operator-(void) const;
  f2n_polyrat_t operator*(const f2n_polyrat_t &that);
  f2n_polyrat_t operator/(const f2n_polyrat_t &that);
  f2n_polyrat_t operator%(const f2n_polyrat_t &that);
  f2n_polyrat_t exp(int e) const;
  friend std::ostream &operator<<(std::ostream &os, const f2n_polyrat_t &a);
  friend std::istream &operator>>(std::istream &is, f2n_polyrat_t &a);
  friend std::istringstream &operator>>(
      std::istringstream &iss, f2n_polyrat_t &a);
  bool from_string(const char *string, spffl::polynomials::f2_poly_t m);

  f2n_polyrat_t &operator+=(const f2n_polyrat_t &that);
  f2n_polyrat_t &operator-=(const f2n_polyrat_t &that);
  f2n_polyrat_t &operator*=(const f2n_polyrat_t &that);
  f2n_polyrat_t &operator/=(const f2n_polyrat_t &that);
  f2n_polyrat_t &operator%=(const f2n_polyrat_t &that);

  bool operator==(const f2n_polyrat_t &that) const;
  bool operator!=(const f2n_polyrat_t &that) const;
  bool operator==(spffl::polynomials::f2n_poly_t that) const;
  bool operator!=(spffl::polynomials::f2n_poly_t that) const;

  bool operator<(const f2n_polyrat_t &that) const;
  bool operator>(const f2n_polyrat_t &that) const;
  bool operator<=(const f2n_polyrat_t &that) const;
  bool operator>=(const f2n_polyrat_t &that) const;

  spffl::polynomials::f2n_poly_t get_numerator(void) const;
  spffl::polynomials::f2n_poly_t get_denominator(void) const;

private:
  spffl::polynomials::f2n_poly_t numer;
  spffl::polynomials::f2n_poly_t denom;

  void simplify();
};

} // namespace spffl::rationals

#endif // F2NPOLYRAT_T_H
