// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// Elements of the ring Z_2[x].

#ifndef F2POLY_T_H
#define F2POLY_T_H

#include "bits/bit_t.h"
#include "bits/count_bits.h"
#include "intmath/log2.h"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

namespace spffl::polynomials {

// ================================================================
class f2_poly_t {
public:
  f2_poly_t(void);

  f2_poly_t(int c0);
  f2_poly_t(int c1, int c0);
  f2_poly_t(int c2, int c1, int c0);

  f2_poly_t(const std::string &s);

  static f2_poly_t from_base_rep(uint64_t b);
  f2_poly_t prime_subfield_element(int v) const;
  bool from_string(const std::string &string);
  int get_characteristic(void);

  f2_poly_t(const f2_poly_t &that);
  ~f2_poly_t(void);

  f2_poly_t &operator=(const f2_poly_t &that);
  f2_poly_t &operator=(int bit); // 0 or 1; other bits ignored.

  f2_poly_t operator+(const f2_poly_t &that) const;
  f2_poly_t operator-(const f2_poly_t &that) const;
  f2_poly_t operator-(void) const;
  f2_poly_t operator*(const f2_poly_t &that) const;
  f2_poly_t operator*(int bit) const; // 0 or 1; other bits ignored.
  f2_poly_t operator/(const f2_poly_t &that) const;
  f2_poly_t operator%(const f2_poly_t &that) const;

  f2_poly_t &operator+=(const f2_poly_t &that);
  f2_poly_t &operator-=(const f2_poly_t &that);
  f2_poly_t &operator*=(const f2_poly_t &that);
  f2_poly_t &operator*=(int bit); // 0 or 1; other bits ignored.
  f2_poly_t &operator/=(const f2_poly_t &that);
  f2_poly_t &operator%=(const f2_poly_t &that);

  void quot_and_rem(
      const f2_poly_t &that, f2_poly_t &rquot, f2_poly_t &rrem) const;
  f2_poly_t gcd(const f2_poly_t &that) const;
  f2_poly_t ext_gcd(const f2_poly_t &that, f2_poly_t &rm, f2_poly_t &rn) const;
  f2_poly_t exp(int power) const;
  f2_poly_t deriv(void) const;
  bool square_root(f2_poly_t &rroot) const;
  int eval(int c) const;
  spffl::bits::bit_t eval(spffl::bits::bit_t c) const;
  int zcount_one_bits(void) const;

  int find_degree(void) const; // deg(0) is defined to be 0.

  bool operator==(int v) const;
  bool operator!=(int v) const;
  bool operator==(const f2_poly_t &that) const;
  bool operator!=(const f2_poly_t &that) const;
  // F2[x] is *not* totally ordered.  Nonetheless, these methods are
  // handy for looping and sorting.
  bool operator<(const f2_poly_t &that) const;
  bool operator>(const f2_poly_t &that) const;
  bool operator<=(const f2_poly_t &that) const;
  bool operator>=(const f2_poly_t &that) const;
  void increment(void);

  friend std::ostream &operator<<(std::ostream &os, const f2_poly_t &poly);
  friend std::istream &operator>>(std::istream &is, f2_poly_t &poly);
  friend std::istringstream &operator>>(
      std::istringstream &iss, f2_poly_t &poly);

  // If the polynomial's degree is less than deg, zero-padding is done.
  // This facilitates nice tabular output in certain situations.
  void dprint(std::ostream &os, int deg) const;

  void set_coeff(int pos, spffl::bits::bit_t b);
  void set_bit(int pos);
  int bit_at(int pos) const;

  // Not for general use, but exposed for unit test.
  void _promote_n(uint64_t shamt);
  void _promote_4(void);
  void _promote_1(void);
  void _demote_1(void);

private:
  std::vector<uint64_t> parts;

  bool cmp(int op, const f2_poly_t &that) const;
  void extend_parts(int new_num_parts);
  void trim_parts(void);
  void check_neg_pos(int pos) const;
  void debug_print(std::ostream &os);
};

} // namespace spffl::polynomials

// Same as the gcd method, but overloaded.  This is important for template use.
spffl::polynomials::f2_poly_t gcd(const spffl::polynomials::f2_poly_t &a,
    const spffl::polynomials::f2_poly_t &b);

// ================================================================
#endif // F2POLY_T_H
