// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2n_polymod_units.h"
#include "f2n_poly_totient.h"
#include "int_factor.h"
#include "int_sqrt.h"
#include "tfacinfo.h"
#include "tvector.h"

namespace spffl::units {

// ----------------------------------------------------------------
// The simplest algorithm is to loop over all possible exponents from 1
// to the order of the unit group.  Instead, we use Lagrange's theorem,
// testing only divisors of the order of the unit group.

int f2n_polymod_order(const spffl::polynomials::f2n_polymod_t &a) {
  spffl::polynomials::f2n_poly_t r = a.get_residue();
  spffl::polynomials::f2n_poly_t m = a.get_modulus();
  spffl::polynomials::f2n_poly_t g = r.gcd(m);
  // xxx make-monic method
  g /= g.get_coeff(g.find_degree());
  spffl::polynomials::f2n_poly_t pol1 = m.prime_sfld_elt(1);

  if (g != pol1) {
    std::cerr << "f2n_polymod_order:  zero or zero divisor " << r << " mod "
              << m << ".\n";
    std::cerr << "gcd(" << r << ", " << m << ") = " << g << "\n";
    exit(1);
  }

  int phi                   = spffl::factorization::f2n_poly_totient(m);
  tfacinfo<int> finfo       = spffl::factorization::int_factor(phi);
  tvector<int> phi_divisors = finfo.get_all_divisors(1);
  int nd                    = phi_divisors.get_num_elements();
  spffl::polynomials::f2n_polymod_t one(pol1, m);

  // The output from get_all_divisors is guaranteed to be sorted up.
  // Thus, here we will find the *least* exponent e such that a^e = 1.
  for (int i = 0; i < nd; i++) {
    spffl::polynomials::f2n_polymod_t ap = a.exp(phi_divisors[i]);
    if (ap == one) {
      return phi_divisors[i];
    }
  }

  // By Lagrange's theorem, g^m = 1 for all units g, with m the order
  // of the unit group.  If we've not found the order of a unit,
  // something is wrong.
  std::cout << "f2n_polymod_order:  Coding error.\n";
  exit(1);
}

// ----------------------------------------------------------------
bool f2n_polymod_find_generator(const spffl::polynomials::f2n_poly_t &m,
    spffl::polynomials::f2n_polymod_t &rg) {
  int mdeg                            = m.find_degree();
  spffl::polynomials::f2n_poly_t gres = m.prime_sfld_elt(1);

  if (mdeg < 1) {
    std::cout << "f2n_polymod_find_generator:  modulus degree "
              << "must be positive; got " << mdeg << ".\n";
    exit(1);
  }
  int phi = spffl::factorization::f2n_poly_totient(m);

  while (gres.find_degree() < mdeg) {
    spffl::polynomials::f2n_polymod_t g(gres, m);
    if (f2n_polymod_order(g) == phi) {
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
// This is Shanks' baby-steps-giant-steps technique, as described in Odlyzko's
// 1999 survey paper "Discrete logarithms:  The past and the future".
//
// h = g^(i + jm), where m = ceil sqrt(n), n is the group size, and
// 0 <= i, j <= m - 1.  Compute hg^(-i) and g^(jm); look for a match.
//
// This cuts the naive search (which is O(n)) down to a search of O(sqrt(n)).

typedef struct _poly_and_index_t {
  spffl::polynomials::f2n_polymod_t elt;
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

int f2n_polymod_log( // Log base g of a.
    const spffl::polynomials::f2n_polymod_t &g,
    const spffl::polynomials::f2n_polymod_t &a) {
  std::cout << "\n";
  std::cout << "g = " << g << "\n";
  std::cout << "a = " << a << "\n";
  int rv                           = -1;
  spffl::polynomials::f2n_poly_t m = g.get_modulus();
  std::cout << "m = " << m << "\n";
  int n = 1 << m.find_degree();
  std::cout << "n = " << n << "\n";
  unsigned k = (unsigned)spffl::intmath::int_sqrt_ceil(n);
  std::cout << "k = " << k << "\n";

  // xxx check gcd(g, m)
  // xxx check gcd(g, a)

  poly_and_index_t *agni = new poly_and_index_t[k];
  poly_and_index_t *gkj  = new poly_and_index_t[k];

  spffl::polynomials::f2n_polymod_t ginv;
  if (!g.recip(ginv)) {
    std::cerr << "f2n_polymod_log:  g="
              << " is a zero divisor.\n";
    exit(1);
  }
  std::cout << "gi = " << ginv << "\n";
  spffl::polynomials::f2n_polymod_t gk = g.exp(k);
  std::cout << "gk = " << gk << "\n";
  unsigned i, j;

  agni[0].elt = a;
  agni[0].idx = 0;
  gkj[0].elt  = g / g;
  gkj[0].idx  = 0;

  std::cout << "agni[" << 0 << "] = " << agni[0].elt << "\n";
  for (i = 1; i < k; i++) {
    agni[i].elt = agni[i - 1].elt * ginv;
    agni[i].idx = i;
    std::cout << "agni[" << i << "] = " << agni[i].elt << "\n";
  }
  std::cout << "gk[" << 0 << "]  = " << gkj[0].elt << "\n";
  for (j = 1; j < k; j++) {
    gkj[j].elt = gkj[j - 1].elt * gk;
    gkj[j].idx = j;
    std::cout << "gk[" << j << "]  = " << gkj[j].elt << "\n";
  }

  qsort(agni, k, sizeof(poly_and_index_t), poly_and_index_qcmp);
  qsort(gkj, k, sizeof(poly_and_index_t), poly_and_index_qcmp);
  for (j = 0; j < k; j++) {
    std::cout << "-- agni[" << j << "] = " << agni[j].elt << " gk[" << j
              << "] = " << gkj[j].elt << "\n";
  }

  for (i = 0, j = 0; i < k && j < k;) {
    std::cout << "agni[" << i << "] = " << agni[i].elt << " gk[" << j
              << "] = " << gkj[j].elt << "\n";
    if (agni[i].elt == gkj[j].elt) {
      // xxx could overflow 32-bit int; fix me.
      std::cout << "found at i=" << i << " j=" << j << "\n";
      rv = agni[i].idx + gkj[j].idx * k;
      break;
    } else if (agni[i].elt < gkj[j].elt) {
      i++;
    } else {
      j++;
    }
  }

  if (rv == -1) {
    std::cerr << "f2n_polymod_log:  couldn't find log base " << g << " of " << a
              << " mod " << m << ".\n";
    exit(1);
  }

  delete[] agni;
  delete[] gkj;
  return rv;
}

} // namespace spffl::units
