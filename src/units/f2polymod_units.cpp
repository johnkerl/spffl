// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2polymod_units.h"
#include "f2poly_factor.h"
#include "f2poly_random.h"
#include "f2poly_totient.h"
#include "int_factor.h"
#include "int_sqrt.h"
#include "tfacinfo.h"
#include "tvector.h"

// ----------------------------------------------------------------
// The simplest algorithm is to loop over all possible exponents from 1
// to the order of the unit group.  Instead, we use Lagrange's theorem,
// testing only divisors of the order of the unit group.

int f2polymod_order(f2polymod_t a) {
  f2poly_t pol1(1);
  f2poly_t r = a.get_residue();
  f2poly_t m = a.get_modulus();
  f2poly_t g = r.gcd(m);

  if (g != pol1) {
    std::cerr << "f2polymod_order:  zero or zero divisor " << r << " mod " << m
              << ".\n";
    exit(1);
  }

  int phi = f2poly_totient(m);
  tfacinfo<int> finfo = int_factor(phi);
  tvector<int> phi_divisors = finfo.get_all_divisors(1);
  int nd = phi_divisors.get_num_elements();
  f2polymod_t one(pol1, m);

  // The output from get_all_divisors is guaranteed to be sorted up.
  // Thus, here we will find the *least* exponent e such that a^e = 1.
  for (int i = 0; i < nd; i++) {
    f2polymod_t ap = a.exp(phi_divisors[i]);
    if (ap == one)
      return phi_divisors[i];
  }

  // By Lagrange's theorem, g^m = 1 for all units g, with m the order
  // of the unit group.  If we've not found the order of a unit,
  // something is wrong.
  std::cout << "f2polymod_order:  Coding error.\n";
  exit(1);
}

// ----------------------------------------------------------------
int f2polymod_find_generator(f2poly_t m, f2polymod_t &rg) {
  int mdeg = m.find_degree();
  f2poly_t gres(1);

  if (mdeg < 1) {
    std::cout << "f2polymod_find_generator:  modulus degree "
              << "must be positive; got " << mdeg << ".\n";
    exit(1);
  }
  int phi = f2poly_totient(m);

  while (gres.find_degree() < mdeg) {
    f2polymod_t g(gres, m);
    if (f2polymod_order(g) == phi) {
      rg = g;
      return 1;
    }
    gres.increment();
  }

  // For irreducible moduli with coefficients in a field, the
  // unit group is cyclic so there is always a generator.
  // Either there is a coding error, the modulus isn't irreducible,
  // or the coefficients don't lie in a field.  Since the latter cases
  // aren't our fault, this situation doesn't merit a fatal error.
  return 0;
}

// ----------------------------------------------------------------
// The naive test is a one-liner:
//   return (f2poly_totient(m) == f2poly_period(m));
// This appears simple, but f2poly_period() will test x^d for all proper
// divisors of phi(m).  For primitivity, it suffices to check only the
// *maximal* proper divisors of phi(m).

int f2poly_is_primitive(f2poly_t m) {
  f2poly_t pol1(1); // 1 as a polynomial.
  f2poly_t polx(1, 0);
  if (polx.gcd(m) != pol1)
    return 0;

  f2polymod_t rcr1(pol1, m); // Equiv. class of 1 in the residue class ring.
  f2polymod_t rcrx(polx, m);

  int phi = f2poly_totient(m);
  tfacinfo<int> finfo = int_factor(phi);
  tvector<int> mpds;
  if (!finfo.get_maximal_proper_divisors(mpds, 1)) {
    // x or x+1 in F2[x].  The former case was already ruled out; the
    // latter is primitive.
    return 1;
  }
  int nmpd = mpds.get_num_elements();
  for (int i = 0; i < nmpd; i++) {
    f2polymod_t rcrxpower = rcrx.exp(mpds[i]);
    if (rcrxpower == rcr1)
      return 0;
  }

  // This can happen when m is reducible.
  f2polymod_t rcrxpower = rcrx.exp(phi);
  if (rcrxpower != rcr1)
    return 0;

  return 1;
}

// ----------------------------------------------------------------
int f2poly_period(f2poly_t m) {
  f2poly_t x(1, 0);
  f2poly_t one(1);
  if (x.gcd(m) != one)
    return 0;
  return f2polymod_order(f2polymod_t(x, m));
}

// ----------------------------------------------------------------
// Lexically lowest
f2poly_t f2poly_find_prim(int degree, int need_irr) {
  f2poly_t rv(0);
  rv.set_bit(degree);
  rv.set_bit(0);

  if (degree < 1) {
    std::cout << "f2poly_find_prim:  degree must be positive; got " << degree
              << ".\n";
    exit(1);
  }

  while (rv.find_degree() == degree) {
    if (f2poly_is_primitive(rv)) {
      if (!need_irr || f2poly_is_irreducible(rv))
        return rv;
    }
    rv.increment();
  }

  // There are irreducibles, and primitive irreducibles, of all positive
  // degrees.  It is an error if we failed to find one.
  std::cout << "f2poly_find_prim:  coding error.\n";
  exit(1);

  return rv;
}

// ----------------------------------------------------------------
f2poly_t f2poly_random_prim(int degree, int need_irr) {
  f2poly_t rv;

  if (degree < 1) {
    std::cout << "f2poly_random_prim:  degree must be positive; "
              << "got " << degree << ".\n";
    exit(1);
  }

  for (;;) {
    rv = f2poly_random(degree);
    if (f2poly_is_primitive(rv)) {
      if (!need_irr || f2poly_is_irreducible(rv))
        return rv;
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
  f2polymod_t elt;
  int idx;
} poly_and_index_t;

static int poly_and_index_qcmp(const void *pv1, const void *pv2) {
  const poly_and_index_t *p1 = (const poly_and_index_t *)pv1;
  const poly_and_index_t *p2 = (const poly_and_index_t *)pv2;
  if (p1->elt < p2->elt)
    return -1;
  if (p1->elt > p2->elt)
    return 1;
  return 0;
}

int f2polymod_log( // Log base g of a.
    f2polymod_t g, f2polymod_t a) {
  int rv = -1;
  f2poly_t m = g.get_modulus();
  int n = 1 << m.find_degree();
  unsigned k = (unsigned)int_sqrt_ceil(n);

  // xxx check gcd(g, m)
  // xxx check gcd(g, a)

  poly_and_index_t *agni = new poly_and_index_t[k];
  poly_and_index_t *gkj = new poly_and_index_t[k];

  f2polymod_t ginv;
  if (!g.recip(ginv)) {
    std::cerr << "f2polymod_log:  g="
              << " is a zero divisor.\n";
    exit(1);
  }
  f2polymod_t gk = g.exp(k);
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
    std::cerr << "f2polymod_log:  error message goes here.\n";
    exit(1);
  }

  delete[] agni;
  delete[] gkj;
  return rv;
}
