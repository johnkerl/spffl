// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "spffl/units/f2_polymod_units.h"
#include "spffl/base/spffl_exception.h"
#include "spffl/containers/tfacinfo.h"
#include "spffl/containers/vector_over.h"
#include "spffl/factorization/f2_poly_factor.h"
#include "spffl/factorization/f2_poly_totient.h"
#include "spffl/factorization/int_factor.h"
#include "spffl/intmath/int_sqrt.h"
#include "spffl/random/f2_poly_random.h"

namespace spffl::units {

// ----------------------------------------------------------------
// The simplest algorithm is to loop over all possible exponents from 1
// to the order of the unit group.  Instead, we use Lagrange's theorem,
// testing only divisors of the order of the unit group.

int f2_polymod_order(spffl::polynomials::f2_polymod_t a) {
  spffl::polynomials::f2_poly_t pol1(1);
  spffl::polynomials::f2_poly_t r = a.get_residue();
  spffl::polynomials::f2_poly_t m = a.get_modulus();
  spffl::polynomials::f2_poly_t g = r.gcd(m);

  if (g != pol1) {
    std::stringstream ss;
    ss << "f2_polymod_order:  zero or zero divisor " << r << " mod " << m << ".\n";
    throw spffl::exception_t(ss.str());
  }

  int phi = spffl::factorization::f2_poly_totient(m);
  tfacinfo<int> finfo = spffl::factorization::int_factor(phi);
  spffl::containers::vector_over<int> phi_divisors = finfo.get_all_divisors(1);
  int nd = phi_divisors.get_num_elements();
  spffl::polynomials::f2_polymod_t one(pol1, m);

  // The output from get_all_divisors is guaranteed to be sorted up.
  // Thus, here we will find the *least* exponent e such that a^e = 1.
  for (int i = 0; i < nd; i++) {
    spffl::polynomials::f2_polymod_t ap = a.exp(phi_divisors[i]);
    if (ap == one) {
      return phi_divisors[i];
    }
  }

  // By Lagrange's theorem, g^m = 1 for all units g, with m the order
  // of the unit group.  If we've not found the order of a unit,
  // something is wrong.
  std::stringstream ss;
  ss << "f2_polymod_order:  Coding error.\n";
  throw spffl::exception_t(ss.str());
}

// ----------------------------------------------------------------
bool f2_polymod_find_generator(
  spffl::polynomials::f2_poly_t m, spffl::polynomials::f2_polymod_t &rg) {
  int mdeg = m.find_degree();
  spffl::polynomials::f2_poly_t gres(1);

  if (mdeg < 1) {
    std::stringstream ss;
    ss << "f2_polymod_find_generator:  modulus degree "
       << "must be positive; got " << mdeg << ".\n";
    throw spffl::exception_t(ss.str());
  }
  int phi = spffl::factorization::f2_poly_totient(m);

  while (gres.find_degree() < mdeg) {
    spffl::polynomials::f2_polymod_t g(gres, m);
    if (f2_polymod_order(g) == phi) {
      rg = g;
      return true;
    }
    gres.increment();
  }

  // For irreducible moduli with coefficients in a field, the
  // unit group is cyclic so there is always a generator.
  // Either there is a coding error, the modulus isn't irreducible,
  // or the coefficients don't lie in a field.  Since the latter cases
  // aren't our fault, this situation doesn't merit a fatal error.
  return false;
}

// ----------------------------------------------------------------
// The naive test is a one-liner:
//   return (spffl::factorization::f2_poly_totient(m) == f2_poly_period(m));
// This appears simple, but f2_poly_period() will test x^d for all proper
// divisors of phi(m).  For primitivity, it suffices to check only the
// *maximal* proper divisors of phi(m).

bool f2_poly_is_primitive(spffl::polynomials::f2_poly_t m) {
  spffl::polynomials::f2_poly_t pol1(1); // 1 as a polynomial.
  spffl::polynomials::f2_poly_t polx(1, 0);
  if (polx.gcd(m) != pol1) {
    return false;
  }

  spffl::polynomials::f2_polymod_t rcr1(pol1, m); // Equiv. class of 1 in the residue class ring.
  spffl::polynomials::f2_polymod_t rcrx(polx, m);

  int phi = spffl::factorization::f2_poly_totient(m);
  tfacinfo<int> finfo = spffl::factorization::int_factor(phi);
  spffl::containers::vector_over<int> mpds;
  if (!finfo.get_maximal_proper_divisors(mpds, 1)) {
    // x or x+1 in F2[x].  The former case was already ruled out; the
    // latter is primitive.
    return true;
  }
  int nmpd = mpds.get_num_elements();
  for (int i = 0; i < nmpd; i++) {
    spffl::polynomials::f2_polymod_t rcrxpower = rcrx.exp(mpds[i]);
    if (rcrxpower == rcr1) {
      return false;
    }
  }

  // This can happen when m is reducible.
  spffl::polynomials::f2_polymod_t rcrxpower = rcrx.exp(phi);
  if (rcrxpower != rcr1) {
    return false;
  }

  return true;
}

// ----------------------------------------------------------------
int f2_poly_period(spffl::polynomials::f2_poly_t m) {
  spffl::polynomials::f2_poly_t x(1, 0);
  spffl::polynomials::f2_poly_t one(1);
  if (x.gcd(m) != one) {
    return 0;
  }
  return f2_polymod_order(spffl::polynomials::f2_polymod_t(x, m));
}

// ----------------------------------------------------------------
// Lexically lowest
spffl::polynomials::f2_poly_t f2_poly_find_prim(int degree, int need_irr) {
  spffl::polynomials::f2_poly_t rv(0);
  rv.set_bit(degree);
  rv.set_bit(0);

  if (degree < 1) {
    std::stringstream ss;
    ss << "f2_poly_find_prim:  degree must be positive; got " << degree << ".\n";
    throw spffl::exception_t(ss.str());
  }

  while (rv.find_degree() == degree) {
    if (f2_poly_is_primitive(rv)) {
      if (!need_irr || spffl::factorization::f2_poly_is_irreducible(rv)) {
        return rv;
      }
    }
    rv.increment();
  }

  // There are irreducibles, and primitive irreducibles, of all positive
  // degrees.  It is an error if we failed to find one.
  std::stringstream ss;
  ss << "f2_poly_find_prim:  coding error.\n";
  throw spffl::exception_t(ss.str());

  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::f2_poly_t f2_poly_random_prim(int degree, int need_irr) {
  spffl::polynomials::f2_poly_t rv;

  if (degree < 1) {
    std::stringstream ss;
    ss << "f2_poly_random_prim:  degree must be positive; "
       << "got " << degree << ".\n";
    throw spffl::exception_t(ss.str());
  }

  for (;;) {
    rv = spffl::random::f2_poly_random(degree);
    if (f2_poly_is_primitive(rv)) {
      if (!need_irr || spffl::factorization::f2_poly_is_irreducible(rv)) {
        return rv;
      }
    }
  }
}

// ----------------------------------------------------------------
// This is Shanks' baby-steps-giant-steps technique, as described in Odlyzko's
// 1999 survey paper "Discrete logarithms:  The past and the future".
//
// h = g^(i + jm), where m = ceil sqrt(n), n is the group size, and
// 0 <= i, j <= m - 1.  Compute hg^(-i) and g^(jm); look for a match.
//
// This cuts the naive search (which is O(n)) down to a search of O(sqrt(n)).

typedef struct _poly_and_index_t {
  spffl::polynomials::f2_polymod_t elt;
  int idx;
} poly_and_index_t;

static int poly_and_index_qcmp(const void *pv1, const void *pv2) {
  const poly_and_index_t *p1 = (const poly_and_index_t *)pv1;
  const poly_and_index_t *p2 = (const poly_and_index_t *)pv2;
  if (p1->elt < p2->elt) {
    return -1;
  }
  if (p1->elt > p2->elt) {
    return 1;
  }
  return 0;
}

int f2_polymod_log( // Log base g of a.
  spffl::polynomials::f2_polymod_t g, spffl::polynomials::f2_polymod_t a) {
  int rv = -1;
  spffl::polynomials::f2_poly_t m = g.get_modulus();
  int n = 1 << m.find_degree();
  unsigned k = (unsigned)spffl::intmath::int_sqrt_ceil(n);

  // xxx check gcd(g, m)
  // xxx check gcd(g, a)

  poly_and_index_t *agni = new poly_and_index_t[k];
  poly_and_index_t *gkj = new poly_and_index_t[k];

  spffl::polynomials::f2_polymod_t ginv;
  if (!g.recip(ginv)) {
    std::stringstream ss;
    ss << "f2_polymod_log:  g="
       << " is a zero divisor.\n";
    throw spffl::exception_t(ss.str());
  }
  spffl::polynomials::f2_polymod_t gk = g.exp(k);
  unsigned i, j;

  agni[0].elt = a;
  agni[0].idx = 0;
  gkj[0].elt = g / g;
  gkj[0].idx = 0;

  for (i = 1; i < k; i++) {
    agni[i].elt = agni[i - 1].elt * ginv;
    agni[i].idx = i;
  }
  for (j = 1; j < k; j++) {
    gkj[j].elt = gkj[j - 1].elt * gk;
    gkj[j].idx = j;
  }

  qsort(agni, k, sizeof(poly_and_index_t), poly_and_index_qcmp);
  qsort(gkj, k, sizeof(poly_and_index_t), poly_and_index_qcmp);

  for (i = 0, j = 0; i < k && j < k;) {
    if (agni[i].elt == gkj[j].elt) {
      // xxx could overflow 32-bit int; fix me.
      rv = agni[i].idx + gkj[j].idx * k;
      break;
    } else if (agni[i].elt < gkj[j].elt) {
      i++;
    } else {
      j++;
    }
  }

  if (rv == -1) {
    // xxx
    std::stringstream ss;
    ss << "f2_polymod_log:  error message goes here.\n";
    throw spffl::exception_t(ss.str());
  }

  delete[] agni;
  delete[] gkj;
  return rv;
}

} // namespace spffl::units
