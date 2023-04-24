// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fp_units.h"
#include "int_factor.h"
#include "int_gcd.h"
#include "int_sqrt.h"
#include "int_totient.h"
#include "tfacinfo.h"
#include "tvector.h"

namespace spffl::units {

// ----------------------------------------------------------------
// The simplest algorithm is to loop over all possible exponents from 1
// to the order of the unit group.  Instead, we use Lagrange's theorem,
// testing only divisors of the order of the unit group.

int fp_order(spffl::intmath::intmod_t a) {
  int r = a.get_residue();
  int p = a.get_modulus();
  int g = spffl::intmath::int_gcd(r, p);

  if (g != 1) {
    std::cerr << "fp_order:  zero or zero divisor " << r << " mod " << p
              << ".\n";
    exit(1);
  }

  int phi = spffl::intmath::int_totient(p);
  tfacinfo<int> finfo = spffl::factorization::int_factor(phi);
  tvector<int> phi_divisors = finfo.get_all_divisors(1);
  int nd = phi_divisors.get_num_elements();
  spffl::intmath::intmod_t one(1, p);

  // The output from get_all_divisors is guaranteed to be sorted up.
  // Thus, here we will find the *least* exponent e such that a^e = 1.
  for (int i = 0; i < nd; i++) {
    spffl::intmath::intmod_t ap = a.exp(phi_divisors[i]);
    if (ap == one)
      return phi_divisors[i];
  }

  // By Lagrange's theorem, g^m = 1 for all units g, with m the order
  // of the unit group.  If we've not found the order of a unit,
  // something is wrong.
  std::cout << "fp_order:  Coding error.\n";
  exit(1);
}

// ----------------------------------------------------------------
int fp_find_generator(int p, spffl::intmath::intmod_t &rg) {
  int gres;
  int phi = spffl::intmath::int_totient(p);

  for (gres = 1; gres < p; gres++) {
    if (spffl::intmath::int_gcd(gres, p) != 1)
      continue;

    spffl::intmath::intmod_t g(gres, p);
    if (fp_order(g) == phi) {
      rg = g;
      return 1;
    }
  }

  // Not necessarily a coding error on our part, since p is not
  // guaranteed to be prime.
  return 0;
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
  spffl::intmath::intmod_t elt;
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

int fp_log( // Log base g of a.
    spffl::intmath::intmod_t g, spffl::intmath::intmod_t a) {
  int rv = -1;
  int p = g.get_modulus();
  unsigned k = (unsigned)spffl::intmath::int_sqrt_ceil(p);

  // xxx check gcd(g, p)
  // xxx check gcd(g, a)

  poly_and_index_t *agni = new poly_and_index_t[k];
  poly_and_index_t *gkj = new poly_and_index_t[k];

  spffl::intmath::intmod_t ginv;
  if (!g.recip(ginv)) {
    std::cerr << "fp_log:  g="
              << " is a zero divisor.\n";
    exit(1);
  }
  spffl::intmath::intmod_t gk = g.exp(k);
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
    std::cerr << "fp_log:  error message goes here.\n";
    exit(1);
  }

  delete[] agni;
  delete[] gkj;
  return rv % spffl::intmath::int_totient(p);
}

} // namespace
