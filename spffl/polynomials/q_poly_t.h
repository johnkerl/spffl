// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// Elements of the ring Q[x].

// #error under construction

#ifndef QPOLY_T_H
#define QPOLY_T_H

#include "intmath/intrat_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

class q_poly_t {
public:
  q_poly_t(void);

  q_poly_t(const spffl::intmath::intrat_t &c0);
  q_poly_t(const spffl::intmath::intrat_t &c1, const spffl::intmath::intrat_t &c0);
  q_poly_t(const spffl::intmath::intrat_t &c2, const spffl::intmath::intrat_t &c1, const spffl::intmath::intrat_t &c0);
  static q_poly_t binomial(
      const spffl::intmath::intrat_t &ci, int i, const spffl::intmath::intrat_t &cj, int j);

  q_poly_t(const q_poly_t &that);
  ~q_poly_t(void);

  q_poly_t &operator=(const q_poly_t &that);
  q_poly_t operator+(const q_poly_t &that) const;
  q_poly_t operator+(const spffl::intmath::intrat_t &a) const;
  q_poly_t operator-(const q_poly_t &that) const;
  q_poly_t operator-(const spffl::intmath::intrat_t &a) const;
  q_poly_t operator-(void) const;
  q_poly_t operator*(const q_poly_t &that) const;
  q_poly_t operator*(const spffl::intmath::intrat_t &a);
  q_poly_t operator/(const q_poly_t &that);
  q_poly_t operator%(const q_poly_t &that);
  q_poly_t operator/(const spffl::intmath::intrat_t &a);

  q_poly_t &operator+=(const q_poly_t &that);
  q_poly_t &operator+=(const spffl::intmath::intrat_t &a);
  q_poly_t &operator-=(const q_poly_t &that);
  q_poly_t &operator-=(const spffl::intmath::intrat_t &a);
  q_poly_t &operator*=(const q_poly_t &that);
  q_poly_t &operator*=(const spffl::intmath::intrat_t &a);
  q_poly_t &operator/=(const q_poly_t &that);
  q_poly_t &operator%=(const q_poly_t &that);
  q_poly_t &operator/=(const spffl::intmath::intrat_t &a);

  void quot_and_rem(
      const q_poly_t &that, q_poly_t &rquot, q_poly_t &rrem) const;
  q_poly_t gcd(const q_poly_t &that) const;
  q_poly_t ext_gcd(const q_poly_t &that, q_poly_t &rm, q_poly_t &rn) const;
  q_poly_t exp(int power) const;
  q_poly_t deriv(void) const;
  spffl::intmath::intrat_t eval(const spffl::intmath::intrat_t &c) const;

  int find_degree(void) const; // deg(0) is defined to be 0.
  spffl::intmath::intrat_t get_coeff(int deg) const;
  void set_coeff(int pos, spffl::intmath::intrat_t c);

  bool operator==(int v) const;
  bool operator!=(int v) const;
  bool operator==(const q_poly_t &that) const;
  bool operator!=(const q_poly_t &that) const;
  // Q[x] is *not* totally ordered.  Nonetheless, these methods are
  // handy for looping and sorting.
  bool operator<(const q_poly_t &that) const;
  bool operator>(const q_poly_t &that) const;
  bool operator<=(const q_poly_t &that) const;
  bool operator>=(const q_poly_t &that) const;

  friend std::ostream &operator<<(std::ostream &os, const q_poly_t &poly);
  friend std::istream &operator>>(std::istream &is, q_poly_t &poly);
  bool from_string(const std::string &string);

  void promote(void);
  void promote_and_add(spffl::intmath::intrat_t c0);

private:
  spffl::intmath::intrat_t *coeffs;
  int degree;

  bool cmp(int cmp, const q_poly_t &that) const;
  void bounds_check(int deg) const;
  void recompute_degree();
};

} // namespace spffl::polynomials

#endif // QPOLY_T_H
