// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "sp_list_elts.h"
#include "f2npoly_totient.h"
#include "f2poly_totient.h"
#include "fppoly_totient.h"
#include "int_gcd.h"
#include "int_power.h"
#include "int_totient.h"

// ----------------------------------------------------------------
tvector<f2poly_t> f2poly_list(int deg) {
  int nel = 1 << deg;
  tvector<f2poly_t> rv(nel);

  int i;
  f2poly_t min(0);
  f2poly_t max(0);
  f2poly_t r;
  min.set_bit(deg);
  max.set_bit(deg + 1);

  for (r = min, i = 0; r < max; r.increment(), i++)
    rv[i] = r;

  return rv;
}

// ----------------------------------------------------------------
tvector<f2npoly_t> f2npoly_list(f2poly_t im, int outerdeg) {
  int innerdeg = im.find_degree();
  int q = 1 << innerdeg;
  int nel = (q - 1) * int_power(q, outerdeg);
  tvector<f2npoly_t> rv(nel);

  int i;
  f2polymod_t zero(f2poly_t(0), im);
  f2polymod_t one(f2poly_t(1), im);
  f2npoly_t r;
  f2npoly_t min(zero);
  f2npoly_t max(zero);
  min.set_coeff(outerdeg, one);
  max.set_coeff(outerdeg + 1, one);

  for (r = min, i = 0; r < max; r.increment(), i++)
    rv[i] = r;

  return rv;
}

// ----------------------------------------------------------------
tvector<fppoly_t> fppoly_list(int p, int deg) {
  int nel = (p - 1) * int_power(p, deg);
  tvector<fppoly_t> rv(nel);

  int i;
  intmod_t zero(0, p), one(1, p);
  fppoly_t min(zero);
  fppoly_t max(zero);
  fppoly_t r;

  min.set_coeff(deg, one);
  max.set_coeff(deg + 1, one);

  for (r = min, i = 0; r < max; r.increment(), i++)
    rv[i] = r;

  return rv;
}

// ----------------------------------------------------------------
tvector<intmod_t> intmod_list(int p, sp_list_type_t type) {
  int nel;
  if (type == SP_LIST_ALL)
    nel = p;
  else if (type == SP_LIST_UNITS)
    nel = int_totient(p);
  else if (type == SP_LIST_NON_UNITS)
    nel = p - int_totient(p);
  else {
    std::cerr << "intmod_list:  unhandled code option.\n";
    exit(1);
  }
  tvector<intmod_t> rv(nel);
  if (type == SP_LIST_UNITS) {
    int i, j;
    for (i = 0, j = 0; i < p; i++) {
      if (int_gcd(i, p) == 1)
        rv[j++] = intmod_t(i, p);
    }
  } else if (type == SP_LIST_NON_UNITS) {
    int i, j;
    for (i = 0, j = 0; i < p; i++) {
      if (int_gcd(i, p) != 1)
        rv[j++] = intmod_t(i, p);
    }
  } else {
    for (int i = 0; i < p; i++)
      rv[i] = intmod_t(i, p);
  }
  return rv;
}

// ----------------------------------------------------------------
tvector<f2polymod_t> f2polymod_list(f2poly_t m, sp_list_type_t type) {
  int deg = m.find_degree();
  int nel;
  if (type == SP_LIST_ALL)
    nel = 1 << deg;
  else if (type == SP_LIST_UNITS)
    nel = f2poly_totient(m);
  else if (type == SP_LIST_NON_UNITS)
    nel = (1 << deg) - f2poly_totient(m);
  else {
    std::cerr << "f2polymod_list:  unhandled code option.\n";
    exit(1);
  }
  tvector<f2polymod_t> rv(nel);

  int i;
  f2poly_t zero(0);
  f2poly_t min(0);
  f2poly_t max(0);
  f2poly_t r;
  max.set_bit(deg);

  if (type == SP_LIST_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      f2poly_t g = r.gcd(m);
      if ((g.find_degree() == 0) && (g != zero)) {
        rv[i++] = f2polymod_t(r, m);
      }
    }
  } else if (type == SP_LIST_NON_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      f2poly_t g = r.gcd(m);
      if ((g.find_degree() != 0) || (g == zero)) {
        rv[i++] = f2polymod_t(r, m);
      }
    }
  } else {
    for (r = min, i = 0; r < max; r.increment(), i++)
      rv[i] = f2polymod_t(r, m);
  }

  return rv;
}

