// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2_poly_t.h"
#include "cmps.h"
#include <ctype.h>
#include <string.h>

namespace spffl::polynomials {

// ----------------------------------------------------------------
// Parts are 64-bit unsigned integers.
static const uint64_t F2_POLY_PART_MASK        = 63;
static const uint64_t F2_POLY_PART_LOG         = 6;
static const uint64_t F2_POLY_NYBBLES_PER_PART = 16;
static const uint64_t F2_POLY_BITS_PER_PART    = 64;
static const uint64_t F2_POLY_MSB              = 0x8000000000000000LL;
static const uint64_t F2_POLY_LSB              = 1LL;
static const uint64_t F2_POLY_FOUR_MSBS        = 0xf000000000000000LL;
static const uint64_t F2_POLY_01_MASK          = 0x5555555555555555LL;

// ----------------------------------------------------------------
f2_poly_t::f2_poly_t(void) {
  uint64_t bits = 0;
  this->parts   = std::vector<uint64_t>(1, bits);
}

// ----------------------------------------------------------------
f2_poly_t::f2_poly_t(int c0) {
  uint64_t bits = c0 & 1;
  this->parts   = std::vector<uint64_t>(1, bits);
}
f2_poly_t::f2_poly_t(int c1, int c0) {
  uint64_t bits = ((c1 & 1) << 1) | (c0 & 1);
  this->parts   = std::vector<uint64_t>(1, bits);
}
f2_poly_t::f2_poly_t(int c2, int c1, int c0) {
  uint64_t bits = ((c2 & 1) << 2) | ((c1 & 1) << 1) | (c0 & 1);
  this->parts   = std::vector<uint64_t>(1, bits);
}

f2_poly_t::f2_poly_t(const std::string &s) {
  uint64_t bits = 0;
  this->parts   = std::vector<uint64_t>(1, bits);

  std::istringstream iss(s, std::ios_base::in);
  iss >> *this;
  if (iss.fail()) {
    std::cerr << "f2_poly_t:  could not construct from \"" << s << "\"\n";
    exit(1);
  }
}

// ----------------------------------------------------------------
// This is a static method.
f2_poly_t f2_poly_t::from_base_rep(uint64_t b) {
  f2_poly_t rv;
  rv.parts = std::vector<uint64_t>(1, b);
  return rv;
}

// ----------------------------------------------------------------
bool f2_poly_t::from_string(const std::string &string) {
  std::istringstream iss(string, std::ios_base::in);
  iss >> *this;
  // return iss.fail() ? 0 : iss.eof() ? 0 : 1;
  return iss.fail() ? false : true;
}

// ----------------------------------------------------------------
f2_poly_t::f2_poly_t(const f2_poly_t &that) { this->parts = that.parts; }

// ----------------------------------------------------------------
f2_poly_t::~f2_poly_t(void) {}

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::prime_subfield_element(int v) const {
  return f2_poly_t(v & 1);
}

// ----------------------------------------------------------------
int f2_poly_t::get_characteristic(void) { return 2; }

// ----------------------------------------------------------------
f2_poly_t &f2_poly_t::operator=(const f2_poly_t &that) {
  this->parts = that.parts;
  return *this;
}

// ----------------------------------------------------------------
f2_poly_t &f2_poly_t::operator=(int bit) {
  this->parts = std::vector<uint64_t>(1, (uint64_t)(bit & 1));
  return *this;
}

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator+(const f2_poly_t &that) const {
  int i;
  f2_poly_t rv;

  if (this->parts.size() < that.parts.size()) {
    rv.parts = std::vector<uint64_t>(that.parts.size());
    for (i = 0; i < this->parts.size(); i++) {
      rv.parts[i] = this->parts[i] ^ that.parts[i];
    }
    for (i = this->parts.size(); i < that.parts.size(); i++) {
      rv.parts[i] = that.parts[i];
    }
  } else {
    rv.parts = std::vector<uint64_t>(this->parts.size());
    for (i = 0; i < that.parts.size(); i++) {
      rv.parts[i] = this->parts[i] ^ that.parts[i];
    }
    for (i = that.parts.size(); i < this->parts.size(); i++) {
      rv.parts[i] = this->parts[i];
    }
  }
  // Cancellation of coefficients may have reduced the degree.
  rv.trim_parts();
  return rv;
}

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator-(const f2_poly_t &that) const {
  return *this + that;
}

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator-(void) const { return *this; }

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator*(const f2_poly_t &that) const {
  f2_poly_t out;
  int adeg = this->find_degree();
  int bdeg = that.find_degree();
  int cdeg = adeg + bdeg;

  out.parts.resize((cdeg + F2_POLY_BITS_PER_PART) >> F2_POLY_PART_LOG);
  for (int i = 0; i < out.parts.size(); i++) {
    out.parts[i] = 0;
  }
  f2_poly_t ashift(*this);
  for (int i = 0; i <= bdeg; i++) {
    if (that.bit_at(i)) {
      for (int j = 0; j < ashift.parts.size(); j++) {
        out.parts[j] ^= ashift.parts[j];
      }
    }
    ashift._promote_1();
  }
  return out;
}

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator*(int bit) const {
  if (bit & 1) {
    return *this;
  } else {
    return f2_poly_t(0);
  }
}
// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator/(const f2_poly_t &that) const {
  f2_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return quot;
}
// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator%(const f2_poly_t &that) const {
  f2_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return rem;
}
// ----------------------------------------------------------------
f2_poly_t &f2_poly_t::operator+=(const f2_poly_t &that) {
  *this = *this + that;
  return *this;
}
f2_poly_t &f2_poly_t::operator-=(const f2_poly_t &that) {
  *this = *this - that;
  return *this;
}
f2_poly_t &f2_poly_t::operator*=(const f2_poly_t &that) {
  *this = *this * that;
  return *this;
}
f2_poly_t &f2_poly_t::operator*=(int bit) {
  *this = *this * bit;
  return *this;
}
f2_poly_t &f2_poly_t::operator/=(const f2_poly_t &that) {
  *this = *this / that;
  return *this;
}
f2_poly_t &f2_poly_t::operator%=(const f2_poly_t &that) {
  *this = *this % that;
  return *this;
}
// ----------------------------------------------------------------
// E.g.
// dividend = 1,2,3,4 (1 + 2x + 3x^2 + 4x^3)
// divisor  = 1,1,2   (1 +  x + 2x^2)
// modulus = 7
//
//             q=4,2   r = 4,3
//        +----------
// 1,1,2  |  1,2,3,4
//        |    2,2,4 shift = 1.  4/2 mod 7 = 2.  1,1,2 * 2 = 2,2,4.
//        +----------
//        |  1 0 1
//        |  4 4 1   shift = 0.  1/2 mod 7 = 4   1,1,2 * 4 = 4,4,1
//        +----------
//        |  4 3
// ----------------------------------------------------------------
// dividend = *this
// divisor  =  that
void f2_poly_t::quot_and_rem(
    const f2_poly_t &that, f2_poly_t &rquot, f2_poly_t &rrem) const {
  int dividend_l1_pos;
  int divisor_l1_pos;
  int l1_diff;
  f2_poly_t shift_divisor;
  int check_pos, quot_pos;
  divisor_l1_pos = that.find_degree();
  if ((divisor_l1_pos == 0) && (that.parts[0] == 0)) {
    // Divisor is zero.
    std::cerr << "f2_poly_quot_and_rem:  Divide by zero.\n";
    exit(1);
  }
  dividend_l1_pos = this->find_degree();
  if ((dividend_l1_pos == 0) && (this->parts[0] == 0)) {
    // Dividend is zero.
    rquot = f2_poly_t(0);
    rrem  = f2_poly_t(0);
    return;
  }
  l1_diff = dividend_l1_pos - divisor_l1_pos;
  if (l1_diff < 0) {
    // Dividend has lower degree than divisor.
    rquot = f2_poly_t(0);
    rrem  = *this;
    return;
  }
  f2_poly_t quot = f2_poly_t(0);
  f2_poly_t rem  = *this;
  shift_divisor  = that;
  shift_divisor._promote_n(l1_diff);
  for (check_pos = dividend_l1_pos, quot_pos = l1_diff;
       check_pos >= divisor_l1_pos; check_pos--, quot_pos--) {
    if (rem.bit_at(check_pos)) {
      rem -= shift_divisor;
      quot.set_bit(quot_pos);
    }
    shift_divisor._demote_1();
  }
  rquot = quot;
  rrem  = rem;
}
// ----------------------------------------------------------------
f2_poly_t f2_poly_t::gcd(const f2_poly_t &that) const {
  f2_poly_t c, q, r;
  f2_poly_t d; // Return value.
  if (*this == 0) {
    return that;
  }
  if (that == 0) {
    return *this;
  }
  c = *this;
  d = that;
  while (1) {
    c.quot_and_rem(d, q, r);
    if (r == 0) {
      break;
    }
    c = d;
    d = r;
  }
  return d;
}
// ----------------------------------------------------------------
// Blankinship's algorithm.
f2_poly_t f2_poly_t::ext_gcd(
    const f2_poly_t &that, f2_poly_t &rm, f2_poly_t &rn) const {
  f2_poly_t mprime, nprime, c, q, r, t, qm, qn;
  f2_poly_t d; // Return value.
  if (*this == 0) {
    rm = 0;
    rn = 1;
    return that;
  }
  if (that == 0) {
    rm = 1;
    rn = 0;
    return *this;
  }
  mprime = 1;
  rn     = 1;
  rm     = 0;
  nprime = 0;
  c      = *this;
  d      = that;
  while (1) {
    c.quot_and_rem(d, q, r);
    if (r == 0) {
      break;
    }
    c      = d;
    d      = r;
    t      = mprime;
    mprime = rm;
    qm     = q * rm;
    rm     = t - qm;
    t      = nprime;
    nprime = rn;
    qn     = q * rn;
    rn     = t - qn;
  }
  return d;
}
// ----------------------------------------------------------------
f2_poly_t f2_poly_t::exp(int e) const {
  int deg      = this->find_degree();
  f2_poly_t xp = *this;
  f2_poly_t zero(0);
  f2_poly_t one(1);
  f2_poly_t rv = one;
  if (*this == zero) {
    if (e == 0) {
      std::cerr << "f2_poly_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    } else if (e < 0) {
      std::cerr << "f2_poly_t::exp:  division by zero.\n";
      exit(1);
    } else {
      return zero;
    }
  } else if (deg == 0) {
    // Unit
    return one;
  } else {
    // Degree 1 or higher.
    if (e < 0) {
      std::cerr << "f2_poly_t::exp:  division by non-unit.\n";
      exit(1);
    } else {
      while (e != 0) {
        if (e & 1) {
          rv *= xp;
        }
        e = (uint64_t)e >> 1;
        xp *= xp;
      }
      return rv;
    }
  }
}
// ----------------------------------------------------------------
f2_poly_t f2_poly_t::deriv(void) const {
  f2_poly_t rv = *this;
  rv._demote_1();
  for (int i = 0; i < rv.parts.size(); i++) {
    rv.parts[i] &= F2_POLY_01_MASK;
  }
  rv.trim_parts();
  return rv;
}
// ----------------------------------------------------------------
// Relies on the fact that f(x^p) = f^p(x) over Fp[x].
//
// in  = a4 x^4 + a2 x^2 + a0
// out = a4 x^2 + a2 x   + a0
bool f2_poly_t::square_root(f2_poly_t &rroot) const {
  int si, di;
  int deg = this->find_degree();
  f2_poly_t root(0);
  for (si = 0, di = 0; si <= deg; si += 2, di++) {
    if (this->bit_at(si)) {
      root.set_bit(di);
    }
    if (this->bit_at(si + 1)) {
      return false;
    }
  }
  rroot = root;
  return true;
}
// ----------------------------------------------------------------
spffl::bits::bit_t f2_poly_t::eval(spffl::bits::bit_t c) const {
  return spffl::bits::bit_t(this->eval(c.get_residue()));
}
// ----------------------------------------------------------------
int f2_poly_t::eval(int c) const {
  if (c & 1) {
    return this->zcount_one_bits();
  } else {
    return this->parts[0] & 1;
  }
}
// ----------------------------------------------------------------
int f2_poly_t::zcount_one_bits(void) const {
  int num_one_bits = 0;
  // TODO: use an iterator
  for (int i = 0; i < this->parts.size(); i++) {
    uint64_t part = this->parts[i];
    num_one_bits +=
        spffl::bits::count_one_bits((unsigned char *)&part, sizeof(part));
  }
  return 1 & num_one_bits;
}
// ----------------------------------------------------------------
int f2_poly_t::find_degree(void) const {
  for (int i = this->parts.size() - 1; i >= 0; i--) {
    if (this->parts[i]) {
      return spffl::intmath::find_msb_64(this->parts[i]) +
             ((uint64_t)i << F2_POLY_PART_LOG);
    }
  }
  return 0; // Zero polynomial.
}
// ----------------------------------------------------------------
bool f2_poly_t::operator==(int v) const {
  for (int i = this->parts.size() - 1; i > 0; i--) {
    if (this->parts[i] != 0) {
      return false;
    }
  }
  return this->parts[0] == (uint64_t)(v & 1);
}
bool f2_poly_t::operator!=(int v) const { return !(*this == v); }
bool f2_poly_t::operator==(const f2_poly_t &that) const {
  return this->cmp(CMP_EQ, that);
}
bool f2_poly_t::operator!=(const f2_poly_t &that) const {
  return this->cmp(CMP_NE, that);
}
bool f2_poly_t::operator<(const f2_poly_t &that) const {
  return this->cmp(CMP_LT, that);
}
bool f2_poly_t::operator>(const f2_poly_t &that) const {
  return this->cmp(CMP_GT, that);
}
bool f2_poly_t::operator<=(const f2_poly_t &that) const {
  return this->cmp(CMP_LE, that);
}
bool f2_poly_t::operator>=(const f2_poly_t &that) const {
  return this->cmp(CMP_GE, that);
}
bool f2_poly_t::cmp(int op, const f2_poly_t &that) const {
  int direction = 0; // -1 = less, 0 = equal, +1 = greater;
  int i;
  int adeg = this->find_degree();
  int bdeg = that.find_degree();
  if (adeg < bdeg) {
    direction = -1;
  } else if (adeg > bdeg) {
    direction = 1;
  } else {
    for (i = adeg >> F2_POLY_PART_LOG; i >= 0; i--) {
      if (this->parts[i] < that.parts[i]) {
        direction = -1;
        break;
      } else if (this->parts[i] > that.parts[i]) {
        direction = 1;
        break;
      }
    }
  }
  switch (op) {
  case CMP_LE:
    return (direction <= 0);
    break;
  case CMP_LT:
    return (direction < 0);
    break;
  case CMP_EQ:
    return (direction == 0);
    break;
  case CMP_NE:
    return (direction != 0);
    break;
  case CMP_GE:
    return (direction >= 0);
    break;
  case CMP_GT:
    return (direction > 0);
    break;
  default:
    std::cerr << "Ack!\n";
    exit(1);
    return false;
    break;
  }
}
// ----------------------------------------------------------------
void f2_poly_t::increment(void) {
  uint64_t zero = 0;
  for (int i = 0; i < this->parts.size(); i++) {
    if (this->parts[i] != ~zero) {
      this->parts[i]++;
      return;
    } else {
      this->parts[i] = zero;
    }
  }
  this->set_bit(this->parts.size() * F2_POLY_BITS_PER_PART);
}
// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const f2_poly_t &poly) {
  if (poly.parts.size() <= 0) {
    std::cerr << "f2_poly_t ostream <<:  empty polynomial.\n";
    exit(1);
  }
  std::ios_base::fmtflags svflags = os.flags();
  os.flags(std::ios_base::hex);
  int i;
  int leader_pos = 0;
  for (i = poly.parts.size() - 1; i >= 0; i--) {
    if ((poly.parts[i]) || (i == 0)) {
      leader_pos = i;
      break;
    }
  }
  for (i = poly.parts.size() - 1; i >= 0; i--) {
    if (i > leader_pos) {
      ;
    } else if (i == leader_pos) {
      os << poly.parts[i];
    } else {
      os << std::setw(F2_POLY_NYBBLES_PER_PART) << std::setfill('0');
      os << poly.parts[i];
    }
  }
  os.flags(svflags);
  return os;
}
// ----------------------------------------------------------------
void f2_poly_t::debug_print(std::ostream &os) {
  std::ios_base::fmtflags svflags = os.flags();
  os.flags(std::ios_base::hex);
  for (int i = this->parts.size() - 1; i >= 0; i--) {
    os << std::setw(F2_POLY_NYBBLES_PER_PART) << std::setfill('0');
    os << this->parts[i];
    if (i > 0) {
      os << '_';
    }
  }
  os.flags(svflags);
}
// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, f2_poly_t &poly) {
  int c;
  poly            = f2_poly_t(0);
  int num_nybbles = 0;
  // Skip over whitespace.
  c = is.peek();
  while ((c == ' ') || (c == '\t') || (c == '\n')) {
    is.ignore(1, c);
    if (is.eof()) {
      break;
    }
    c = is.peek();
  }
  if (is.eof()) {
    is.setstate(std::ios::failbit);
    return is;
  }
  c = is.peek();
  while (isxdigit(c)) {
    if (is.eof()) {
      break;
    }
    c = is.get();
    poly._promote_4();
    if (isdigit(c)) {
      poly.parts[0] |= c - '0';
    } else if (islower(c)) {
      poly.parts[0] |= c - 'a' + 10;
    } else {
      poly.parts[0] |= c - 'A' + 10;
    }
    num_nybbles++;
    c = is.peek();
  }
  if (num_nybbles == 0) {
    is.setstate(std::ios::failbit);
  }
  return is;
}
// ----------------------------------------------------------------
std::istringstream &operator>>(std::istringstream &iss, f2_poly_t &poly) {
  int c;
  poly            = f2_poly_t(0);
  int num_nybbles = 0;
  // Skip over whitespace.
  c = iss.peek();
  if (c == EOF) {
    iss.setstate(std::ios::failbit);
    return iss;
  }
  while ((c == ' ') || (c == '\t') || (c == '\n')) {
    iss.ignore(1, c);
    c = iss.peek();
  }
  if (c == EOF) {
    iss.setstate(std::ios::failbit);
    return iss;
  }
  c = iss.peek();
  while (isxdigit(c)) {
    c = iss.get();
    poly._promote_4();
    if (isdigit(c)) {
      poly.parts[0] |= c - '0';
    } else if (islower(c)) {
      poly.parts[0] |= c - 'a' + 10;
    } else {
      poly.parts[0] |= c - 'A' + 10;
    }
    num_nybbles++;
    c = iss.peek();
  }
  if (num_nybbles == 0) {
    iss.setstate(std::ios::failbit);
  }
  if (c == EOF) {
    iss.setstate(std::ios::eofbit);
  }
  return iss;
}
// ----------------------------------------------------------------
void f2_poly_t::_promote_n(uint64_t shamt) {
  // For comparison:
  //	for (uint64_t ii = 0; ii < shamt; ii++)
  //		this->_promote_1();
  uint64_t num_parts_shift = shamt >> F2_POLY_PART_LOG;
  uint64_t num_bits_shift  = shamt & F2_POLY_PART_MASK;
  uint64_t cmpl_bits_shift = F2_POLY_BITS_PER_PART - num_bits_shift;
  int odeg                 = this->find_degree();
  int ndeg                 = odeg + shamt;
  int onum_parts           = (odeg >> F2_POLY_PART_LOG) + 1;
  int nnum_parts           = (ndeg >> F2_POLY_PART_LOG) + 1;
  int parts_diff;
  int i;
  this->extend_parts(nnum_parts);
  parts_diff = this->parts.size() - onum_parts;
  if (num_bits_shift == 0) {
    for (i = onum_parts - 1; i >= 0; i--) {
      this->parts[i + num_parts_shift] = this->parts[i];
    }
    for (i = this->parts.size() - onum_parts - 1; i >= 0; i--) {
      this->parts[i] = 0;
    }
  } else {
    int di = this->parts.size() - 1;
    int si = onum_parts - 1;
    if ((odeg & F2_POLY_PART_MASK) >= cmpl_bits_shift) {
      this->parts[di] = this->parts[si] >> cmpl_bits_shift;
      di--;
      si--;
    } else {
      si--;
    }
    for (; si >= 0; si--, di--) {
      this->parts[di] = (this->parts[si] >> cmpl_bits_shift) |
                        (this->parts[si + 1] << num_bits_shift);
    }
    this->parts[di] = this->parts[si + 1] << num_bits_shift;
    di--;
    si--;
    for (; di >= 0; di--) {
      this->parts[di] = 0;
    }
  }
}

