// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// Elements of the ring Z_2[x].

#ifndef F2POLY_T_H
#define F2POLY_T_H

#include "bit_t.h"
#include "count_bits.h"
#include "log2.h"
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <sstream>

namespace spffl::polynomials {

// ================================================================
class f2_poly_t {
public:
  f2_poly_t(void);

  f2_poly_t(int c0);
  f2_poly_t(int c1, int c0);
  f2_poly_t(int c2, int c1, int c0);
  f2_poly_t(int c3, int c2, int c1, int c0);
  f2_poly_t(int c4, int c3, int c2, int c1, int c0);
  f2_poly_t(int c5, int c4, int c3, int c2, int c1, int c0);

  f2_poly_t(const std::string & s);

  static f2_poly_t from_base_rep(uint64_t b);
  f2_poly_t prime_sfld_elt(int v) const;
  bool from_string(const char *string);
  int get_characteristic(void);

  f2_poly_t(const f2_poly_t &that);
  ~f2_poly_t(void);

  f2_poly_t &operator=(f2_poly_t that);
  f2_poly_t &operator=(int bit); // 0 or 1; other bits ignored.
  f2_poly_t operator+(f2_poly_t that) const;
  f2_poly_t operator-(f2_poly_t that) const;
  f2_poly_t operator-(void) const;
  f2_poly_t operator*(f2_poly_t that) const;
  f2_poly_t operator*(int bit); // 0 or 1; other bits ignored.
  f2_poly_t operator/(f2_poly_t that);
  f2_poly_t operator%(f2_poly_t that);

  f2_poly_t &operator+=(f2_poly_t that);
  f2_poly_t &operator-=(f2_poly_t that);
  f2_poly_t &operator*=(f2_poly_t that);
  f2_poly_t &operator*=(int bit); // 0 or 1; other bits ignored.
  f2_poly_t &operator/=(f2_poly_t &that);
  f2_poly_t &operator%=(f2_poly_t &that);

  void quot_and_rem(f2_poly_t &that, f2_poly_t &rquot, f2_poly_t &rrem);
  f2_poly_t gcd(f2_poly_t &that);
  f2_poly_t ext_gcd(f2_poly_t &that, f2_poly_t &rm, f2_poly_t &rn);
  f2_poly_t exp(int power);
  f2_poly_t deriv(void);
  bool square_root(f2_poly_t &rroot);
  int eval(int c);
  spffl::bits::bit_t eval(spffl::bits::bit_t c);
  int zcount_one_bits(void);

  int find_degree(void) const; // deg(0) is defined to be 0.

  bool operator==(int v) const;
  bool operator!=(int v) const;
  bool operator==(f2_poly_t that) const;
  bool operator!=(f2_poly_t that) const;
  // F2[x] is *not* totally ordered.  Nonetheless, these methods are
  // handy for looping and sorting.
  bool operator<(f2_poly_t that) const;
  bool operator>(f2_poly_t that) const;
  bool operator<=(f2_poly_t that) const;
  bool operator>=(f2_poly_t that) const;
  void increment(void);

  friend std::ostream &operator<<(std::ostream &os, const f2_poly_t &poly);
  friend std::istream &operator>>(std::istream &is, f2_poly_t &poly);
  friend std::istringstream &operator>>(std::istringstream &iss,
                                        f2_poly_t &poly);

  // If the polynomial's degree is less than deg, zero-padding is done.
  // This facilitates nice tabular output in certain situations.
  void dprint(std::ostream &os, int deg) const;

  void set_coeff(int pos, spffl::bits::bit_t b);
  void set_bit(int pos);
  int bit_at(int pos) const;

private:
  uint64_t *parts;
  int num_parts;

  bool cmp(int op, f2_poly_t &that) const;
  void promote_n(uint64_t shamt);
  void promote_4(void);
  void promote_1(void);
  void demote_1(void);
  void extend_parts(int new_num_parts);
  void trim_parts(void);
  void check_neg_pos(int pos) const;
  void debug_print(std::ostream &os);
};

} // namespace spffl::polynomials

// Same as the gcd method, but overloaded.  This is important for template use.
spffl::polynomials::f2_poly_t gcd(spffl::polynomials::f2_poly_t a,
                                  spffl::polynomials::f2_poly_t b);

// ================================================================
#endif // F2POLY_T_H
