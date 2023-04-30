// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "bit_t.h"
#include <iomanip>
#include <iostream>
namespace spffl::bits {

// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const bit_t &a) {
  char c = '0' + a.residue;
  os << c;
  return os;
}

// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, bit_t &a) {
  unsigned r;
  int c;

  // Skip over whitespace.
  c = is.peek();
  if (c == EOF) {
    is.setstate(std::ios::failbit);
    return is;
  }
  while ((c == ' ') || (c == '\t') || (c == '\n')) {
    is.ignore(1, c);
    c = is.peek();
  }
  if (c == EOF) {
    is.setstate(std::ios::failbit);
    return is;
  }

  is >> r;
  a.residue = r & 1;
  return is;
}

// ----------------------------------------------------------------
bool bit_t::from_string(const std::string &string) {
  unsigned r;
  std::istringstream iss(string, std::ios_base::in);
  iss >> r;
  if (iss.fail()) {
    return false;
  } else {
    this->residue = r & 1;
    return true;
  }
}

} // namespace spffl::bits