// ----------------------------------------------------------------
//        2        1        0
// 00000000 aabbccdd 11223344  pre
// 0000000a abbccdd1 12233440  post
// parts[2] = (parts[2] << 4) | (parts[1] >> 28)
// parts[1] = (parts[1] << 4) | (parts[0] >> 28)
// parts[0] =  parts[0] << 4;
//        1        0
// 0000ccdd 11223344  pre
// 000ccdd1 12233440  post
// parts[1] = (parts[1] << 4) | (parts[0] >> 28)
// parts[0] =  parts[0] << 4;
void f2_poly_t::_promote_4(void) {
  if (this->parts[this->parts.size() - 1] & F2_POLY_FOUR_MSBS) {
    this->extend_parts(this->parts.size() + 1);
  }
  for (int i = this->parts.size() - 1; i > 0; i--) {
    this->parts[i] = (this->parts[i] << 4) | (this->parts[i - 1] >> 60);
  }
  this->parts[0] <<= 4;
}

void f2_poly_t::_promote_1(void) {
  if (this->parts[this->parts.size() - 1] & F2_POLY_MSB) {
    this->extend_parts(this->parts.size() + 1);
  }
  for (int i = this->parts.size() - 1; i > 0; i--) {
    this->parts[i] = (this->parts[i] << 1) |
                     (this->parts[i - 1] >> (F2_POLY_BITS_PER_PART - 1));
  }
  this->parts[0] <<= 1;
}

