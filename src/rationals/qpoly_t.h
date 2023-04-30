// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// Elements of the ring Q[x].

// #error under construction

#ifndef QPOLY_T_H
#define QPOLY_T_H

#include "intrat_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::rationals {

class qpoly_t {
public:
  qpoly_t(void);

  qpoly_t(const intrat_t &c0);
  qpoly_t(const intrat_t &c1, const intrat_t &c0);
  qpoly_t(const intrat_t &c2, const intrat_t &c1, const intrat_t &c0);
  static qpoly_t binomial(const intrat_t &ci, int i, const intrat_t &cj, int j);

  qpoly_t(const qpoly_t &that);
  ~qpoly_t(void);

  qpoly_t &operator=(const qpoly_t &that);
  qpoly_t operator+(const qpoly_t &that) const;
  qpoly_t operator+(const intrat_t &a) const;
  qpoly_t operator-(const qpoly_t &that) const;
  qpoly_t operator-(const intrat_t &a) const;
  qpoly_t operator-(void) const;
  qpoly_t operator*(const qpoly_t &that) const;
  qpoly_t operator*(const intrat_t &a);
  qpoly_t operator/(const qpoly_t &that);
  qpoly_t operator%(const qpoly_t &that);
  qpoly_t operator/(const intrat_t &a);

  qpoly_t &operator+=(const qpoly_t &that);
  qpoly_t &operator+=(const intrat_t &a);
  qpoly_t &operator-=(const qpoly_t &that);
  qpoly_t &operator-=(const intrat_t &a);
  qpoly_t &operator*=(const qpoly_t &that);
  qpoly_t &operator*=(const intrat_t &a);
  qpoly_t &operator/=(const qpoly_t &that);
  qpoly_t &operator%=(const qpoly_t &that);
  qpoly_t &operator/=(const intrat_t &a);

  void quot_and_rem(const qpoly_t &that, qpoly_t &rquot, qpoly_t &rrem) const;
  qpoly_t gcd(const qpoly_t &that) const;
  qpoly_t ext_gcd(const qpoly_t &that, qpoly_t &rm, qpoly_t &rn) const;
  qpoly_t exp(int power) const;
  qpoly_t deriv(void) const;
  intrat_t eval(const intrat_t &c) const;

  int find_degree(void) const; // deg(0) is defined to be 0.
  intrat_t get_coeff(int deg) const;
  void set_coeff(int pos, intrat_t c);

  bool operator==(int v) const;
  bool operator!=(int v) const;
  bool operator==(const qpoly_t &that) const;
  bool operator!=(const qpoly_t &that) const;
  // Q[x] is *not* totally ordered.  Nonetheless, these methods are
  // handy for looping and sorting.
  bool operator<(const qpoly_t &that) const;
  bool operator>(const qpoly_t &that) const;
  bool operator<=(const qpoly_t &that) const;
  bool operator>=(const qpoly_t &that) const;

  friend std::ostream &operator<<(std::ostream &os, const qpoly_t &poly);
  friend std::istream &operator>>(std::istream &is, qpoly_t &poly);
  bool from_string(const char *string);

  void promote(void);
  void promote_and_add(intrat_t c0);

private:
  intrat_t *coeffs;
  int degree;

  bool cmp(int cmp, const qpoly_t &that) const;
  void bounds_check(int deg) const;
  void recompute_degree();
};

} // namespace spffl::rationals

#endif // QPOLY_T_H
