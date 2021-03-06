// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include "spminchar.h"

#include "tmatrix.h"
#include "bit_matrix_t.h"

// ----------------------------------------------------------------
int f2pm_froblen(f2polymod_t a)
{
	int rv = 0;
	f2polymod_t ap = a;

	do {
		rv++;
		ap = ap * ap;
	} while (ap != a);

	return rv;
}

// ----------------------------------------------------------------
int f2npm_froblen(f2npolymod_t a)
{
	int rv = 0;
	int q  = 1 << a.get_residue().get_coeff(0).get_modulus().find_degree();
	f2npolymod_t ap = a;

	do {
		rv++;
		ap = ap.exp(q);
	} while (ap != a);

	return rv;
}

// ----------------------------------------------------------------
int fppm_froblen(fppolymod_t a)
{
	int rv = 0;
	int p = a.get_char();
	fppolymod_t ap = a;

	do {
		rv++;
		ap = ap.exp(p);
	} while (ap != a);

	return rv;
}

// ----------------------------------------------------------------
// To compute the min poly of a, we could do the following:
//   (x - a) (x - a^p) ...
// up to one less than the Frobenius length of a.  However, that requires (at
// the implementation level) a higher-order type of polynomial:  input is
// thingie_t, output has coeffs which are thingie_t's.
//
// A simple alternative is found in section 4.7 of Berlekamp's _Algebraic
// Coding Theory_.  Let u be the primitive element for our Fq.  Throughout
// SPFFL, we use the vector-space representation, so a is a polynomial in u.
// The minimal polynomial mp(a, x) is such that mp(a) = 0.  Use row-reduction
// to solve for the coefficients of mp(a, x).  The advantage is that only
// thingie_t's are needed.
//
// Example:  q=16.  m = 10011 = x^4 + x + 1.  a = 1011 = u^3 + u + 1.
// mp(a, x) = m4 x^4 + m3 x^3 + m2 x^2 + m1 x + m0.
// mp(a, a) = m4 a^4 + m3 a^3 + m2 a^2 + m1 a + m0 = 0.
// a = 1011; a^2 = 1001; a^3 = 1100; a^4 = 1101.
// m4(1101) + m3(1100) + m2(1001) + m1(1011) + m0(0001) = (0000).
// (m4,m4,0,m4)+(m3,m3,0,0)+(m2,0,0,m2)+(m1,0,m1,m1)+(0,0,0,m0)=(0,0,0,0);
//
// [ m0+m1+m2+ 0+m4 = 0 ]
// [  0+m1+ 0+ 0+ 0 = 0 ]
// [  0+ 0+ 0+m3+m4 = 0 ]
// [  0+m1+m2+m3+m4 = 0 ]
//
// [ 1 1 1 0 1 ] [ m0 ] = [ 0 ]
// [ 0 1 0 0 0 ] [ m1 ] = [ 0 ]
// [ 0 0 0 1 1 ] [ m2 ] = [ 0 ]
// [ 0 1 1 1 1 ] [ m3 ] = [ 0 ]
//               [ m4 ]
//
// Kernel basis: [ 1 0 0 1 1 ]
// x^4 + x^3 + 1 is the minimal polynomial for 1011 = u^3 + u + 1.

// ----------------------------------------------------------------
f2poly_t f2pm_min_poly(f2polymod_t a)
{
	f2poly_t m = a.get_modulus();
	f2polymod_t ap = a.prime_sfld_elt(1);
	int n = m.find_degree();
	int l = f2pm_froblen(a);
	bit_matrix_t A(n,l+1);
	for (int j = 0; j <= l; j++) {
		for (int i = 0; i < n; i++) {
			f2poly_t apr = ap.get_residue();
			A[i].set(j, apr.bit_at(i));
		}
		ap *= a;
	}
	bit_matrix_t B;
	if (!A.get_kernel_basis(B)) {
		std::cerr << "poo!\n";
		exit(1);
	}
	if (B.get_rank_rr() != 1) {
		std::cerr << "double poo!\n";
		std::cerr << B << "\n";
		exit(1);
	}
	f2poly_t p;
	for (int j = 0; j <= l; j++)
		if (B[0].get(j) == 1)
			p.set_bit(j);
	return p;
}

// ----------------------------------------------------------------
f2npoly_t f2npm_min_poly(f2npolymod_t a)
{
	f2npoly_t m = a.get_modulus();
	f2npolymod_t ap = a.prime_sfld_elt(1);
	f2polymod_t zero = a.get_residue().get_coeff(0).prime_sfld_elt(0);
	f2polymod_t one  = a.get_residue().get_coeff(0).prime_sfld_elt(1);
	int n = m.find_degree();
	int l = f2npm_froblen(a);
	tmatrix<f2polymod_t> A(zero, n, l+1);
	for (int j = 0; j <= l; j++) {
		for (int i = 0; i < n; i++) {
			f2npoly_t apr = ap.get_residue();
			A[i][j] = apr.get_coeff(i);
		}
		ap *= a;
	}
	tmatrix<f2polymod_t> B;
	if (!A.get_kernel_basis(B, zero, one)) {
		std::cerr << "poo!\n";
		exit(1);
	}
	if (B.get_rank_rr() != 1) {
		std::cerr << "double poo!\n";
		std::cerr << B << "\n";
		exit(1);
	}
	f2npoly_t mp;
	for (int j = 0; j <= l; j++)
		mp.set_coeff(j, B[0][j]);
	return mp;
}

// ----------------------------------------------------------------
fppoly_t fppm_min_poly(fppolymod_t a)
{
	fppoly_t m = a.get_modulus();
	fppolymod_t ap = a.prime_sfld_elt(1);
	int p = a.get_char();
	intmod_t zero(0, p);
	intmod_t one (1, p);
	int n = m.find_degree();
	int l = fppm_froblen(a);
	tmatrix<intmod_t> A(zero, n, l+1);
	for (int j = 0; j <= l; j++) {
		for (int i = 0; i < n; i++) {
			fppoly_t apr = ap.get_residue();
			A[i][j] = apr.get_coeff(i);
		}
		ap *= a;
	}
	tmatrix<intmod_t> B;
	if (!A.get_kernel_basis(B, zero, one)) {
		std::cerr << "poo!\n";
		exit(1);
	}
	if (B.get_rank_rr() != 1) {
		std::cerr << "double poo!\n";
		std::cerr << B << "\n";
		exit(1);
	}
	fppoly_t mp;
	for (int j = 0; j <= l; j++)
		mp.set_coeff(j, B[0][j]);
	return mp;
}

// ----------------------------------------------------------------
f2poly_t f2pm_char_poly(f2polymod_t a)
{
	f2poly_t mp = f2pm_min_poly(a);
	f2poly_t m = a.get_modulus();
	int n = m.find_degree();
	int l = f2pm_froblen(a);
	f2poly_t cp = mp.exp(n/l);
	return cp;
}

// ----------------------------------------------------------------
f2npoly_t f2npm_char_poly(f2npolymod_t a)
{
	f2npoly_t mp = f2npm_min_poly(a);
	f2npoly_t m = a.get_modulus();
	int n = m.find_degree();
	int l = f2npm_froblen(a);
	f2npoly_t cp = mp.exp(n/l);
	return cp;
}

// ----------------------------------------------------------------
fppoly_t fppm_char_poly(fppolymod_t a)
{
	fppoly_t mp = fppm_min_poly(a);
	fppoly_t m = a.get_modulus();
	int n = m.find_degree();
	int l = fppm_froblen(a);
	fppoly_t cp = mp.exp(n/l);
	return cp;
}
