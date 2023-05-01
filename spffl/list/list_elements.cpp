// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "list/list_elements.h"
#include "base/spffl_exception.h"
#include "factorization/f2_poly_totient.h"
#include "factorization/f2n_poly_totient.h"
#include "factorization/fp_poly_totient.h"
#include "intmath/int_gcd.h"
#include "intmath/int_power.h"
#include "intmath/int_totient.h"

namespace spffl::list {

// ----------------------------------------------------------------
tvector<spffl::polynomials::f2_poly_t> f2_poly_list(int deg) {
  int nel = 1 << deg;
  tvector<spffl::polynomials::f2_poly_t> rv(nel);

  int i;
  spffl::polynomials::f2_poly_t min(0);
  spffl::polynomials::f2_poly_t max(0);
  spffl::polynomials::f2_poly_t r;
  min.set_bit(deg);
  max.set_bit(deg + 1);

  for (r = min, i = 0; r < max; r.increment(), i++) {
    rv[i] = r;
  }

  return rv;
}

// ----------------------------------------------------------------
tvector<spffl::polynomials::f2n_poly_t> f2n_poly_list(
    spffl::polynomials::f2_poly_t im, int outerdeg) {
  int innerdeg = im.find_degree();
  int q        = 1 << innerdeg;
  int nel      = (q - 1) * spffl::intmath::int_power(q, outerdeg);
  tvector<spffl::polynomials::f2n_poly_t> rv(nel);

  int i;
  spffl::polynomials::f2_polymod_t zero(spffl::polynomials::f2_poly_t(0), im);
  spffl::polynomials::f2_polymod_t one(spffl::polynomials::f2_poly_t(1), im);
  spffl::polynomials::f2n_poly_t r;
  spffl::polynomials::f2n_poly_t min(zero);
  spffl::polynomials::f2n_poly_t max(zero);
  min.set_coeff(outerdeg, one);
  max.set_coeff(outerdeg + 1, one);

  for (r = min, i = 0; r < max; r.increment(), i++) {
    rv[i] = r;
  }

  return rv;
}

// ----------------------------------------------------------------
tvector<spffl::polynomials::fp_poly_t> fp_poly_list(int p, int deg) {
  int nel = (p - 1) * spffl::intmath::int_power(p, deg);
  tvector<spffl::polynomials::fp_poly_t> rv(nel);

  int i;
  spffl::intmath::intmod_t zero(0, p), one(1, p);
  spffl::polynomials::fp_poly_t min(zero);
  spffl::polynomials::fp_poly_t max(zero);
  spffl::polynomials::fp_poly_t r;

  min.set_coeff(deg, one);
  max.set_coeff(deg + 1, one);

  for (r = min, i = 0; r < max; r.increment(), i++) {
    rv[i] = r;
  }

  return rv;
}

// ----------------------------------------------------------------
tvector<spffl::intmath::intmod_t> intmod_list(int p, sp_list_type_t type) {
  int nel;
  if (type == SP_LIST_ALL) {
    nel = p;
  } else if (type == SP_LIST_UNITS) {
    nel = spffl::intmath::int_totient(p);
  } else if (type == SP_LIST_NON_UNITS) {
    nel = p - spffl::intmath::int_totient(p);
  } else {
    std::stringstream ss;
    ss << "intmod_list:  unhandled code option.\n";
    throw spffl::exception_t(ss.str());
  }
  tvector<spffl::intmath::intmod_t> rv(nel);
  if (type == SP_LIST_UNITS) {
    int i, j;
    for (i = 0, j = 0; i < p; i++) {
      if (spffl::intmath::int_gcd(i, p) == 1) {
        rv[j++] = spffl::intmath::intmod_t(i, p);
      }
    }
  } else if (type == SP_LIST_NON_UNITS) {
    int i, j;
    for (i = 0, j = 0; i < p; i++) {
      if (spffl::intmath::int_gcd(i, p) != 1) {
        rv[j++] = spffl::intmath::intmod_t(i, p);
      }
    }
  } else {
    for (int i = 0; i < p; i++) {
      rv[i] = spffl::intmath::intmod_t(i, p);
    }
  }
  return rv;
}

// ----------------------------------------------------------------
tvector<spffl::polynomials::f2_polymod_t> f2_polymod_list(
    spffl::polynomials::f2_poly_t m, sp_list_type_t type) {
  int deg = m.find_degree();
  int nel;
  if (type == SP_LIST_ALL) {
    nel = 1 << deg;
  } else if (type == SP_LIST_UNITS) {
    nel = spffl::factorization::f2_poly_totient(m);
  } else if (type == SP_LIST_NON_UNITS) {
    nel = (1 << deg) - spffl::factorization::f2_poly_totient(m);
  } else {
    std::stringstream ss;
    ss << "f2_polymod_list:  unhandled code option.\n";
    throw spffl::exception_t(ss.str());
  }
  tvector<spffl::polynomials::f2_polymod_t> rv(nel);

  int i;
  spffl::polynomials::f2_poly_t zero(0);
  spffl::polynomials::f2_poly_t min(0);
  spffl::polynomials::f2_poly_t max(0);
  spffl::polynomials::f2_poly_t r;
  max.set_bit(deg);

  if (type == SP_LIST_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      spffl::polynomials::f2_poly_t g = r.gcd(m);
      if ((g.find_degree() == 0) && (g != zero)) {
        rv[i++] = spffl::polynomials::f2_polymod_t(r, m);
      }
    }
  } else if (type == SP_LIST_NON_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      spffl::polynomials::f2_poly_t g = r.gcd(m);
      if ((g.find_degree() != 0) || (g == zero)) {
        rv[i++] = spffl::polynomials::f2_polymod_t(r, m);
      }
    }
  } else {
    for (r = min, i = 0; r < max; r.increment(), i++) {
      rv[i] = spffl::polynomials::f2_polymod_t(r, m);
    }
  }

  return rv;
}

