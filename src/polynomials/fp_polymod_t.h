// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLYMOD_T_H
#define FPPOLYMOD_T_H

#include "fp_poly_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

class fp_polymod_t {
public:
  fp_polymod_t(fp_poly_t residue, fp_poly_t modulus);
  fp_polymod_t(void);
  fp_polymod_t(const fp_polymod_t &that);
  ~fp_polymod_t(void);

  fp_polymod_t prime_sfld_elt(int v) const;
  static fp_polymod_t prime_sfld_elt(int v, fp_poly_t m);
  int get_char(void);

  fp_polymod_t &operator=(fp_polymod_t that);
  fp_polymod_t operator+(fp_polymod_t that);
  fp_polymod_t operator-(fp_polymod_t that);
  fp_polymod_t operator-(void);
  fp_polymod_t operator*(fp_polymod_t that);
  fp_polymod_t operator*(int a); // Repeated addition.
  fp_polymod_t operator*(spffl::intmath::intmod_t a);
  fp_polymod_t operator/(fp_polymod_t that);
  fp_polymod_t operator%(fp_polymod_t that);
  int recip(fp_polymod_t &rinv);
  fp_polymod_t exp(int e);
  friend std::ostream &operator<<(std::ostream &os, const fp_polymod_t &a);
  // Modulus must have already been set:  this sets only the residue.
  friend std::istream &operator>>(std::ostream &os, const fp_polymod_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss,
                                        fp_polymod_t &a);
  int from_string(char *string, fp_poly_t &m);

  fp_polymod_t &operator+=(fp_polymod_t that);
  fp_polymod_t &operator-=(fp_polymod_t that);
  fp_polymod_t &operator*=(fp_polymod_t that);
  fp_polymod_t &operator*=(int a);
  fp_polymod_t &operator*=(spffl::intmath::intmod_t a);
  fp_polymod_t &operator/=(fp_polymod_t that);
  fp_polymod_t &operator%=(fp_polymod_t that);

  int operator==(fp_polymod_t that) const;
  int operator!=(fp_polymod_t that) const;
  int operator==(int that) const;
  int operator!=(int that) const;
  // Polynomial quotient rings are *not* totally ordered.
  // Nonetheless, these methods are handy for looping and sorting.
  int operator<(fp_polymod_t that) const;
  int operator>(fp_polymod_t that) const;
  int operator<=(fp_polymod_t that) const;
  int operator>=(fp_polymod_t that) const;

  fp_poly_t get_residue(void) const;
  fp_poly_t get_modulus(void) const;

private:
  fp_poly_t residue;
  fp_poly_t modulus;

  void check_moduli(fp_polymod_t &that) const;
};

} // namespace

#endif // FPPOLYMOD_T_H