void f2_poly_t::_demote_1(void) {
  for (int i = 0; i < this->parts.size() - 1; i++) {
    this->parts[i] = (this->parts[i] >> 1) |
                     (this->parts[i + 1] << (F2_POLY_BITS_PER_PART - 1));
  }
  this->parts[this->parts.size() - 1] >>= 1;
  if (this->parts[this->parts.size() - 1] == 0) {
    if (this->parts.size() > 0) {
      this->trim_parts();
    }
  }
}

// ----------------------------------------------------------------
int f2_poly_t::bit_at(int pos) const {
  int which_part = pos >> F2_POLY_PART_LOG;
  int which_bit  = pos & F2_POLY_PART_MASK;
  if (which_part >= this->parts.size()) {
    return 0;
  }
  this->check_neg_pos(pos);
  return (this->parts[which_part] >> which_bit) & F2_POLY_LSB;
}

// ----------------------------------------------------------------
// req deg 37   req   print 10 chars
// this deg 4   would print  1 char
void f2_poly_t::dprint(std::ostream &os, int reqdeg) const {
  int thisdeg    = this->find_degree();
  int reqnchars  = (reqdeg + 4) >> 2;
  int thisnchars = (thisdeg + 4) >> 2;
  int morechars  = reqnchars - thisnchars;
  for (int i = 0; i < morechars; i++) {
    os << '0';
  }
  os << *this;
}