// ----------------------------------------------------------------
tvector<spffl::polynomials::f2n_polymod_t> f2n_polymod_list(
    spffl::polynomials::f2n_poly_t om, sp_list_type_t type) {
  spffl::polynomials::f2_polymod_t c0 = om.get_coeff(0);
  spffl::polynomials::f2_poly_t im    = c0.get_modulus();
  int outerdeg                        = om.find_degree();
  int innerdeg                        = im.find_degree();
  int nel;
  if (type == SP_LIST_ALL) {
    nel = 1 << (outerdeg * innerdeg);
  } else if (type == SP_LIST_UNITS) {
    nel = spffl::factorization::f2n_poly_totient(om);
  } else if (type == SP_LIST_NON_UNITS) {
    nel = (1 << (outerdeg * innerdeg)) -
          spffl::factorization::f2n_poly_totient(om);
  } else {
    std::stringstream ss;
    ss << "f2n_polymod_list:  unhandled code option.\n";
    throw spffl::exception_t(ss.str());
  }
  tvector<spffl::polynomials::f2n_polymod_t> rv(nel);

  int i;
  spffl::polynomials::f2_polymod_t zero = c0.prime_subfield_element(0);
  spffl::polynomials::f2_polymod_t one  = c0.prime_subfield_element(1);
  spffl::polynomials::f2n_poly_t min(zero);
  spffl::polynomials::f2n_poly_t max(zero);
  spffl::polynomials::f2n_poly_t r;
  max.set_coeff(outerdeg, one);

  if (type == SP_LIST_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      spffl::polynomials::f2n_poly_t g = r.gcd(om);
      if ((g.find_degree() == 0) && (g != zero)) {
        rv[i++] = spffl::polynomials::f2n_polymod_t(r, om);
      }
    }
  } else if (type == SP_LIST_NON_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      spffl::polynomials::f2n_poly_t g = r.gcd(om);
      if ((g.find_degree() != 0) || (g == zero)) {
        rv[i++] = spffl::polynomials::f2n_polymod_t(r, om);
      }
    }
  } else {
    for (r = min, i = 0; r < max; r.increment(), i++) {
      rv[i] = spffl::polynomials::f2n_polymod_t(r, om);
    }
  }

  return rv;
}

