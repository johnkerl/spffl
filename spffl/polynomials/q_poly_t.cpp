// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "base/cmps.h"
#include "base/spffl_exception.h"
#include "base/tokenize.h"
#include "intmath/intrat_t.h"
#include "polynomials/q_poly_t.h"
#include <stdlib.h>
#include <string.h>

namespace spffl::polynomials {

// ----------------------------------------------------------------
q_poly_t::q_poly_t(void) {
  spffl::intmath::intrat_t zero(0);
  this->degree    = 0;
  this->coeffs    = new spffl::intmath::intrat_t[this->degree + 1];
  this->coeffs[0] = zero;
}

// ----------------------------------------------------------------
q_poly_t::q_poly_t(const spffl::intmath::intrat_t &c0) {
  this->degree    = 0;
  this->coeffs    = new spffl::intmath::intrat_t[this->degree + 1];
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
q_poly_t::q_poly_t(const spffl::intmath::intrat_t &c1, const spffl::intmath::intrat_t &c0) {
  this->degree    = 1;
  this->coeffs    = new spffl::intmath::intrat_t[this->degree + 1];
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
q_poly_t::q_poly_t(const spffl::intmath::intrat_t &c2, const spffl::intmath::intrat_t &c1, const spffl::intmath::intrat_t &c0) {
  this->degree    = 2;
  this->coeffs    = new spffl::intmath::intrat_t[this->degree + 1];
  this->coeffs[2] = c2;
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
// This is a static method.
q_poly_t q_poly_t::binomial(
    const spffl::intmath::intrat_t &ci, int i, const spffl::intmath::intrat_t &cj, int j) {
  q_poly_t rv(0);
  rv.set_coeff(i, ci);
  rv.set_coeff(j, cj);
  return rv;
}

// ----------------------------------------------------------------
q_poly_t::q_poly_t(const q_poly_t &that) {
  this->degree = that.degree;
  this->coeffs = new spffl::intmath::intrat_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++) {
    this->coeffs[i] = that.coeffs[i];
  }
}

// ----------------------------------------------------------------
q_poly_t::~q_poly_t(void) {
  delete[] this->coeffs;
  this->coeffs = 0;
  this->degree = -1;
}

// ----------------------------------------------------------------
q_poly_t &q_poly_t::operator=(const q_poly_t &that) {
  if (this->coeffs) {
    delete[] this->coeffs;
  }
  this->degree = that.degree;
  this->coeffs = new spffl::intmath::intrat_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++) {
    this->coeffs[i] = that.coeffs[i];
  }
  return *this;
}

// ----------------------------------------------------------------
q_poly_t q_poly_t::operator+(const q_poly_t &that) const {
  int i;
  q_poly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new spffl::intmath::intrat_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i] + that.coeffs[i];
    }
    for (i = this->degree + 1; i <= that.degree; i++) {
      rv.coeffs[i] = that.coeffs[i];
    }
  } else {
    rv.degree = this->degree;
    rv.coeffs = new spffl::intmath::intrat_t[rv.degree + 1];
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
q_poly_t q_poly_t::operator+(const spffl::intmath::intrat_t &a) const {
  q_poly_t rv(*this);
  rv.coeffs[0] += a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
q_poly_t q_poly_t::operator-(const q_poly_t &that) const {
  int i;
  q_poly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new spffl::intmath::intrat_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i] - that.coeffs[i];
    }
    for (i = this->degree + 1; i <= that.degree; i++) {
      rv.coeffs[i] = -that.coeffs[i];
    }
  } else {
    rv.degree = this->degree;
    rv.coeffs = new spffl::intmath::intrat_t[rv.degree + 1];
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
q_poly_t q_poly_t::operator-(const spffl::intmath::intrat_t &a) const {
  q_poly_t rv(*this);
  rv.coeffs[0] -= a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
q_poly_t q_poly_t::operator-(void) const {
  q_poly_t rv;
  rv.coeffs = new spffl::intmath::intrat_t[rv.degree + 1];
  for (int i = 0; i <= this->degree; i++) {
    rv.coeffs[i] = -this->coeffs[i];
  }
  return rv;
}

// ----------------------------------------------------------------
q_poly_t q_poly_t::operator*(const q_poly_t &that) const {
  q_poly_t rv;
  rv.degree = this->degree + that.degree;
  rv.coeffs = new spffl::intmath::intrat_t[rv.degree + 1];

  spffl::intmath::intrat_t zero = this->coeffs[0] - this->coeffs[0];
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
q_poly_t q_poly_t::operator*(const spffl::intmath::intrat_t &a) {
  q_poly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] *= a;
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
q_poly_t q_poly_t::operator/(const q_poly_t &that) {
  q_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return quot;
}

// ----------------------------------------------------------------
q_poly_t q_poly_t::operator%(const q_poly_t &that) {
  q_poly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return rem;
}

// ----------------------------------------------------------------
q_poly_t q_poly_t::operator/(const spffl::intmath::intrat_t &a) {
  q_poly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] /= a;
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
q_poly_t &q_poly_t::operator+=(const q_poly_t &that) {
  *this = *this + that;
  return *this;
}
q_poly_t &q_poly_t::operator+=(const spffl::intmath::intrat_t &a) {
  *this = *this + a;
  return *this;
}
q_poly_t &q_poly_t::operator-=(const q_poly_t &that) {
  *this = *this - that;
  return *this;
}
q_poly_t &q_poly_t::operator-=(const spffl::intmath::intrat_t &a) {
  *this = *this - a;
  return *this;
}
q_poly_t &q_poly_t::operator*=(const q_poly_t &that) {
  *this = *this * that;
  return *this;
}
q_poly_t &q_poly_t::operator*=(const spffl::intmath::intrat_t &a) {
  *this = *this * a;
  return *this;
}
q_poly_t &q_poly_t::operator/=(const q_poly_t &that) {
  *this = *this / that;
  return *this;
}
q_poly_t &q_poly_t::operator%=(const q_poly_t &that) {
  *this = *this % that;
  return *this;
}
q_poly_t &q_poly_t::operator/=(const spffl::intmath::intrat_t &a) {
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
void q_poly_t::quot_and_rem(
    const q_poly_t &that, q_poly_t &rquot, q_poly_t &rrem) const {
  spffl::intmath::intrat_t zero = this->coeffs[0] - this->coeffs[0];

  if (that == zero) {
    std::stringstream ss;
    ss << "q_poly_t::quot_and_rem:  division by zero.\n";
    throw spffl::exception_t(ss.str());
  }
  if (*this == zero) {
    rquot = q_poly_t(0);
    rrem  = *this;
    return;
  }

  int dividend_degree = this->degree;
  int divisor_degree  = that.degree;

  if (dividend_degree < divisor_degree) {
    rquot = q_poly_t(0);
    rrem  = *this;
    return;
  }

  q_poly_t quot;
  quot.degree = this->degree - that.degree;
  quot.coeffs = new spffl::intmath::intrat_t[quot.degree + 1];

  q_poly_t rem = *this;

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

  int max_shift           = dividend_degree - divisor_degree;
  spffl::intmath::intrat_t divisor_leader = that.coeffs[divisor_degree];
  spffl::intmath::intrat_t dlinv          = spffl::intmath::intrat_t(1) / divisor_leader;
  for (int shift = max_shift; shift >= 0; shift--) {
    spffl::intmath::intrat_t rem_leader       = rem.coeffs[shift + divisor_degree];
    spffl::intmath::intrat_t multiplier       = rem_leader * dlinv;
    q_poly_t divisor_with_mul = that * multiplier;
    quot.coeffs[shift]        = multiplier;

    int stop = shift + divisor_with_mul.degree;
    for (int i = shift; i <= stop; i++) {
      rem.coeffs[i] -= divisor_with_mul.coeffs[i - shift];
    }
  }

  // Quotient degree must be the difference of dividend and divisor
  // degrees.  If not, we have made a mistake.
  if (quot.coeffs[quot.degree] == zero) {
    std::stringstream ss;
    ss << "q_poly_t division: coding error.\n";
    throw spffl::exception_t(ss.str());
  }

  // The remainder degree is less than the divisor's degree.
  rem.recompute_degree();

  rquot = quot;
  rrem  = rem;
}

// ----------------------------------------------------------------
q_poly_t q_poly_t::gcd(const q_poly_t &that) const {
  q_poly_t c, q, r;
  q_poly_t d; // Return value.

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

q_poly_t q_poly_t::ext_gcd(
    const q_poly_t &that, q_poly_t &rm, q_poly_t &rn) const {
  q_poly_t mprime, nprime, c, q, r, t, qm, qn;
  q_poly_t d; // Return value.

  // Initialize
  mprime = q_poly_t(1);
  rn     = q_poly_t(1);
  rm     = q_poly_t(0);
  nprime = q_poly_t(0);
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
q_poly_t q_poly_t::exp(int e) const {
  int deg       = this->find_degree();
  q_poly_t xp   = *this;
  q_poly_t zero = q_poly_t(0);
  q_poly_t one  = q_poly_t(1);
  q_poly_t rv   = one;

  if (*this == zero) {
    if (e == 0) {
      std::stringstream ss;
      ss << "q_poly_t::exp:  0 ^ 0 undefined.\n";
      throw spffl::exception_t(ss.str());
    } else if (e < 0) {
      std::stringstream ss;
      ss << "q_poly_t::exp:  division by zero.\n";
      throw spffl::exception_t(ss.str());
    } else {
      return zero;
    }
  } else if (deg == 0) {
    // Unit
    return q_poly_t(this->coeffs[0].exp(e));
  } else {
    // Degree 1 or higher.
    if (e < 0) {
      std::stringstream ss;
      ss << "q_poly_t::exp:  division by non-unit.\n";
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
q_poly_t q_poly_t::deriv(void) const {
  if (this->degree == 0) {
    return q_poly_t(0);
  }

  q_poly_t rv(*this);
  rv.degree--;
  for (int i = 1; i <= this->degree; i++) {
    rv.coeffs[i - 1] = this->coeffs[i] * spffl::intmath::intrat_t(i);
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
spffl::intmath::intrat_t q_poly_t::eval(const spffl::intmath::intrat_t &c) const {
  spffl::intmath::intrat_t rv = this->coeffs[this->degree];
  for (int i = this->degree - 1; i >= 0; i--) {
    rv *= c;
    rv += this->coeffs[i];
  }
  return rv;
}

// ----------------------------------------------------------------
int q_poly_t::find_degree(void) const { return this->degree; }

// ----------------------------------------------------------------
spffl::intmath::intrat_t q_poly_t::get_coeff(int deg) const {
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
void q_poly_t::set_coeff(int pos, spffl::intmath::intrat_t c) {
  if (pos < 0) {
    this->bounds_check(pos);
  }

  spffl::intmath::intrat_t zero(0);
  if (pos > this->degree) {
    spffl::intmath::intrat_t *temp = new spffl::intmath::intrat_t[pos + 1];
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
void q_poly_t::recompute_degree(void) {
  bool is_zero  = true;
  spffl::intmath::intrat_t zero = this->coeffs[0] - this->coeffs[0];

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
bool q_poly_t::operator==(int v) const {
  int d = this->degree;
  if (d != 0) {
    return false;
  }
  return this->coeffs[0] == v;
}

// ----------------------------------------------------------------
bool q_poly_t::operator!=(int v) const { return !(*this == v); }

// ----------------------------------------------------------------
bool q_poly_t::operator==(const q_poly_t &that) const {
  return this->cmp(CMP_EQ, that);
}

// ----------------------------------------------------------------
bool q_poly_t::operator!=(const q_poly_t &that) const {
  return this->cmp(CMP_NE, that);
}

// ----------------------------------------------------------------
bool q_poly_t::operator<(const q_poly_t &that) const {
  return this->cmp(CMP_LT, that);
}

// ----------------------------------------------------------------
bool q_poly_t::operator>(const q_poly_t &that) const {
  return this->cmp(CMP_GT, that);
}

// ----------------------------------------------------------------
bool q_poly_t::operator<=(const q_poly_t &that) const {
  return this->cmp(CMP_LE, that);
}

// ----------------------------------------------------------------
bool q_poly_t::operator>=(const q_poly_t &that) const {
  return this->cmp(CMP_GE, that);
}

// ----------------------------------------------------------------
bool q_poly_t::cmp(int cmp, const q_poly_t &that) const {
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
void q_poly_t::bounds_check(int deg) const {
  if ((deg < 0) || (deg > this->degree)) {
    std::stringstream ss;
    ss << "q_poly_t: degree " << deg << " out of bounds 0:" << this->degree
       << ".\n";
    throw spffl::exception_t(ss.str());
  }
}

// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const q_poly_t &poly) {
  int d = poly.find_degree();

  for (int i = d; i >= 0; i--) {
    if (i < d) {
      os << ",";
    }
    os << poly.get_coeff(i);
  }

  return os;
}

// ----------------------------------------------------------------
std::istream &operator>>(std::istream &is, q_poly_t &poly) {
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

  if (!poly.from_string(s)) {
    is.setstate(std::ios::failbit);
  }
  return is;
}

// ----------------------------------------------------------------
bool q_poly_t::from_string(const std::string &string) {
  if (this->coeffs) {
    delete[] this->coeffs;
  }

  int num_commas = 0;
  for (const char *q = string.c_str(); *q; q++) {
    if (*q == ',') {
      num_commas++;
    }
  }

  if (num_commas == 0) {
    // Allow comma-free input as long as all residues are
    // single-digit.
    int len      = string.length();
    this->degree = len - 1;
    this->coeffs = new spffl::intmath::intrat_t[this->degree + 1];
    int si, ci;
    for (si = 0, ci = this->degree; si < len; si++, ci--) {
      char ascii_digit = string[si];
      if ((ascii_digit < '0') || (ascii_digit > '9')) {
        std::stringstream ss;
        ss << "q_poly_t::from_string: "
           << "non-numerical input \"" << string << "\"\n";
        ss << "Didn't like '" << ascii_digit << "'\n";
        return false;
      }
      this->coeffs[ci] = spffl::intmath::intrat_t(ascii_digit - '0');
    }
  } else {
    char *dup   = strdup(string.c_str());
    char **argv = new char *[num_commas + 1];
    int argc    = spffl::base::tokenize(dup, ",", argv, num_commas + 1);
    if (argc < 1) {
      // Needs an error message, but this coding error is
      // unlikely since we already counted commas.
      return false;
    }

    this->degree = argc - 1;
    this->coeffs = new spffl::intmath::intrat_t[this->degree + 1];
    int argi, ci;
    for (argi = 0, ci = this->degree; argi < argc; argi++, ci--) {
      // Scan each coefficient.
      int r;

      std::istringstream iss(argv[argi], std::ios_base::in);
      iss >> r;
      if (iss.fail()) {
        std::stringstream ss;
        ss << "q_poly_t::from_string: "
           << "scan failure at \"" << string << "\"\n";
        return false;
      } else {
        this->coeffs[ci] = spffl::intmath::intrat_t(r);
      }
    }
    delete[] argv;
    free(dup);
  }

  this->recompute_degree();
  return true;
}

// ----------------------------------------------------------------
void q_poly_t::promote(void) {
  if (!this->coeffs) {
    std::stringstream ss;
    ss << "q_poly_t::promote: null data.\n";
    throw spffl::exception_t(ss.str());
  }
  spffl::intmath::intrat_t *ocoeffs = this->coeffs;
  this->coeffs      = new spffl::intmath::intrat_t[this->degree + 2];
  for (int i = 0; i <= this->degree; i++) {
    this->coeffs[i + 1] = ocoeffs[i];
  }
  this->coeffs[0] = this->coeffs[1] - this->coeffs[1];
  this->degree++;
  delete[] ocoeffs;
}

// ----------------------------------------------------------------
void q_poly_t::promote_and_add(spffl::intmath::intrat_t c0) {
  this->promote();
  this->coeffs[0] = c0;
}

} // namespace spffl::polynomials
