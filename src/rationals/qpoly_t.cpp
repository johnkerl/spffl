// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl_exception.h"
#include "qpoly_t.h"
#include "cmps.h"
#include "tokenize.h"
#include <stdlib.h>
#include <string.h>

namespace spffl::rationals {

// ----------------------------------------------------------------
qpoly_t::qpoly_t(void) {
  intrat_t zero(0);
  this->degree    = 0;
  this->coeffs    = new intrat_t[this->degree + 1];
  this->coeffs[0] = zero;
}

// ----------------------------------------------------------------
qpoly_t::qpoly_t(const intrat_t &c0) {
  this->degree    = 0;
  this->coeffs    = new intrat_t[this->degree + 1];
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
qpoly_t::qpoly_t(const intrat_t &c1, const intrat_t &c0) {
  this->degree    = 1;
  this->coeffs    = new intrat_t[this->degree + 1];
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
qpoly_t::qpoly_t(const intrat_t &c2, const intrat_t &c1, const intrat_t &c0) {
  this->degree    = 2;
  this->coeffs    = new intrat_t[this->degree + 1];
  this->coeffs[2] = c2;
  this->coeffs[1] = c1;
  this->coeffs[0] = c0;
  this->recompute_degree();
}

// ----------------------------------------------------------------
// This is a static method.
qpoly_t qpoly_t::binomial(
    const intrat_t &ci, int i, const intrat_t &cj, int j) {
  qpoly_t rv(0);
  rv.set_coeff(i, ci);
  rv.set_coeff(j, cj);
  return rv;
}

// ----------------------------------------------------------------
qpoly_t::qpoly_t(const qpoly_t &that) {
  this->degree = that.degree;
  this->coeffs = new intrat_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++) {
    this->coeffs[i] = that.coeffs[i];
  }
}

// ----------------------------------------------------------------
qpoly_t::~qpoly_t(void) {
  delete[] this->coeffs;
  this->coeffs = 0;
  this->degree = -1;
}

// ----------------------------------------------------------------
qpoly_t &qpoly_t::operator=(const qpoly_t &that) {
  if (this->coeffs) {
    delete[] this->coeffs;
  }
  this->degree = that.degree;
  this->coeffs = new intrat_t[this->degree + 1];
  for (int i = 0; i <= that.degree; i++) {
    this->coeffs[i] = that.coeffs[i];
  }
  return *this;
}

// ----------------------------------------------------------------
qpoly_t qpoly_t::operator+(const qpoly_t &that) const {
  int i;
  qpoly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new intrat_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i] + that.coeffs[i];
    }
    for (i = this->degree + 1; i <= that.degree; i++) {
      rv.coeffs[i] = that.coeffs[i];
    }
  } else {
    rv.degree = this->degree;
    rv.coeffs = new intrat_t[rv.degree + 1];
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
qpoly_t qpoly_t::operator+(const intrat_t &a) const {
  qpoly_t rv(*this);
  rv.coeffs[0] += a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
qpoly_t qpoly_t::operator-(const qpoly_t &that) const {
  int i;
  qpoly_t rv;

  if (this->degree < that.degree) {
    rv.degree = that.degree;
    rv.coeffs = new intrat_t[rv.degree + 1];
    for (i = 0; i <= this->degree; i++) {
      rv.coeffs[i] = this->coeffs[i] - that.coeffs[i];
    }
    for (i = this->degree + 1; i <= that.degree; i++) {
      rv.coeffs[i] = -that.coeffs[i];
    }
  } else {
    rv.degree = this->degree;
    rv.coeffs = new intrat_t[rv.degree + 1];
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
qpoly_t qpoly_t::operator-(const intrat_t &a) const {
  qpoly_t rv(*this);
  rv.coeffs[0] -= a;
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
qpoly_t qpoly_t::operator-(void) const {
  qpoly_t rv;
  rv.coeffs = new intrat_t[rv.degree + 1];
  for (int i = 0; i <= this->degree; i++) {
    rv.coeffs[i] = -this->coeffs[i];
  }
  return rv;
}

// ----------------------------------------------------------------
qpoly_t qpoly_t::operator*(const qpoly_t &that) const {
  qpoly_t rv;
  rv.degree = this->degree + that.degree;
  rv.coeffs = new intrat_t[rv.degree + 1];

  intrat_t zero = this->coeffs[0] - this->coeffs[0];
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
qpoly_t qpoly_t::operator*(const intrat_t &a) {
  qpoly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] *= a;
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
qpoly_t qpoly_t::operator/(const qpoly_t &that) {
  qpoly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return quot;
}

// ----------------------------------------------------------------
qpoly_t qpoly_t::operator%(const qpoly_t &that) {
  qpoly_t quot, rem;
  this->quot_and_rem(that, quot, rem);
  return rem;
}

// ----------------------------------------------------------------
qpoly_t qpoly_t::operator/(const intrat_t &a) {
  qpoly_t rv = *this;
  for (int i = 0; i <= rv.degree; i++) {
    rv.coeffs[i] /= a;
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
qpoly_t &qpoly_t::operator+=(const qpoly_t &that) {
  *this = *this + that;
  return *this;
}
qpoly_t &qpoly_t::operator+=(const intrat_t &a) {
  *this = *this + a;
  return *this;
}
qpoly_t &qpoly_t::operator-=(const qpoly_t &that) {
  *this = *this - that;
  return *this;
}
qpoly_t &qpoly_t::operator-=(const intrat_t &a) {
  *this = *this - a;
  return *this;
}
qpoly_t &qpoly_t::operator*=(const qpoly_t &that) {
  *this = *this * that;
  return *this;
}
qpoly_t &qpoly_t::operator*=(const intrat_t &a) {
  *this = *this * a;
  return *this;
}
qpoly_t &qpoly_t::operator/=(const qpoly_t &that) {
  *this = *this / that;
  return *this;
}
qpoly_t &qpoly_t::operator%=(const qpoly_t &that) {
  *this = *this % that;
  return *this;
}
qpoly_t &qpoly_t::operator/=(const intrat_t &a) {
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
void qpoly_t::quot_and_rem(
    const qpoly_t &that, qpoly_t &rquot, qpoly_t &rrem) const {
  intrat_t zero = this->coeffs[0] - this->coeffs[0];

  if (that == zero) {
    std::stringstream ss;
    ss << "qpoly_t::quot_and_rem:  division by zero.\n";
    exit(1);
  }
  if (*this == zero) {
    rquot = qpoly_t(0);
    rrem  = *this;
    return;
  }

  int dividend_degree = this->degree;
  int divisor_degree  = that.degree;

  if (dividend_degree < divisor_degree) {
    rquot = qpoly_t(0);
    rrem  = *this;
    return;
  }

  qpoly_t quot;
  quot.degree = this->degree - that.degree;
  quot.coeffs = new intrat_t[quot.degree + 1];

  qpoly_t rem = *this;

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
  intrat_t divisor_leader = that.coeffs[divisor_degree];
  intrat_t dlinv          = intrat_t(1) / divisor_leader;
  for (int shift = max_shift; shift >= 0; shift--) {
    intrat_t rem_leader      = rem.coeffs[shift + divisor_degree];
    intrat_t multiplier      = rem_leader * dlinv;
    qpoly_t divisor_with_mul = that * multiplier;
    quot.coeffs[shift]       = multiplier;

    int stop = shift + divisor_with_mul.degree;
    for (int i = shift; i <= stop; i++) {
      rem.coeffs[i] -= divisor_with_mul.coeffs[i - shift];
    }
  }

  // Quotient degree must be the difference of dividend and divisor
  // degrees.  If not, we have made a mistake.
  if (quot.coeffs[quot.degree] == zero) {
    std::stringstream ss;
    ss << "qpoly_t division: coding error.\n";
    exit(1);
  }

  // The remainder degree is less than the divisor's degree.
  rem.recompute_degree();

  rquot = quot;
  rrem  = rem;
}

// ----------------------------------------------------------------
qpoly_t qpoly_t::gcd(const qpoly_t &that) const {
  qpoly_t c, q, r;
  qpoly_t d; // Return value.

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

qpoly_t qpoly_t::ext_gcd(const qpoly_t &that, qpoly_t &rm, qpoly_t &rn) const {
  qpoly_t mprime, nprime, c, q, r, t, qm, qn;
  qpoly_t d; // Return value.

  // Initialize
  mprime = qpoly_t(1);
  rn     = qpoly_t(1);
  rm     = qpoly_t(0);
  nprime = qpoly_t(0);
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
qpoly_t qpoly_t::exp(int e) const {
  int deg      = this->find_degree();
  qpoly_t xp   = *this;
  qpoly_t zero = qpoly_t(0);
  qpoly_t one  = qpoly_t(1);
  qpoly_t rv   = one;

  if (*this == zero) {
    if (e == 0) {
      std::stringstream ss;
      ss << "qpoly_t::exp:  0 ^ 0 undefined.\n";
      exit(1);
    } else if (e < 0) {
      std::stringstream ss;
      ss << "qpoly_t::exp:  division by zero.\n";
      exit(1);
    } else {
      return zero;
    }
  } else if (deg == 0) {
    // Unit
    return qpoly_t(this->coeffs[0].exp(e));
  } else {
    // Degree 1 or higher.
    if (e < 0) {
      std::stringstream ss;
      ss << "qpoly_t::exp:  division by non-unit.\n";
      exit(1);
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
qpoly_t qpoly_t::deriv(void) const {
  if (this->degree == 0) {
    return qpoly_t(0);
  }

  qpoly_t rv(*this);
  rv.degree--;
  for (int i = 1; i <= this->degree; i++) {
    rv.coeffs[i - 1] = this->coeffs[i] * intrat_t(i);
  }
  rv.recompute_degree();
  return rv;
}

// ----------------------------------------------------------------
intrat_t qpoly_t::eval(const intrat_t &c) const {
  intrat_t rv = this->coeffs[this->degree];
  for (int i = this->degree - 1; i >= 0; i--) {
    rv *= c;
    rv += this->coeffs[i];
  }
  return rv;
}

// ----------------------------------------------------------------
int qpoly_t::find_degree(void) const { return this->degree; }

// ----------------------------------------------------------------
intrat_t qpoly_t::get_coeff(int deg) const {
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
void qpoly_t::set_coeff(int pos, intrat_t c) {
  if (pos < 0) {
    this->bounds_check(pos);
  }

  intrat_t zero(0);
  if (pos > this->degree) {
    intrat_t *temp = new intrat_t[pos + 1];
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
void qpoly_t::recompute_degree(void) {
  bool is_zero  = true;
  intrat_t zero = this->coeffs[0] - this->coeffs[0];

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
bool qpoly_t::operator==(int v) const {
  int d = this->degree;
  if (d != 0) {
    return false;
  }
  return this->coeffs[0] == v;
}

// ----------------------------------------------------------------
bool qpoly_t::operator!=(int v) const { return !(*this == v); }

// ----------------------------------------------------------------
bool qpoly_t::operator==(const qpoly_t &that) const {
  return this->cmp(CMP_EQ, that);
}

// ----------------------------------------------------------------
bool qpoly_t::operator!=(const qpoly_t &that) const {
  return this->cmp(CMP_NE, that);
}

// ----------------------------------------------------------------
bool qpoly_t::operator<(const qpoly_t &that) const {
  return this->cmp(CMP_LT, that);
}

// ----------------------------------------------------------------
bool qpoly_t::operator>(const qpoly_t &that) const {
  return this->cmp(CMP_GT, that);
}

// ----------------------------------------------------------------
bool qpoly_t::operator<=(const qpoly_t &that) const {
  return this->cmp(CMP_LE, that);
}

// ----------------------------------------------------------------
bool qpoly_t::operator>=(const qpoly_t &that) const {
  return this->cmp(CMP_GE, that);
}

// ----------------------------------------------------------------
bool qpoly_t::cmp(int cmp, const qpoly_t &that) const {
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
    exit(1);
    return false;
    break;
  }
}

// ----------------------------------------------------------------
void qpoly_t::bounds_check(int deg) const {
  if ((deg < 0) || (deg > this->degree)) {
    std::stringstream ss;
    ss << "qpoly_t: degree " << deg
              << " out of bounds 0:" << this->degree << ".\n";
    exit(1);
  }
}

// ----------------------------------------------------------------
std::ostream &operator<<(std::ostream &os, const qpoly_t &poly) {
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
std::istream &operator>>(std::istream &is, qpoly_t &poly) {
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
bool qpoly_t::from_string(const std::string &string) {
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
    this->coeffs = new intrat_t[this->degree + 1];
    int si, ci;
    for (si = 0, ci = this->degree; si < len; si++, ci--) {
      char ascii_digit = string[si];
      if ((ascii_digit < '0') || (ascii_digit > '9')) {
        std::stringstream ss;
        ss << "qpoly_t::from_string: "
                  << "non-numerical input \"" << string << "\"\n";
        ss << "Didn't like '" << ascii_digit << "'\n";
        return false;
      }
      this->coeffs[ci] = intrat_t(ascii_digit - '0');
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
    this->coeffs = new intrat_t[this->degree + 1];
    int argi, ci;
    for (argi = 0, ci = this->degree; argi < argc; argi++, ci--) {
      // Scan each coefficient.
      int r;

      std::istringstream iss(argv[argi], std::ios_base::in);
      iss >> r;
      if (iss.fail()) {
        std::stringstream ss;
        ss << "qpoly_t::from_string: "
                  << "scan failure at \"" << string << "\"\n";
        return false;
      } else {
        this->coeffs[ci] = intrat_t(r);
      }
    }
    delete[] argv;
    free(dup);
  }

  this->recompute_degree();
  return true;
}

// ----------------------------------------------------------------
void qpoly_t::promote(void) {
  if (!this->coeffs) {
    std::stringstream ss;
    ss << "qpoly_t::promote: null data.\n";
    exit(1);
  }
  intrat_t *ocoeffs = this->coeffs;
  this->coeffs      = new intrat_t[this->degree + 2];
  for (int i = 0; i <= this->degree; i++) {
    this->coeffs[i + 1] = ocoeffs[i];
  }
  this->coeffs[0] = this->coeffs[1] - this->coeffs[1];
  this->degree++;
  delete[] ocoeffs;
}

// ----------------------------------------------------------------
void qpoly_t::promote_and_add(intrat_t c0) {
  this->promote();
  this->coeffs[0] = c0;
}

} // namespace spffl::rationals