// ----------------------------------------------------------------
tvector<f2npolymod_t> f2npolymod_list(f2npoly_t om, sp_list_type_t type) {
  f2polymod_t c0 = om.get_coeff(0);
  f2poly_t im = c0.get_modulus();
  int outerdeg = om.find_degree();
  int innerdeg = im.find_degree();
  int nel;
  if (type == SP_LIST_ALL)
    nel = 1 << (outerdeg * innerdeg);
  else if (type == SP_LIST_UNITS)
    nel = f2npoly_totient(om);
  else if (type == SP_LIST_NON_UNITS)
    nel = (1 << (outerdeg * innerdeg)) - f2npoly_totient(om);
  else {
    std::cerr << "f2npolymod_list:  unhandled code option.\n";
    exit(1);
  }
  tvector<f2npolymod_t> rv(nel);

  int i;
  f2polymod_t zero = c0.prime_sfld_elt(0);
  f2polymod_t one = c0.prime_sfld_elt(1);
  f2npoly_t min(zero);
  f2npoly_t max(zero);
  f2npoly_t r;
  max.set_coeff(outerdeg, one);

  if (type == SP_LIST_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      f2npoly_t g = r.gcd(om);
      if ((g.find_degree() == 0) && (g != zero)) {
        rv[i++] = f2npolymod_t(r, om);
      }
    }
  } else if (type == SP_LIST_NON_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      f2npoly_t g = r.gcd(om);
      if ((g.find_degree() != 0) || (g == zero)) {
        rv[i++] = f2npolymod_t(r, om);
      }
    }
  } else {
    for (r = min, i = 0; r < max; r.increment(), i++)
      rv[i] = f2npolymod_t(r, om);
  }

  return rv;
}

// ----------------------------------------------------------------
tvector<fppolymod_t> fppolymod_list(fppoly_t m, sp_list_type_t type) {
  int p = m.get_char();
  int n = m.find_degree();
  int nel;
  if (type == SP_LIST_ALL)
    nel = int_power(p, n);
  else if (type == SP_LIST_UNITS)
    nel = fppoly_totient(m);
  else if (type == SP_LIST_NON_UNITS)
    nel = int_power(p, n) - fppoly_totient(m);
  else {
    std::cerr << "fppolymod_list:  unhandled code option.\n";
    exit(1);
  }
  tvector<fppolymod_t> rv(nel);

  int i;
  intmod_t zero(0, p), one(1, p);
  fppoly_t min(zero);
  fppoly_t max(zero);
  fppoly_t r;
  max.set_coeff(n, one);

  if (type == SP_LIST_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      fppoly_t g = r.gcd(m);
      if ((g.find_degree() == 0) && (g != zero)) {
        rv[i++] = fppolymod_t(r, m);
      }
    }
  } else if (type == SP_LIST_NON_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      fppoly_t g = r.gcd(m);
      if ((g.find_degree() != 0) || (g == zero)) {
        rv[i++] = fppolymod_t(r, m);
      }
    }
  } else {
    for (r = min, i = 0; r < max; r.increment(), i++)
      rv[i] = fppolymod_t(r, m);
  }

  return rv;
}

// ----------------------------------------------------------------
tvector<f2polymod_t> f2polymod_glist(f2polymod_t g, sp_list_type_t type) {
  f2poly_t m = g.get_modulus();
  f2poly_t gres = g.get_residue();
  f2poly_t gr = m.gcd(gres);
  int deg = m.find_degree();
  int maxnel = 1 << deg;
  tvector<f2polymod_t> rv(maxnel);
  int nel = 0;
  f2poly_t r;
  f2poly_t zero(0);
  f2poly_t min(0);
  f2poly_t max(0);
  max.set_bit(deg);

  if (type == SP_LIST_MULTIPLES) {
    for (r = min; r < max; r.increment())
      if ((r % gr) == zero)
        rv[nel++] = f2polymod_t(r, m);
  }

  else if (type == SP_LIST_REL_PRIME) {
    for (r = min; r < max; r.increment()) {
      f2poly_t d = r.gcd(gr);
      if ((d.find_degree() == 0) && (d != zero)) {
        rv[nel++] = f2polymod_t(r, m);
      }
    }
  }

  rv.trim_num_elements(nel);
  return rv;
}

