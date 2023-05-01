// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// Elements of the ring F_q[x].

#ifndef FPNPOLY_T_H
#define FPNPOLY_T_H

#include "polynomials/fp_polymod_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

class fpn_poly_t {
public:
  fpn_poly_t(void);

  fpn_poly_t(const fp_polymod_t &c0);
  fpn_poly_t(const fp_polymod_t &c1, const fp_polymod_t &c0);
  fpn_poly_t(
      const fp_polymod_t &c2, const fp_polymod_t &c1, const fp_polymod_t &c0);

  static fpn_poly_t from_base_rep(int b, const fp_poly_t &m);

  fpn_poly_t(const fpn_poly_t &that);
  ~fpn_poly_t(void);

  fpn_poly_t prime_subfield_element(int v) const;
  static fpn_poly_t prime_subfield_element(int v, const fp_poly_t &m);
  int get_characteristic(void) const;

  fpn_poly_t &operator=(const fpn_poly_t &that);

  fpn_poly_t operator+(const fpn_poly_t &that) const;
  fpn_poly_t operator+(const fp_polymod_t &a) const;
  fpn_poly_t operator-(const fpn_poly_t &that) const;
  fpn_poly_t operator-(const fp_polymod_t &a) const;
  fpn_poly_t operator-(void) const;
  fpn_poly_t operator*(const fpn_poly_t &that) const;
  fpn_poly_t operator*(const fp_polymod_t &a) const;
  fpn_poly_t operator*(const spffl::intmath::intmod_t &a) const;
  fpn_poly_t operator/(const fpn_poly_t &that) const;
  fpn_poly_t operator%(const fpn_poly_t &that) const;
  fpn_poly_t operator/(const fp_polymod_t &a) const;

  fpn_poly_t &operator+=(const fpn_poly_t &that);
  fpn_poly_t &operator-=(const fpn_poly_t &that);
  fpn_poly_t &operator*=(const fpn_poly_t &that);
  fpn_poly_t &operator/=(const fpn_poly_t &that);
  fpn_poly_t &operator%=(const fpn_poly_t &that);
  fpn_poly_t &operator+=(const fp_polymod_t &a);
  fpn_poly_t &operator-=(const fp_polymod_t &a);
  fpn_poly_t &operator*=(const fp_polymod_t &a);
  fpn_poly_t &operator/=(const fp_polymod_t &a);

  void quot_and_rem(
      const fpn_poly_t &that, fpn_poly_t &rquot, fpn_poly_t &rrem) const;
  fpn_poly_t gcd(const fpn_poly_t &that) const;
  fpn_poly_t ext_gcd(
      const fpn_poly_t &that, fpn_poly_t &rm, fpn_poly_t &rn) const;
  fpn_poly_t exp(int power) const;
  fpn_poly_t deriv(void) const;
  bool pth_root(fpn_poly_t &rroot) const;
  fp_polymod_t eval(const fp_polymod_t &c) const;

  int find_degree(void) const; // deg(0) is defined to be 0.
  fp_polymod_t get_coeff(int deg) const;
  void set_coeff(int pos, const fp_polymod_t &c);

  bool operator==(int v) const;
  bool operator!=(int v) const;
  bool operator==(const fpn_poly_t &that) const;
  bool operator!=(const fpn_poly_t &that) const;
  // Fq[x] is *not* totally ordered.  Nonetheless, these methods are
  // handy for looping and sorting.
  bool operator<(const fpn_poly_t &that) const;
  bool operator>(const fpn_poly_t &that) const;
  bool operator<=(const fpn_poly_t &that) const;
  bool operator>=(const fpn_poly_t &that) const;
  void increment(void);

  friend std::ostream &operator<<(std::ostream &os, const fpn_poly_t &poly);
  // Modulus must have already been set:
  friend std::istream &operator>>(std::istream &is, fpn_poly_t &poly);
  bool from_string(const std::string &string, fp_poly_t m);

  void promote(void);
  void promote_and_add(const fp_polymod_t &c0);

private:
  fp_polymod_t *coeffs;
  int degree;

  bool cmp(int cmp, const fpn_poly_t &that) const;
  void bounds_check(int deg) const;
  void recompute_degree();
};

} // namespace spffl::polynomials

// Same as the gcd method, but overloaded.  This is important for template use.
spffl::polynomials::fpn_poly_t gcd(const spffl::polynomials::fpn_poly_t &a,
    const spffl::polynomials::fpn_poly_t &b);

#endif // FPNPOLY_T_H
