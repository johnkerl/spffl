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

#include <string.h>
#include "f2npoly_t.h"
#include "cmps.h"
#include "tokenize.h"

// ----------------------------------------------------------------
f2npoly_t::f2npoly_t(void)
{
	f2polymod_t invalid(f2poly_t(0), f2poly_t(1));
	this->degree = 0;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[0] = invalid;
}

// ----------------------------------------------------------------
f2npoly_t::f2npoly_t(f2polymod_t c0)
{
	this->degree = 0;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[0] = c0;
	this->recompute_degree();
}

// ----------------------------------------------------------------
f2npoly_t::f2npoly_t(f2polymod_t c1, f2polymod_t c0)
{
	this->degree = 1;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[1] = c1;
	this->coeffs[0] = c0;
	this->recompute_degree();
}

// ----------------------------------------------------------------
f2npoly_t::f2npoly_t(f2polymod_t c2, f2polymod_t c1, f2polymod_t c0)
{
	this->degree = 2;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[2] = c2;
	this->coeffs[1] = c1;
	this->coeffs[0] = c0;
	this->recompute_degree();
}

// ----------------------------------------------------------------
f2npoly_t::f2npoly_t(f2polymod_t c3, f2polymod_t c2, f2polymod_t c1,
	f2polymod_t c0)
{
	this->degree = 3;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[3] = c3;
	this->coeffs[2] = c2;
	this->coeffs[1] = c1;
	this->coeffs[0] = c0;
	this->recompute_degree();
}

// ----------------------------------------------------------------
f2npoly_t::f2npoly_t(f2polymod_t c4, f2polymod_t c3, f2polymod_t c2,
	f2polymod_t c1, f2polymod_t c0)
{
	this->degree = 4;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[4] = c4;
	this->coeffs[3] = c3;
	this->coeffs[2] = c2;
	this->coeffs[1] = c1;
	this->coeffs[0] = c0;
	this->recompute_degree();
}

// ----------------------------------------------------------------
f2npoly_t::f2npoly_t(f2polymod_t c5, f2polymod_t c4, f2polymod_t c3,
	f2polymod_t c2, f2polymod_t c1, f2polymod_t c0)
{
	this->degree = 5;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[5] = c5;
	this->coeffs[4] = c4;
	this->coeffs[3] = c3;
	this->coeffs[2] = c2;
	this->coeffs[1] = c1;
	this->coeffs[0] = c0;
	this->recompute_degree();
}

// ----------------------------------------------------------------
f2npoly_t::f2npoly_t(int c0, f2poly_t m)
{
	this->degree = 0;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[0] = f2polymod_t(f2poly_t(c0), m);
	this->recompute_degree();
}
f2npoly_t::f2npoly_t(int c1, int c0, f2poly_t m)
{
	this->degree = 1;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[1] = f2polymod_t(f2poly_t(c1), m);
	this->coeffs[0] = f2polymod_t(f2poly_t(c0), m);
	this->recompute_degree();
}
f2npoly_t::f2npoly_t(int c2, int c1, int c0, f2poly_t m)
{
	this->degree = 2;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[2] = f2polymod_t(f2poly_t(c2), m);
	this->coeffs[1] = f2polymod_t(f2poly_t(c1), m);
	this->coeffs[0] = f2polymod_t(f2poly_t(c0), m);
	this->recompute_degree();
}
f2npoly_t::f2npoly_t(int c3, int c2, int c1, int c0, f2poly_t m)
{
	this->degree = 3;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[3] = f2polymod_t(f2poly_t(c3), m);
	this->coeffs[2] = f2polymod_t(f2poly_t(c2), m);
	this->coeffs[1] = f2polymod_t(f2poly_t(c1), m);
	this->coeffs[0] = f2polymod_t(f2poly_t(c0), m);
	this->recompute_degree();
}
f2npoly_t::f2npoly_t(int c4, int c3, int c2, int c1, int c0, f2poly_t m)
{
	this->degree = 4;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[4] = f2polymod_t(f2poly_t(c4), m);
	this->coeffs[3] = f2polymod_t(f2poly_t(c3), m);
	this->coeffs[2] = f2polymod_t(f2poly_t(c2), m);
	this->coeffs[1] = f2polymod_t(f2poly_t(c1), m);
	this->coeffs[0] = f2polymod_t(f2poly_t(c0), m);
	this->recompute_degree();
}
f2npoly_t::f2npoly_t(int c5, int c4, int c3, int c2, int c1, int c0, f2poly_t m)
{
	this->degree = 5;
	this->coeffs = new f2polymod_t[this->degree + 1];
	this->coeffs[5] = f2polymod_t(f2poly_t(c5), m);
	this->coeffs[4] = f2polymod_t(f2poly_t(c4), m);
	this->coeffs[3] = f2polymod_t(f2poly_t(c3), m);
	this->coeffs[2] = f2polymod_t(f2poly_t(c2), m);
	this->coeffs[1] = f2polymod_t(f2poly_t(c1), m);
	this->coeffs[0] = f2polymod_t(f2poly_t(c0), m);
	this->recompute_degree();
}

