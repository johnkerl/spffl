// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/polynomials/fpn_poly_t.h"
#include "spffl/base/cmps.h"
#include "spffl/base/spffl_exception.h"
#include "spffl/base/tokenize.h"

#include <string.h>

namespace spffl::polynomials {

// ----------------------------------------------------------------
fpn_poly_t::fpn_poly_t(void) {
  fp_polymod_t a; // Use default constructor.
  this->degree    = 0;
  this->coeffs    = new fp_polymod_t[this->degree + 1];
  this->coeffs[0] = a;
}

// ----------------------------------------------------------------
fpn_poly_t::fpn_poly_t(const fp_polymod_t &c0) {
  this->degree    = 0;
  this->coeffs    = new fp_polymod_t[this->degree + 1];
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
fpn_poly_t::fpn_poly_t(const fp_polymod_t &c1, const fp_polymod_t &c0) {
  this->degree    = 1;
  this->coeffs    = new fp_polymod_t[this->degree + 1];
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
fpn_poly_t::fpn_poly_t(
    const fp_polymod_t &c2, const fp_polymod_t &c1, const fp_polymod_t &c0) {
  this->degree    = 2;
  this->coeffs    = new fp_polymod_t[this->degree + 1];
  this->coeffs[2] = c2;
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
// This is a static method.
fpn_poly_t fpn_poly_t::from_base_rep(int b, const fp_poly_t &m) {
  fpn_poly_t rv;
  std::stringstream ss;
  ss << "unimplemented function!\n";
  throw spffl::exception_t(ss.str());
  return rv;
}

// ----------------------------------------------------------------
fpn_poly_t::fpn_poly_t(const fpn_poly_t &that) {
  this->degree = that.degree;
  this->coeffs = new fp_polymod_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++) {
    this->coeffs[i] = that.coeffs[i];
  }
}

// ----------------------------------------------------------------
fpn_poly_t::~fpn_poly_t(void) {
  delete[] this->coeffs;
  this->coeffs = 0;
  this->degree = -1;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::prime_subfield_element(int v) const {
  fp_polymod_t c0 = this->coeffs[0].prime_subfield_element(v);
  return fpn_poly_t(c0);
}

// ----------------------------------------------------------------
// This is a static method.

fpn_poly_t fpn_poly_t::prime_subfield_element(int v, const fp_poly_t &m) {
  int p = m.get_coeff(0).get_modulus();
  return fpn_poly_t(fp_polymod_t(fp_poly_t(spffl::intmath::intmod_t(v, p)), m));
}

// ----------------------------------------------------------------
int fpn_poly_t::get_characteristic(void) const {
  return this->coeffs[0].get_characteristic();
}

// ----------------------------------------------------------------
fpn_poly_t &fpn_poly_t::operator=(const fpn_poly_t &that) {
  if (this->coeffs) {
    delete[] this->coeffs;
  }
  this->degree = that.degree;
  this->coeffs = new fp_polymod_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++) {
    this->coeffs[i] = that.coeffs[i];
  }
  return *this;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::operator+(const fpn_poly_t &that) const {
  int i;
  fpn_poly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new fp_polymod_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i] + that.coeffs[i];
    }
    for (i = this->degree + 1; i <= that.degree; i++) {
      rv.coeffs[i] = that.coeffs[i];
    }
  } else {
    rv.degree = this->degree;
    rv.coeffs = new fp_polymod_t[rv.degree + 1];
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
fpn_poly_t fpn_poly_t::operator-(const fpn_poly_t &that) const {
  int i;
  fpn_poly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new fp_polymod_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i] - that.coeffs[i];
    }
    for (i = this->degree + 1; i <= that.degree; i++) {
      rv.coeffs[i] = -that.coeffs[i];
    }
  } else {
    rv.degree = this->degree;
    rv.coeffs = new fp_polymod_t[rv.degree + 1];
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
fpn_poly_t fpn_poly_t::operator-(void) const {
  fpn_poly_t rv;
  rv.coeffs = new fp_polymod_t[rv.degree + 1];
  for (int i = 0; i <= this->degree; i++) {
    rv.coeffs[i] = -this->coeffs[i];
  }
  return rv;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::operator*(const fpn_poly_t &that) const {
  fpn_poly_t rv;
  rv.degree = this->degree + that.degree;
  rv.coeffs = new fp_polymod_t[rv.degree + 1];

  fp_polymod_t zero = this->coeffs[0] - this->coeffs[0];
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
fpn_poly_t fpn_poly_t::operator*(const spffl::intmath::intmod_t &a) const {
  fpn_poly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] *= a;
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::operator/(const fpn_poly_t &that) const {
  fpn_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return quot;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::operator%(const fpn_poly_t &that) const {
  fpn_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return rem;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::operator+(const fp_polymod_t &a) const {
  fpn_poly_t rv(*this);
  rv.coeffs[0] += a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::operator-(const fp_polymod_t &a) const {
  fpn_poly_t rv(*this);
  rv.coeffs[0] -= a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::operator*(const fp_polymod_t &a) const {
  fpn_poly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] *= a;
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::operator/(const fp_polymod_t &a) const {
  fpn_poly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] /= a;
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
fpn_poly_t &fpn_poly_t::operator+=(const fpn_poly_t &that) {
  *this = *this + that;
  return *this;
}
fpn_poly_t &fpn_poly_t::operator+=(const fp_polymod_t &a) {
  *this = *this + a;
  return *this;
}
fpn_poly_t &fpn_poly_t::operator-=(const fpn_poly_t &that) {
  *this = *this - that;
  return *this;
}
fpn_poly_t &fpn_poly_t::operator-=(const fp_polymod_t &a) {
  *this = *this - a;
  return *this;
}
fpn_poly_t &fpn_poly_t::operator*=(const fpn_poly_t &that) {
  *this = *this * that;
  return *this;
}
fpn_poly_t &fpn_poly_t::operator*=(const fp_polymod_t &a) {
  *this = *this * a;
  return *this;
}
fpn_poly_t &fpn_poly_t::operator/=(const fpn_poly_t &that) {
  *this = *this / that;
  return *this;
}
fpn_poly_t &fpn_poly_t::operator%=(const fpn_poly_t &that) {
  *this = *this % that;
  return *this;
}
fpn_poly_t &fpn_poly_t::operator/=(const fp_polymod_t &a) {
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
void fpn_poly_t::quot_and_rem(
    const fpn_poly_t &that, fpn_poly_t &rquot, fpn_poly_t &rrem) const {
  fp_polymod_t zero = this->coeffs[0] - this->coeffs[0];

  if (that == zero) {
    std::stringstream ss;
    ss << "fpn_poly_t::quot_and_rem:  division by zero.\n";
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

  fpn_poly_t quot;
  quot.degree = this->degree - that.degree;
  quot.coeffs = new fp_polymod_t[quot.degree + 1];

  fpn_poly_t rem = *this;

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
  fp_polymod_t divisor_leader = that.coeffs[divisor_degree];
  fp_polymod_t dlinv;
  if (!divisor_leader.recip(dlinv)) {
    std::stringstream ss;
    ss << "fpn_poly_t::quot_and_rem:  zero or zero divisor "
       << "in leading coefficient " << divisor_leader << "\n"
       << "  of divisor " << that << ".\n";
    throw spffl::exception_t(ss.str());
  }
  for (int shift = max_shift; shift >= 0; shift--) {
    fp_polymod_t rem_leader     = rem.coeffs[shift + divisor_degree];
    fp_polymod_t multiplier     = rem_leader * dlinv;
    fpn_poly_t divisor_with_mul = that * multiplier;
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
    ss << "fpn_poly_t division: coding error.\n";
    throw spffl::exception_t(ss.str());
  }

  // The remainder degree is less than the divisor's degree.
  rem.recompute_degree();

  rquot = quot;
  rrem  = rem;
}

// ----------------------------------------------------------------
fpn_poly_t fpn_poly_t::gcd(const fpn_poly_t &that) const {
  fpn_poly_t c, q, r;
  fpn_poly_t d; // Return value.

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

fpn_poly_t fpn_poly_t::ext_gcd(
    const fpn_poly_t &that, fpn_poly_t &rm, fpn_poly_t &rn) const {
  fpn_poly_t mprime, nprime, c, q, r, t, qm, qn;
  fpn_poly_t d; // Return value.

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
fpn_poly_t fpn_poly_t::exp(int e) const {
  int deg         = this->find_degree();
  fpn_poly_t xp   = *this;
  fpn_poly_t zero = this->prime_subfield_element(0);
  fpn_poly_t one  = this->prime_subfield_element(1);
  fpn_poly_t rv   = one;

  if (*this == zero) {
    if (e == 0) {
      std::stringstream ss;
      ss << "fpn_poly_t::exp:  0 ^ 0 undefined.\n";
      throw spffl::exception_t(ss.str());
    } else if (e < 0) {
      std::stringstream ss;
      ss << "fpn_poly_t::exp:  division by zero.\n";
      throw spffl::exception_t(ss.str());
    } else {
      return zero;
    }
  } else if (deg == 0) {
    // Unit
    return fpn_poly_t(this->coeffs[0].exp(e));
  } else {
    // Degree 1 or higher.
    if (e < 0) {
      std::stringstream ss;
      ss << "fpn_poly_t::exp:  division by non-unit.\n";
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
fpn_poly_t fpn_poly_t::deriv(void) const {
  if (this->degree == 0) {
    return this->prime_subfield_element(0);
  }

  fpn_poly_t rv(*this);
  int p = this->get_characteristic();
  rv.degree--;
  for (int i = 1; i <= this->degree; i++) {
    rv.coeffs[i - 1] = this->coeffs[i] * spffl::intmath::intmod_t(i, p);
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
// Relies on the fact that f(x^p) = f^p(x) in Fp[x].

bool fpn_poly_t::pth_root(fpn_poly_t &rroot) const {
  fp_poly_t m       = this->coeffs[0].get_modulus();
  fp_polymod_t zero = this->coeffs[0].prime_subfield_element(0);
  int si, di, j;
  fpn_poly_t out;
  int p = this->get_characteristic();

  out.set_coeff(this->degree, zero);
  for (di = this->degree - 1; di >= 0; di--) {
    out.coeffs[di] = zero;
  }

  for (si = 0, di = 0; si <= this->degree; si += p, di++) {
    out.coeffs[di] = this->coeffs[si];
    for (j = 1; j < p; j++) {
      if (si + j > this->degree) {
        break;
      }
      if (this->coeffs[si + j] != zero) {
        return false;
      }
    }
  }

  out.recompute_degree();
  rroot = out;
  return true;
}

// ----------------------------------------------------------------
fp_polymod_t fpn_poly_t::eval(const fp_polymod_t &c) const {
  fp_polymod_t rv = this->coeffs[this->degree];
  for (int i = this->degree - 1; i >= 0; i--) {
    rv *= c;
    rv += this->coeffs[i];
  }
  return rv;
}

// ----------------------------------------------------------------
int fpn_poly_t::find_degree(void) const { return this->degree; }

// ----------------------------------------------------------------
fp_polymod_t fpn_poly_t::get_coeff(int deg) const {
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
void fpn_poly_t::set_coeff(int pos, const fp_polymod_t &c) {
  if (pos < 0) {
    this->bounds_check(pos);
  }

  fp_polymod_t zero = this->coeffs[0].prime_subfield_element(0);
  if (pos > this->degree) {
    fp_polymod_t *temp = new fp_polymod_t[pos + 1];
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
void fpn_poly_t::recompute_degree(void) {
  bool is_zero      = true;
  fp_polymod_t zero = this->coeffs[0] - this->coeffs[0];

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
bool fpn_poly_t::operator==(int v) const {
  int d = this->degree;
  if (d != 0) {
    return false;
  }
  return this->coeffs[0].get_residue() == v;
}

// ----------------------------------------------------------------
bool fpn_poly_t::operator!=(int v) const { return !(*this == v); }

// ----------------------------------------------------------------
bool fpn_poly_t::operator==(const fpn_poly_t &that) const {
  return this->cmp(CMP_EQ, that);
}

// ----------------------------------------------------------------
bool fpn_poly_t::operator!=(const fpn_poly_t &that) const {
  return this->cmp(CMP_NE, that);
}

// ----------------------------------------------------------------
bool fpn_poly_t::operator<(const fpn_poly_t &that) const {
  return this->cmp(CMP_LT, that);
}

// ----------------------------------------------------------------
bool fpn_poly_t::operator>(const fpn_poly_t &that) const {
  return this->cmp(CMP_GT, that);
}

// ----------------------------------------------------------------
bool fpn_poly_t::operator<=(const fpn_poly_t &that) const {
  return this->cmp(CMP_LE, that);
}

// ----------------------------------------------------------------
bool fpn_poly_t::operator>=(const fpn_poly_t &that) const {
  return this->cmp(CMP_GE, that);
}

// ----------------------------------------------------------------
void fpn_poly_t::increment(void) {
  std::stringstream ss;
  ss << "fpn_poly_t::increment:  unimplemented.\n";
  throw spffl::exception_t(ss.str());
#if 0
	fp_poly_t m = this->coeffs[0].get_modulus();
	int d = m.find_degree();
	fp_poly_t max(0);
	max.set_bit(d);
	fp_poly_t r0(0), r1(1);
	fp_polymod_t m0(r0, m);
	fp_polymod_t m1(r1, m);
	for (int i = 0; i <= this->degree; i++) {
		fp_poly_t r = this->coeffs[i].get_residue();
		r.increment();
		if (r != max) {
			this->coeffs[i] = fp_polymod_t(r, m);
			return;
		}
		else {
			this->coeffs[i] = fp_polymod_t(r0, m);
		}
	}
	this->set_coeff(this->degree + 1, m1);
#endif
}

// ----------------------------------------------------------------
bool fpn_poly_t::cmp(int cmp, const fpn_poly_t &that) const {
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
void fpn_poly_t::bounds_check(int deg) const {
  if ((deg < 0) || (deg > this->degree)) {
    std::stringstream ss;
    ss << "fpn_poly_t: degree " << deg << " out of bounds 0:" << this->degree
       << ".\n";
    throw spffl::exception_t(ss.str());
  }
}

// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const fpn_poly_t &poly) {
  int d       = poly.find_degree();
  fp_poly_t m = poly.get_coeff(0).get_modulus();

  for (int i = d; i >= 0; i--) {
    if (i < d) {
      os << ":";
    }
    os << poly.get_coeff(i).get_residue();
  }

  return os;
}

// ----------------------------------------------------------------
// Coefficient 0 modulus must already be set.

std::istream &operator>>(std::istream &is, fpn_poly_t &poly) {
  fp_poly_t r;
  fp_poly_t m        = poly.coeffs[0].get_modulus();
  fp_polymod_t zeroc = poly.coeffs[0].prime_subfield_element(0);
  poly               = fpn_poly_t(zeroc);

  r = m; // set modulus
  is >> r;
  if (is.fail()) {
    std::stringstream ss;
    ss << "fpn_poly_t: scan failure.\n";
    return is;
  }
  poly.coeffs[0] = fp_polymod_t(r, m);
  while (!is.eof() && is.peek() == ':') {
    (void)is.get();
    is >> r;
    if (is.fail()) {
      std::stringstream ss;
      ss << "fpn_poly_t: scan failure.\n";
      return is;
    }
    poly.promote_and_add(fp_polymod_t(r, m));
  }

  poly.recompute_degree();
  return is;
}

// ----------------------------------------------------------------
bool fpn_poly_t::from_string(const std::string &string, fp_poly_t m) {
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
  this->coeffs = new fp_polymod_t[this->degree + 1];
  int argi, ci;
  for (argi = 0, ci = this->degree; argi < argc; argi++, ci--) {
    // Scan each coefficient, then reduce mod m
    fp_poly_t r = m; // Set modulus

    std::istringstream iss(argv[argi], std::ios_base::in);
    iss >> r;
    if (iss.fail()) {
      std::stringstream ss;
      ss << "fpn_poly_t::from_string: "
         << "scan failure at \"" << string << "\"\n";
      return false;
    } else {
      this->coeffs[ci] = fp_polymod_t(r, m);
    }
  }
  delete[] argv;
  free(dup);

  this->recompute_degree();
  return true;
}

// ----------------------------------------------------------------
void fpn_poly_t::promote(void) {
  if (!this->coeffs) {
    std::stringstream ss;
    ss << "fpn_poly_t::promote: null data.\n";
    throw spffl::exception_t(ss.str());
  }
  fp_polymod_t *ocoeffs = this->coeffs;
  this->coeffs          = new fp_polymod_t[this->degree + 2];
  for (int i = 0; i <= this->degree; i++) {
    this->coeffs[i + 1] = ocoeffs[i];
  }
  this->coeffs[0] = this->coeffs[1] - this->coeffs[1];
  this->degree++;
  delete[] ocoeffs;
}

// ----------------------------------------------------------------
void fpn_poly_t::promote_and_add(const fp_polymod_t &c0) {
  this->promote();
  this->coeffs[0] = c0;
}

} // namespace spffl::polynomials

// ----------------------------------------------------------------
spffl::polynomials::fpn_poly_t gcd(const spffl::polynomials::fpn_poly_t &a,
    const spffl::polynomials::fpn_poly_t &b) {
  return a.gcd(b);
}
