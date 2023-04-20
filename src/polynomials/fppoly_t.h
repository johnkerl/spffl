// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// Elements of the ring Z_p[x].

#ifndef FPPOLY_T_H
#define FPPOLY_T_H

#include "intmod_t.h"
#include <iomanip>
#include <iostream>

class fppoly_t {
public:
  fppoly_t(void);

  fppoly_t(intmod_t c0);
  fppoly_t(intmod_t c1, intmod_t c0);
  fppoly_t(intmod_t c2, intmod_t c1, intmod_t c0);
  fppoly_t(intmod_t c3, intmod_t c2, intmod_t c1, intmod_t c0);
  fppoly_t(intmod_t c4, intmod_t c3, intmod_t c2, intmod_t c1, intmod_t c0);
  fppoly_t(intmod_t c5, intmod_t c4, intmod_t c3, intmod_t c2, intmod_t c1,
           intmod_t c0);

  fppoly_t(int c0, int m);
  fppoly_t(int c1, int c0, int m);
  fppoly_t(int c2, int c1, int c0, int m);
  fppoly_t(int c3, int c2, int c1, int c0, int m);
  fppoly_t(int c4, int c3, int c2, int c1, int c0, int m);
  fppoly_t(int c5, int c4, int c3, int c2, int c1, int c0, int m);

  static fppoly_t from_base_rep(int b, int modulus);
  fppoly_t prime_sfld_elt(int v) const;
  int get_char(void);

  fppoly_t(const fppoly_t &that);
  ~fppoly_t(void);

  fppoly_t &operator=(fppoly_t that);
  fppoly_t operator+(fppoly_t that) const;
  fppoly_t operator+(intmod_t a) const;
  fppoly_t operator-(fppoly_t that) const;
  fppoly_t operator-(intmod_t a) const;
  fppoly_t operator-(void) const;
  fppoly_t operator*(fppoly_t that) const;
  fppoly_t operator*(intmod_t a);
  fppoly_t operator/(fppoly_t that);
  fppoly_t operator%(fppoly_t that);
  fppoly_t operator/(intmod_t a);

  fppoly_t &operator+=(fppoly_t that);
  fppoly_t &operator+=(intmod_t a);
  fppoly_t &operator-=(fppoly_t that);
  fppoly_t &operator-=(intmod_t a);
  fppoly_t &operator*=(fppoly_t that);
  fppoly_t &operator*=(intmod_t a);
  fppoly_t &operator/=(fppoly_t &that);
  fppoly_t &operator%=(fppoly_t &that);
  fppoly_t &operator/=(intmod_t a);

  void quot_and_rem(fppoly_t &that, fppoly_t &rquot, fppoly_t &rrem);
  fppoly_t gcd(fppoly_t &that);
  fppoly_t ext_gcd(fppoly_t &that, fppoly_t &rm, fppoly_t &rn);
  fppoly_t exp(int power);
  fppoly_t deriv(void);
  int pth_root(fppoly_t &rroot);
  intmod_t eval(intmod_t c);

  int find_degree(void) const; // deg(0) is defined to be 0.
  intmod_t get_coeff(int deg) const;
  void set_coeff(int pos, intmod_t c);

  int operator==(int v) const;
  int operator!=(int v) const;
  int operator==(fppoly_t that) const;
  int operator!=(fppoly_t that) const;
  // Fp[x] is *not* totally ordered.  Nonetheless, these methods are
  // handy for looping and sorting.
  int operator<(fppoly_t that) const;
  int operator>(fppoly_t that) const;
  int operator<=(fppoly_t that) const;
  int operator>=(fppoly_t that) const;
  void increment(void);

  friend std::ostream &operator<<(std::ostream &os, const fppoly_t &poly);
  // p must have already been set:
  friend std::istream &operator>>(std::istream &is, fppoly_t &poly);
  // friend std::istringstream & operator>>(std::istringstream & iss,
  // fppoly_t & poly);
  int from_string(char *string, int p);

  void promote(void);
  void promote_and_add(intmod_t c0);

private:
  intmod_t *coeffs;
  int degree;

  int cmp(int cmp, fppoly_t &that) const;
  void bounds_check(int deg) const;
  void recompute_degree();
};

// Same as the gcd method, but overloaded.  This is important for template use.
fppoly_t gcd(fppoly_t a, fppoly_t b);

#endif // FPPOLY_T_H
