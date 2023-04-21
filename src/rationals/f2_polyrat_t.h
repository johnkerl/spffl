// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYRAT_T_H
#define F2POLYRAT_T_H

#include "f2_poly_t.h"
#include <iomanip>
#include <iostream>
#include <sstream>

class f2_polyrat_t {
public:
  f2_polyrat_t(f2_poly_t numerator, f2_poly_t denominator);
  f2_polyrat_t(f2_poly_t numerator);
  f2_polyrat_t(int inumer);
  f2_polyrat_t(void);
  f2_polyrat_t(const f2_polyrat_t &that);
  ~f2_polyrat_t(void);

  f2_polyrat_t prime_sfld_elt(int v) const;
  int get_char(void);

  f2_polyrat_t &operator=(f2_polyrat_t that);
  f2_polyrat_t &operator=(f2_poly_t numer);
  f2_polyrat_t operator+(f2_polyrat_t that) const;
  f2_polyrat_t operator-(f2_polyrat_t that) const;
  f2_polyrat_t operator-(void) const;
  f2_polyrat_t operator*(f2_polyrat_t that);
  f2_polyrat_t operator/(f2_polyrat_t that);
  f2_polyrat_t operator%(f2_polyrat_t that);
  f2_polyrat_t exp(int e);
  friend std::ostream &operator<<(std::ostream &os, const f2_polyrat_t &a);
  friend std::istream &operator>>(std::istream &is, f2_polyrat_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss,
                                        f2_polyrat_t &a);
  int from_string(char *string);

  f2_polyrat_t &operator+=(f2_polyrat_t that);
  f2_polyrat_t &operator-=(f2_polyrat_t that);
  f2_polyrat_t &operator*=(f2_polyrat_t that);
  f2_polyrat_t &operator/=(f2_polyrat_t that);
  f2_polyrat_t &operator%=(f2_polyrat_t that);

  int operator==(f2_polyrat_t that) const;
  int operator!=(f2_polyrat_t that) const;
  int operator==(f2_poly_t that) const;
  int operator!=(f2_poly_t that) const;

  int operator<(f2_polyrat_t that) const;
  int operator>(f2_polyrat_t that) const;
  int operator<=(f2_polyrat_t that) const;
  int operator>=(f2_polyrat_t that) const;

  f2_poly_t get_numerator(void) const;
  f2_poly_t get_denominator(void) const;

private:
  f2_poly_t numer;
  f2_poly_t denom;

  void simplify();
};

#endif // F2POLYRAT_T_H
