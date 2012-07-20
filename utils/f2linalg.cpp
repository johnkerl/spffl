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

#include "f2linalg.h"
#include "f2poly_t.h"

// ----------------------------------------------------------------
tvector<bit_t>
f2_vector_from_base_rep(
	int base_rep,
	int len)
{
	tvector<bit_t> v(len);
	for (int i = len - 1; i >= 0; i--) {
		v[i] = bit_t(base_rep & 1);
		base_rep >>= 1;
	}
	return v;
}

// ----------------------------------------------------------------
tmatrix<bit_t>
f2_matrix_from_base_rep(
	int base_rep,
	int num_rows,
	int num_cols)
{
	tmatrix<bit_t> A(num_rows, num_cols);
	for (int i = num_rows - 1; i >= 0; i--) {
		for (int j = num_cols - 1; j >= 0; j--) {
			A[i][j] = bit_t(base_rep & 1);
			base_rep >>= 1;
		}
	}
	return A;
}

// ----------------------------------------------------------------
f2poly_t f2_char_poly(
	tmatrix<bit_t> & A)
{
	if (!A.is_square()) {
		std::cerr << "f2_char_poly():  non-square input.\n";
		exit(1);
	}

	int i, j;
	int n = A.get_num_rows();
	tmatrix<f2poly_t> A_lI(n, n);
	f2poly_t lambda(f2poly_t(1, 0));
	f2poly_t det;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			A_lI[i][j] = f2poly_t(A[i][j].get_residue());
			if (i == j)
				A_lI[i][j] -= lambda;
		}
	}

	det = A_lI.ed_det();

	return det;
}

// ----------------------------------------------------------------
tmatrix<bit_t> f2_companion_matrix(
	f2poly_t chpol)
{
	int n = chpol.find_degree();
	tmatrix<bit_t> rv(n, n);
	int i;

	// chpol = 13 = 10011
	// 0 0 1 1
	// 1 0 0 0
	// 0 1 0 0
	// 0 0 1 0

	rv = bit_t(0);
	for (i = 1; i < n; i++)
		rv[i][i-1] = bit_t(1);
	for (i = 0; i < n; i++)
		if (chpol.bit_at(i))
			rv[0][n-1-i] = bit_t(1);

	return rv;
}

// ----------------------------------------------------------------
static f2npoly_t f2polymod_char_or_min_poly(
	f2polymod_t a,
	int do_min)
{
	f2poly_t m = a.get_modulus();
	int d = m.find_degree();
	f2poly_t r1(1);
	f2polymod_t one(r1, m);
	f2npoly_t rv = one;
	f2polymod_t ap = a;

	for (int i = 0; i < d; i++) {
		f2npoly_t factor(one, ap);
		rv *= factor;
		ap = ap * ap; // Frobenius
		if (do_min && (ap == a))
			break;
	}

	return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2polymod_char_poly(
	f2polymod_t a)
{
	return f2polymod_char_or_min_poly(a, 0);
}

// ----------------------------------------------------------------
f2npoly_t f2polymod_min_poly(
	f2polymod_t a)
{
	return f2polymod_char_or_min_poly(a, 1);
}
