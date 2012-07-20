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

// How to compute the order of the unit group of a residue class ring over
// F_q[x], i.e. the totient function of a polynomial in F_q[x].  Let the prime
// factorization of f(x) be
//
//   f(x) = \prod_{i=1}^m {f_i}^{e_i}
//
// The CRT says
//
//   \F_q[x]/<{f(x)}> \cong \oplus_{i=1}^m \F_q[x]/\pig{{f_i}^{e_i}}
//
// as a ring isomorphism, and likewise for the multiplicative group (units).
// So the question reduces to, what is the totient function of ${f_i}^{e_i}$.
// Let $d_i = \deg(f_i)$.  Then a \emph{non}-unit in the residue class ring is
// is any multiple of $f_i$.  The $i$th factor ring has order $q^{d_i e_i}$.
// Any non-zero poly of degree less than $d_i$ is necessarily relatively prime
// to $f_i$, since $f_i$ is prime.  Letting the zero poly have degree 0, there
// are $q^{d_i e_i - d_i}$ multiples of $f_i$.  Then the number of units in
// the $i$th factor ring is
//
//   q^{d_i e_i} - q^{d_i e_i-d_i } = q^{d_i (e_i-1)}(q^{d_i} -1)
//
// and so the order of the multiplicative group is
//
//   \prod_{i=1}^m q^{d_i (e_i-1)}(q^{d_i} -1)
//
// In the irreducible case, $m=1$, $d_1=n$, $e_1=1$, whence
//
//   q^{n (1-1)}(q^{n} -1) = q^{n-1}

// which recovers the special case for finite fields.

#include "f2poly_totient.h"
#include "f2poly_factor.h"

int f2poly_totient(
	f2poly_t f)
{
	int rv = 1;
	tfacinfo<f2poly_t> finfo = f2poly_factor(f);
	int nf = finfo.get_num_distinct();

	for (int i = 0; i < nf; i++) {
		f2poly_t fi = finfo.get_ith_factor(i);
		int ei = finfo.get_ith_count(i);
		int di = fi.find_degree();
		rv *= (1 << (di * (ei-1))) * ((1 << di) -1);
	}

	return rv;
}
