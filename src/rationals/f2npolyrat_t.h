// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLYRAT_T_H
#define F2NPOLYRAT_T_H

#include "f2npoly_t.h"
#include <iomanip>
#include <iostream>
#include <sstream>

class f2npolyrat_t {
public:
  f2npolyrat_t(f2npoly_t numerator, f2npoly_t denominator);
  f2npolyrat_t(f2npoly_t numerator);
  f2npolyrat_t(void);
  f2npolyrat_t(const f2npolyrat_t &that);
  ~f2npolyrat_t(void);

  f2npolyrat_t prime_sfld_elt(int v) const;
  static f2npolyrat_t prime_sfld_elt(int v, f2poly_t m);
  int get_char(void);

  f2npolyrat_t &operator=(f2npolyrat_t that);
  f2npolyrat_t &operator=(f2npoly_t numer);
  f2npolyrat_t operator+(f2npolyrat_t that) const;
  f2npolyrat_t operator-(f2npolyrat_t that) const;
  f2npolyrat_t operator-(void) const;
  f2npolyrat_t operator*(f2npolyrat_t that);
  f2npolyrat_t operator/(f2npolyrat_t that);
  f2npolyrat_t operator%(f2npolyrat_t that);
  f2npolyrat_t exp(int e);
  friend std::ostream &operator<<(std::ostream &os, const f2npolyrat_t &a);
  friend std::istream &operator>>(std::istream &is, f2npolyrat_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss,
                                        f2npolyrat_t &a);
  int from_string(char *string, f2poly_t m);

  f2npolyrat_t &operator+=(f2npolyrat_t that);
  f2npolyrat_t &operator-=(f2npolyrat_t that);
  f2npolyrat_t &operator*=(f2npolyrat_t that);
  f2npolyrat_t &operator/=(f2npolyrat_t that);
  f2npolyrat_t &operator%=(f2npolyrat_t that);

  int operator==(f2npolyrat_t that) const;
  int operator!=(f2npolyrat_t that) const;
  int operator==(f2npoly_t that) const;
  int operator!=(f2npoly_t that) const;

  int operator<(f2npolyrat_t that) const;
  int operator>(f2npolyrat_t that) const;
  int operator<=(f2npolyrat_t that) const;
  int operator>=(f2npolyrat_t that) const;

  f2npoly_t get_numerator(void) const;
  f2npoly_t get_denominator(void) const;

private:
  f2npoly_t numer;
  f2npoly_t denom;

  void simplify();
};

#endif // F2NPOLYRAT_T_H
