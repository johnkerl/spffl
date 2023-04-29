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

namespace spffl::polynomials {

class fp_poly_t {
public:
  fp_poly_t(void);

  fp_poly_t(const spffl::intmath::intmod_t &c0);
  fp_poly_t(const spffl::intmath::intmod_t &c1, const spffl::intmath::intmod_t &c0);
  fp_poly_t(const spffl::intmath::intmod_t &c2, const spffl::intmath::intmod_t &c1,
      const spffl::intmath::intmod_t &c0);

  fp_poly_t(int c0, int m);
  fp_poly_t(int c1, int c0, int m);
  fp_poly_t(int c2, int c1, int c0, int m);

  static fp_poly_t from_base_rep(int b, int modulus);
  fp_poly_t prime_sfld_elt(int v) const;
  int get_characteristic(void) const;

  fp_poly_t(const fp_poly_t &that);
  ~fp_poly_t(void);

  fp_poly_t &operator=(fp_poly_t that);
  fp_poly_t operator+(fp_poly_t that) const;
  fp_poly_t operator+(spffl::intmath::intmod_t a) const;
  fp_poly_t operator-(fp_poly_t that) const;
  fp_poly_t operator-(spffl::intmath::intmod_t a) const;
  fp_poly_t operator-(void) const;
  fp_poly_t operator*(fp_poly_t that) const;
  fp_poly_t operator*(spffl::intmath::intmod_t a);
  fp_poly_t operator/(fp_poly_t that);
  fp_poly_t operator%(fp_poly_t that);
  fp_poly_t operator/(spffl::intmath::intmod_t a);

  fp_poly_t &operator+=(fp_poly_t that);
  fp_poly_t &operator+=(spffl::intmath::intmod_t a);
  fp_poly_t &operator-=(fp_poly_t that);
  fp_poly_t &operator-=(spffl::intmath::intmod_t a);
  fp_poly_t &operator*=(fp_poly_t that);
  fp_poly_t &operator*=(spffl::intmath::intmod_t a);
  fp_poly_t &operator/=(fp_poly_t &that);
  fp_poly_t &operator%=(fp_poly_t &that);
  fp_poly_t &operator/=(spffl::intmath::intmod_t a);

  void quot_and_rem(fp_poly_t &that, fp_poly_t &rquot, fp_poly_t &rrem);
  fp_poly_t gcd(fp_poly_t &that);
  fp_poly_t ext_gcd(fp_poly_t &that, fp_poly_t &rm, fp_poly_t &rn);
  fp_poly_t exp(int power);
  fp_poly_t deriv(void);
  bool pth_root(fp_poly_t &rroot);
  spffl::intmath::intmod_t eval(spffl::intmath::intmod_t c);

  int find_degree(void) const; // deg(0) is defined to be 0.
  spffl::intmath::intmod_t get_coeff(int deg) const;
  void set_coeff(int pos, spffl::intmath::intmod_t c);

  bool operator==(int v) const;
  bool operator!=(int v) const;
  bool operator==(fp_poly_t that) const;
  bool operator!=(fp_poly_t that) const;
  // Fp[x] is *not* totally ordered.  Nonetheless, these methods are
  // handy for looping and sorting.
  bool operator<(fp_poly_t that) const;
  bool operator>(fp_poly_t that) const;
  bool operator<=(fp_poly_t that) const;
  bool operator>=(fp_poly_t that) const;
  void increment(void);

  friend std::ostream &operator<<(std::ostream &os, const fp_poly_t &poly);
  // p must have already been set:
  friend std::istream &operator>>(std::istream &is, fp_poly_t &poly);
  // friend std::istringstream & operator>>(std::istringstream & iss,
  // fp_poly_t & poly);
  bool from_string(const char *string, int p);

  void promote(void);
  void promote_and_add(spffl::intmath::intmod_t c0);

private:
  spffl::intmath::intmod_t *coeffs;
  int degree;

  bool cmp(int cmp, fp_poly_t &that) const;
  void bounds_check(int deg) const;
  void recompute_degree();
};

} // namespace spffl::polynomials

// Same as the gcd method, but overloaded.  This is important for template use.
spffl::polynomials::fp_poly_t gcd(
    spffl::polynomials::fp_poly_t a, spffl::polynomials::fp_poly_t b);

#endif // FPPOLY_T_H
