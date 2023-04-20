// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLYMOD_T_H
#define FPPOLYMOD_T_H

#include "fppoly_t.h"
#include <iomanip>
#include <iostream>

class fppolymod_t {
public:
  fppolymod_t(fppoly_t residue, fppoly_t modulus);
  fppolymod_t(void);
  fppolymod_t(const fppolymod_t &that);
  ~fppolymod_t(void);

  fppolymod_t prime_sfld_elt(int v) const;
  static fppolymod_t prime_sfld_elt(int v, fppoly_t m);
  int get_char(void);

  fppolymod_t &operator=(fppolymod_t that);
  fppolymod_t operator+(fppolymod_t that);
  fppolymod_t operator-(fppolymod_t that);
  fppolymod_t operator-(void);
  fppolymod_t operator*(fppolymod_t that);
  fppolymod_t operator*(int a); // Repeated addition.
  fppolymod_t operator*(intmod_t a);
  fppolymod_t operator/(fppolymod_t that);
  fppolymod_t operator%(fppolymod_t that);
  int recip(fppolymod_t &rinv);
  fppolymod_t exp(int e);
  friend std::ostream &operator<<(std::ostream &os, const fppolymod_t &a);
  // Modulus must have already been set:  this sets only the residue.
  friend std::istream &operator>>(std::ostream &os, const fppolymod_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss,
                                        fppolymod_t &a);
  int from_string(char *string, fppoly_t &m);

  fppolymod_t &operator+=(fppolymod_t that);
  fppolymod_t &operator-=(fppolymod_t that);
  fppolymod_t &operator*=(fppolymod_t that);
  fppolymod_t &operator*=(int a);
  fppolymod_t &operator*=(intmod_t a);
  fppolymod_t &operator/=(fppolymod_t that);
  fppolymod_t &operator%=(fppolymod_t that);

  int operator==(fppolymod_t that) const;
  int operator!=(fppolymod_t that) const;
  int operator==(int that) const;
  int operator!=(int that) const;
  // Polynomial quotient rings are *not* totally ordered.
  // Nonetheless, these methods are handy for looping and sorting.
  int operator<(fppolymod_t that) const;
  int operator>(fppolymod_t that) const;
  int operator<=(fppolymod_t that) const;
  int operator>=(fppolymod_t that) const;

  fppoly_t get_residue(void) const;
  fppoly_t get_modulus(void) const;

private:
  fppoly_t residue;
  fppoly_t modulus;

  void check_moduli(fppolymod_t &that) const;
};

#endif // FPPOLYMOD_T_H
