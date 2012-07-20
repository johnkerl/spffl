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

#include "int_gcd.h"

// ----------------------------------------------------------------
int int_gcd(int a, int b)
{
	int r;

	if (a == 0)
		return b;
	if (b == 0)
		return a;

	if (a < 0) // Breaks for most negative int (-2^31); I don't care.
		a = -a;
	if (b < 0)
		b = -b;

	while (1) {
		r = a % b;
		if (r == 0)
			break;
		a = b;
		b = r;
	}

	return b;
}

// ----------------------------------------------------------------
int int_ext_gcd(int a, int b, int * pm, int * pn)
{
	int mprime, nprime, c, q, r, t, qm, qn;
	int d;   // Return value.

	// Initialize
	mprime = 1;
	*pn    = 1;
	*pm    = 0;
	nprime = 0;
	c = a;
	d = b;

	while (1) {

		// Divide
		q = c / d;
		r = c % d;
		// Note:  now c = qd + r and 0 <= r < d

		// Remainder zero?
		if (r == 0)
			break;

		// Recycle
		c = d;
		d = r;

		t      = mprime;
		mprime = *pm;
		qm     = q * *pm;
		*pm    = t - qm;

		t      = nprime;
		nprime = *pn;
		qn     = q * *pn;
		*pn    = t - qn;
	}
	return d;
}

// ----------------------------------------------------------------
int int_lcm(int a, int b)
{
	return (a * b) / int_gcd(a, b);
}

// ----------------------------------------------------------------
int gcd(int a, int b)
{
	return int_gcd(a, b);
}
