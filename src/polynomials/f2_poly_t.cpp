// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2_poly_t.h"
#include "cmps.h"
#include <ctype.h>

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
// Parts are 32-bit unsigned integers.
#define F2POLY_PART_MASK 31
#define F2POLY_PART_LOG 5
#define F2POLY_NYBBLES_PER_PART (sizeof(unsigned) * 2)
#define F2POLY_BITS_PER_PART (sizeof(unsigned) * 8)
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t::f2_poly_t(void) {
  this->num_parts = 1;
  this->parts = new unsigned[1];
  this->parts[0] = 0;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t::f2_poly_t(int c0) {
  this->num_parts = 1;
  this->parts = new unsigned[1];
  this->parts[0] = c0 & 1;
}
f2_poly_t::f2_poly_t(int c1, int c0) {
  this->num_parts = 1;
  this->parts = new unsigned[1];
  this->parts[0] = ((c1 & 1) << 1) | (c0 & 1);
}
f2_poly_t::f2_poly_t(int c2, int c1, int c0) {
  this->num_parts = 1;
  this->parts = new unsigned[1];
  this->parts[0] = ((c2 & 1) << 2) | ((c1 & 1) << 1) | (c0 & 1);
}
f2_poly_t::f2_poly_t(int c3, int c2, int c1, int c0) {
  this->num_parts = 1;
  this->parts = new unsigned[1];
  this->parts[0] =
      ((c3 & 1) << 3) | ((c2 & 1) << 2) | ((c1 & 1) << 1) | (c0 & 1);
}
f2_poly_t::f2_poly_t(int c4, int c3, int c2, int c1, int c0) {
  this->num_parts = 1;
  this->parts = new unsigned[1];
  this->parts[0] = ((c4 & 1) << 4) | ((c3 & 1) << 3) | ((c2 & 1) << 2) |
                   ((c1 & 1) << 1) | (c0 & 1);
}
f2_poly_t::f2_poly_t(int c5, int c4, int c3, int c2, int c1, int c0) {
  this->num_parts = 1;
  this->parts = new unsigned[1];
  this->parts[0] = ((c5 & 1) << 5) | ((c4 & 1) << 4) | ((c3 & 1) << 3) |
                   ((c2 & 1) << 2) | ((c1 & 1) << 1) | (c0 & 1);
}
#endif

// ----------------------------------------------------------------
// This is a static method.
#ifndef F2POLY_SMALL
f2_poly_t f2_poly_t::from_base_rep(unsigned b) {
  f2_poly_t rv;
  rv.num_parts = 1;
  rv.parts = new unsigned[1];
  rv.parts[0] = b;
  return rv;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
int f2_poly_t::from_string(char *string) {
  std::istringstream iss(string, std::ios_base::in);
  iss >> *this;
  // return iss.fail() ? 0 : iss.eof() ? 0 : 1;
  return iss.fail() ? 0 : 1;
}
#endif

#ifdef F2POLY_SMALL
int f2_poly_t::from_string(char *string) {
  std::istringstream iss(string, std::ios_base::in);
  iss.flags(std::ios_base::hex);
  iss >> this->bits;
  return iss.fail() ? 0 : 1;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t::f2_poly_t(const f2_poly_t &that) {
  this->num_parts = that.num_parts;
  this->parts = new unsigned[this->num_parts];
  for (int i = 0; i < this->num_parts; i++)
    this->parts[i] = that.parts[i];
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t::~f2_poly_t(void) {
  if (this->parts)
    delete[] this->parts;
  this->parts = 0;
  this->num_parts = 0;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t f2_poly_t::prime_sfld_elt(int v) const { return f2_poly_t(v & 1); }
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
int f2_poly_t::get_char(void) { return 2; }
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t &f2_poly_t::operator=(f2_poly_t that) {
  if (this->parts)
    delete[] this->parts;
  this->num_parts = that.num_parts;
  this->parts = new unsigned[this->num_parts];
  for (int i = 0; i < this->num_parts; i++)
    this->parts[i] = that.parts[i];
  return *this;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t &f2_poly_t::operator=(int bit) {
  if (this->parts)
    delete[] this->parts;
  this->num_parts = 1;
  this->parts = new unsigned[this->num_parts];
  this->parts[0] = bit & 1;
  return *this;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t f2_poly_t::operator+(f2_poly_t that) const {
  int i;
  f2_poly_t rv;

  if (this->num_parts < that.num_parts) {
    rv.num_parts = that.num_parts;
    rv.parts = new unsigned[rv.num_parts];
    for (i = 0; i < this->num_parts; i++)
      rv.parts[i] = this->parts[i] ^ that.parts[i];
    for (i = this->num_parts; i < that.num_parts; i++)
      rv.parts[i] = that.parts[i];
  } else {
    rv.num_parts = this->num_parts;
    rv.parts = new unsigned[rv.num_parts];
    for (i = 0; i < that.num_parts; i++)
      rv.parts[i] = this->parts[i] ^ that.parts[i];
    for (i = that.num_parts; i < this->num_parts; i++)
      rv.parts[i] = this->parts[i];
  }
  // Cancellation of coefficients may have reduced the degree.
  rv.trim_parts();
  return rv;
}
#endif

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator-(f2_poly_t that) const { return *this + that; }

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator-(void) const { return *this; }

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t f2_poly_t::operator*(f2_poly_t that) const {
  f2_poly_t out;
  int adeg = this->find_degree();
  int bdeg = that.find_degree();
  int cdeg = adeg + bdeg;

  out.num_parts = (cdeg + F2POLY_BITS_PER_PART) >> F2POLY_PART_LOG;
  out.parts = new unsigned[out.num_parts];
  for (int i = 0; i < out.num_parts; i++)
    out.parts[i] = 0;
  f2_poly_t ashift(*this);
  for (int i = 0; i <= bdeg; i++) {
    if (that.bit_at(i)) {
      for (int j = 0; j < ashift.num_parts; j++)
        out.parts[j] ^= ashift.parts[j];
    }
    ashift.promote_1();
  }
  return out;
}
#endif

#ifdef F2POLY_SMALL
f2_poly_t f2_poly_t::operator*(f2_poly_t that) const {
  f2_poly_t prod = 0;
  int this_deg = this->find_degree();
  int that_deg = that.find_degree();
  int prod_deg = this_deg + that_deg;
  if (prod_deg > F2POLY_MAX_DEGREE) {
    std::cerr << "f2_poly_t: multiplication overflow.\n";
    exit(1);
  }

  unsigned a = this->bits;
  unsigned b = that.bits;
  unsigned c = 0;
  unsigned ashift = a;

  for (int j = 0; j <= that_deg; j++) {
    if (F2POLY_BIT_AT(b, j))
      c ^= ashift;
    ashift <<= 1;
  }

  prod.bits = c;
  return prod;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t f2_poly_t::operator*(int bit) {
  if (bit & 1)
    return *this;
  else
    return f2_poly_t(0);
}
#endif

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator/(f2_poly_t that) {
  f2_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return quot;
}

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::operator%(f2_poly_t that) {
  f2_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return rem;
}

// ----------------------------------------------------------------
f2_poly_t &f2_poly_t::operator+=(f2_poly_t that) {
  *this = *this + that;
  return *this;
}
f2_poly_t &f2_poly_t::operator-=(f2_poly_t that) {
  *this = *this - that;
  return *this;
}
f2_poly_t &f2_poly_t::operator*=(f2_poly_t that) {
  *this = *this * that;
  return *this;
}
f2_poly_t &f2_poly_t::operator*=(int bit) {
  *this = *this * bit;
  return *this;
}
f2_poly_t &f2_poly_t::operator/=(f2_poly_t &that) {
  *this = *this / that;
  return *this;
}
f2_poly_t &f2_poly_t::operator%=(f2_poly_t &that) {
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
#ifndef F2POLY_SMALL
// dividend = *this
// divisor  =  that

void f2_poly_t::quot_and_rem(f2_poly_t &that, f2_poly_t &rquot, f2_poly_t &rrem) {
  int dividend_l1_pos;
  int divisor_l1_pos;
  int l1_diff;
  f2_poly_t shift_divisor;
  int check_pos, quot_pos;

  divisor_l1_pos = that.find_degree();
  if ((divisor_l1_pos == 0) && (that.parts[0] == 0)) {
    // Divisor is zero.
    std::cerr << "f2poly_quot_and_rem:  Divide by zero.\n";
    exit(1);
  }

  dividend_l1_pos = this->find_degree();
  if ((dividend_l1_pos == 0) && (this->parts[0] == 0)) {
    // Dividend is zero.
    rquot = f2_poly_t(0);
    rrem = f2_poly_t(0);
    return;
  }

  l1_diff = dividend_l1_pos - divisor_l1_pos;
  if (l1_diff < 0) {
    // Dividend has lower degree than divisor.
    rquot = f2_poly_t(0);
    rrem = *this;
    return;
  }

  f2_poly_t quot = f2_poly_t(0);
  f2_poly_t rem = *this;
  shift_divisor = that;
  shift_divisor.promote_n(l1_diff);

  for (check_pos = dividend_l1_pos, quot_pos = l1_diff;
       check_pos >= divisor_l1_pos; check_pos--, quot_pos--) {
    if (rem.bit_at(check_pos)) {
      rem -= shift_divisor;
      quot.set_bit(quot_pos);
    }
    shift_divisor.demote_1();
  }
  rquot = quot;
  rrem = rem;
}
#endif

#ifdef F2POLY_SMALL
void f2_poly_t::quot_and_rem(f2_poly_t &that, f2_poly_t &rquot, f2_poly_t &rrem) {
  int dividend_l1_pos;
  int divisor_l1_pos;
  int l1_diff;
  unsigned shift_divisor;
  int check_pos;
  int quot_pos;

  if (that == 0) {
    // Divisor is zero.
    std::cerr << "f2_poly_t::quot_and_rem:  Divide by zero.\n";
    exit(1);
  }
  divisor_l1_pos = that.find_degree();

  if (*this == 0) {
    rquot = 0;
    rrem = 0;
    return;
  }
  dividend_l1_pos = this->find_degree();

  l1_diff = dividend_l1_pos - divisor_l1_pos;

  if (l1_diff < 0) {
    // Dividend has lower degree than divisor.
    rquot = 0;
    rrem = *this;
    return;
  }

  shift_divisor = that.bits << l1_diff;

  rrem = *this;
  rquot = 0;
  for (check_pos = dividend_l1_pos, quot_pos = l1_diff;
       check_pos >= divisor_l1_pos; check_pos--, quot_pos--) {
    if (F2POLY_BIT_AT(rrem.bits, check_pos)) {
      rrem.bits ^= shift_divisor;
      F2POLY_SET_BIT(rquot.bits, quot_pos);
    }
    shift_divisor >>= 1;
  }
}
#endif

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::gcd(f2_poly_t &that) {
  f2_poly_t c, q, r;
  f2_poly_t d; // Return value.

  if (*this == 0)
    return that;
  if (that == 0)
    return *this;

  c = *this;
  d = that;

  while (1) {
    c.quot_and_rem(d, q, r);
    if (r == 0)
      break;
    c = d;
    d = r;
  }
  return d;
}

// ----------------------------------------------------------------
f2_poly_t gcd(f2_poly_t a, f2_poly_t b) { return a.gcd(b); }

// ----------------------------------------------------------------
// Blankinship's algorithm.

#ifndef F2POLY_SMALL
f2_poly_t f2_poly_t::ext_gcd(f2_poly_t &that, f2_poly_t &rm, f2_poly_t &rn) {
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
  rn = 1;
  rm = 0;
  nprime = 0;
  c = *this;
  d = that;

  while (1) {
    c.quot_and_rem(d, q, r);
    if (r == 0)
      break;
    c = d;
    d = r;

    t = mprime;
    mprime = rm;
    qm = q * rm;
    rm = t - qm;

    t = nprime;
    nprime = rn;
    qn = q * rn;
    rn = t - qn;
  }
  return d;
}
#endif

#ifdef F2POLY_SMALL
f2_poly_t f2_poly_t::ext_gcd(f2_poly_t &that, f2_poly_t &rm, f2_poly_t &rn) {
  f2_poly_t mprime, nprime, c, q, r, t, qm, qn;
  f2_poly_t d; // Return value.

  if (*this == 0) {
    rm.bits = 0;
    rn.bits = 1;
    return that;
  }
  if (that == 0) {
    rm.bits = 1;
    rn.bits = 0;
    return *this;
  }

  // Initialize
  mprime.bits = 1;
  rn.bits = 1;
  rm.bits = 0;
  nprime.bits = 0;
  c = *this;
  d = that;

  while (1) {

    // Divide
    // q = c / d, r = c % d
    c.quot_and_rem(d, q, r);
    // Note:  now c = qd + r and 0 <= r < d

    // Remainder zero?
    if (r == 0)
      break;

    // Recycle
    c = d;
    d = r;

    t = mprime;
    mprime = rm;
    qm = q * rm;
    rm = t - qm;

    t = nprime;
    nprime = rn;
    qn = q * rn;
    rn = t - qn;
  }
  return d;
}
#endif

// ----------------------------------------------------------------
f2_poly_t f2_poly_t::exp(int e) {
  int deg = this->find_degree();
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
        if (e & 1)
          rv *= xp;
        e = (unsigned)e >> 1;
        xp *= xp;
      }
      return rv;
    }
  }
}

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
f2_poly_t f2_poly_t::deriv(void) {
  f2_poly_t rv = *this;
  rv.demote_1();
  for (int i = 0; i < rv.num_parts; i++)
    rv.parts[i] &= 0x55555555;
  rv.trim_parts();
  return rv;
}
#endif

// ----------------------------------------------------------------
// Relies on the fact that f(x^p) = f^p(x) over Fp[x].
//
// in  = a4 x^4 + a2 x^2 + a0
// out = a4 x^2 + a2 x   + a0

#ifndef F2POLY_SMALL
int f2_poly_t::square_root(f2_poly_t &rroot) {
  int si, di;
  int deg = this->find_degree();
  f2_poly_t root(0);

  for (si = 0, di = 0; si <= deg; si += 2, di++) {
    if (this->bit_at(si))
      root.set_bit(di);
    if (this->bit_at(si + 1))
      return 0;
  }

  rroot = root;
  return 1;
}
#endif

#ifdef F2POLY_SMALL
int f2_poly_t::square_root(f2_poly_t &rroot) {
  int deg = this->find_degree();
  int si, di;
  rroot.bits = 0;
  f2_poly_t inbit(1), outbit(1);

  for (si = 0, di = 0; si <= deg; si += 2, di++) {
    if (this->bits & inbit.bits)
      rroot.bits |= outbit.bits;
    inbit.bits <<= 1;
    if (this->bits & inbit.bits)
      return 0;
    inbit.bits <<= 1;
    outbit.bits <<= 1;
  }

  return 1;
}
#endif

// ----------------------------------------------------------------
bit_t f2_poly_t::eval(bit_t c) { return bit_t(this->eval(c.get_residue())); }

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
int f2_poly_t::eval(int c) {
  if (c & 1)
    return this->zcount_one_bits();
  else
    return this->parts[0] & 1;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
int f2_poly_t::zcount_one_bits(void) {
  return 1 & count_one_bits((unsigned char *)this->parts,
                            this->num_parts * sizeof(this->parts[0]));
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
int f2_poly_t::find_degree(void) const {
  for (int i = this->num_parts - 1; i >= 0; i--) {
    if (this->parts[i])
      return spffl::intmath::find_msb_32(this->parts[i]) + (i << F2POLY_PART_LOG);
  }
  return 0; // Zero polynomial.
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
int f2_poly_t::operator==(int v) const {
  for (int i = this->num_parts - 1; i > 0; i--)
    if (this->parts[i] != 0)
      return 0;
  return this->parts[0] == (unsigned)(v & 1);
}

int f2_poly_t::operator!=(int v) const { return !(*this == v); }

int f2_poly_t::operator==(f2_poly_t that) const {
  return this->cmp(CMP_EQ, that);
}

int f2_poly_t::operator!=(f2_poly_t that) const {
  return this->cmp(CMP_NE, that);
}

int f2_poly_t::operator<(f2_poly_t that) const { return this->cmp(CMP_LT, that); }

int f2_poly_t::operator>(f2_poly_t that) const { return this->cmp(CMP_GT, that); }

int f2_poly_t::operator<=(f2_poly_t that) const {
  return this->cmp(CMP_LE, that);
}

int f2_poly_t::operator>=(f2_poly_t that) const {
  return this->cmp(CMP_GE, that);
}

int f2_poly_t::cmp(int op, f2_poly_t &that) const {
  int direction = 0; // -1 = less, 0 = equal, +1 = greater;
  int i;

  int adeg = this->find_degree();
  int bdeg = that.find_degree();
  if (adeg < bdeg) {
    direction = -1;
  } else if (adeg > bdeg) {
    direction = 1;
  } else {
    for (i = adeg >> F2POLY_PART_LOG; i >= 0; i--) {
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
    return 0;
    break;
  }
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
void f2_poly_t::increment(void) {
  unsigned zero = 0;
  for (int i = 0; i < this->num_parts; i++) {
    if (this->parts[i] != ~zero) {
      this->parts[i]++;
      return;
    } else {
      this->parts[i] = zero;
    }
  }
  this->set_bit(this->num_parts * F2POLY_BITS_PER_PART);
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
std::ostream &operator<<(std::ostream &os, const f2_poly_t &poly) {
  if (poly.num_parts <= 0) {
    std::cerr << "f2_poly_t ostream <<:  empty polynomial.\n";
    exit(1);
  }

  std::ios_base::fmtflags svflags = os.flags();
  os.flags(std::ios_base::hex);

  int i;
  int leader_pos = 0;
  for (i = poly.num_parts - 1; i >= 0; i--) {
    if ((poly.parts[i]) || (i == 0)) {
      leader_pos = i;
      break;
    }
  }

  for (i = poly.num_parts - 1; i >= 0; i--) {
    if (i > leader_pos) {
      ;
    } else if (i == leader_pos) {
      os << poly.parts[i];
    } else {
      os << std::setw(8) << std::setfill('0');
      os << poly.parts[i];
    }
  }

  os.flags(svflags);
  return os;
}
#endif

#ifdef F2POLY_SMALL
std::ostream &operator<<(std::ostream &os, const f2_poly_t &poly) {
  std::ios_base::fmtflags svflags = os.flags();
  os.flags(std::ios_base::hex);
  os << poly.bits;
  os.flags(svflags);
  return os;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
void f2_poly_t::debug_print(std::ostream &os) {
  std::ios_base::fmtflags svflags = os.flags();
  os.flags(std::ios_base::hex);

  for (int i = this->num_parts - 1; i >= 0; i--) {
    os << std::setw(8) << std::setfill('0');
    os << this->parts[i];
    if (i > 0)
      os << '_';
  }

  os.flags(svflags);
}
#endif

#ifdef F2POLY_SMALL
void f2_poly_t::debug_print(std::ostream &os) { os << *this; }
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
std::istream &operator>>(std::istream &is, f2_poly_t &poly) {
  int c;
  poly = f2_poly_t(0);
  int num_nybbles = 0;

  // Skip over whitespace.
  c = is.peek();
  while ((c == ' ') || (c == '\t') || (c == '\n')) {
    is.ignore(1, c);
    if (is.eof())
      break;
    c = is.peek();
  }

  if (is.eof()) {
    is.setstate(std::ios::failbit);
    return is;
  }

  c = is.peek();
  while (isxdigit(c)) {
    if (is.eof())
      break;
    c = is.get();
    poly.promote_4();
    if (isdigit(c))
      poly.parts[0] |= c - '0';
    else if (islower(c))
      poly.parts[0] |= c - 'a' + 10;
    else
      poly.parts[0] |= c - 'A' + 10;
    num_nybbles++;
    c = is.peek();
  }

  if (num_nybbles == 0)
    is.setstate(std::ios::failbit);
  return is;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
std::istringstream &operator>>(std::istringstream &iss, f2_poly_t &poly) {
  int c;
  poly = f2_poly_t(0);
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
    poly.promote_4();
    if (isdigit(c))
      poly.parts[0] |= c - '0';
    else if (islower(c))
      poly.parts[0] |= c - 'a' + 10;
    else
      poly.parts[0] |= c - 'A' + 10;
    num_nybbles++;
    c = iss.peek();
  }

  if (num_nybbles == 0)
    iss.setstate(std::ios::failbit);
  if (c == EOF)
    iss.setstate(std::ios::eofbit);

  return iss;
}
#endif

// ----------------------------------------------------------------
#ifdef F2POLY_SMALL
std::istream &operator>>(std::istream &is, f2_poly_t &poly) {
  std::ios_base::fmtflags svflags = is.flags();
  is.flags(std::ios_base::hex);
  is >> poly.bits;
  is.flags(svflags);

  return is;
}
#endif

// ----------------------------------------------------------------
#ifdef F2POLY_SMALL
std::istringstream &operator>>(std::istringstream &iss, f2_poly_t &poly) {
  std::ios_base::fmtflags svflags = iss.flags();
  iss.flags(std::ios_base::hex);

  // Attempt to skip over whitespace.
  // The istringstream class appears to permit no way to ignore a set of
  // characters.  E.g. if the input is 0, space, tab, space, 1, then the
  // following won't suffice.

  while (iss.peek() == ' ')
    iss.ignore(1, ' ');
  while (iss.peek() == '\t')
    iss.ignore(1, '\t');
  while (iss.peek() == '\n')
    iss.ignore(1, '\n');

  iss >> poly.bits;
  iss.flags(svflags);

  return iss;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
void f2_poly_t::promote_n(unsigned shamt) {
  // For comparison:
  //	for (unsigned ii = 0; ii < shamt; ii++)
  //		this->promote_1();

  int num_parts_shift = shamt >> F2POLY_PART_LOG;
  int num_bits_shift = shamt & F2POLY_PART_MASK;
  int cmpl_bits_shift = 32 - num_bits_shift;
  int odeg = this->find_degree();
  int ndeg = odeg + shamt;
  int onum_parts = (odeg >> F2POLY_PART_LOG) + 1;
  int nnum_parts = (ndeg >> F2POLY_PART_LOG) + 1;
  int parts_diff;
  int i;

  this->extend_parts(nnum_parts);
  parts_diff = this->num_parts - onum_parts;
  // Note: after the call to extend_parts(), num_parts has a new value.

  if (num_bits_shift == 0) {
    for (i = onum_parts - 1; i >= 0; i--) {
      this->parts[i + num_parts_shift] = this->parts[i];
    }
    for (i = this->num_parts - onum_parts - 1; i >= 0; i--) {
      this->parts[i] = 0;
    }
  }

  else {
    int di = this->num_parts - 1;
    int si = onum_parts - 1;

    if ((odeg & F2POLY_PART_MASK) >= cmpl_bits_shift) {

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
#endif

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

#ifndef F2POLY_SMALL
void f2_poly_t::promote_4(void) {
  if (this->parts[this->num_parts - 1] & 0xf0000000)
    this->extend_parts(this->num_parts + 1);

  for (int i = this->num_parts - 1; i > 0; i--)
    this->parts[i] = (this->parts[i] << 4) | (this->parts[i - 1] >> 28);
  this->parts[0] <<= 4;
}

void f2_poly_t::promote_1(void) {
  if (this->parts[this->num_parts - 1] & 0x80000000)
    this->extend_parts(this->num_parts + 1);

  for (int i = this->num_parts - 1; i > 0; i--)
    this->parts[i] = (this->parts[i] << 1) | (this->parts[i - 1] >> 31);
  this->parts[0] <<= 1;
}

void f2_poly_t::demote_1(void) {
  for (int i = 0; i < this->num_parts - 1; i++)
    this->parts[i] = (this->parts[i] >> 1) | (this->parts[i + 1] << 31);
  this->parts[this->num_parts - 1] >>= 1;

  if (this->parts[this->num_parts - 1] == 0)
    if (this->num_parts > 0)
      this->num_parts--;
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
int f2_poly_t::bit_at(int pos) const {
  int which_part = pos >> F2POLY_PART_LOG;
  int which_bit = pos & F2POLY_PART_MASK;

  if (which_part >= this->num_parts)
    return 0;

  this->check_neg_pos(pos);
  return (this->parts[which_part] >> which_bit) & 1;
}
#endif

// ----------------------------------------------------------------
// req deg 37   req   print 10 chars
// this deg 4   would print  1 char
#ifndef F2POLY_SMALL
void f2_poly_t::dprint(std::ostream &os, int reqdeg) const {
  int thisdeg = this->find_degree();
  int reqnchars = (reqdeg + 4) >> 2;
  int thisnchars = (thisdeg + 4) >> 2;
  int morechars = reqnchars - thisnchars;
  for (int i = 0; i < morechars; i++)
    os << '0';
  os << *this;
}
#endif

// ----------------------------------------------------------------
#ifdef F2POLY_SMALL
void f2_poly_t::dprint(std::ostream &os, int deg) const {
  int tdeg = this->find_degree();
  int maxdeg = (tdeg > deg) ? tdeg : deg;
  int nchars = (maxdeg >> 2) + 1;

  std::ios_base::fmtflags svflags = os.flags();
  os.flags(std::ios_base::hex);

  os << std::setw(nchars) << std::setfill('0') << this->bits;

  os.flags(svflags);
}
#endif

// ----------------------------------------------------------------
#ifndef F2POLY_SMALL
void f2_poly_t::set_bit(int pos) {
  int which_part = pos >> F2POLY_PART_LOG;
  int which_bit = pos & F2POLY_PART_MASK;

  if (which_part >= this->num_parts)
    this->extend_parts(which_part + 1);

  this->check_neg_pos(pos);
  this->parts[which_part] |= (1 << which_bit);
}
#endif

#ifndef F2POLY_SMALL
void f2_poly_t::set_coeff(int pos, bit_t b) {
  int which_part = pos >> F2POLY_PART_LOG;
  int which_bit = pos & F2POLY_PART_MASK;

  if (which_part >= this->num_parts) {
    if (b.get_residue())
      this->extend_parts(which_part + 1);
    else
      return;
  }

  this->check_neg_pos(pos);
  if (b.get_residue()) {
    this->parts[which_part] |= (1 << which_bit);
  } else {
    this->parts[which_part] &= ~(1 << which_bit);
    this->trim_parts();
  }
}
#endif

#ifndef F2POLY_SMALL
void f2_poly_t::extend_parts(int new_num_parts) {
  int i;

  if (new_num_parts <= this->num_parts)
    return;
  unsigned *temp = new unsigned[new_num_parts];
  for (i = 0; i < this->num_parts; i++)
    temp[i] = this->parts[i];
  for (i = this->num_parts; i < new_num_parts; i++)
    temp[i] = 0;

  delete[] this->parts;
  this->parts = temp;
  this->num_parts = new_num_parts;
}

void f2_poly_t::trim_parts(void) {
  int d = this->find_degree();
  this->num_parts = (d >> F2POLY_PART_LOG) + 1;
}

void f2_poly_t::check_neg_pos(int pos) const {
  if (pos < 0) {
    std::cerr << "f2poly: negative bit position " << pos << " disallowed.\n";
    exit(1);
  }
}
#endif

// ----------------------------------------------------------------
#ifdef F2POLY_SMALL
void f2_poly_t::bounds_check_abend(int deg) const {
  if ((deg < 0) || (deg > (int)F2POLY_MAX_DEGREE)) {
    std::cerr << "f2_poly_t: degree " << deg
              << " out of bounds 0:" << F2POLY_MAX_DEGREE << ".\n";
    exit(1);
  }
}
#endif
