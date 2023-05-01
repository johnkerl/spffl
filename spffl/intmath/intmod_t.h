// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef INTMOD_T_H
#define INTMOD_T_H

#include "intmath/int_totient.h"
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdlib.h>

namespace spffl::intmath {

class intmod_t {
public:
  intmod_t(int residue, int modulus);
  intmod_t(void);
  intmod_t(const intmod_t &that);
  ~intmod_t(void);

  intmod_t prime_subfield_element(int v) const;

  intmod_t &operator=(const intmod_t &that);

  intmod_t operator+(const intmod_t &that) const;
  intmod_t operator-(const intmod_t &that) const;
  intmod_t operator-(void) const;
  intmod_t operator*(const intmod_t &that) const;
  intmod_t operator/(const intmod_t &that) const;
  intmod_t operator%(const intmod_t &that) const;
  intmod_t operator+(int a) const;
  intmod_t operator-(int a) const;
  intmod_t operator*(int a) const;
  bool recip(intmod_t &rinv) const;
  intmod_t exp(int e) const;

  friend std::ostream &operator<<(std::ostream &os, const intmod_t &a);
  // Modulus must have already been set:  this sets only the residue.
  friend std::istream &operator>>(std::istream &is, intmod_t &a);
  bool from_string(const std::string &string, int modulus);

  intmod_t &operator+=(const intmod_t &that);
  intmod_t &operator-=(const intmod_t &that);
  intmod_t &operator*=(const intmod_t &that);
  intmod_t &operator/=(const intmod_t &that);
  intmod_t &operator%=(const intmod_t &that);

  bool operator==(const intmod_t &that) const;
  bool operator!=(const intmod_t &that) const;
  bool operator==(int that) const;
  bool operator!=(int that) const;
  // Z/mZ is *not* totally ordered.  Nonetheless, these methods are
  // handy for looping and sorting.
  bool operator<(const intmod_t &that) const;
  bool operator>(const intmod_t &that) const;
  bool operator<=(const intmod_t &that) const;
  bool operator>=(const intmod_t &that) const;

  int get_residue(void) const;
  int get_modulus(void) const;

private:
  int residue;
  int modulus;

  void check_moduli(const intmod_t &that) const;
  void check_modulus(void) const;
};

} // namespace spffl::intmath

#endif // INTMOD_T_H
