// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl at math dot arizona dot edu
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place, Suite 330, Boston, MA  02111-1307  USA
// ================================================================

#include "f2ipoly_factor.h"
#include "bit_t.h"
#include "tmatrix.h"
#include "tfacinfo.h"

//#define F2POLY_FACTOR_DEBUG

static void f2ipoly_pre_berlekamp(
	f2ipoly_t f,
	tfacinfo<f2ipoly_t> & rfinfo);

static void f2ipoly_berlekamp(
	f2ipoly_t f,
	tfacinfo<f2ipoly_t> & rfinfo);

f2ipoly_t f2ipoly_from_vector(
	tvector<bit_t> v,
	int n);

// ----------------------------------------------------------------
tfacinfo<f2ipoly_t> f2ipoly_factor(
	f2ipoly_t f)
{
	tfacinfo<f2ipoly_t> finfo;
	if (f.find_degree() == 0) {
		finfo.insert_unit(f);
		return finfo;
	}
	f2ipoly_pre_berlekamp(f, finfo);
	return finfo;
}

// ----------------------------------------------------------------
static void f2ipoly_pre_berlekamp(
	f2ipoly_t   f,
	tfacinfo<f2ipoly_t> & rfinfo)
{
	f2ipoly_t d = f.deriv();
	f2ipoly_t g = f.gcd(d);

#ifdef F2POLY_FACTOR_DEBUG
	std::cout << "\n";
	std::cout << "f2ipoly_pre_berlekamp input = " << f
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
	else if (g == 1) {
		// Input is squarefree.
		f2ipoly_berlekamp(f, rfinfo);
	}
	else if (d == 0) {
		// Input is a perfect square
		f2ipoly_t s;
		tfacinfo<f2ipoly_t> sfinfo;
		if (!f.square_root(s)) {
			std::cerr << "Coding error: file "
				<< __FILE__ << " line "
				<< __LINE__ << "\n";
			exit(1);
		}

		// Multiplicity is p only if degree is > 0.
		f2ipoly_pre_berlekamp(s, sfinfo);
		if (f.find_degree() > 0)
			sfinfo.exp_all(2);
		rfinfo.merge(sfinfo);
	}

	else {
		f2ipoly_t q = f / g;
		f2ipoly_pre_berlekamp(g, rfinfo);
		f2ipoly_pre_berlekamp(q, rfinfo);
	}
}

// ----------------------------------------------------------------
// See my "Computation in finite fields" (ffcomp.pdf) for a full description
// of this algorithm.
//
// Given squarefree f(x), we want to find polynomials h(x) such that
// h^q equiv h (mod f).  (Example: f = 31 = 7 * b.  Deg(f) = 5.)
// By explicit search, we can find the following polynomials h of degree
// < 5 such that h**2 = h mod f (Lidl and Niederreiter call these "f-reducing
// polynomials"): 00 01 1c 1d.
//
// To avoid having to do a search, we use linear algebra instead.
//
// f = x^5+x^4+1 = 110001
//   x^0 = 00001
//   x^2 = 00100
//   x^4 = 10000
//   x^6 = 10011
//   x^8 = 11101
//
// h   = a_4 x^4 + a_3 x^3 + a_2 x^2 + a_1 x + a_0
// h^2 = a_4(x^4+x^3+x^2+1) + a_3(x^4+x+1) + a_2(x^4) + a_1(x^2) + a_0(1)
//
// [ a_4 ]     [ 1 1 1 0 0 ]     [ a_4 ]
// [ a_3 ]     [ 1 0 0 0 0 ]     [ a_3 ]
// [ a_2 ]  =  [ 1 0 0 1 0 ]  *  [ a_2 ]
// [ a_1 ]     [ 1 1 0 0 0 ]     [ a_1 ]
// [ a_0 ]     [ 1 1 0 0 1 ]     [ a_0 ]
//
// [ 0 ]  .  [ 0 1 1 0 0 ]  .  [ a_4 ]
// [ 0 ]  .  [ 1 1 0 0 0 ]  .  [ a_3 ]
// [ 0 ]  =  [ 1 0 1 1 0 ]  *  [ a_2 ]
// [ 0 ]  .  [ 1 1 0 1 0 ]  .  [ a_1 ]
// [ 0 ]  .  [ 1 1 0 0 0 ]  .  [ a_0 ]
//
// Call the matrix B.  Its (n-1-j)th column is x^{jq} mod f.  Put it in
// row-echelon form to obtain
//
// [ 1 0 1 0 0 ]
// [ 0 1 1 0 0 ]
// [ 0 0 0 1 0 ]
// [ 0 0 0 0 0 ]
// [ 0 0 0 0 0 ]
//
// with kernel basis
//
// [ 1 1 1 0 0 ]
// [ 0 0 0 0 1 ]
//
// These are h1 = 1c and h2 = 1, respectively.  Compute gcd(f, h1) = 7 and
// gcd(f, h1+1) = b to obtain non-trivial factors of f.

