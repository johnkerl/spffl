// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2npolymod_units.h"
#include "f2npoly_totient.h"
#include "tvector.h"
#include "tfacinfo.h"
#include "int_factor.h"
#include "int_sqrt.h"

// ----------------------------------------------------------------
// The simplest algorithm is to loop over all possible exponents from 1
// to the order of the unit group.  Instead, we use Lagrange's theorem,
// testing only divisors of the order of the unit group.

int f2npolymod_order(
	f2npolymod_t a)
{
	f2npoly_t r = a.get_residue();
	f2npoly_t m = a.get_modulus();
	f2npoly_t g = r.gcd(m);
	// xxx make-monic method
	g /= g.get_coeff(g.find_degree());
	f2npoly_t pol1 = m.prime_sfld_elt(1);

	if (g != pol1) {
		std::cerr << "f2npolymod_order:  zero or zero divisor "
			<< r << " mod " << m << ".\n";
		std::cerr << "gcd(" << r << ", " << m << ") = " << g << "\n";
		exit(1);
	}

	int phi = f2npoly_totient(m);
	tfacinfo<int> finfo = int_factor(phi);
	tvector<int> phi_divisors = finfo.get_all_divisors(1);
	int nd = phi_divisors.get_num_elements();
	f2npolymod_t one(pol1, m);

	// The output from get_all_divisors is guaranteed to be sorted up.
	// Thus, here we will find the *least* exponent e such that a^e = 1.
	for (int i = 0; i < nd; i++) {
		f2npolymod_t ap = a.exp(phi_divisors[i]);
		if (ap == one)
			return phi_divisors[i];
	}

	// By Lagrange's theorem, g^m = 1 for all units g, with m the order
	// of the unit group.  If we've not found the order of a unit,
	// something is wrong.
	std::cout << "f2npolymod_order:  Coding error.\n";
	exit(1);
}

// ----------------------------------------------------------------
int f2npolymod_find_generator(
	f2npoly_t m,
	f2npolymod_t & rg)
{
	int mdeg = m.find_degree();
	f2npoly_t gres = m.prime_sfld_elt(1);

	if (mdeg < 1) {
		std::cout << "f2npolymod_find_generator:  modulus degree "
			<< "must be positive; got " << mdeg << ".\n";
		exit(1);
	}
	int phi = f2npoly_totient(m);

	while (gres.find_degree() < mdeg) {
		f2npolymod_t g(gres, m);
		if (f2npolymod_order(g) == phi) {
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
// This is Shanks' baby-steps-giant-steps technique, as described in Odlyzko's
// 1999 survey paper "Discrete logarithms:  The past and the future".
//
// h = g^(i + jm), where m = ceil sqrt(n), n is the group size, and
// 0 <= i, j <= m - 1.  Compute hg^(-i) and g^(jm); look for a match.
//
// This cuts the naive search (which is O(n)) down to a search of O(sqrt(n)).

typedef struct _poly_and_index_t {
	f2npolymod_t elt;
	int         idx;
} poly_and_index_t;

static int poly_and_index_qcmp(const void * pv1, const void * pv2)
{
	const poly_and_index_t * p1 = (const poly_and_index_t *)pv1;
	const poly_and_index_t * p2 = (const poly_and_index_t *)pv2;
	if (p1->elt < p2->elt)
		return -1;
	if (p1->elt > p2->elt)
		return 1;
	return 0;
}

int f2npolymod_log( // Log base g of a.
	f2npolymod_t g,
	f2npolymod_t a)
{
std::cout << "\n";
std::cout << "g = " << g << "\n";
std::cout << "a = " << a << "\n";
	int rv = -1;
	f2npoly_t m = g.get_modulus();
std::cout << "m = " << m << "\n";
	int n = 1 << m.find_degree();
std::cout << "n = " << n << "\n";
	unsigned k = (unsigned)int_sqrt(n, ICEIL);
std::cout << "k = " << k << "\n";

	// xxx check gcd(g, m)
	// xxx check gcd(g, a)

	poly_and_index_t * agni = new poly_and_index_t[k];
	poly_and_index_t * gkj  = new poly_and_index_t[k];

	f2npolymod_t ginv;
	if (!g.recip(ginv)) {
		std::cerr << "f2npolymod_log:  g=" << " is a zero divisor.\n";
		exit(1);
	}
std::cout << "gi = " << ginv << "\n";
	f2npolymod_t gk = g.exp(k);
std::cout << "gk = " << gk << "\n";
	unsigned i, j;

	agni[0].elt = a;
	agni[0].idx = 0;
	gkj [0].elt = g / g;
	gkj [0].idx = 0;

std::cout << "agni["<<0<<"] = " << agni[0].elt << "\n";
	for (i = 1; i < k; i++) {
		agni[i].elt = agni[i-1].elt * ginv;
		agni[i].idx = i;
std::cout << "agni["<<i<<"] = " << agni[i].elt << "\n";
	}
std::cout << "gk["<<0<<"]  = " << gkj[0].elt << "\n";
	for (j = 1; j < k; j++) {
		gkj[j].elt = gkj[j-1].elt * gk;
		gkj[j].idx = j;
std::cout << "gk["<<j<<"]  = " << gkj[j].elt << "\n";
	}

	qsort(agni, k, sizeof(poly_and_index_t), poly_and_index_qcmp);
	qsort(gkj,  k, sizeof(poly_and_index_t), poly_and_index_qcmp);
	for (j = 0; j < k; j++) {
std::cout << "-- agni["<<j<<"] = " << agni[j].elt << " gk["<<j<<"] = " << gkj[j].elt << "\n";
	}

	for (i = 0, j = 0; i < k && j < k; ) {
std::cout << "agni["<<i<<"] = " << agni[i].elt << " gk["<<j<<"] = " << gkj[j].elt << "\n";
		if (agni[i].elt == gkj[j].elt) {
			// xxx could overflow 32-bit int; fix me.
std::cout << "found at i=" << i << " j=" << j << "\n";
			rv = agni[i].idx + gkj[j].idx * k;
			break;
		}
		else if (agni[i].elt < gkj[j].elt) {
			i++;
		}
		else {
			j++;
		}
	}

	if (rv == -1) {
		std::cerr << "f2npolymod_log:  couldn't find log base "
			<< g << " of " << a << " mod " << m << ".\n";
		exit(1);
	}

	delete [] agni;
	delete [] gkj;
	return rv;
}
