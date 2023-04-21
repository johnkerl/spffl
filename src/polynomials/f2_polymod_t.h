// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYMOD_T_H
#define F2POLYMOD_T_H

#include "f2_poly_t.h"
#include <iomanip>
#include <iostream>

class f2_polymod_t {
public:
  f2_polymod_t(f2_poly_t residue, f2_poly_t modulus);
  f2_polymod_t(void);
  f2_polymod_t(const f2_polymod_t &that);
  ~f2_polymod_t(void);

  f2_polymod_t prime_sfld_elt(int v) const;
  static f2_polymod_t prime_sfld_elt(int v, f2_poly_t m);
  int get_char(void);

  f2_polymod_t &operator=(f2_polymod_t that);
  f2_polymod_t operator+(f2_polymod_t that);
  f2_polymod_t operator-(f2_polymod_t that);
  f2_polymod_t operator-(void);
  f2_polymod_t operator*(f2_polymod_t that);
  f2_polymod_t operator*(int a); // Repeated addition.
  f2_polymod_t operator/(f2_polymod_t that);
  f2_polymod_t operator%(f2_polymod_t that);
  int recip(f2_polymod_t &rinv);
  f2_polymod_t exp(int e);
  friend std::ostream &operator<<(std::ostream &os, const f2_polymod_t &a);
  // Modulus must have already been set:  this sets only the residue.
  friend std::istream &operator>>(std::istream &is, f2_polymod_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss,
                                        f2_polymod_t &a);
  int from_string(char *string, f2_poly_t m);

  f2_polymod_t &operator+=(f2_polymod_t that);
  f2_polymod_t &operator-=(f2_polymod_t that);
  f2_polymod_t &operator*=(f2_polymod_t that);
  f2_polymod_t &operator*=(int a);
  f2_polymod_t &operator/=(f2_polymod_t that);
  f2_polymod_t &operator%=(f2_polymod_t that);

  int operator==(f2_polymod_t that) const;
  int operator!=(f2_polymod_t that) const;
  int operator==(int that) const;
  int operator!=(int that) const;
  // Polynomial quotient rings are *not* totally ordered.
  // Nonetheless, these methods are handy for looping and sorting.
  int operator<(f2_polymod_t that) const;
  int operator>(f2_polymod_t that) const;
  int operator<=(f2_polymod_t that) const;
  int operator>=(f2_polymod_t that) const;

  f2_poly_t get_residue(void) const;
  f2_poly_t get_modulus(void) const;
  void change_modulus(f2_poly_t new_modulus);

private:
  f2_poly_t residue;
  f2_poly_t modulus;

  void check_moduli(f2_polymod_t &that) const;
};

inline f2_polymod_t::f2_polymod_t(void) {
  // Use default ctors for residue and modulus.
}

inline f2_polymod_t::~f2_polymod_t(void) {}

#endif // F2POLYMOD_T_H
