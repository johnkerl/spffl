// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "polynomials/f2n_poly_t.h"
#include "base/cmps.h"
#include "base/spffl_exception.h"
#include "base/tokenize.h"
#include <string.h>

namespace spffl::polynomials {

// ----------------------------------------------------------------
f2n_poly_t::f2n_poly_t(void) {
  f2_polymod_t invalid(f2_poly_t(0), f2_poly_t(1));
  this->degree    = 0;
  this->coeffs    = new f2_polymod_t[this->degree + 1];
  this->coeffs[0] = invalid;
}

// ----------------------------------------------------------------
f2n_poly_t::f2n_poly_t(const f2_polymod_t &c0) {
  this->degree    = 0;
  this->coeffs    = new f2_polymod_t[this->degree + 1];
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
f2n_poly_t::f2n_poly_t(const f2_polymod_t &c1, const f2_polymod_t &c0) {
  this->degree    = 1;
  this->coeffs    = new f2_polymod_t[this->degree + 1];
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
f2n_poly_t::f2n_poly_t(
    const f2_polymod_t &c2, const f2_polymod_t &c1, const f2_polymod_t &c0) {
  this->degree    = 2;
  this->coeffs    = new f2_polymod_t[this->degree + 1];
  this->coeffs[2] = c2;
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
f2n_poly_t::f2n_poly_t(int c0, const f2_poly_t &m) {
  this->degree    = 0;
  this->coeffs    = new f2_polymod_t[this->degree + 1];
  this->coeffs[0] = f2_polymod_t(f2_poly_t(c0), m);
  this->recompute_degree();
}
f2n_poly_t::f2n_poly_t(int c1, int c0, const f2_poly_t &m) {
  this->degree    = 1;
  this->coeffs    = new f2_polymod_t[this->degree + 1];
  this->coeffs[1] = f2_polymod_t(f2_poly_t(c1), m);
  this->coeffs[0] = f2_polymod_t(f2_poly_t(c0), m);
  this->recompute_degree();
}
f2n_poly_t::f2n_poly_t(int c2, int c1, int c0, const f2_poly_t &m) {
  this->degree    = 2;
  this->coeffs    = new f2_polymod_t[this->degree + 1];
  this->coeffs[2] = f2_polymod_t(f2_poly_t(c2), m);
  this->coeffs[1] = f2_polymod_t(f2_poly_t(c1), m);
  this->coeffs[0] = f2_polymod_t(f2_poly_t(c0), m);
  this->recompute_degree();
}

// ----------------------------------------------------------------
// This is a static method.
f2n_poly_t f2n_poly_t::from_base_rep(int b, const f2_poly_t &m) {
  f2n_poly_t rv;
  std::stringstream ss;
  ss << "unimplemented function!\n";
  throw spffl::exception_t(ss.str());
// xxx fix me
#if 0
	// Find degree.
	if (b == 0) {
		rv.degree = 0;
	}
	else {
		int temp = b;
		rv.degree = -1;
		while (temp) {
			temp /= m;
			rv.degree++;
		}
	}

	rv.coeffs = new f2_polymod_t[rv.degree + 1];
	for (int i = 0; i <= rv.degree; i++) {
		rv.coeffs[i] = f2_polymod_t(b % m, m);
		b /= m;
	}
#endif
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t::f2n_poly_t(const f2n_poly_t &that) {
  this->degree = that.degree;
  this->coeffs = new f2_polymod_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++) {
    this->coeffs[i] = that.coeffs[i];
  }
}

// ----------------------------------------------------------------
f2n_poly_t::~f2n_poly_t(void) {
  delete[] this->coeffs;
  this->coeffs = 0;
  this->degree = -1;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::prime_subfield_element(int v) const {
  f2_polymod_t c0 = this->coeffs[0].prime_subfield_element(v);
  return f2n_poly_t(c0);
}

// ----------------------------------------------------------------
// This is a static method.

f2n_poly_t f2n_poly_t::prime_subfield_element(int v, const f2_poly_t &m) {
  return f2n_poly_t(f2_polymod_t(f2_poly_t(v), m));
}

// ----------------------------------------------------------------
int f2n_poly_t::get_characteristic(void) const { return 2; }

// ----------------------------------------------------------------
f2n_poly_t &f2n_poly_t::operator=(const f2n_poly_t &that) {
  if (this->coeffs) {
    delete[] this->coeffs;
  }
  this->degree = that.degree;
  this->coeffs = new f2_polymod_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++) {
    this->coeffs[i] = that.coeffs[i];
  }
  return *this;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator+(const f2n_poly_t &that) const {
  int i;
  f2n_poly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new f2_polymod_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i] + that.coeffs[i];
    }
    for (i = this->degree + 1; i <= that.degree; i++) {
      rv.coeffs[i] = that.coeffs[i];
    }
  } else {
    rv.degree = this->degree;
    rv.coeffs = new f2_polymod_t[rv.degree + 1];
    for (i = 0; i <= that.degree; i++) {
      rv.coeffs[i] = this->coeffs[i] + that.coeffs[i];
    }
    for (i = that.degree + 1; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i];
    }
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator+(const f2_polymod_t &a) const {
  f2n_poly_t rv(*this);
  rv.coeffs[0] += a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator-(const f2n_poly_t &that) const {
  int i;
  f2n_poly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new f2_polymod_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i] - that.coeffs[i];
    }
    for (i = this->degree + 1; i <= that.degree; i++) {
      rv.coeffs[i] = -that.coeffs[i];
    }
  } else {
    rv.degree = this->degree;
    rv.coeffs = new f2_polymod_t[rv.degree + 1];
    for (i = 0; i <= that.degree; i++) {
      rv.coeffs[i] = this->coeffs[i] - that.coeffs[i];
    }
    for (i = that.degree + 1; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i];
    }
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator-(const f2_polymod_t &a) const {
  f2n_poly_t rv(*this);
  rv.coeffs[0] -= a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator-(void) const {
  f2n_poly_t rv;
  rv.coeffs = new f2_polymod_t[rv.degree + 1];
  for (int i = 0; i <= this->degree; i++) {
    rv.coeffs[i] = -this->coeffs[i];
  }
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator*(const f2n_poly_t &that) const {
  f2n_poly_t rv;
  rv.degree = this->degree + that.degree;
  rv.coeffs = new f2_polymod_t[rv.degree + 1];

  f2_polymod_t zero = this->coeffs[0] - this->coeffs[0];
  for (int k = 0; k <= rv.degree; k++) {
    rv.coeffs[k] = zero;
  }
  for (int i = 0; i <= this->degree; i++) {
    for (int j = 0; j <= that.degree; j++) {
      rv.coeffs[i + j] += this->coeffs[i] * that.coeffs[j];
    }
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator*(const f2_polymod_t &a) const {
  f2n_poly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] *= a;
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator/(const f2n_poly_t &that) const {
  f2n_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return quot;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator%(const f2n_poly_t &that) const {
  f2n_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return rem;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::operator/(const f2_polymod_t &a) const {
  f2n_poly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] /= a;
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t &f2n_poly_t::operator+=(const f2n_poly_t &that) {
  *this = *this + that;
  return *this;
}
f2n_poly_t &f2n_poly_t::operator+=(const f2_polymod_t &a) {
  *this = *this + a;
  return *this;
}
f2n_poly_t &f2n_poly_t::operator-=(const f2n_poly_t &that) {
  *this = *this - that;
  return *this;
}
f2n_poly_t &f2n_poly_t::operator-=(const f2_polymod_t &a) {
  *this = *this - a;
  return *this;
}
f2n_poly_t &f2n_poly_t::operator*=(const f2n_poly_t &that) {
  *this = *this * that;
  return *this;
}
f2n_poly_t &f2n_poly_t::operator*=(const f2_polymod_t &a) {
  *this = *this * a;
  return *this;
}
f2n_poly_t &f2n_poly_t::operator/=(const f2n_poly_t &that) {
  *this = *this / that;
  return *this;
}
f2n_poly_t &f2n_poly_t::operator%=(const f2n_poly_t &that) {
  *this = *this % that;
  return *this;
}
f2n_poly_t &f2n_poly_t::operator/=(const f2_polymod_t &a) {
  *this = *this / a;
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
void f2n_poly_t::quot_and_rem(
    const f2n_poly_t &that, f2n_poly_t &rquot, f2n_poly_t &rrem) const {
  f2_polymod_t zero = this->coeffs[0] - this->coeffs[0];

  if (that == zero) {
    std::stringstream ss;
    ss << "f2n_poly_t::quot_and_rem:  division by zero.\n";
    throw spffl::exception_t(ss.str());
  }
  if (*this == zero) {
    rquot = this->prime_subfield_element(0);
    rrem  = *this;
    return;
  }

  int dividend_degree = this->degree;
  int divisor_degree  = that.degree;

  if (dividend_degree < divisor_degree) {
    rquot = this->prime_subfield_element(0);
    rrem  = *this;
    return;
  }

  f2n_poly_t quot;
  quot.degree = this->degree - that.degree;
  quot.coeffs = new f2_polymod_t[quot.degree + 1];

  f2n_poly_t rem = *this;

  //       +--------
  // ooooo | ooooooo
  //       | ooooo
  //       +--------
  //       |  ooooo
  //       +--------
  //       |   ooooo
  //       +--------
  //       |    oooo

  // x^5+1 / x^3 = x^2 rem 1
  // quot deg = dividend deg - divisor deg
  // rem deg  < divisor deg

  int max_shift               = dividend_degree - divisor_degree;
  f2_polymod_t divisor_leader = that.coeffs[divisor_degree];
  f2_polymod_t dlinv;
  if (!divisor_leader.recip(dlinv)) {
    std::stringstream ss;
    ss << "f2n_poly_t::quot_and_rem:  zero or zero divisor "
       << "in leading coefficient " << divisor_leader << "\n"
       << "  of divisor " << that << ".\n";
    throw spffl::exception_t(ss.str());
  }
  for (int shift = max_shift; shift >= 0; shift--) {
    f2_polymod_t rem_leader     = rem.coeffs[shift + divisor_degree];
    f2_polymod_t multiplier     = rem_leader * dlinv;
    f2n_poly_t divisor_with_mul = that * multiplier;
    quot.coeffs[shift]          = multiplier;

    int stop = shift + divisor_with_mul.degree;
    for (int i = shift; i <= stop; i++) {
      rem.coeffs[i] -= divisor_with_mul.coeffs[i - shift];
    }
  }

  // Quotient degree must be the difference of dividend and divisor
  // degrees.  If not, we have made a mistake.
  if (quot.coeffs[quot.degree] == zero) {
    std::stringstream ss;
    ss << "f2n_poly_t division: coding error.\n";
    throw spffl::exception_t(ss.str());
  }

  // The remainder degree is less than the divisor's degree.
  rem.recompute_degree();

  rquot = quot;
  rrem  = rem;
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::gcd(const f2n_poly_t &that) const {
  f2n_poly_t c, q, r;
  f2n_poly_t d; // Return value.

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

f2n_poly_t f2n_poly_t::ext_gcd(
    const f2n_poly_t &that, f2n_poly_t &rm, f2n_poly_t &rn) const {
  f2n_poly_t mprime, nprime, c, q, r, t, qm, qn;
  f2n_poly_t d; // Return value.

  // Initialize
  mprime = this->prime_subfield_element(1);
  rn     = this->prime_subfield_element(1);
  rm     = this->prime_subfield_element(0);
  nprime = this->prime_subfield_element(0);
  c      = *this;
  d      = that;

  while (1) {
    c.quot_and_rem(d, q, r);
    if (r == 0) {
      break;
    }

    c = d;
    d = r;

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
f2n_poly_t f2n_poly_t::exp(int e) const {
  int deg         = this->find_degree();
  f2n_poly_t xp   = *this;
  f2n_poly_t zero = this->prime_subfield_element(0);
  f2n_poly_t one  = this->prime_subfield_element(1);
  f2n_poly_t rv   = one;

  if (*this == zero) {
    if (e == 0) {
      std::stringstream ss;
      ss << "f2n_poly_t::exp:  0 ^ 0 undefined.\n";
      throw spffl::exception_t(ss.str());
    } else if (e < 0) {
      std::stringstream ss;
      ss << "f2n_poly_t::exp:  division by zero.\n";
      throw spffl::exception_t(ss.str());
    } else {
      return zero;
    }
  } else if (deg == 0) {
    // Unit
    return f2n_poly_t(this->coeffs[0].exp(e));
  } else {
    // Degree 1 or higher.
    if (e < 0) {
      std::stringstream ss;
      ss << "f2n_poly_t::exp:  division by non-unit.\n";
      throw spffl::exception_t(ss.str());
    } else {
      while (e != 0) {
        if (e & 1) {
          rv *= xp;
        }
        e = (unsigned)e >> 1;
        xp *= xp;
      }
      return rv;
    }
  }
}

// ----------------------------------------------------------------
f2n_poly_t f2n_poly_t::deriv(void) const {
  if (this->degree == 0) {
    return this->prime_subfield_element(0);
  }

  f2n_poly_t rv(*this);
  f2_poly_t m = this->coeffs[0].get_modulus();
  rv.degree--;
  for (int i = 1; i <= this->degree; i++) {
    rv.coeffs[i - 1] = this->coeffs[i] * f2_polymod_t(i, m);
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
// E.g. (ax^2 + bx + c) ^ 2 = a^2 x^4 + b^2 x^2 + c^2, where odd coefficients
// vanish since the characteristic is 2.  To square-root a given polynomial:
//
// * Make sure the odd-degree terms are zero.
// * For even-degree terms, cut the exponent in half.
// * For even-degree terms, square-root the coefficients.
//
// For extension fields of F2, the squaring map is automorphic.  Therefore
// square roots exists for all coefficients.  Let n be the degree over F2.
// Then a^{2^n} = a for all coefficients, and a^{2^{n-1}} = sqrt(a).

bool f2n_poly_t::square_root(f2n_poly_t &rroot) const {
  f2_poly_t m = this->coeffs[0].get_modulus();
  f2_polymod_t zero(0, m);
  int si, di;
  f2n_poly_t out;
  int n   = m.find_degree();
  int pow = 1 << (n - 1);

  out.set_coeff(this->degree, zero);
  for (di = this->degree - 1; di >= 0; di--) {
    out.coeffs[di] = zero;
  }

  for (si = 0, di = 0; si <= this->degree; si += 2, di++) {
    out.coeffs[di] = this->coeffs[si].exp(pow);
    if (si + 1 > this->degree) {
      break;
    }
    if (this->coeffs[si + 1] != zero) {
      return false;
    }
  }
  out.recompute_degree();
  rroot = out;
  return true;
}

// ----------------------------------------------------------------
f2_polymod_t f2n_poly_t::eval(const f2_polymod_t &c) const {
  f2_polymod_t rv = this->coeffs[this->degree];
  for (int i = this->degree - 1; i >= 0; i--) {
    rv *= c;
    rv += this->coeffs[i];
  }
  return rv;
}

// ----------------------------------------------------------------
int f2n_poly_t::find_degree(void) const { return this->degree; }

// ----------------------------------------------------------------
f2_polymod_t f2n_poly_t::get_coeff(int deg) const {
  if (deg < 0) {
    this->bounds_check(deg);
  }

  if (deg > this->degree) {
    return (this->coeffs[0] - this->coeffs[0]);
  } else {
    return this->coeffs[deg];
  }
}

// ----------------------------------------------------------------
void f2n_poly_t::set_coeff(int pos, const f2_polymod_t &c) {
  if (pos < 0) {
    this->bounds_check(pos);
  }

  f2_polymod_t zero(0, this->coeffs[0].get_modulus());
  if (pos > this->degree) {
    f2_polymod_t *temp = new f2_polymod_t[pos + 1];
    for (int i = 0; i <= this->degree; i++) {
      temp[i] = this->coeffs[i];
    }
    for (int i = this->degree + 1; i < pos; i++) {
      temp[i] = zero;
    }
    temp[pos] = c;

    delete[] this->coeffs;
    this->coeffs = temp;
    this->degree = pos;
    if (c == zero) {
      this->recompute_degree();
    }
  } else {
    this->coeffs[pos] = c;
    if ((pos == this->degree) && (c == zero)) {
      this->recompute_degree();
    }
  }
}

// ----------------------------------------------------------------
void f2n_poly_t::change_modulus(const f2_poly_t &new_modulus) {
  for (int i = 0; i <= this->degree; i++) {
    this->coeffs[i].change_modulus(new_modulus);
  }
}

// ----------------------------------------------------------------
void f2n_poly_t::recompute_degree(void) {
  bool is_zero      = true;
  f2_polymod_t zero = this->coeffs[0] - this->coeffs[0];

  for (int i = this->degree; i >= 0; i--) {
    if (this->coeffs[i] != zero) {
      is_zero      = false;
      this->degree = i;
      break;
    }
  }
  if (is_zero) {
    this->degree = 0;
  }
}

// ----------------------------------------------------------------
bool f2n_poly_t::operator==(int v) const {
  int d = this->degree;
  if (d != 0) {
    return false;
  }
  return this->coeffs[0].get_residue() == v;
}

// ----------------------------------------------------------------
bool f2n_poly_t::operator!=(int v) const { return !(*this == v); }

// ----------------------------------------------------------------
bool f2n_poly_t::operator==(const f2n_poly_t &that) const {
  return this->cmp(CMP_EQ, that);
}

// ----------------------------------------------------------------
bool f2n_poly_t::operator!=(const f2n_poly_t &that) const {
  return this->cmp(CMP_NE, that);
}

// ----------------------------------------------------------------
bool f2n_poly_t::operator<(const f2n_poly_t &that) const {
  return this->cmp(CMP_LT, that);
}

// ----------------------------------------------------------------
bool f2n_poly_t::operator>(const f2n_poly_t &that) const {
  return this->cmp(CMP_GT, that);
}

// ----------------------------------------------------------------
bool f2n_poly_t::operator<=(const f2n_poly_t &that) const {
  return this->cmp(CMP_LE, that);
}

// ----------------------------------------------------------------
bool f2n_poly_t::operator>=(const f2n_poly_t &that) const {
  return this->cmp(CMP_GE, that);
}

// ----------------------------------------------------------------
void f2n_poly_t::increment(void) {
  f2_poly_t m = this->coeffs[0].get_modulus();
  int d       = m.find_degree();
  f2_poly_t max(0);
  max.set_bit(d);
  f2_poly_t r0(0), r1(1);
  f2_polymod_t m0(r0, m);
  f2_polymod_t m1(r1, m);
  for (int i = 0; i <= this->degree; i++) {
    f2_poly_t r = this->coeffs[i].get_residue();
    r.increment();
    if (r != max) {
      this->coeffs[i] = f2_polymod_t(r, m);
      return;
    } else {
      this->coeffs[i] = f2_polymod_t(r0, m);
    }
  }
  this->set_coeff(this->degree + 1, m1);
}

// ----------------------------------------------------------------
bool f2n_poly_t::cmp(int cmp, const f2n_poly_t &that) const {
  int direction = 0; // -1 = less, 0 = equal, +1 = greater;

  if (this->degree < that.degree) {
    direction = -1;
  } else if (this->degree > that.degree) {
    direction = 1;
  } else {
    for (int i = this->degree; i >= 0; i--) {
      if (this->coeffs[i] < that.coeffs[i]) {
        direction = -1;
        break;
      } else if (this->coeffs[i] > that.coeffs[i]) {
        direction = 1;
        break;
      }
    }
  }

  switch (cmp) {
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
    std::stringstream ss;
    ss << "Ack!\n";
    throw spffl::exception_t(ss.str());
    return false;
    break;
  }
}

// ----------------------------------------------------------------
void f2n_poly_t::bounds_check(int deg) const {
  if ((deg < 0) || (deg > this->degree)) {
    std::stringstream ss;
    ss << "f2n_poly_t: degree " << deg << " out of bounds 0:" << this->degree
       << ".\n";
    throw spffl::exception_t(ss.str());
  }
}

// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const f2n_poly_t &poly) {
  int d       = poly.find_degree();
  f2_poly_t m = poly.get_coeff(0).get_modulus();

  for (int i = d; i >= 0; i--) {
    if (m > 9) {
      if (i < d) {
        os << ":";
      }
    }
    os << poly.get_coeff(i).get_residue();
  }

  return os;
}

// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, f2n_poly_t &poly) {
  f2_poly_t r;
  f2_poly_t m = poly.coeffs[0].get_modulus();
  poly        = f2n_poly_t(f2_polymod_t(0, m));

  if (m <= 10) {
    char c;
    is >> c;
    if (is.fail()) {
      std::stringstream ss;
      ss << "f2n_poly_t: scan failure.\n";
      return is;
    }
    if (!isdigit(c)) {
      std::stringstream ss;
      ss << "f2n_poly_t: non-numeric input '" << c << "'\n";
      return is;
    }
    r              = c - '0';
    poly.coeffs[0] = f2_polymod_t(r, m);

    while (isdigit(is.peek())) {
      r = c - '0';
      poly.promote_and_add(f2_polymod_t(r, m));
    }
  } else {
    is >> r;
    if (is.fail()) {
      std::stringstream ss;
      ss << "f2n_poly_t: scan failure.\n";
      return is;
    }
    poly.coeffs[0] = f2_polymod_t(r, m);
    while (is.peek() == ':') {
      (void)is.get();
      is >> r;
      if (is.fail()) {
        std::stringstream ss;
        ss << "f2n_poly_t: scan failure.\n";
        return is;
      }
      poly.promote_and_add(f2_polymod_t(r, m));
    }
  }
  poly.recompute_degree();
  return is;
}

// ----------------------------------------------------------------
// Coefficient 0 modulus must already be set.

std::istringstream &operator>>(std::istringstream &iss, f2n_poly_t &poly) {
  f2_poly_t r;
  f2_poly_t m = poly.coeffs[0].get_modulus();
  poly        = f2n_poly_t(f2_polymod_t(0, m));

  iss >> r;
  if (iss.fail()) {
    std::stringstream ss;
    ss << "f2n_poly_t: scan failure at \"" << iss.str() << "\"\n";
    return iss;
  }
  poly.coeffs[0] = f2_polymod_t(r, m);
  while (!iss.eof() && (iss.peek() == ':')) {
    (void)iss.get();
    iss >> r;
    if (iss.fail()) {
      std::stringstream ss;
      ss << "f2n_poly_t: scan failure at \"" << iss.str() << "\"\n";
      return iss;
    }
    poly.promote_and_add(f2_polymod_t(r, m));
  }

  poly.recompute_degree();
  return iss;
}

// ----------------------------------------------------------------
bool f2n_poly_t::from_string(const std::string &string, const f2_poly_t &m) {
  if (this->coeffs) {
    delete[] this->coeffs;
  }

  int num_colons = 0;
  for (const char *q = string.c_str(); *q; q++) {
    if (*q == ':') {
      num_colons++;
    }
  }

  // TODO: more use of std::string methods
  char *dup   = strdup(string.c_str());
  char **argv = new char *[num_colons + 1];
  int argc    = spffl::base::tokenize(dup, ":", argv, num_colons + 1);
  if (argc < 1) {
    // Needs an error message, but this coding error is
    // unlikely since we already counted colons.
    return false;
  }

  this->degree = argc - 1;
  this->coeffs = new f2_polymod_t[this->degree + 1];
  int argi, ci;
  for (argi = 0, ci = this->degree; argi < argc; argi++, ci--) {
    // Scan each coefficient, then reduce mod m
    f2_poly_t r;

    std::istringstream iss(argv[argi], std::ios_base::in);
    iss >> r;
    if (iss.fail()) {
      std::stringstream ss;
      ss << "f2n_poly_t::from_string: "
         << "scan failure at \"" << string << "\"\n";
      return false;
    } else {
      this->coeffs[ci] = f2_polymod_t(r, m);
    }
  }
  delete[] argv;
  free(dup);

  this->recompute_degree();
  return true;
}

// ----------------------------------------------------------------
void f2n_poly_t::promote(void) {
  if (!this->coeffs) {
    std::stringstream ss;
    ss << "f2n_poly_t::promote: null data.\n";
    throw spffl::exception_t(ss.str());
  }
  f2_polymod_t *ocoeffs = this->coeffs;
  this->coeffs          = new f2_polymod_t[this->degree + 2];
  for (int i = 0; i <= this->degree; i++) {
    this->coeffs[i + 1] = ocoeffs[i];
  }
  this->coeffs[0] = this->coeffs[1] - this->coeffs[1];
  this->degree++;
  delete[] ocoeffs;
}

// ----------------------------------------------------------------
void f2n_poly_t::promote_and_add(const f2_polymod_t &c0) {
  this->promote();
  this->coeffs[0] = c0;
}

} // namespace spffl::polynomials

// ----------------------------------------------------------------
spffl::polynomials::f2n_poly_t gcd(const spffl::polynomials::f2n_poly_t &a,
    const spffl::polynomials::f2n_poly_t &b) {
  return a.gcd(b);
}