// ----------------------------------------------------------------
tvector<spffl::polynomials::fp_polymod_t> fp_polymod_list(
    spffl::polynomials::fp_poly_t m, sp_list_type_t type) {
  int p = m.get_characteristic();
  int n = m.find_degree();
  int nel;
  if (type == SP_LIST_ALL) {
    nel = spffl::intmath::int_power(p, n);
  } else if (type == SP_LIST_UNITS) {
    nel = spffl::factorization::fp_poly_totient(m);
  } else if (type == SP_LIST_NON_UNITS) {
    nel = spffl::intmath::int_power(p, n) -
          spffl::factorization::fp_poly_totient(m);
  } else {
    std::stringstream ss;
    ss << "fp_polymod_list:  unhandled code option.\n";
    throw spffl::exception_t(ss.str());
  }
  tvector<spffl::polynomials::fp_polymod_t> rv(nel);

  int i;
  spffl::intmath::intmod_t zero(0, p), one(1, p);
  spffl::polynomials::fp_poly_t min(zero);
  spffl::polynomials::fp_poly_t max(zero);
  spffl::polynomials::fp_poly_t r;
  max.set_coeff(n, one);

  if (type == SP_LIST_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      spffl::polynomials::fp_poly_t g = r.gcd(m);
      if ((g.find_degree() == 0) && (g != zero)) {
        rv[i++] = spffl::polynomials::fp_polymod_t(r, m);
      }
    }
  } else if (type == SP_LIST_NON_UNITS) {
    for (r = min, i = 0; r < max; r.increment()) {
      spffl::polynomials::fp_poly_t g = r.gcd(m);
      if ((g.find_degree() != 0) || (g == zero)) {
        rv[i++] = spffl::polynomials::fp_polymod_t(r, m);
      }
    }
  } else {
    for (r = min, i = 0; r < max; r.increment(), i++) {
      rv[i] = spffl::polynomials::fp_polymod_t(r, m);
    }
  }

  return rv;
}

// ----------------------------------------------------------------
tvector<spffl::polynomials::f2_polymod_t> f2_polymod_glist(
    spffl::polynomials::f2_polymod_t g, sp_list_type_t type) {
  spffl::polynomials::f2_poly_t m    = g.get_modulus();
  spffl::polynomials::f2_poly_t gres = g.get_residue();
  spffl::polynomials::f2_poly_t gr   = m.gcd(gres);
  int deg                            = m.find_degree();
  int maxnel                         = 1 << deg;
  tvector<spffl::polynomials::f2_polymod_t> rv(maxnel);
  int nel = 0;
  spffl::polynomials::f2_poly_t r;
  spffl::polynomials::f2_poly_t zero(0);
  spffl::polynomials::f2_poly_t min(0);
  spffl::polynomials::f2_poly_t max(0);
  max.set_bit(deg);

  if (type == SP_LIST_MULTIPLES) {
    for (r = min; r < max; r.increment()) {
      if ((r % gr) == zero) {
        rv[nel++] = spffl::polynomials::f2_polymod_t(r, m);
      }
    }
  }

  else if (type == SP_LIST_REL_PRIME) {
    for (r = min; r < max; r.increment()) {
      spffl::polynomials::f2_poly_t d = r.gcd(gr);
      if ((d.find_degree() == 0) && (d != zero)) {
        rv[nel++] = spffl::polynomials::f2_polymod_t(r, m);
      }
    }
  }

  rv.trim_num_elements(nel);
  return rv;
}

// ----------------------------------------------------------------
tvector<spffl::intmath::intmod_t> intmod_glist(
    spffl::intmath::intmod_t g, sp_list_type_t type) {
  int m  = g.get_modulus();
  int gr = spffl::intmath::int_gcd(m, g.get_residue());
  tvector<spffl::intmath::intmod_t> rv(m);
  int nel = 0;

  if (type == SP_LIST_MULTIPLES) {
    for (int r = 0; r < m; r++) {
      if ((r % gr) == 0) {
        rv[nel++] = spffl::intmath::intmod_t(r, m);
      }
    }
  } else if (type == SP_LIST_REL_PRIME) {
    for (int r = 0; r < m; r++) {
      if (spffl::intmath::int_gcd(r, gr) == 1) {
        rv[nel++] = spffl::intmath::intmod_t(r, m);
      }
    }
  }

  rv.trim_num_elements(nel);
  return rv;
}

