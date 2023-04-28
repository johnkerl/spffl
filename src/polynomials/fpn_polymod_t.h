// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPNPOLYMOD_T_H
#define FPNPOLYMOD_T_H

#include "fpn_poly_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

class fpn_polymod_t {
public:
  fpn_polymod_t(fpn_poly_t residue, fpn_poly_t modulus);
  fpn_polymod_t(void);
  fpn_polymod_t(const fpn_polymod_t &that);
  ~fpn_polymod_t(void);

  fpn_polymod_t prime_sfld_elt(int v) const;
  static fpn_polymod_t prime_sfld_elt(int v, fpn_poly_t om);
  int get_characteristic(void);

  fpn_polymod_t &operator=(fpn_polymod_t that);
  fpn_polymod_t operator+(fpn_polymod_t that);
  fpn_polymod_t operator-(fpn_polymod_t that);
  fpn_polymod_t operator-(void);
  fpn_polymod_t operator*(fpn_polymod_t that);
  fpn_polymod_t operator*(int a); // Repeated addition.
  fpn_polymod_t operator/(fpn_polymod_t that);
  fpn_polymod_t operator%(fpn_polymod_t that);
  bool recip(fpn_polymod_t &rinv);
  fpn_polymod_t exp(int e);
  friend std::ostream &operator<<(std::ostream &os, const fpn_polymod_t &a);
  // Modulus must have already been set:  this sets only the residue.
  friend std::istream &operator>>(std::ostream &os, const fpn_polymod_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss,
                                        fpn_polymod_t &a);
  bool from_string(char *string, fpn_poly_t &m);

  fpn_polymod_t &operator+=(fpn_polymod_t that);
  fpn_polymod_t &operator-=(fpn_polymod_t that);
  fpn_polymod_t &operator*=(fpn_polymod_t that);
  fpn_polymod_t &operator*=(int a);
  fpn_polymod_t &operator/=(fpn_polymod_t that);
  fpn_polymod_t &operator%=(fpn_polymod_t that);

  bool operator==(fpn_polymod_t that) const;
  bool operator!=(fpn_polymod_t that) const;
  bool operator==(int that) const;
  bool operator!=(int that) const;
  // Polynomial quotient rings are *not* totally ordered.
  // Nonetheless, these methods are handy for looping and sorting.
  bool operator<(fpn_polymod_t that) const;
  bool operator>(fpn_polymod_t that) const;
  bool operator<=(fpn_polymod_t that) const;
  bool operator>=(fpn_polymod_t that) const;

  fpn_poly_t get_residue(void) const;
  fpn_poly_t get_modulus(void) const;

private:
  fpn_poly_t residue;
  fpn_poly_t modulus;

  void check_moduli(fpn_polymod_t &that) const;
};

} // namespace spffl::polynomials

#endif // FPNPOLYMOD_T_H