static void f2ipoly_berlekamp(
	f2ipoly_t   f,
	tfacinfo<f2ipoly_t> & rfinfo)
{
	int n  = f.find_degree();
	f2ipoly_t x(1, 0);
	f2ipoly_t x2 = (x * x) % f;
	f2ipoly_t x2i(1);
	int i, j, row, rank, dimker;
	bit_t zero(0);
	bit_t one(1);

#ifdef F2POLY_FACTOR_DEBUG
	std::cout << "\n";
	std::cout << "f2ipoly_berlekamp input = " << f << "\n";
#endif
	tmatrix<bit_t> BI(n, n);

	if (n < 2) {
		rfinfo.insert_factor(f);
		return;
	}

	// Populate the B matrix.
	for (j = 0; j < n; j++) {
		for (i = 0; i < n; i++) {
			BI[n-1-i][n-1-j] = bit_t(x2i.bit_at(i));
		}
		x2i = (x2i * x2) % f;
	}

#ifdef F2POLY_FACTOR_DEBUG
	std::cout << "B =\n" << BI << "\n";
#endif

	// Form B - I.
	for (i = 0; i < n; i++)
		BI[i][i] -= one;

#ifdef F2POLY_FACTOR_DEBUG
	std::cout << "B-I =\n" << BI << "\n";
#endif

	BI.row_echelon_form();

#ifdef F2POLY_FACTOR_DEBUG
	std::cout << "B-I, rr =\n" << BI << "\n";
#endif

	rank = BI.get_rank_rr();
	dimker = n - rank;

	if (dimker == 1) {
		rfinfo.insert_factor(f);
		return;
	}

	// Find a basis for the nullspace of B - I.
	tmatrix<bit_t> nullspace_basis;
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
#ifdef F2POLY_FACTOR_DEBUG
	std::cout << "nullity = " << dimker << "\n";
	std::cout << "nullspace basis =\n" << nullspace_basis << "\n";
#endif // F2POLY_FACTOR_DEBUG

	// For each h in the nullspace basis, form
	//   f1 = gcd(f, h)
	//   f2 = gcd(f, h-1)
	// Now, the polynomial h=1 is always in the nullspace, in which case
	// f1 = 1 and f2 = f, which results in a trivial factorization.  Any
	// of the other h's will work fine, producing a non-trivial
	// factorization of f into two factors.  (Note that either or both
	// of them may be reducible, in which we'll need to apply this
	// algorithm recursively until we're down to irreducible factors.)
	// Here, for the sake of illustration, is what happens with all the
	// h's, even though we need only one of them (with f = 703):

	//h=001
	//  f1: 001
	//  f2: 70e = 2 3 7 b d
	//h=102     = 2 3 b d
	//  f1: 102 = 2 3 b d
	//  f2: 007 = 7
	//h=284     = 2 2 7 3b
	//  f1: 00e = 2 7
	//  f2: 081 = 3 b d
	//h=0e8     = 2 2 2 3 b
	//  f1: 03a = 2 3 b
	//  f2: 023 = 7 d
	//h=310     = 2 2 2 2 7 b
	//  f1: 062 = 2 7 b
	//  f2: 017 = 3 d

	for (row = 0; row <  dimker; row++) {
		f2ipoly_t h, hc;
		h = f2ipoly_from_vector(nullspace_basis[row], n);
		hc = h + f2ipoly_t(1);

		f2ipoly_t check1 = (h  * h)  % f;
		f2ipoly_t check2 = (hc * hc) % f;
		if ((h != check1) || (hc != check2)) {
			std::cerr << "Coding error: file "
				<< __FILE__ << " line "
				<< __LINE__ << "\n";
			std::cerr << "  h  = " << h
				<< "  h^2  = " << check1 << "\n";
			std::cerr << "  hc = " << hc
				<< "  hc^2 = " << check2 << "\n";
			exit(1);
		}

		f2ipoly_t f1 = f.gcd(h);
		f2ipoly_t f2 = f.gcd(hc);

#ifdef F2POLY_FACTOR_DEBUG
		std::cout << "h  = " << h  << "  hc = " << hc << "\n";
		std::cout << "f1 = " << f1 << "  f2 = " << f2 << "\n";
#endif // F2POLY_FACTOR_DEBUG

		if ((f1 == 1) || (f2 == 1))
			continue;

		// The nullity of B-I is the number of irreducible
		// factors of f.  If the nullity is 2, we have a
		// pair of factors which are both irreducible and
		// so we don't need to recurse.
		if (dimker == 2) {
			rfinfo.insert_factor(f1);
			rfinfo.insert_factor(f2);
		}
		else {
			f2ipoly_pre_berlekamp(f1, rfinfo);
			f2ipoly_pre_berlekamp(f2, rfinfo);
		}
		return;
	}
	std::cerr << "Coding error: file "
		<< __FILE__ << " line "
		<< __LINE__ << "\n";
	exit(1);
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_from_vector(
	tvector<bit_t> v,
	int n)
{
	f2ipoly_t f(0);
	bit_t one(1);
	for (int i = 0; i < n; i++)
		if (v[n-1-i] == one)
			f.set_bit(i);
	return f;
}


//// ----------------------------------------------------------------
//// Given the prime factorization p1^m1 ... pk^mk of n, how to enumerate all
//// factors of n?
////
//// Example 72 = 2^3 * 3^2.  Exponent on 2 is one of 0, 1, 2, 3.  Exponent on
//// 3 is one of 0, 1, 2.  Number of possibilities:  product over i of (mi + 1).
//// Factors are:
////
////	2^0 3^0    1
////	2^0 3^1    3
////	2^0 3^2    9
////	2^1 3^0    2
////	2^1 3^1    6
////	2^1 3^2   18
////	2^2 3^0    4
////	2^2 3^1   12
////	2^2 3^2   36
////	2^3 3^0    8
////	2^3 3^1   24
////	2^3 3^2   72
//
//unsigned f2ipoly_num_divisors(
//	f2ipoly_factor_info_t * pfinfo)
//{
//	unsigned rv;
//	int i;
//
//	if ((pfinfo->num_distinct < 0)
//		|| (pfinfo->num_distinct > F2POLY_MAX_NUM_FACTORS))
//	{
//		fprintf(stderr, "f2ipoly_num_divisors:  num distinct (%d) "
//			"out of bounds 0-%d\n",
//			pfinfo->num_distinct, F2POLY_MAX_NUM_FACTORS);
//		exit(1);
//	}
//
//	rv = 1;
//	for (i = 0; i < pfinfo->num_distinct; i++)
//		rv *= pfinfo->factor_counts[i].count + 1;
//	return rv;
//}

//// ----------------------------------------------------------------
//// See comments to the above.  k is treated as a multibase representation
//// over the bases mi+1.
//
//f2ipoly_t f2ipoly_kth_divisor(
//	f2ipoly_factor_info_t * pfinfo,
//	unsigned k)
//{
//	f2ipoly_t rv;
//	f2ipoly_t fp;
//	int i;
//	unsigned base;
//	unsigned power;
//
//	rv = f2ipoly_from_base_rep(1);
//	for (i = 0; i < pfinfo->num_distinct; i++) {
//		base = pfinfo->factor_counts[i].count + 1;
//		power = k % base;
//		k = k / base;
//
//		fp = f2ipoly_power(&pfinfo->factor_counts[i].f, power);
//		rv = f2ipoly_mul(&rv, &fp);
//	}
//	return rv;
//}

//// ----------------------------------------------------------------
//// The caller must free the return value.
//
//f2ipoly_t * f2ipoly_get_all_divisors(
//	f2ipoly_t * pr,
//	unsigned * pnum_divisors)
//{
//	f2ipoly_factor_info_t finfo;
//	unsigned nf, k;
//	f2ipoly_t * all_divisors;
//
//	f2ipoly_factor(pr, &finfo);
//	nf = f2ipoly_num_divisors(&finfo);
//	*pnum_divisors = nf;
//
//	all_divisors = (f2ipoly_t *)malloc_check(nf * sizeof(f2ipoly_t));
//	for (k = 0; k < nf; k++) {
//		all_divisors[k] = f2ipoly_kth_divisor(&finfo, k);
//	}
//	qsort(all_divisors, nf, sizeof(f2ipoly_t), f2ipoly_qcmp);
//
//	return all_divisors;
//}
