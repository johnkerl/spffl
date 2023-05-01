// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLYMOD_T_H
#define FPPOLYMOD_T_H

#include "polynomials/fp_poly_t.h"
#include <iomanip>
#include <iostream>

namespace spffl::polynomials {

class fp_polymod_t {
public:
  fp_polymod_t(const fp_poly_t &residue, const fp_poly_t &modulus);
  fp_polymod_t(void);
  fp_polymod_t(const fp_polymod_t &that);
  ~fp_polymod_t(void);

  fp_polymod_t prime_subfield_element(int v) const;
  static fp_polymod_t prime_subfield_element(int v, const fp_poly_t &m);
  int get_characteristic(void) const;

  fp_polymod_t &operator=(const fp_polymod_t &that);

  fp_polymod_t operator+(const fp_polymod_t &that) const;
  fp_polymod_t operator-(const fp_polymod_t &that) const;
  fp_polymod_t operator-(void) const;
  fp_polymod_t operator*(const fp_polymod_t &that) const;
  fp_polymod_t operator*(int a) const; // Repeated addition.
  fp_polymod_t operator*(spffl::intmath::intmod_t a) const;
  fp_polymod_t operator/(const fp_polymod_t &that) const;
  fp_polymod_t operator%(const fp_polymod_t &that) const;
  bool recip(fp_polymod_t &rinv) const;
  fp_polymod_t exp(int e) const;
  friend std::ostream &operator<<(std::ostream &os, const fp_polymod_t &a);
  // Modulus must have already been set:  this sets only the residue.
  friend std::istream &operator>>(std::ostream &os, const fp_polymod_t &a);
  friend std::istringstream &operator>>(
      std::istringstream &iss, fp_polymod_t &a);
  bool from_string(const std::string &string, fp_poly_t &m);

  fp_polymod_t &operator+=(const fp_polymod_t &that);
  fp_polymod_t &operator-=(const fp_polymod_t &that);
  fp_polymod_t &operator*=(const fp_polymod_t &that);
  fp_polymod_t &operator*=(int a);
  fp_polymod_t &operator*=(const spffl::intmath::intmod_t &a);
  fp_polymod_t &operator/=(const fp_polymod_t &that);
  fp_polymod_t &operator%=(const fp_polymod_t &that);

  bool operator==(const fp_polymod_t &that) const;
  bool operator!=(const fp_polymod_t &that) const;
  bool operator==(int that) const;
  bool operator!=(int that) const;
  // Polynomial quotient rings are *not* totally ordered.
  // Nonetheless, these methods are handy for looping and sorting.
  bool operator<(const fp_polymod_t &that) const;
  bool operator>(const fp_polymod_t &that) const;
  bool operator<=(const fp_polymod_t &that) const;
  bool operator>=(const fp_polymod_t &that) const;

  fp_poly_t get_residue(void) const;
  fp_poly_t get_modulus(void) const;

private:
  fp_poly_t residue;
  fp_poly_t modulus;

  void check_moduli(const fp_polymod_t &that) const;
};

} // namespace spffl::polynomials

#endif // FPPOLYMOD_T_H
