// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
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

#include "f2pmlinalg.h"
#include "f2npoly_t.h"
#include "f2npoly_factor.h"
#include "f2poly_factor.h"
#include "f2polymod_units.h"
#include "f2polymod_convert.h"
#include "int_gcd.h"

// ----------------------------------------------------------------
f2npoly_t f2pm_char_poly(
	tmatrix<f2polymod_t> & A)
{
	if (!A.is_square()) {
		std::cerr << "f2pm_char_poly():  non-square input.\n";
		exit(1);
	}

	int i, j;
	int n = A.get_num_rows();
	tmatrix<f2npoly_t> tI_A(n, n);
	f2poly_t m = A[0][0].get_modulus();
	f2polymod_t  c1(f2poly_t(1), m);
	f2polymod_t  c0(f2poly_t(0), m);
	f2npoly_t    t(c1, c0);
	f2npoly_t    pol1(c1);
	f2npoly_t    det;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			tI_A[i][j] = - f2npoly_t(A[i][j]);
			if (i == j)
				tI_A[i][j] += t;
		}
	}

	det = tI_A.ed_det();
	return det;
}

// ----------------------------------------------------------------
tmatrix<f2polymod_t> f2np_companion_matrix(
	f2npoly_t chpol)
{
	int n = chpol.find_degree();
	f2poly_t m = chpol.get_coeff(0).get_modulus();
	f2poly_t zero(0);
	f2poly_t one(1);
	f2polymod_t zero_m(zero, m);
	f2polymod_t one_m(one,  m);
	tmatrix<f2polymod_t> rv(n, n);
	int i;

	// chpol = 10011
	// 0 0 1 1
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0

	rv = zero_m;
	for (i = 1; i < n; i++)
		rv[i][i-1] = one_m;
	for (i = 0; i < n; i++)
		rv[0][n-1-i] = -chpol.get_coeff(i);

	return rv;
}

// ----------------------------------------------------------------
// Diagonalizability test

