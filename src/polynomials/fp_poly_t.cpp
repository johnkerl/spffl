// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fp_poly_t.h"
#include "cmps.h"
#include "tokenize.h"
#include <string.h>

namespace spffl::polynomials {

// ----------------------------------------------------------------
fp_poly_t::fp_poly_t(void) {
  spffl::intmath::intmod_t invalid(-1, 1);
  this->degree = 0;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[0] = invalid;
}

// ----------------------------------------------------------------
fp_poly_t::fp_poly_t(spffl::intmath::intmod_t c0) {
  this->degree = 0;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
fp_poly_t::fp_poly_t(spffl::intmath::intmod_t c1, spffl::intmath::intmod_t c0) {
  this->degree = 1;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
fp_poly_t::fp_poly_t(spffl::intmath::intmod_t c2, spffl::intmath::intmod_t c1,
                     spffl::intmath::intmod_t c0) {
  this->degree = 2;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[2] = c2;
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
fp_poly_t::fp_poly_t(spffl::intmath::intmod_t c3, spffl::intmath::intmod_t c2,
                     spffl::intmath::intmod_t c1, spffl::intmath::intmod_t c0) {
  this->degree = 3;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[3] = c3;
  this->coeffs[2] = c2;
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
fp_poly_t::fp_poly_t(spffl::intmath::intmod_t c4, spffl::intmath::intmod_t c3,
                     spffl::intmath::intmod_t c2, spffl::intmath::intmod_t c1,
                     spffl::intmath::intmod_t c0) {
  this->degree = 4;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[4] = c4;
  this->coeffs[3] = c3;
  this->coeffs[2] = c2;
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
fp_poly_t::fp_poly_t(spffl::intmath::intmod_t c5, spffl::intmath::intmod_t c4,
                     spffl::intmath::intmod_t c3, spffl::intmath::intmod_t c2,
                     spffl::intmath::intmod_t c1, spffl::intmath::intmod_t c0) {
  this->degree = 5;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[5] = c5;
  this->coeffs[4] = c4;
  this->coeffs[3] = c3;
  this->coeffs[2] = c2;
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
fp_poly_t::fp_poly_t(int c0, int m) {
  this->degree = 0;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[0] = spffl::intmath::intmod_t(c0, m);
  this->recompute_degree();
}
fp_poly_t::fp_poly_t(int c1, int c0, int m) {
  this->degree = 1;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[1] = spffl::intmath::intmod_t(c1, m);
  this->coeffs[0] = spffl::intmath::intmod_t(c0, m);
  this->recompute_degree();
}
fp_poly_t::fp_poly_t(int c2, int c1, int c0, int m) {
  this->degree = 2;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[2] = spffl::intmath::intmod_t(c2, m);
  this->coeffs[1] = spffl::intmath::intmod_t(c1, m);
  this->coeffs[0] = spffl::intmath::intmod_t(c0, m);
  this->recompute_degree();
}
fp_poly_t::fp_poly_t(int c3, int c2, int c1, int c0, int m) {
  this->degree = 3;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[3] = spffl::intmath::intmod_t(c3, m);
  this->coeffs[2] = spffl::intmath::intmod_t(c2, m);
  this->coeffs[1] = spffl::intmath::intmod_t(c1, m);
  this->coeffs[0] = spffl::intmath::intmod_t(c0, m);
  this->recompute_degree();
}
fp_poly_t::fp_poly_t(int c4, int c3, int c2, int c1, int c0, int m) {
  this->degree = 4;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[4] = spffl::intmath::intmod_t(c4, m);
  this->coeffs[3] = spffl::intmath::intmod_t(c3, m);
  this->coeffs[2] = spffl::intmath::intmod_t(c2, m);
  this->coeffs[1] = spffl::intmath::intmod_t(c1, m);
  this->coeffs[0] = spffl::intmath::intmod_t(c0, m);
  this->recompute_degree();
}
fp_poly_t::fp_poly_t(int c5, int c4, int c3, int c2, int c1, int c0, int m) {
  this->degree = 5;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  this->coeffs[5] = spffl::intmath::intmod_t(c5, m);
  this->coeffs[4] = spffl::intmath::intmod_t(c4, m);
  this->coeffs[3] = spffl::intmath::intmod_t(c3, m);
  this->coeffs[2] = spffl::intmath::intmod_t(c2, m);
  this->coeffs[1] = spffl::intmath::intmod_t(c1, m);
  this->coeffs[0] = spffl::intmath::intmod_t(c0, m);
  this->recompute_degree();
}

// ----------------------------------------------------------------
// This is a static method.
fp_poly_t fp_poly_t::from_base_rep(int b, int m) {
  fp_poly_t rv;

  // Find degree.
  if (b == 0) {
    rv.degree = 0;
  } else {
    int temp = b;
    rv.degree = -1;
    while (temp) {
      temp /= m;
      rv.degree++;
    }
  }

  rv.coeffs = new spffl::intmath::intmod_t[rv.degree + 1];
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] = spffl::intmath::intmod_t(b % m, m);
    b /= m;
  }
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t::fp_poly_t(const fp_poly_t &that) {
  this->degree = that.degree;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++)
    this->coeffs[i] = that.coeffs[i];
}

// ----------------------------------------------------------------
fp_poly_t::~fp_poly_t(void) {
  delete[] this->coeffs;
  this->coeffs = 0;
  this->degree = -1;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::prime_sfld_elt(int v) const {
  spffl::intmath::intmod_t c0 = this->coeffs[0].prime_sfld_elt(v);
  return fp_poly_t(c0);
}

// ----------------------------------------------------------------
int fp_poly_t::get_characteristic(void) {
  return this->coeffs[0].get_modulus();
}

// ----------------------------------------------------------------
fp_poly_t &fp_poly_t::operator=(fp_poly_t that) {
  if (this->coeffs)
    delete[] this->coeffs;
  this->degree = that.degree;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++)
    this->coeffs[i] = that.coeffs[i];
  return *this;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator+(fp_poly_t that) const {
  int i;
  fp_poly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new spffl::intmath::intmod_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++)
      rv.coeffs[i] = this->coeffs[i] + that.coeffs[i];
    for (i = this->degree + 1; i <= that.degree; i++)
      rv.coeffs[i] = that.coeffs[i];
  } else {
    rv.degree = this->degree;
    rv.coeffs = new spffl::intmath::intmod_t[rv.degree + 1];
    for (i = 0; i <= that.degree; i++)
      rv.coeffs[i] = this->coeffs[i] + that.coeffs[i];
    for (i = that.degree + 1; i <= this->degree; i++)
      rv.coeffs[i] = this->coeffs[i];
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator+(spffl::intmath::intmod_t a) const {
  fp_poly_t rv(*this);
  rv.coeffs[0] += a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator-(fp_poly_t that) const {
  int i;
  fp_poly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new spffl::intmath::intmod_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++)
      rv.coeffs[i] = this->coeffs[i] - that.coeffs[i];
    for (i = this->degree + 1; i <= that.degree; i++)
      rv.coeffs[i] = -that.coeffs[i];
  } else {
    rv.degree = this->degree;
    rv.coeffs = new spffl::intmath::intmod_t[rv.degree + 1];
    for (i = 0; i <= that.degree; i++)
      rv.coeffs[i] = this->coeffs[i] - that.coeffs[i];
    for (i = that.degree + 1; i <= this->degree; i++)
      rv.coeffs[i] = this->coeffs[i];
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator-(spffl::intmath::intmod_t a) const {
  fp_poly_t rv(*this);
  rv.coeffs[0] -= a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator-(void) const {
  fp_poly_t rv;
  rv.coeffs = new spffl::intmath::intmod_t[rv.degree + 1];
  for (int i = 0; i <= this->degree; i++)
    rv.coeffs[i] = -this->coeffs[i];
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator*(fp_poly_t that) const {
  fp_poly_t rv;
  rv.degree = this->degree + that.degree;
  rv.coeffs = new spffl::intmath::intmod_t[rv.degree + 1];

  spffl::intmath::intmod_t zero = this->coeffs[0] - this->coeffs[0];
  for (int k = 0; k <= rv.degree; k++)
    rv.coeffs[k] = zero;
  for (int i = 0; i <= this->degree; i++)
    for (int j = 0; j <= that.degree; j++)
      rv.coeffs[i + j] += this->coeffs[i] * that.coeffs[j];
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator*(spffl::intmath::intmod_t a) {
  fp_poly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++)
    rv.coeffs[i] *= a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator/(fp_poly_t that) {
  fp_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return quot;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator%(fp_poly_t that) {
  fp_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return rem;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::operator/(spffl::intmath::intmod_t a) {
  fp_poly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++)
    rv.coeffs[i] /= a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t &fp_poly_t::operator+=(fp_poly_t that) {
  *this = *this + that;
  return *this;
}
fp_poly_t &fp_poly_t::operator+=(spffl::intmath::intmod_t a) {
  *this = *this + a;
  return *this;
}
fp_poly_t &fp_poly_t::operator-=(fp_poly_t that) {
  *this = *this - that;
  return *this;
}
fp_poly_t &fp_poly_t::operator-=(spffl::intmath::intmod_t a) {
  *this = *this - a;
  return *this;
}
fp_poly_t &fp_poly_t::operator*=(fp_poly_t that) {
  *this = *this * that;
  return *this;
}
fp_poly_t &fp_poly_t::operator*=(spffl::intmath::intmod_t a) {
  *this = *this * a;
  return *this;
}
fp_poly_t &fp_poly_t::operator/=(fp_poly_t &that) {
  *this = *this / that;
  return *this;
}
fp_poly_t &fp_poly_t::operator%=(fp_poly_t &that) {
  *this = *this % that;
  return *this;
}
fp_poly_t &fp_poly_t::operator/=(spffl::intmath::intmod_t a) {
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
void fp_poly_t::quot_and_rem(fp_poly_t &that, fp_poly_t &rquot,
                             fp_poly_t &rrem) {
  spffl::intmath::intmod_t zero = this->coeffs[0] - this->coeffs[0];

  if (that == zero) {
    std::cerr << "fp_poly_t::quot_and_rem:  division by zero.\n";
    exit(1);
  }
  if (*this == zero) {
    rquot = this->prime_sfld_elt(0);
    rrem = *this;
    return;
  }

  int dividend_degree = this->degree;
  int divisor_degree = that.degree;

  if (dividend_degree < divisor_degree) {
    rquot = this->prime_sfld_elt(0);
    rrem = *this;
    return;
  }

  fp_poly_t quot;
  quot.degree = this->degree - that.degree;
  quot.coeffs = new spffl::intmath::intmod_t[quot.degree + 1];

  fp_poly_t rem = *this;

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

  int max_shift = dividend_degree - divisor_degree;
  spffl::intmath::intmod_t divisor_leader = that.coeffs[divisor_degree];
  spffl::intmath::intmod_t dlinv;
  if (!divisor_leader.recip(dlinv)) {
    std::cerr << "fp_poly_t::quot_and_rem:  zero or zero divisor "
              << "in leading coefficient " << divisor_leader << "\n"
              << "  of divisor " << that << ".\n";
    exit(1);
  }
  for (int shift = max_shift; shift >= 0; shift--) {
    spffl::intmath::intmod_t rem_leader = rem.coeffs[shift + divisor_degree];
    spffl::intmath::intmod_t multiplier = rem_leader * dlinv;
    fp_poly_t divisor_with_mul = that * multiplier;
    quot.coeffs[shift] = multiplier;

    int stop = shift + divisor_with_mul.degree;
    for (int i = shift; i <= stop; i++)
      rem.coeffs[i] -= divisor_with_mul.coeffs[i - shift];
  }

  // Quotient degree must be the difference of dividend and divisor
  // degrees.  If not, we have made a mistake.
  if (quot.coeffs[quot.degree] == zero) {
    std::cerr << "fp_poly_t division: coding error.\n";
    exit(1);
  }

  // The remainder degree is less than the divisor's degree.
  rem.recompute_degree();

  rquot = quot;
  rrem = rem;
}

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::gcd(fp_poly_t &that) {
  fp_poly_t c, q, r;
  fp_poly_t d; // Return value.

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
// Blankinship's algorithm.

fp_poly_t fp_poly_t::ext_gcd(fp_poly_t &that, fp_poly_t &rm, fp_poly_t &rn) {
  fp_poly_t mprime, nprime, c, q, r, t, qm, qn;
  fp_poly_t d; // Return value.

  // Initialize
  mprime = this->prime_sfld_elt(1);
  rn = this->prime_sfld_elt(1);
  rm = this->prime_sfld_elt(0);
  nprime = this->prime_sfld_elt(0);
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

// ----------------------------------------------------------------
fp_poly_t fp_poly_t::exp(int e) {
  int deg = this->find_degree();
  fp_poly_t xp = *this;
  fp_poly_t zero = this->prime_sfld_elt(0);
  fp_poly_t one = this->prime_sfld_elt(1);
  fp_poly_t rv = one;

  if (*this == zero) {
    if (e == 0) {
      std::cerr << "fp_poly_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    } else if (e < 0) {
      std::cerr << "fp_poly_t::exp:  division by zero.\n";
      exit(1);
    } else {
      return zero;
    }
  } else if (deg == 0) {
    // Unit
    return fp_poly_t(this->coeffs[0].exp(e));
  } else {
    // Degree 1 or higher.
    if (e < 0) {
      std::cerr << "fp_poly_t::exp:  division by non-unit.\n";
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
fp_poly_t fp_poly_t::deriv(void) {
  if (this->degree == 0)
    return this->prime_sfld_elt(0);

  fp_poly_t rv(*this);
  int p = this->get_characteristic();
  rv.degree--;
  for (int i = 1; i <= this->degree; i++)
    rv.coeffs[i - 1] = this->coeffs[i] * spffl::intmath::intmod_t(i, p);
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
// Relies on the fact that f(x^p) = f^p(x) in Fp[x].

bool fp_poly_t::pth_root(fp_poly_t &rroot) {
  int p = this->get_characteristic();
  spffl::intmath::intmod_t zero(0, p);
  int si, di;
  int j;
  fp_poly_t out;

  out.set_coeff(this->degree, zero);
  for (di = this->degree - 1; di >= 0; di--)
    out.coeffs[di] = zero;

  for (si = 0, di = 0; si <= this->degree; si += p, di++) {
    out.coeffs[di] = this->coeffs[si];
    for (j = 1; j < p; j++) {
      if (si + j > this->degree)
        break;
      if (this->coeffs[si + j] != zero)
        return false;
    }
  }
  out.recompute_degree();
  rroot = out;
  return true;
}

// ----------------------------------------------------------------
spffl::intmath::intmod_t fp_poly_t::eval(spffl::intmath::intmod_t c) {
  spffl::intmath::intmod_t rv = this->coeffs[this->degree];
  for (int i = this->degree - 1; i >= 0; i--) {
    rv *= c;
    rv += this->coeffs[i];
  }
  return rv;
}

// ----------------------------------------------------------------
int fp_poly_t::find_degree(void) const { return this->degree; }

// ----------------------------------------------------------------
spffl::intmath::intmod_t fp_poly_t::get_coeff(int deg) const {
  if (deg < 0)
    this->bounds_check(deg);

  if (deg > this->degree)
    return (this->coeffs[0] - this->coeffs[0]);
  else
    return this->coeffs[deg];
}

// ----------------------------------------------------------------
void fp_poly_t::set_coeff(int pos, spffl::intmath::intmod_t c) {
  if (pos < 0)
    this->bounds_check(pos);

  spffl::intmath::intmod_t zero(0, this->coeffs[0].get_modulus());
  if (pos > this->degree) {
    spffl::intmath::intmod_t *temp = new spffl::intmath::intmod_t[pos + 1];
    for (int i = 0; i <= this->degree; i++)
      temp[i] = this->coeffs[i];
    for (int i = this->degree + 1; i < pos; i++)
      temp[i] = zero;
    temp[pos] = c;

    delete[] this->coeffs;
    this->coeffs = temp;
    this->degree = pos;
    if (c == zero)
      this->recompute_degree();
  } else {
    this->coeffs[pos] = c;
    if ((pos == this->degree) && (c == zero))
      this->recompute_degree();
  }
}

// ----------------------------------------------------------------
void fp_poly_t::recompute_degree(void) {
  bool is_zero = true;
  spffl::intmath::intmod_t zero = this->coeffs[0] - this->coeffs[0];

  for (int i = this->degree; i >= 0; i--) {
    if (this->coeffs[i] != zero) {
      is_zero = false;
      this->degree = i;
      break;
    }
  }
  if (is_zero)
    this->degree = 0;
}

// ----------------------------------------------------------------
bool fp_poly_t::operator==(int v) const {
  int d = this->degree;
  if (d != 0)
    return false;
  return this->coeffs[0].get_residue() == v;
}

// ----------------------------------------------------------------
bool fp_poly_t::operator!=(int v) const { return !(*this == v); }

// ----------------------------------------------------------------
bool fp_poly_t::operator==(fp_poly_t that) const {
  return this->cmp(CMP_EQ, that);
}

// ----------------------------------------------------------------
bool fp_poly_t::operator!=(fp_poly_t that) const {
  return this->cmp(CMP_NE, that);
}

// ----------------------------------------------------------------
bool fp_poly_t::operator<(fp_poly_t that) const {
  return this->cmp(CMP_LT, that);
}

// ----------------------------------------------------------------
bool fp_poly_t::operator>(fp_poly_t that) const {
  return this->cmp(CMP_GT, that);
}

// ----------------------------------------------------------------
bool fp_poly_t::operator<=(fp_poly_t that) const {
  return this->cmp(CMP_LE, that);
}

// ----------------------------------------------------------------
bool fp_poly_t::operator>=(fp_poly_t that) const {
  return this->cmp(CMP_GE, that);
}

// ----------------------------------------------------------------
bool fp_poly_t::cmp(int cmp, fp_poly_t &that) const {
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
    std::cerr << "Ack!\n";
    exit(1);
    return false;
    break;
  }
}

// ----------------------------------------------------------------
void fp_poly_t::increment(void) {
  int p = this->get_characteristic();
  spffl::intmath::intmod_t zero(0, p);
  spffl::intmath::intmod_t one(1, p);
  for (int i = 0; i <= this->degree; i++) {
    int r = this->coeffs[i].get_residue();
    if (r < p - 1) {
      this->coeffs[i] += one;
      return;
    } else {
      this->coeffs[i] = zero;
    }
  }
  this->set_coeff(this->degree + 1, one);
}

// ----------------------------------------------------------------
void fp_poly_t::bounds_check(int deg) const {
  if ((deg < 0) || (deg > this->degree)) {
    std::cerr << "fp_poly_t: degree " << deg
              << " out of bounds 0:" << this->degree << ".\n";
    exit(1);
  }
}

// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const fp_poly_t &poly) {
  int d = poly.find_degree();
  int m = poly.get_coeff(0).get_modulus();

  for (int i = d; i >= 0; i--) {
    if (m > 9)
      if (i < d)
        os << ",";
    os << poly.get_coeff(i).get_residue();
  }

  return os;
}

// ----------------------------------------------------------------
// Coefficient 0 modulus must already be set.

std::istream &operator>>(std::istream &is, fp_poly_t &poly) {
  int p = poly.get_characteristic();
  std::stringstream ss;
  char c;

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

  while (isdigit(c) || (c == ',')) {
    c = is.get();
    ss << c;
    c = is.peek();
    if (c == EOF) {
      is.setstate(std::ios::eofbit);
      break;
    }
  }

  std::string s = ss.str();
  if (s.length() == 0) {
    is.setstate(std::ios::failbit);
    return is;
  }

  if (!poly.from_string(s.c_str(), p))
    is.setstate(std::ios::failbit);
  return is;
}

// ----------------------------------------------------------------
bool fp_poly_t::from_string(const char *string, int p) {
  if (this->coeffs)
    delete[] this->coeffs;

  int num_commas = 0;
  for (const char *q = string; *q; q++)
    if (*q == ',')
      num_commas++;

  if ((num_commas == 0) && (p < 10)) {
    // Allow comma-free input as long as all residues are
    // single-digit.
    int len = strlen(string);
    this->degree = len - 1;
    this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
    int si, ci;
    for (si = 0, ci = this->degree; si < len; si++, ci--) {
      char ascii_digit = string[si];
      if ((ascii_digit < '0') || (ascii_digit > '9')) {
        std::cerr << "fp_poly_t::from_string: "
                  << "non-numerical input \"" << string << "\"\n";
        std::cerr << "Didn't like '" << ascii_digit << "'\n";
        return false;
      }
      this->coeffs[ci] = spffl::intmath::intmod_t(ascii_digit - '0', p);
    }
  } else {
    char *dup = strdup(string);
    char **argv = new char *[num_commas + 1];
    int argc = spffl::base::tokenize(dup, ",", argv, num_commas + 1);
    if (argc < 1) {
      // Needs an error message, but this coding error is
      // unlikely since we already counted commas.
      return false;
    }

    this->degree = argc - 1;
    this->coeffs = new spffl::intmath::intmod_t[this->degree + 1];
    int argi, ci;
    for (argi = 0, ci = this->degree; argi < argc; argi++, ci--) {
      // Scan each coefficient, then reduce mod p
      int r;

      std::istringstream iss(argv[argi], std::ios_base::in);
      iss >> r;
      if (iss.fail()) {
        std::cerr << "fp_poly_t::from_string: "
                  << "scan failure at \"" << string << "\"\n";
        return false;
      } else {
        this->coeffs[ci] = spffl::intmath::intmod_t(r, p);
      }
    }
    delete[] argv;
    free(dup);
  }

  this->recompute_degree();
  return true;
}

// ----------------------------------------------------------------
void fp_poly_t::promote(void) {
  if (!this->coeffs) {
    std::cerr << "fp_poly_t::promote: null data.\n";
    exit(1);
  }
  spffl::intmath::intmod_t *ocoeffs = this->coeffs;
  this->coeffs = new spffl::intmath::intmod_t[this->degree + 2];
  for (int i = 0; i <= this->degree; i++)
    this->coeffs[i + 1] = ocoeffs[i];
  this->coeffs[0] = this->coeffs[1] - this->coeffs[1];
  this->degree++;
  delete[] ocoeffs;
}

// ----------------------------------------------------------------
void fp_poly_t::promote_and_add(spffl::intmath::intmod_t c0) {
  this->promote();
  this->coeffs[0] = c0;
}

} // namespace spffl::polynomials

// ----------------------------------------------------------------
spffl::polynomials::fp_poly_t gcd(spffl::polynomials::fp_poly_t a,
                                  spffl::polynomials::fp_poly_t b) {
  return a.gcd(b);
}