// ----------------------------------------------------------------
// This is a static method.
f2npoly_t f2npoly_t::from_base_rep(int b, f2poly_t m)
{
	f2npoly_t rv;
	std::cerr << "unimplemented function!\n";
	exit(1);
// xxx fix me
#if 0
	// Find degree.
	if (b == 0) {
		rv.degree = 0;
	}
	else {
		int temp = b;
		rv.degree = -1;
		while (temp) {
			temp /= m;
			rv.degree++;
		}
	}

	rv.coeffs = new f2polymod_t[rv.degree + 1];
	for (int i = 0; i <= rv.degree; i++) {
		rv.coeffs[i] = f2polymod_t(b % m, m);
		b /= m;
	}
#endif
	return rv;
}

// ----------------------------------------------------------------
f2npoly_t::f2npoly_t(const f2npoly_t & that)
{
	this->degree = that.degree;
	this->coeffs = new f2polymod_t[this->degree + 1];
	for (int i = 0; i <= that.degree; i++)
		this->coeffs[i] = that.coeffs[i];
}

// ----------------------------------------------------------------
f2npoly_t::~f2npoly_t(void)
{
	delete [] this->coeffs;
	this->coeffs = 0;
	this->degree = -1;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::prime_sfld_elt(int v) const
{
	f2polymod_t c0 = this->coeffs[0].prime_sfld_elt(v);
	return f2npoly_t(c0);
}

// ----------------------------------------------------------------
// This is a static method.

f2npoly_t f2npoly_t::prime_sfld_elt(int v, f2poly_t m)
{
	return f2npoly_t(f2polymod_t(f2poly_t(v), m));
}

// ----------------------------------------------------------------
int f2npoly_t::get_char(void)
{
	return 2;
}

// ----------------------------------------------------------------
f2npoly_t & f2npoly_t::operator=(f2npoly_t that)
{
	if (this->coeffs)
		delete [] this->coeffs;
	this->degree = that.degree;
	this->coeffs = new f2polymod_t[this->degree + 1];
	for (int i = 0; i <= that.degree; i++)
		this->coeffs[i] = that.coeffs[i];
	return *this;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator+(f2npoly_t that) const
{
	int i;
	f2npoly_t rv;

	if (this->degree < that.degree) {
		rv.degree = that.degree;
		rv.coeffs = new f2polymod_t[rv.degree + 1];
		for (i = 0; i <= this->degree; i++)
			rv.coeffs[i] = this->coeffs[i] + that.coeffs[i];
		for (i = this->degree+1; i <= that.degree; i++)
			rv.coeffs[i] = that.coeffs[i];
	}
	else {
		rv.degree = this->degree;
		rv.coeffs = new f2polymod_t[rv.degree + 1];
		for (i = 0; i <= that.degree; i++)
			rv.coeffs[i] = this->coeffs[i] + that.coeffs[i];
		for (i = that.degree+1; i <= this->degree; i++)
			rv.coeffs[i] = this->coeffs[i];
	}
	rv.recompute_degree();
	return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator+(f2polymod_t a) const
{
	f2npoly_t rv(*this);
	rv.coeffs[0] += a;
	rv.recompute_degree();
	return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator-(f2npoly_t that) const
{
	int i;
	f2npoly_t rv;

	if (this->degree < that.degree) {
		rv.degree = that.degree;
		rv.coeffs = new f2polymod_t[rv.degree + 1];
		for (i = 0; i <= this->degree; i++)
			rv.coeffs[i] = this->coeffs[i] - that.coeffs[i];
		for (i = this->degree+1; i <= that.degree; i++)
			rv.coeffs[i] = - that.coeffs[i];
	}
	else {
		rv.degree = this->degree;
		rv.coeffs = new f2polymod_t[rv.degree + 1];
		for (i = 0; i <= that.degree; i++)
			rv.coeffs[i] = this->coeffs[i] - that.coeffs[i];
		for (i = that.degree+1; i <= this->degree; i++)
			rv.coeffs[i] = this->coeffs[i];
	}
	rv.recompute_degree();
	return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator-(f2polymod_t a) const
{
	f2npoly_t rv(*this);
	rv.coeffs[0] -= a;
	rv.recompute_degree();
	return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator-(void) const
{
	f2npoly_t rv;
	rv.coeffs = new f2polymod_t[rv.degree + 1];
	for (int i = 0; i <= this->degree; i++)
		rv.coeffs[i] = - this->coeffs[i];
	return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator*(f2npoly_t that) const
{
	f2npoly_t rv;
	rv.degree = this->degree + that.degree;
	rv.coeffs = new f2polymod_t[rv.degree + 1];

	f2polymod_t zero = this->coeffs[0] - this->coeffs[0];
	for (int k = 0; k <= rv.degree; k++)
		rv.coeffs[k] = zero;
	for (int i = 0; i <= this->degree; i++)
		for (int j = 0; j <= that.degree; j++)
			rv.coeffs[i+j] += this->coeffs[i] * that.coeffs[j];
	rv.recompute_degree();
	return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator*(f2polymod_t a)
{
	f2npoly_t rv = *this;
	for (int i = 0; i <= rv.degree; i++)
		rv.coeffs[i] *= a;
	rv.recompute_degree();
	return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator/(f2npoly_t that)
{
	f2npoly_t quot, rem;
	this->quot_and_rem(that, quot, rem);
	return quot;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator%(f2npoly_t that)
{
	f2npoly_t quot, rem;
	this->quot_and_rem(that, quot, rem);
	return rem;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::operator/(f2polymod_t a)
{
	f2npoly_t rv = *this;
	for (int i = 0; i <= rv.degree; i++)
		rv.coeffs[i] /= a;
	rv.recompute_degree();
	return rv;
}

// ----------------------------------------------------------------
f2npoly_t & f2npoly_t::operator+=(f2npoly_t that)
{
	*this = *this + that;
	return *this;
}
f2npoly_t & f2npoly_t::operator+=(f2polymod_t a)
{
	*this = *this + a;
	return *this;
}
f2npoly_t & f2npoly_t::operator-=(f2npoly_t that)
{
	*this = *this - that;
	return *this;
}
f2npoly_t & f2npoly_t::operator-=(f2polymod_t a)
{
	*this = *this - a;
	return *this;
}
f2npoly_t & f2npoly_t::operator*=(f2npoly_t that)
{
	*this = *this * that;
	return *this;
}
f2npoly_t & f2npoly_t::operator*=(f2polymod_t a)
{
	*this = *this * a;
	return *this;
}
f2npoly_t & f2npoly_t::operator/=(f2npoly_t & that)
{
	*this = *this / that;
	return *this;
}
f2npoly_t & f2npoly_t::operator%=(f2npoly_t & that)
{
	*this = *this % that;
	return *this;
}
f2npoly_t & f2npoly_t::operator/=(f2polymod_t a)
{
	*this = *this / a;
	return *this;
}

// ----------------------------------------------------------------
// E.g.
// dividend = 1,2,3,4 (1 + 2x + 3x^2 + 4x^3)
// divisor  = 1,1,2   (1 +  x + 2x^2)
// modulus = 7
//
//             q=4,2   r = 4,3
//        +----------
// 1,1,2  |  1,2,3,4
//        |    2,2,4 shift = 1.  4/2 mod 7 = 2.  1,1,2 * 2 = 2,2,4.
//        +----------
//        |  1 0 1
//        |  4 4 1   shift = 0.  1/2 mod 7 = 4   1,1,2 * 4 = 4,4,1
//        +----------
//        |  4 3

// ----------------------------------------------------------------
void f2npoly_t::quot_and_rem(
	f2npoly_t & that,
	f2npoly_t & rquot,
	f2npoly_t & rrem)
{
	f2polymod_t zero = this->coeffs[0] - this->coeffs[0];

	if (that == zero) {
		std::cerr << "f2npoly_t::quot_and_rem:  division by zero.\n";
		exit(1);
	}
	if (*this == zero) {
		rquot = this->prime_sfld_elt(0);
		rrem  = *this;
		return;
	}

	int dividend_degree = this->degree;
	int divisor_degree  = that.degree;

	if (dividend_degree < divisor_degree) {
		rquot = this->prime_sfld_elt(0);
		rrem  = *this;
		return;
	}

	f2npoly_t quot;
	quot.degree = this->degree - that.degree;
	quot.coeffs = new f2polymod_t[quot.degree + 1];

	f2npoly_t rem  = *this;

//       +--------
// ooooo | ooooooo
//       | ooooo
//       +--------
//       |  ooooo
//       +--------
//       |   ooooo
//       +--------
//       |    oooo

// x^5+1 / x^3 = x^2 rem 1
// quot deg = dividend deg - divisor deg
// rem deg  < divisor deg

	int max_shift = dividend_degree - divisor_degree;
	f2polymod_t divisor_leader = that.coeffs[divisor_degree];
	f2polymod_t dlinv;
	if (!divisor_leader.recip(dlinv)) {
		std::cerr << "f2npoly_t::quot_and_rem:  zero or zero divisor "
			<< "in leading coefficient " << divisor_leader << "\n"
			<< "  of divisor " << that << ".\n";
		exit(1);
	}
	for (int shift = max_shift; shift >= 0; shift--) {
		f2polymod_t rem_leader = rem.coeffs[shift + divisor_degree];
		f2polymod_t multiplier = rem_leader * dlinv;
		f2npoly_t divisor_with_mul = that * multiplier;
		quot.coeffs[shift] = multiplier;

		int stop = shift + divisor_with_mul.degree;
		for (int i = shift; i <= stop; i++)
			rem.coeffs[i] -= divisor_with_mul.coeffs[i-shift];
	}

	// Quotient degree must be the difference of dividend and divisor
	// degrees.  If not, we have made a mistake.
	if (quot.coeffs[quot.degree] == zero) {
		std::cerr << "f2npoly_t division: coding error.\n";
		exit(1);
	}

	// The remainder degree is less than the divisor's degree.
	rem.recompute_degree();

	rquot = quot;
	rrem  = rem;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::gcd(f2npoly_t & that)
{
	f2npoly_t c, q, r;
	f2npoly_t d;   // Return value.

	if (*this == 0)
		return that;
	if (that == 0)
		return *this;

	c = *this;
	d = that;

	while (1) {

		c.quot_and_rem(d, q, r);

		if (r == 0)
			break;
		c = d;
		d = r;
	}
	return d;
}

// ----------------------------------------------------------------
f2npoly_t gcd(f2npoly_t a, f2npoly_t b)
{
	return a.gcd(b);
}

// ----------------------------------------------------------------
// Blankinship's algorithm.

f2npoly_t f2npoly_t::ext_gcd(f2npoly_t & that, f2npoly_t & rm, f2npoly_t & rn)
{
	f2npoly_t mprime, nprime, c, q, r, t, qm, qn;
	f2npoly_t d;   // Return value.

	// Initialize
	mprime = this->prime_sfld_elt(1);
	rn     = this->prime_sfld_elt(1);
	rm     = this->prime_sfld_elt(0);
	nprime = this->prime_sfld_elt(0);
	c = *this;
	d = that;

	while (1) {
		c.quot_and_rem(d, q, r);
		if (r == 0)
			break;

		c = d;
		d = r;

		t      = mprime;
		mprime = rm;
		qm     = q * rm;
		rm     = t - qm;

		t      = nprime;
		nprime = rn;
		qn     = q * rn;
		rn     = t - qn;
	}
	return d;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::exp(int e)
{
	int deg = this->find_degree();
	f2npoly_t xp   = *this;
	f2npoly_t zero = this->prime_sfld_elt(0);
	f2npoly_t one  = this->prime_sfld_elt(1);
	f2npoly_t rv   = one;

	if (*this == zero) {
		if (e == 0) {
			std::cerr << "f2npoly_t::exp:  0 ^ 0 undefined.\n";
			exit(1);
		}
		else if (e < 0) {
			std::cerr << "f2npoly_t::exp:  division by zero.\n";
			exit(1);
		}
		else {
			return zero;
		}
	}
	else if (deg == 0) {
		// Unit
		return f2npoly_t(this->coeffs[0].exp(e));
	}
	else {
		// Degree 1 or higher.
		if (e < 0) {
			std::cerr << "f2npoly_t::exp:  division by non-unit.\n";
			exit(1);
		}
		else {
			while (e != 0) {
				if (e & 1)
					rv *= xp;
				e = (unsigned)e >> 1;
				xp *= xp;
			}
			return rv;
		}
	}
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_t::deriv(void)
{
	if (this->degree == 0)
		return this->prime_sfld_elt(0);

	f2npoly_t rv(*this);
	f2poly_t m = this->coeffs[0].get_modulus();
	rv.degree--;
	for (int i = 1; i <= this->degree; i++)
		rv.coeffs[i-1] = this->coeffs[i] * f2polymod_t(i, m);
	rv.recompute_degree();
	return rv;
}

// ----------------------------------------------------------------
// E.g. (ax^2 + bx + c) ^ 2 = a^2 x^4 + b^2 x^2 + c^2, where odd coefficients
// vanish since the characteristic is 2.  To square-root a given polynomial:
//
// * Make sure the odd-degree terms are zero.
// * For even-degree terms, cut the exponent in half.
// * For even-degree terms, square-root the coefficients.
//
// For extension fields of F2, the squaring map is automorphic.  Therefore
// square roots exists for all coefficients.  Let n be the degree over F2.
// Then a^{2^n} = a for all coefficients, and a^{2^{n-1}} = sqrt(a).

int f2npoly_t::square_root(f2npoly_t & rroot)
{
	f2poly_t m = this->coeffs[0].get_modulus();
	f2polymod_t zero(0, m);
	int si, di;
	f2npoly_t out;
	int n = m.find_degree();
	int pow = 1 << (n-1);

	out.set_coeff(this->degree, zero);
	for (di = this->degree - 1; di >= 0; di--)
		out.coeffs[di] = zero;

	for (si = 0, di = 0; si <= this->degree; si += 2, di++) {
		out.coeffs[di] = this->coeffs[si].exp(pow);
		if (si+1 > this->degree)
			break;
		if (this->coeffs[si+1] != zero)
			return 0;
	}
	out.recompute_degree();
	rroot = out;
	return 1;
}

// ----------------------------------------------------------------
f2polymod_t f2npoly_t::eval(f2polymod_t c)
{
	f2polymod_t rv = this->coeffs[this->degree];
	for (int i = this->degree - 1; i >= 0; i--) {
		rv *= c;
		rv += this->coeffs[i];
	}
	return rv;
}

// ----------------------------------------------------------------
int f2npoly_t::find_degree(void) const
{
	return this->degree;
}

// ----------------------------------------------------------------
f2polymod_t f2npoly_t::get_coeff(int deg) const
{
	if (deg < 0)
		this->bounds_check(deg);

	if (deg > this->degree)
		return (this->coeffs[0] - this->coeffs[0]);
	else
		return this->coeffs[deg];
}

// ----------------------------------------------------------------
void f2npoly_t::set_coeff(int pos, f2polymod_t c)
{
	if (pos < 0)
		this->bounds_check(pos);

	f2polymod_t zero(0, this->coeffs[0].get_modulus());
	if (pos > this->degree) {
		f2polymod_t * temp = new f2polymod_t[pos+1];
		for (int i = 0; i <= this->degree; i++)
			temp[i] = this->coeffs[i];
		for (int i = this->degree + 1; i < pos; i++)
			temp[i] = zero;
		temp[pos] = c;

		delete [] this->coeffs;
		this->coeffs = temp;
		this->degree = pos;
		if (c == zero)
			this->recompute_degree();
	}
	else {
		this->coeffs[pos] = c;
		if ((pos == this->degree) && (c == zero))
			this->recompute_degree();
	}
}

// ----------------------------------------------------------------
void f2npoly_t::change_modulus(f2poly_t new_modulus)
{
	for (int i = 0; i <= this->degree; i++)
		this->coeffs[i].change_modulus(new_modulus);
}

// ----------------------------------------------------------------
void f2npoly_t::recompute_degree(void)
{
	int is_zero = 1;
	f2polymod_t zero = this->coeffs[0] - this->coeffs[0];

	for (int i = this->degree; i >= 0; i--) {
		if (this->coeffs[i] != zero) {
			is_zero = 0;
			this->degree = i;
			break;
		}
	}
	if (is_zero)
		this->degree = 0;
}

// ----------------------------------------------------------------
int f2npoly_t::operator==(int v) const
{
	int d = this->degree;
	if (d != 0)
		return 0;
	return this->coeffs[0].get_residue() == v;
}

// ----------------------------------------------------------------
int f2npoly_t::operator!=(int v) const
{
	return !(*this == v);
}

// ----------------------------------------------------------------
int f2npoly_t::operator==(f2npoly_t that) const
{
	return this->cmp(CMP_EQ, that);
}

// ----------------------------------------------------------------
int f2npoly_t::operator!=(f2npoly_t that) const
{
	return this->cmp(CMP_NE, that);
}

// ----------------------------------------------------------------
int  f2npoly_t::operator< (f2npoly_t that) const
{
	return this->cmp(CMP_LT, that);
}

// ----------------------------------------------------------------
int  f2npoly_t::operator> (f2npoly_t that) const
{
	return this->cmp(CMP_GT, that);
}

// ----------------------------------------------------------------
int  f2npoly_t::operator<=(f2npoly_t that) const
{
	return this->cmp(CMP_LE, that);
}

// ----------------------------------------------------------------
int  f2npoly_t::operator>=(f2npoly_t that) const
{
	return this->cmp(CMP_GE, that);
}

// ----------------------------------------------------------------
void f2npoly_t::increment(void)
{
	f2poly_t m = this->coeffs[0].get_modulus();
	int d = m.find_degree();
	f2poly_t max(0);
	max.set_bit(d);
	f2poly_t r0(0), r1(1);
	f2polymod_t m0(r0, m);
	f2polymod_t m1(r1, m);
	for (int i = 0; i <= this->degree; i++) {
		f2poly_t r = this->coeffs[i].get_residue();
		r.increment();
		if (r != max) {
			this->coeffs[i] = f2polymod_t(r, m);
			return;
		}
		else {
			this->coeffs[i] = f2polymod_t(r0, m);
		}
	}
	this->set_coeff(this->degree + 1, m1);
}

// ----------------------------------------------------------------
int f2npoly_t::cmp(int cmp, f2npoly_t & that) const
{
	int direction = 0; // -1 = less, 0 = equal, +1 = greater;

	if (this->degree < that.degree) {
		direction = -1;
	}
	else if (this->degree > that.degree) {
		direction =  1;
	}
	else {
		for (int i = this->degree; i >= 0; i--) {
			if (this->coeffs[i] < that.coeffs[i]) {
				direction = -1;
				break;
			}
			else if (this->coeffs[i] > that.coeffs[i]) {
				direction =  1;
				break;
			}
		}
	}

	switch (cmp) {
	case CMP_LE: return (direction <= 0); break;
	case CMP_LT: return (direction <  0); break;
	case CMP_EQ: return (direction == 0); break;
	case CMP_NE: return (direction != 0); break;
	case CMP_GE: return (direction >= 0); break;
	case CMP_GT: return (direction >  0); break;
	default:
		std::cerr << "Ack!\n";
		exit(1);
		return 0;
		break;
	}
}

// ----------------------------------------------------------------
void f2npoly_t::bounds_check(int deg) const
{
	if ((deg < 0) || (deg > this->degree)) {
		std::cerr
			<< "f2npoly_t: degree "
			<< deg
			<< " out of bounds 0:"
			<< this->degree
			<< ".\n";
		exit(1);
	}
}

// ----------------------------------------------------------------
std::ostream & operator<<(
	std::ostream & os,
	const f2npoly_t & poly)
{
	int d = poly.find_degree();
	f2poly_t m = poly.get_coeff(0).get_modulus();

	for (int i = d; i >= 0; i--) {
		if (m > 9)
			if (i < d)
				os << ":";
		os << poly.get_coeff(i).get_residue();
	}

	return os;
}

// ----------------------------------------------------------------
std::istream & operator>>(
	std::istream & is,
	f2npoly_t & poly)
{
	f2poly_t r;
	f2poly_t m  = poly.coeffs[0].get_modulus();
	poly = f2npoly_t(f2polymod_t(0, m));

	if (m <= 10) {
		char c;
		is >> c;
		if (is.fail()) {
			std::cerr << "f2npoly_t: scan failure.\n";
			return is;
		}
		if (!isdigit(c)) {
			std::cerr << "f2npoly_t: non-numeric input '"
				<< c << "'\n";
			return is;
		}
		r = c - '0';
		poly.coeffs[0] = f2polymod_t(r, m);

		while (isdigit(is.peek())) {
			r = c - '0';
			poly.promote_and_add(f2polymod_t(r, m));
		}
	}
	else {
		is >> r;
		if (is.fail()) {
			std::cerr << "f2npoly_t: scan failure.\n";
			return is;
		}
		poly.coeffs[0] = f2polymod_t(r, m);
		while (is.peek() == ':') {
			(void)is.get();
			is >> r;
			if (is.fail()) {
				std::cerr << "f2npoly_t: scan failure.\n";
				return is;
			}
			poly.promote_and_add(f2polymod_t(r, m));
		}

	}
	poly.recompute_degree();
	return is;
}

// ----------------------------------------------------------------
// Coefficient 0 modulus must already be set.

std::istringstream & operator>>(std::istringstream & iss,
	f2npoly_t & poly)
{
	f2poly_t r;
	f2poly_t m  = poly.coeffs[0].get_modulus();
	poly = f2npoly_t(f2polymod_t(0, m));

	iss >> r;
	if (iss.fail()) {
		std::cerr << "f2npoly_t: scan failure at \""
			<< iss.str() << "\"\n";
		return iss;
	}
	poly.coeffs[0] = f2polymod_t(r, m);
	while (!iss.eof() && (iss.peek() == ':')) {
		(void)iss.get();
		iss >> r;
		if (iss.fail()) {
			std::cerr << "f2npoly_t: scan failure at \""
				<< iss.str() << "\"\n";
			return iss;
		}
		poly.promote_and_add(f2polymod_t(r, m));
	}

	poly.recompute_degree();
	return iss;
}

// ----------------------------------------------------------------
int f2npoly_t::from_string(char * string, f2poly_t m)
{
	if (this->coeffs)
		delete [] this->coeffs;

	int num_colons = 0;
	for (char * q = string; *q; q++)
		if (*q == ':')
			num_colons++;

	char * dup = strdup(string);
	char ** argv = new char *[num_colons + 1];
	int argc = tokenize(dup, ":", argv, num_colons+1);
	if (argc < 1) {
		// Needs an error message, but this coding error is
		// unlikely since we already counted colons.
		return 0;
	}

	this->degree = argc - 1;
	this->coeffs = new f2polymod_t[this->degree + 1];
	int argi, ci;
	for (argi = 0, ci = this->degree; argi < argc; argi++, ci--) {
		// Scan each coefficient, then reduce mod m
		f2poly_t r;

		std::istringstream iss(argv[argi], std::ios_base::in);
		iss >> r;
		if (iss.fail()) {
			std::cerr << "f2npoly_t::from_string: "
				<< "scan failure at \""
				<< string << "\"\n";
			return 0;
		}
		else {
			this->coeffs[ci] = f2polymod_t(r, m);
		}
	}
	delete [] argv;
	free(dup);

	this->recompute_degree();
	return 1;
}

// ----------------------------------------------------------------
void f2npoly_t::promote(void)
{
	if (!this->coeffs) {
		std::cerr << "f2npoly_t::promote: null data.\n";
		exit(1);
	}
	f2polymod_t * ocoeffs = this->coeffs;
	this->coeffs = new f2polymod_t[this->degree + 2];
	for (int i = 0; i <= this->degree; i++)
		this->coeffs[i+1] = ocoeffs[i];
	this->coeffs[0] = this->coeffs[1] - this->coeffs[1];
	this->degree++;
	delete [] ocoeffs;
}

// ----------------------------------------------------------------
void f2npoly_t::promote_and_add(f2polymod_t c0)
{
	this->promote();
	this->coeffs[0] = c0;
}