// ----------------------------------------------------------------
tmatrix<spffl::polynomials::f2_polymod_t> f2_polymod_An_list(
    spffl::polynomials::f2_poly_t m, int n) {
  int d  = m.find_degree();
  int q  = 1 << d;
  int qn = spffl::intmath::int_power(q, n);
  tmatrix<spffl::polynomials::f2_polymod_t> rv(qn, n);
  int i, j;

  tvector<spffl::polynomials::f2_polymod_t> Fq =
      f2_polymod_list(m, SP_LIST_ALL);

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

tmatrix<spffl::polynomials::f2_polymod_t> f2_polymod_Pn_list(
    spffl::polynomials::f2_poly_t m, int n) {
  int i, j, k;
  int d = m.find_degree();
  int q = 1 << d;
  tvector<spffl::polynomials::f2_polymod_t> Fq =
      f2_polymod_list(m, SP_LIST_ALL);
  spffl::polynomials::f2_polymod_t zero =
      spffl::polynomials::f2_polymod_t::prime_subfield_element(0, m);
  spffl::polynomials::f2_polymod_t one =
      spffl::polynomials::f2_polymod_t::prime_subfield_element(1, m);

  int oP = 0;
  for (k = 0; k <= n; k++) {
    oP += spffl::intmath::int_power(q, k);
  }
  tmatrix<spffl::polynomials::f2_polymod_t> rv(oP, n + 1);

  int didx = 0;
  for (k = 0; k <= n; k++) {
    int qk = spffl::intmath::int_power(q, k);
    for (i = 0; i < qk; i++) {
      int baserep = i;
      for (j = 0; j < k; j++) {
        rv[didx][k - j - 1] = Fq[baserep % q];
        baserep /= q;
      }
      rv[didx][k] = one;
      for (j = k + 1; j <= n; j++) {
        rv[didx][j] = zero;
      }
      didx++;
    }
  }

  if (didx != oP) {
    std::stringstream ss;
    ss << "Pn_Fq_list:  coding error.\n";
    throw spffl::exception_t(ss.str());
  }

  return rv;
}

// ----------------------------------------------------------------
tmatrix<spffl::polynomials::fp_polymod_t> fp_polymod_An_list(
    spffl::polynomials::fp_poly_t m, int n) {
  int d  = m.find_degree();
  int p  = m.get_characteristic();
  int q  = spffl::intmath::int_power(p, d);
  int qn = spffl::intmath::int_power(q, n);
  tmatrix<spffl::polynomials::fp_polymod_t> rv(qn, n);
  int i, j;

  tvector<spffl::polynomials::fp_polymod_t> Fq =
      fp_polymod_list(m, SP_LIST_ALL);

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

tmatrix<spffl::polynomials::fp_polymod_t> fp_polymod_Pn_list(
    spffl::polynomials::fp_poly_t m, int n) {
  int i, j, k;
  int d = m.find_degree();
  int p = m.get_characteristic();
  int q = spffl::intmath::int_power(p, d);
  tvector<spffl::polynomials::fp_polymod_t> Fq =
      fp_polymod_list(m, SP_LIST_ALL);
  spffl::polynomials::fp_polymod_t zero =
      spffl::polynomials::fp_polymod_t::prime_subfield_element(0, m);
  spffl::polynomials::fp_polymod_t one =
      spffl::polynomials::fp_polymod_t::prime_subfield_element(1, m);

  int oP = 0;
  for (k = 0; k <= n; k++) {
    oP += spffl::intmath::int_power(q, k);
  }
  tmatrix<spffl::polynomials::fp_polymod_t> rv(oP, n + 1);

  int didx = 0;
  for (k = 0; k <= n; k++) {
    int qk = spffl::intmath::int_power(q, k);
    for (i = 0; i < qk; i++) {
      int baserep = i;
      for (j = 0; j < k; j++) {
        rv[didx][k - j - 1] = Fq[baserep % q];
        baserep /= q;
      }
      rv[didx][k] = one;
      for (j = k + 1; j <= n; j++) {
        rv[didx][j] = zero;
      }
      didx++;
    }
  }

  if (didx != oP) {
    std::stringstream ss;
    ss << "Pn_Fq_list:  coding error.\n";
    throw spffl::exception_t(ss.str());
  }

  return rv;
}

} // namespace spffl::list