// ----------------------------------------------------------------
void f2_poly_t::set_bit(int pos) {
  int which_part = pos >> F2_POLY_PART_LOG;
  int which_bit  = pos & F2_POLY_PART_MASK;
  if (which_part >= this->parts.size()) {
    this->extend_parts(which_part + 1);
  }
  this->check_neg_pos(pos);
  this->parts[which_part] |= (F2_POLY_LSB << which_bit);
}
void f2_poly_t::set_coeff(int pos, spffl::bits::bit_t b) {
  int which_part = pos >> F2_POLY_PART_LOG;
  int which_bit  = pos & F2_POLY_PART_MASK;
  if (which_part >= this->parts.size()) {
    if (b.get_residue()) {
      this->extend_parts(which_part + 1);
    } else {
      return;
    }
  }
  this->check_neg_pos(pos);
  if (b.get_residue()) {
    this->parts[which_part] |= (1 << which_bit);
  } else {
    this->parts[which_part] &= ~(1 << which_bit);
    this->trim_parts();
  }
}
void f2_poly_t::extend_parts(int new_num_parts) {
  this->parts.resize(new_num_parts);
}
void f2_poly_t::trim_parts(void) {
  int d             = this->find_degree();
  int new_num_parts = (d >> F2_POLY_PART_LOG) + 1;
  if (new_num_parts < this->parts.size()) {
    this->parts.resize(new_num_parts);
  }
}
void f2_poly_t::check_neg_pos(int pos) const {
  if (pos < 0) {
    std::cerr << "f2_poly: negative bit position " << pos << " disallowed.\n";
    exit(1);
  }
}
} // namespace spffl::polynomials
// ----------------------------------------------------------------
spffl::polynomials::f2_poly_t gcd(const spffl::polynomials::f2_poly_t &a,
    const spffl::polynomials::f2_poly_t &b) {
  return a.gcd(b);
}
