// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// Elements of the ring F_q[x], with q a power of 2.

#ifndef F2NPOLY_T_H
#define F2NPOLY_T_H

#include "polynomials/f2_polymod_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

class f2n_poly_t {
public:
  f2n_poly_t(void);

  f2n_poly_t(const f2_polymod_t &c0);
  f2n_poly_t(const f2_polymod_t &c1, const f2_polymod_t &c0);
  f2n_poly_t(
      const f2_polymod_t &c2, const f2_polymod_t &c1, const f2_polymod_t &c0);

  f2n_poly_t(int c0, const f2_poly_t &m);
  f2n_poly_t(int c1, int c0, const f2_poly_t &m);
  f2n_poly_t(int c2, int c1, int c0, const f2_poly_t &m);

  static f2n_poly_t from_base_rep(int b, const f2_poly_t &m);

  f2n_poly_t(const f2n_poly_t &that);
  ~f2n_poly_t(void);

  f2n_poly_t prime_subfield_element(int v) const;
  static f2n_poly_t prime_subfield_element(int v, const f2_poly_t &m);
  int get_characteristic(void) const;

  f2n_poly_t &operator=(const f2n_poly_t &that);

  f2n_poly_t operator+(const f2n_poly_t &that) const;
  f2n_poly_t operator+(const f2_polymod_t &a) const;
  f2n_poly_t operator-(const f2n_poly_t &that) const;
  f2n_poly_t operator-(const f2_polymod_t &a) const;
  f2n_poly_t operator-(void) const;
  f2n_poly_t operator*(const f2n_poly_t &that) const;
  f2n_poly_t operator*(const f2_polymod_t &a) const;
  f2n_poly_t operator/(const f2n_poly_t &that) const;
  f2n_poly_t operator%(const f2n_poly_t &that) const;
  f2n_poly_t operator/(const f2_polymod_t &a) const;

  f2n_poly_t &operator+=(const f2n_poly_t &that);
  f2n_poly_t &operator+=(const f2_polymod_t &a);
  f2n_poly_t &operator-=(const f2n_poly_t &that);
  f2n_poly_t &operator-=(const f2_polymod_t &a);
  f2n_poly_t &operator*=(const f2n_poly_t &that);
  f2n_poly_t &operator*=(const f2_polymod_t &a);
  f2n_poly_t &operator/=(const f2n_poly_t &that);
  f2n_poly_t &operator%=(const f2n_poly_t &that);
  f2n_poly_t &operator/=(const f2_polymod_t &a);

  void quot_and_rem(
      const f2n_poly_t &that, f2n_poly_t &rquot, f2n_poly_t &rrem) const;
  f2n_poly_t gcd(const f2n_poly_t &that) const;
  f2n_poly_t ext_gcd(
      const f2n_poly_t &that, f2n_poly_t &rm, f2n_poly_t &rn) const;
  f2n_poly_t exp(int power) const;
  f2n_poly_t deriv(void) const;
  bool square_root(f2n_poly_t &rroot) const;
  f2_polymod_t eval(const f2_polymod_t &c) const;

  int find_degree(void) const; // deg(0) is defined to be 0.
  f2_polymod_t get_coeff(int deg) const;
  void set_coeff(int pos, const f2_polymod_t &c);
  void change_modulus(const f2_poly_t &new_modulus);

  bool operator==(int v) const;
  bool operator!=(int v) const;
  bool operator==(const f2n_poly_t &that) const;
  bool operator!=(const f2n_poly_t &that) const;
  // Fq[x] is *not* totally ordered.  Nonetheless, these methods are
  // handy for looping and sorting.
  bool operator<(const f2n_poly_t &that) const;
  bool operator>(const f2n_poly_t &that) const;
  bool operator<=(const f2n_poly_t &that) const;
  bool operator>=(const f2n_poly_t &that) const;
  void increment(void);

  friend std::ostream &operator<<(std::ostream &os, const f2n_poly_t &poly);
  // Modulus must have already been set:
  friend std::istream &operator>>(std::istream &is, f2n_poly_t &poly);
  friend std::istringstream &operator>>(
      std::istringstream &iss, f2n_poly_t &poly);
  bool from_string(const std::string &string, const f2_poly_t &m);

  void promote(void);
  void promote_and_add(const f2_polymod_t &c0);

private:
  f2_polymod_t *coeffs;
  int degree;

  bool cmp(int cmp, const f2n_poly_t &that) const;
  void bounds_check(int deg) const;
  void recompute_degree();
};

} // namespace spffl::polynomials

// Same as the gcd method, but overloaded.  This is important for template use.
spffl::polynomials::f2n_poly_t gcd(const spffl::polynomials::f2n_poly_t &a,
    const spffl::polynomials::f2n_poly_t &b);

#endif // F2NPOLY_T_H
