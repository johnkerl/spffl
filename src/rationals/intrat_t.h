// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef INTRAT_T_H
#define INTRAT_T_H

#include <iomanip>
#include <iostream>
#include <sstream>

namespace spffl::rationals {

class intrat_t {
public:
  intrat_t(int numerator, int denominator);
  intrat_t(int numerator);
  intrat_t(void);
  intrat_t(const intrat_t &that);
  ~intrat_t(void);

  intrat_t &operator=(intrat_t that);
  intrat_t &operator=(int numer);
  intrat_t operator+(intrat_t that) const;
  intrat_t operator-(intrat_t that) const;
  intrat_t operator-(void) const;
  intrat_t operator*(intrat_t that);
  intrat_t operator/(intrat_t that);
  intrat_t operator%(intrat_t that);
  intrat_t exp(int e);
  friend std::ostream &operator<<(std::ostream &os, const intrat_t &a);
  friend std::istream &operator>>(std::istream &is, intrat_t &a);
  friend std::istringstream &operator>>(std::istringstream &iss, intrat_t &a);
  int from_string(char *string);

  intrat_t &operator+=(intrat_t that);
  intrat_t &operator-=(intrat_t that);
  intrat_t &operator*=(intrat_t that);
  intrat_t &operator/=(intrat_t that);
  intrat_t &operator%=(intrat_t that);

  bool operator==(intrat_t that) const;
  bool operator!=(intrat_t that) const;
  bool operator==(int that) const;
  bool operator!=(int that) const;

  bool operator<(intrat_t that) const;
  bool operator>(intrat_t that) const;
  bool operator<=(intrat_t that) const;
  bool operator>=(intrat_t that) const;

  int get_numerator(void) const;
  int get_denominator(void) const;

private:
  int numer;
  int denom;

  void simplify();
};

} // namespace spffl::rationals

#endif // INTRAT_T_H
