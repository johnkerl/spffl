// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLYMOD_T_H
#define F2NPOLYMOD_T_H

#include "polynomials/f2n_poly_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

class f2n_polymod_t {
public:
  f2n_polymod_t(const f2n_poly_t &residue, const f2n_poly_t &modulus);
  f2n_polymod_t(void);
  f2n_polymod_t(const f2n_polymod_t &that);
  ~f2n_polymod_t(void);

  f2n_polymod_t prime_subfield_element(int v) const;
  static f2n_polymod_t prime_subfield_element(int v, const f2n_poly_t &om);
  int get_characteristic(void) const;

  f2n_polymod_t &operator=(const f2n_polymod_t &that);

  f2n_polymod_t operator+(const f2n_polymod_t &that) const;
  f2n_polymod_t operator-(const f2n_polymod_t &that) const;
  f2n_polymod_t operator-(void) const;
  f2n_polymod_t operator*(const f2n_polymod_t &that) const;
  f2n_polymod_t operator*(int a) const; // Repeated addition.
  f2n_polymod_t operator/(const f2n_polymod_t &that) const;
  f2n_polymod_t operator%(const f2n_polymod_t &that) const;
  bool recip(f2n_polymod_t &rinv) const;
  f2n_polymod_t exp(int e) const;
  friend std::ostream &operator<<(std::ostream &os, const f2n_polymod_t &a);
  // Modulus must have already been set:  this sets only the residue.
  friend std::istream &operator>>(std::ostream &os, const f2n_polymod_t &a);
  friend std::istringstream &operator>>(
      std::istringstream &iss, f2n_polymod_t &a);
  bool from_string(const std::string &string, f2n_poly_t &m);

  f2n_polymod_t &operator+=(const f2n_polymod_t &that);
  f2n_polymod_t &operator-=(const f2n_polymod_t &that);
  f2n_polymod_t &operator*=(const f2n_polymod_t &that);
  f2n_polymod_t &operator*=(int a);
  f2n_polymod_t &operator/=(const f2n_polymod_t &that);
  f2n_polymod_t &operator%=(const f2n_polymod_t &that);

  bool operator==(const f2n_polymod_t &that) const;
  bool operator!=(const f2n_polymod_t &that) const;
  bool operator==(int that) const;
  bool operator!=(int that) const;
  // Polynomial quotient rings are *not* totally ordered.
  // Nonetheless, these methods are handy for looping and sorting.
  bool operator<(const f2n_polymod_t &that) const;
  bool operator>(const f2n_polymod_t &that) const;
  bool operator<=(const f2n_polymod_t &that) const;
  bool operator>=(const f2n_polymod_t &that) const;

  f2n_poly_t get_residue(void) const;
  f2n_poly_t get_modulus(void) const;

private:
  f2n_poly_t residue;
  f2n_poly_t modulus;

  void check_moduli(const f2n_polymod_t &that) const;
};

} // namespace spffl::polynomials

#endif // F2NPOLYMOD_T_H
