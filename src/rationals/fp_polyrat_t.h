// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLYRAT_T_H
#define FPPOLYRAT_T_H

#include "fp_poly_t.h"
#include <iomanip>
#include <iostream>
#include <sstream>

class fp_polyrat_t {
public:
  fp_polyrat_t(fp_poly_t numerator, fp_poly_t denominator);
  fp_polyrat_t(fp_poly_t numerator);
  fp_polyrat_t(void);
  fp_polyrat_t(const fp_polyrat_t &that);
  ~fp_polyrat_t(void);

  fp_polyrat_t prime_sfld_elt(int v) const;
  static fp_polyrat_t prime_sfld_elt(int v, int p);
  int get_char(void);

  fp_polyrat_t &operator=(fp_polyrat_t that);
  fp_polyrat_t &operator=(fp_poly_t numer);
  fp_polyrat_t operator+(fp_polyrat_t that) const;
  fp_polyrat_t operator-(fp_polyrat_t that) const;
  fp_polyrat_t operator-(void) const;
  fp_polyrat_t operator*(fp_polyrat_t that);
  fp_polyrat_t operator/(fp_polyrat_t that);
  fp_polyrat_t operator%(fp_polyrat_t that);
  fp_polyrat_t exp(int e);
  friend std::ostream &operator<<(std::ostream &os, const fp_polyrat_t &a);
  friend std::istream &operator>>(std::istream &is, fp_polyrat_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss,
                                        fp_polyrat_t &a);
  int from_string(char *string, int p);

  fp_polyrat_t &operator+=(fp_polyrat_t that);
  fp_polyrat_t &operator-=(fp_polyrat_t that);
  fp_polyrat_t &operator*=(fp_polyrat_t that);
  fp_polyrat_t &operator/=(fp_polyrat_t that);
  fp_polyrat_t &operator%=(fp_polyrat_t that);

  int operator==(fp_polyrat_t that) const;
  int operator!=(fp_polyrat_t that) const;
  int operator==(fp_poly_t that) const;
  int operator!=(fp_poly_t that) const;

  int operator<(fp_polyrat_t that) const;
  int operator>(fp_polyrat_t that) const;
  int operator<=(fp_polyrat_t that) const;
  int operator>=(fp_polyrat_t that) const;

  fp_poly_t get_numerator(void) const;
  fp_poly_t get_denominator(void) const;

private:
  fp_poly_t numer;
  fp_poly_t denom;

  void simplify();
};

#endif // FPPOLYRAT_T_H
