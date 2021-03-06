// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2npoly_factor.h"
#include "f2npoly_random.h"
#include "f2polymod_t.h"
#include "tmatrix.h"
#include "tfacinfo.h"

//#define F2NPOLY_FACTOR_DEBUG

static void f2npoly_pre_berlekamp(
	f2npoly_t f,
	tfacinfo<f2npoly_t> & rfinfo,
	int recurse);

static void f2npoly_berlekamp(
	f2npoly_t f,
	tfacinfo<f2npoly_t> & rfinfo,
	int recurse);

f2npoly_t f2npoly_from_vector(
	tvector<f2polymod_t> v,
	int n);

// ----------------------------------------------------------------
tfacinfo<f2npoly_t> f2npoly_factor(
	f2npoly_t f)
{
	tfacinfo<f2npoly_t> finfo;
	int d = f.find_degree();
	f2polymod_t c0 = f.get_coeff(0);
	f2poly_t m = c0.get_modulus();
	f2polymod_t zero = c0.prime_sfld_elt(0);
	f2polymod_t one  = c0.prime_sfld_elt(1);

	if (d == 0) {
		finfo.insert_unit(f);
		return finfo;
	}

	f2polymod_t leader = f.get_coeff(d);
	if ((leader != zero) && (leader != one)) {
		finfo.insert_unit(leader);
		f /= leader;
	}

	f2npoly_pre_berlekamp(f, finfo, 1);
	return finfo;
}

// ----------------------------------------------------------------
static void f2npoly_pre_berlekamp(
	f2npoly_t   f,
	tfacinfo<f2npoly_t> & rfinfo,
	int recurse)
{
	f2npoly_t d = f.deriv();
	f2npoly_t g = f.gcd(d);

#ifdef F2NPOLY_FACTOR_DEBUG
	std::cout << "\n";
	std::cout << "f2npoly_pre_berlekamp input = " << f
		<< "  f' = " << d
		<< "  (f,f') = " << g
		<< "\n";
#endif

	if (g == 0) {
		if (f != 0) {
			std::cerr << "Coding error: file "
				<< __FILE__ << " line "
				<< __LINE__ << "\n";
			exit(1);
		}
		rfinfo.insert_factor(f);
		return;
	}
	else if (g.find_degree() == 0) {
		// Input is squarefree.
		f2npoly_berlekamp(f, rfinfo, recurse);
	}
	else if (d == 0) {
		// Input is a perfect square
		f2npoly_t s;
		tfacinfo<f2npoly_t> sfinfo;
		f2poly_t m = f.get_coeff(0).get_modulus();
		if (!f.square_root(s)) {
			std::cerr << "Coding error: file "
				<< __FILE__ << " line "
				<< __LINE__ << "\n";
			exit(1);
		}
#ifdef F2NPOLY_FACTOR_DEBUG
		std::cout << "square root of " << f << " = " << s << "\n";
#endif

		// Multiplicity is p only if degree is > 0.
		f2npoly_pre_berlekamp(s, sfinfo, recurse);
		if (f.find_degree() > 0)
			sfinfo.exp_all(2);
		rfinfo.merge(sfinfo);
	}
	else {
		f2npoly_t q = f / g;

		// Input was already made monic, so these factors should
		// be as well.
		g /= g.get_coeff(g.find_degree());
		q /= q.get_coeff(q.find_degree());

		f2npoly_pre_berlekamp(g, rfinfo, recurse);
		f2npoly_pre_berlekamp(q, rfinfo, recurse);
	}
}

// ----------------------------------------------------------------
// See my "Computation in finite fields" (ffcomp.pdf) for a full description
// of this algorithm.  See f2poly_factor.cpp for some sample data.