int f2pm_matrix_is_dable(
	tmatrix<f2polymod_t> & A,

	//int allow_field_extension,
	f2poly_t & rext_modulus,

	tvector<f2polymod_t> & reigenvalues)
	// xxx matrix of (row) eigenvectors
	// xxx or, teigen_info template class
	//	num eigenvalues
	//	eigenvalues[]
	//	eigenvectors *

	//tmatrix<f2polymod_t> * pD,
	//tmatrix<f2polymod_t> * pP)

	// int verbose
{
	int rv = 1;
	int verbose = 1; // xxx make arg
	int allow_field_extension = 1; // xxx make arg

	if (verbose) {
		std::cout << "\n";
		std::cout << "f2pm dable input =\n" << A << "\n";
	}

	// Compute the matrix's characteristic polynomial.
	f2npoly_t chpol = f2pm_char_poly(A);

	if (verbose)
		std::cout << "chpoly = " << chpol << "\n";

	// Factor the char poly into irreducibles over the base field.
	tfacinfo<f2npoly_t> base_finfo = f2npoly_factor(chpol);

	if (verbose)
		std::cout << "factors = " << base_finfo << "\n";

	// Find the LCM of the degrees of the factors, over the base field.
	int deglcm = 1;
	for (int i = 0; i < base_finfo.get_num_distinct(); i++) {
		f2npoly_t factor = base_finfo.get_ith_factor(i);
		int deg = factor.find_degree();
		std::cout << "  factor = " << factor << ", deg = "
			<< deg << "\n";
		deglcm = int_lcm(deglcm, deg);
	}

	if (verbose)
		std::cout << "LCM of degrees = " << deglcm << "\n";

	// Find a modulus for the splitting field of the char poly.
	// The absolute degree is the degree over F2, not over the base field.
	f2poly_t base_modulus = A[0][0].get_modulus();
	int base_degree = base_modulus.find_degree();
	int absolute_ext_degree = deglcm * base_degree;
	if ((deglcm == 1) || !allow_field_extension) {
		// Use specified modulus if degrees are equal.
		rext_modulus = base_modulus;
	}
	else {
		rext_modulus = f2poly_find_irr(absolute_ext_degree);
	}

	if (verbose) {
		std::cout << "Base modulus = "
			<< base_modulus << "\n";
		std::cout << "Extension degree (over F2) = "
			<< absolute_ext_degree << "\n";
		std::cout << "Extension modulus = "
			<< rext_modulus << "\n";
	}

	// Convert chpoly from base field to extension field.
	f2npoly_t ext_chpol;
	tmatrix<f2polymod_t> ext_A;
	if ((deglcm == 1) || !allow_field_extension) {
		ext_chpol = chpol;
		ext_A = A;
	}
	else {
		f2polymod_t base_g, ext_g;

		if (!f2polymod_find_generator(base_modulus, base_g)) {
			std::cerr << "Can't find generator mod "
				<< base_modulus << ".\n";
			exit(1);
		}
		if (!f2polymod_convert_prep(base_g, rext_modulus, ext_g)) {
			std::cerr << "Can't find generator mod "
				<< rext_modulus << ".\n";
			exit(1);
		}

		ext_chpol = f2polymod_convert_poly(base_g, ext_g, chpol);
		ext_A = f2polymod_convert_matrix(base_g, ext_g, A);
	}

	tfacinfo<f2npoly_t> ext_finfo = f2npoly_factor(ext_chpol);

	int nev = 0;
	for (int i = 0; i < ext_finfo.get_num_distinct(); i++) {
		f2npoly_t factor = ext_finfo.get_ith_factor(i);
		int d = factor.find_degree();
		if (d == 1)
			nev++;
	}

	reigenvalues = tvector<f2polymod_t>(nev);
	for (int i = 0; i < nev; i++) {
		f2npoly_t factor = ext_finfo.get_ith_factor(i);
		int d = factor.find_degree();
		if (d != 1) {
			rv = 0;
			// Use only linear factors, for rational-form case.
			continue;
		}
		reigenvalues[i] = factor.get_coeff(0);
	}

	// Compute nullities and multiplicities for each eigenvalue.
	int n = ext_A.get_num_rows();
	for (int i = 0; i < nev; i++) {
		tmatrix<f2polymod_t> A_tI(ext_A);
		A_tI -= reigenvalues[i];
		int rank = A_tI.get_rank();
		int nullity = n - rank;
		int multiplicity = ext_finfo.get_ith_count(i);
		if (nullity != multiplicity)
			rv = 0;

		if (verbose) {
			std::cout << "Eigenvalue " << reigenvalues[i]
				<< " multiplicity " << multiplicity
				<< " nullity " << nullity << "\n";
			std::cout << "A - " << reigenvalues[i] << " * I =\n"
				<< A_tI << "\n";
		}

		// tmatrix<f2polymod_t> kbi = A_tI.get_kernel_basis();
		// append to eigenvectors
		// xxx find eigenvectors
		// rr first to avoid redundant cpt'ns (and cmt)
		// then kerbas
	}

	//if (rv == 1) {
	//	rD = tmatrix<f2polymod_t>(n, n);
	//	rP = tmatrix<f2polymod_t>(n, n);
	//	f2polymod_t zero = splitA[0][0] - splitA[0][0];
	//	D = zero;
	//	int k = 0;
	//	for (int i = 0; i < reinfo.get_nev(); i++) {
	//		for (int j = 0; j < reinfo.get_multiplicity(i); j++) {
	//			D[k][k] = reinfo.get_eigenvalue(i);
	//			P[k] = reinfo.get_eigenvector(i, j);
	//			k++;
	//		}
	//	}
	//	P = P.transpose();
	//
	//	tmatrix<f2polymod_t> PD = P * D;
	//	tmatrix<f2polymod_t> AP = splitA * P;
	//	if (PD != AP) {
	//		std::cerr << "f2pm_matrix_is_dable: coding error.\n";
	//		exit(1);
	//	}
	//}

	return rv;
}

// ----------------------------------------------------------------
tvector<f2polymod_t>
ft_vector_from_base_rep(
	int base_rep,
	f2poly_t m,
	int len)
{
	tvector<f2polymod_t> v(len);
	int i;
	int t = 1 << m.find_degree();

	for (i = len - 1; i >= 0; i--) {
		f2poly_t r = f2poly_t::from_base_rep(base_rep % t);
		v[i] = f2polymod_t(r, m);
		base_rep /= t;
	}
	return v;
}
