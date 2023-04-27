// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLYMOD_T_H
#define F2NPOLYMOD_T_H

#include "f2n_poly_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

class f2n_polymod_t {
public:
  f2n_polymod_t(f2n_poly_t residue, f2n_poly_t modulus);
  f2n_polymod_t(void);
  f2n_polymod_t(const f2n_polymod_t &that);
  ~f2n_polymod_t(void);

  f2n_polymod_t prime_sfld_elt(int v) const;
  static f2n_polymod_t prime_sfld_elt(int v, f2n_poly_t om);
  int get_char(void);

  f2n_polymod_t &operator=(f2n_polymod_t that);
  f2n_polymod_t operator+(f2n_polymod_t that);
  f2n_polymod_t operator-(f2n_polymod_t that);
  f2n_polymod_t operator-(void);
  f2n_polymod_t operator*(f2n_polymod_t that);
  f2n_polymod_t operator*(int a); // Repeated addition.
  f2n_polymod_t operator/(f2n_polymod_t that);
  f2n_polymod_t operator%(f2n_polymod_t that);
  bool recip(f2n_polymod_t &rinv);
  f2n_polymod_t exp(int e);
  friend std::ostream &operator<<(std::ostream &os, const f2n_polymod_t &a);
  // Modulus must have already been set:  this sets only the residue.
  friend std::istream &operator>>(std::ostream &os, const f2n_polymod_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss,
                                        f2n_polymod_t &a);
  bool from_string(char *string, f2n_poly_t &m);

  f2n_polymod_t &operator+=(f2n_polymod_t that);
  f2n_polymod_t &operator-=(f2n_polymod_t that);
  f2n_polymod_t &operator*=(f2n_polymod_t that);
  f2n_polymod_t &operator*=(int a);
  f2n_polymod_t &operator/=(f2n_polymod_t that);
  f2n_polymod_t &operator%=(f2n_polymod_t that);

  bool operator==(f2n_polymod_t that) const;
  bool operator!=(f2n_polymod_t that) const;
  bool operator==(int that) const;
  bool operator!=(int that) const;
  // Polynomial quotient rings are *not* totally ordered.
  // Nonetheless, these methods are handy for looping and sorting.
  bool operator<(f2n_polymod_t that) const;
  bool operator>(f2n_polymod_t that) const;
  bool operator<=(f2n_polymod_t that) const;
  bool operator>=(f2n_polymod_t that) const;

  f2n_poly_t get_residue(void) const;
  f2n_poly_t get_modulus(void) const;

private:
  f2n_poly_t residue;
  f2n_poly_t modulus;

  void check_moduli(f2n_polymod_t &that) const;
};

} // namespace spffl::polynomials

#endif // F2NPOLYMOD_T_H