// ----------------------------------------------------------------
tvector<intmod_t> intmod_glist(intmod_t g, sp_list_type_t type) {
  int m = g.get_modulus();
  int gr = int_gcd(m, g.get_residue());
  tvector<intmod_t> rv(m);
  int nel = 0;

  if (type == SP_LIST_MULTIPLES) {
    for (int r = 0; r < m; r++) {
      if ((r % gr) == 0)
        rv[nel++] = intmod_t(r, m);
    }
  } else if (type == SP_LIST_REL_PRIME) {
    for (int r = 0; r < m; r++) {
      if (int_gcd(r, gr) == 1)
        rv[nel++] = intmod_t(r, m);
    }
  }

  rv.trim_num_elements(nel);
  return rv;
}

// ----------------------------------------------------------------
tmatrix<f2polymod_t> f2polymod_An_list(f2poly_t m, int n) {
  int d = m.find_degree();
  int q = 1 << d;
  int qn = int_power(q, n);
  tmatrix<f2polymod_t> rv(qn, n);
  int i, j;

  tvector<f2polymod_t> Fq = f2polymod_list(m, SP_LIST_ALL);

  for (i = 0; i < qn; i++) {
    int baserep = i;
    for (j = 0; j < n; j++) {
      rv[i][n - j - 1] = Fq[baserep % q];
      baserep /= q;
    }
  }

  return rv;
}

// ----------------------------------------------------------------
// P2(Fq):
//   (?:?:1) q^2
//   (?:1:0) q^1
//   (1:0:0) q^0
// # = q^0 + q^2

tmatrix<f2polymod_t> f2polymod_Pn_list(f2poly_t m, int n) {
  int i, j, k;
  int d = m.find_degree();
  int q = 1 << d;
  tvector<f2polymod_t> Fq = f2polymod_list(m, SP_LIST_ALL);
  f2polymod_t zero = f2polymod_t::prime_sfld_elt(0, m);
  f2polymod_t one = f2polymod_t::prime_sfld_elt(1, m);

  int oP = 0;
  for (k = 0; k <= n; k++)
    oP += int_power(q, k);
  tmatrix<f2polymod_t> rv(oP, n + 1);

  int didx = 0;
  for (k = 0; k <= n; k++) {
    int qk = int_power(q, k);
    for (i = 0; i < qk; i++) {
      int baserep = i;
      for (j = 0; j < k; j++) {
        rv[didx][k - j - 1] = Fq[baserep % q];
        baserep /= q;
      }
      rv[didx][k] = one;
      for (j = k + 1; j <= n; j++)
        rv[didx][j] = zero;
      didx++;
    }
  }

  if (didx != oP) {
    std::cerr << "Pn_Fq_list:  coding error.\n";
    exit(1);
  }

  return rv;
}

// ----------------------------------------------------------------
tmatrix<fppolymod_t> fppolymod_An_list(fppoly_t m, int n) {
  int d = m.find_degree();
  int p = m.get_char();
  int q = int_power(p, d);
  int qn = int_power(q, n);
  tmatrix<fppolymod_t> rv(qn, n);
  int i, j;

  tvector<fppolymod_t> Fq = fppolymod_list(m, SP_LIST_ALL);

  for (i = 0; i < qn; i++) {
    int baserep = i;
    for (j = 0; j < n; j++) {
      rv[i][n - j - 1] = Fq[baserep % q];
      baserep /= q;
    }
  }

  return rv;
}

// ----------------------------------------------------------------
// P2(Fq):
//   (?:?:1) q^2
//   (?:1:0) q^1
//   (1:0:0) q^0
// # = q^0 + q^2

tmatrix<fppolymod_t> fppolymod_Pn_list(fppoly_t m, int n) {
  int i, j, k;
  int d = m.find_degree();
  int p = m.get_char();
  int q = int_power(p, d);
  tvector<fppolymod_t> Fq = fppolymod_list(m, SP_LIST_ALL);
  fppolymod_t zero = fppolymod_t::prime_sfld_elt(0, m);
  fppolymod_t one = fppolymod_t::prime_sfld_elt(1, m);

  int oP = 0;
  for (k = 0; k <= n; k++)
    oP += int_power(q, k);
  tmatrix<fppolymod_t> rv(oP, n + 1);

  int didx = 0;
  for (k = 0; k <= n; k++) {
    int qk = int_power(q, k);
    for (i = 0; i < qk; i++) {
      int baserep = i;
      for (j = 0; j < k; j++) {
        rv[didx][k - j - 1] = Fq[baserep % q];
        baserep /= q;
      }
      rv[didx][k] = one;
      for (j = k + 1; j <= n; j++)
        rv[didx][j] = zero;
      didx++;
    }
  }

  if (didx != oP) {
    std::cerr << "Pn_Fq_list:  coding error.\n";
    exit(1);
  }

  return rv;
}