static void f2npoly_berlekamp(
	f2npoly_t   f,
	tfacinfo<f2npoly_t> & rfinfo,
	int recurse)
{
	int n  = f.find_degree();
	f2polymod_t c0 = f.get_coeff(0);
	f2poly_t m = c0.get_modulus();
	int q = 1 << m.find_degree();
	f2polymod_t zero = c0.prime_sfld_elt(0);
	f2polymod_t one  = c0.prime_sfld_elt(1);
	f2npoly_t x(one, zero);
	f2npoly_t xq;
	f2npoly_t xqi = one;
	f2npoly_t f1, f2;
	int i, j, row, rank, dimker;

	xq = x;
	for (int i = 1; i < q; i++)
		xq = (xq * x) % f;

#ifdef F2NPOLY_FACTOR_DEBUG
	std::cout << "\n";
	std::cout << "f2npoly_berlekamp input = " << f << "\n";
	std::cout << "x" << " = " << x << "\n";
#endif
	tmatrix<f2polymod_t> BI(n, n);

	if (n < 2) {
		rfinfo.insert_factor(f);
		return;
	}

	// Populate the B matrix.
	for (j = 0; j < n; j++) {
		for (i = 0; i < n; i++) {
			BI[n-1-i][n-1-j] = xqi.get_coeff(i);
		}
#ifdef F2NPOLY_FACTOR_DEBUG
		std::cout << "x^" << q << "*" << j << " = " << xqi << "\n";
#endif
		xqi = (xqi * xq) % f;
	}

#ifdef F2NPOLY_FACTOR_DEBUG
	std::cout << "B =\n" << BI << "\n";
#endif

	// Form B - I.
	for (i = 0; i < n; i++)
		BI[i][i] -= one;

#ifdef F2NPOLY_FACTOR_DEBUG
	std::cout << "B-I =\n" << BI << "\n";
#endif

	BI.row_echelon_form();

#ifdef F2NPOLY_FACTOR_DEBUG
	std::cout << "B-I, rr =\n" << BI << "\n";
#endif

	rank = BI.get_rank_rr();
	dimker = n - rank;

	if (dimker == 1) {
		rfinfo.insert_factor(f);
		return;
	}

	// Find a basis for the nullspace of B - I.
	tmatrix<f2polymod_t> nullspace_basis;
	if (!BI.get_kernel_basis(nullspace_basis, zero, one)) {
		std::cerr << "Coding error: file "
			<< __FILE__ << " line "
			<< __LINE__ << "\n";
		exit(1);
	}
	if (nullspace_basis.get_num_rows() != dimker) {
		std::cerr << "Coding error: file "
			<< __FILE__ << " line "
			<< __LINE__ << "\n";
		exit(1);
	}
#ifdef F2NPOLY_FACTOR_DEBUG
	std::cout << "nullity = " << dimker << "\n";
	std::cout << "nullspace basis =\n" << nullspace_basis << "\n";
#endif // F2NPOLY_FACTOR_DEBUG

	int got_it = 0;
	for (row = 0; row <  dimker && !got_it; row++) {
		f2npoly_t h = f2npoly_from_vector(nullspace_basis[row], n);
#ifdef F2NPOLY_FACTOR_DEBUG
			std::cout << "h  = " << h << "\n";
#endif // F2NPOLY_FACTOR_DEBUG
		if (h == 1)
			continue;

		for (int c = 0; c < q; c++) {
			f2poly_t f2pc = f2poly_t::from_base_rep(c);
			f2polymod_t f2pmc(f2pc, m);
			f2npoly_t f2npc(f2pmc);
			f2npoly_t hc = h - f2npc;
			f1 = f.gcd(hc);

#ifdef F2NPOLY_FACTOR_DEBUG
			std::cout << "hc  = " << hc << "  f1 = " << f1 << "\n";
#endif // F2NPOLY_FACTOR_DEBUG
			int f1d = f1.find_degree();
			int fd  = f.find_degree();
			if ((0 < f1d) && (f1d < fd)) {
				got_it = 1;
				break;
			}
		}
	}

	if (!got_it) {
		// No non-trivial factors found.
		std::cerr << "Coding error: file "
			<< __FILE__ << " line "
			<< __LINE__ << "\n";
		exit(1);
	}

	f2 = f / f1;

#ifdef F2NPOLY_FACTOR_DEBUG
	std::cout << "f1 = " << f1 << "  f2 = " << f2 << "\n";
#endif // F2NPOLY_FACTOR_DEBUG

	// Input was already made monic, so these factors should
	// be as well.
	f1 /= f1.get_coeff(f1.find_degree());
	f2 /= f2.get_coeff(f2.find_degree());

	// The nullity of B-I is the number of irreducible
	// factors of r.  If the nullity is 2, we have a
	// pair of factors which are both irreducible and
	// so we don't need to recurse.
	if (dimker == 2) {
		rfinfo.insert_factor(f1);
		rfinfo.insert_factor(f2);
	}
	else if (!recurse) {
		rfinfo.insert_factor(f1);
		rfinfo.insert_factor(f2);
	}
	else {
		f2npoly_pre_berlekamp(f1, rfinfo, recurse);
		f2npoly_pre_berlekamp(f2, rfinfo, recurse);
	}
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_from_vector(
	tvector<f2polymod_t> v,
	int n)
{
	f2npoly_t f;
	f.set_coeff(0, v[0] - v[0]);
	for (int i = 0; i < n; i++)
		f.set_coeff(n-1-i, v[i]);
	return f;
}

// ----------------------------------------------------------------
int f2npoly_roots(
	f2npoly_t f,
	tvector<f2polymod_t> & rroots)
{
	tfacinfo<f2npoly_t> finfo = f2npoly_factor(f);
	int nf = finfo.get_num_distinct();
	int nr = 0;
	int i, j;

	for (i = 0; i < nf; i++) {
		f2npoly_t factor = finfo.get_ith_factor(i);
		int deg = factor.find_degree();
		if (deg != 1)
			continue;
		nr++;
	}

	if (nr == 0) {
		// xxx or, if nr != degree.  What do we want the semantics
		// to be?
		return 0;
	}

	tvector<f2polymod_t> rv(nr);

	for (i = 0, j = 0; i < nf; i++) {
		f2npoly_t factor = finfo.get_ith_factor(i);
		int deg = factor.find_degree();
		if (deg != 1)
			continue;
		f2polymod_t c1 = factor.get_coeff(1);
		f2polymod_t c0 = factor.get_coeff(0);
		rv[j++] = - c0 / c1;
	}

	rroots = rv;
	return 1;
}

// ----------------------------------------------------------------
int f2npoly_is_irreducible(
	f2npoly_t f)
{
	tfacinfo<f2npoly_t> finfo;

	int d = f.find_degree();
	if (d == 0)
		return 0;
	if (d == 1)
		return 1;

	f /= f.get_coeff(d);
	f2npoly_pre_berlekamp(f, finfo, 0);

#ifdef F2NPOLY_FACTOR_DEBUG
	std::cout << "f2npirr: input = " << f << "\n";
	std::cout << "factors = " << finfo << "\n";
	std::cout << "# factors = " << finfo.get_num_factors() << "\n";
#endif// F2NPOLY_FACTOR_DEBUG

	if (finfo.get_num_factors() == 1)
		return 1;
	else
		return 0;
}

// ----------------------------------------------------------------
// Lexically lowest
f2npoly_t f2npoly_find_irr(
	f2poly_t m,
	int degree)
{
	f2poly_t c0(0), c1(1);
	f2polymod_t zero(c0, m), one(c1, m);
	f2npoly_t rv = zero;
	rv.set_coeff(degree, one);

	if (degree < 1) {
		std::cout << "f2npoly_find_irr:  degree must be positive; got "
			<< degree << ".\n";
		exit(1);
	}

	while (rv.find_degree() == degree) {
		if (rv.get_coeff(0) != zero) {
			if (f2npoly_is_irreducible(rv))
				return rv;
		}
		rv.increment();
	}

	// There are irreducibles of all positive degrees, so it is
	// an error if we failed to find one.
	std::cout << "f2npoly_find_irr:  coding error.\n";
	exit(1);

	return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_random_irr(
	f2poly_t m,
	int degree)
{
	f2poly_t c0(0);
	f2polymod_t zero(c0, m);
	f2npoly_t rv;

	if (degree < 1) {
		std::cout
			<< "f2npoly_random_irr:  degree must be positive; got "
			<< degree << ".\n";
		exit(1);
	}

	for (;;) {
		rv = f2npoly_random(m, degree);
		if (rv.get_coeff(0) == zero)
			continue;
		if (f2npoly_is_irreducible(rv)) {
			rv /= rv.get_coeff(degree); // make monic
			return rv;
		}
	}
}
