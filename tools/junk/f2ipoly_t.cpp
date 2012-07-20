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

#include "f2ipoly_t.h"
#include "cmps.h"
#include "log2.h"
#include "count_bits.h"

#define F2IPOLY_BIT_AT(p,j)    ( ((p) >> (j)) & 1 )
#define F2IPOLY_SET_BIT(p,j)   ( (p) |=  ((unsigned long long)1 << (j)) )
#define F2IPOLY_CLEAR_BIT(p,j) ( (p) &= ~((unsigned long long)1 << (j)) )

// ----------------------------------------------------------------
f2ipoly_t::f2ipoly_t(void)
{
	this->bits = 0LL;
}

// ----------------------------------------------------------------
f2ipoly_t::f2ipoly_t(int c0)
{
	this->bits = (c0 & 1);
}
f2ipoly_t::f2ipoly_t(int c1, int c0)
{
	this->bits =
		((c1 & 1) << 1) |
		(c0 & 1);
}
f2ipoly_t::f2ipoly_t(int c2, int c1, int c0)
{
	this->bits =
		((c2 & 1) << 2) |
		((c1 & 1) << 1) |
		(c0 & 1);
}
f2ipoly_t::f2ipoly_t(int c3, int c2, int c1, int c0)
{
	this->bits =
		((c3 & 1) << 3) |
		((c2 & 1) << 2) |
		((c1 & 1) << 1) |
		(c0 & 1);
}
f2ipoly_t::f2ipoly_t(int c4, int c3, int c2, int c1, int c0)
{
	this->bits =
		((c4 & 1) << 4) |
		((c3 & 1) << 3) |
		((c2 & 1) << 2) |
		((c1 & 1) << 1) |
		(c0 & 1);
}
f2ipoly_t::f2ipoly_t(int c5, int c4, int c3, int c2, int c1, int c0)
{
	this->bits =
		((c5 & 1) << 5) |
		((c4 & 1) << 4) |
		((c3 & 1) << 3) |
		((c2 & 1) << 2) |
		((c1 & 1) << 1) |
		(c0 & 1);
}

// ----------------------------------------------------------------
// This is a static method.
f2ipoly_t f2ipoly_t::from_base_rep(unsigned long long b)
{
	f2ipoly_t rv;
	rv.bits = b;
	return rv;
}

// ----------------------------------------------------------------
int f2ipoly_t::from_string(char * string)
{
	std::istringstream iss(string, std::ios_base::in);
	iss.flags(std::ios_base::hex);
	iss >> this->bits;
	return iss.fail() ? 0 : 1;
}

// ----------------------------------------------------------------
f2ipoly_t::f2ipoly_t(const f2ipoly_t & that)
{
	this->bits = that.bits;
}

// ----------------------------------------------------------------
f2ipoly_t::~f2ipoly_t(void)
{
	this->bits = 0LL;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_t::prime_sfld_elt(int v) const
{
	f2ipoly_t rv(v & 1);
	return rv;
}

// ----------------------------------------------------------------
f2ipoly_t & f2ipoly_t::operator=(int bit)
{
	this->bits = (unsigned long long)(bit & 1);
	return *this;
}

// ----------------------------------------------------------------
f2ipoly_t & f2ipoly_t::operator=(f2ipoly_t that)
{
	this->bits = that.bits;
	return *this;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_t::operator+(f2ipoly_t that) const
{
	f2ipoly_t rv;
	rv.bits = this->bits ^ that.bits;
	return rv;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_t::operator-(f2ipoly_t that) const
{
	f2ipoly_t rv;
	rv.bits = this->bits ^ that.bits;
	return rv;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_t::operator-(void) const
{
	return *this;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_t::operator*(f2ipoly_t that) const
{
	f2ipoly_t prod = 0;
	int this_deg = this->find_degree();
	int that_deg = that.find_degree();
	int prod_deg = this_deg + that_deg;
	if (prod_deg > F2IPOLY_MAX_DEGREE) {
		std::cerr << "f2ipoly_t: multiplication overflow.\n";
		exit(1);
	}

	unsigned long long a = this->bits;
	unsigned long long b = that.bits;
	unsigned long long c = 0LL;
	unsigned long long ashift = a;

	for (int j = 0; j <= that_deg; j++) {
		if (F2IPOLY_BIT_AT(b, j))
			c ^= ashift;
		ashift <<= 1;
	}

	prod.bits = c;
	return prod;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_t::operator*(int bit)
{
	f2ipoly_t rv;
	if (bit & 1)
		rv.bits = this->bits;
	else
		rv.bits = 0LL;
	return rv;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_t::operator/(f2ipoly_t that)
{
	f2ipoly_t quot, rem;
	this->quot_and_rem(that, quot, rem);
	return quot;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_t::operator%(f2ipoly_t that)
{
	f2ipoly_t quot, rem;
	this->quot_and_rem(that, quot, rem);
	return rem;
}

// ----------------------------------------------------------------
f2ipoly_t & f2ipoly_t::operator+=(f2ipoly_t that)
{
	*this = *this + that;
	return *this;
}
f2ipoly_t & f2ipoly_t::operator-=(f2ipoly_t that)
{
	*this = *this - that;
	return *this;
}
f2ipoly_t & f2ipoly_t::operator*=(f2ipoly_t that)
{
	*this = *this * that;
	return *this;
}
f2ipoly_t & f2ipoly_t::operator*=(int bit)
{
	*this = *this * bit;
	return *this;
}
f2ipoly_t & f2ipoly_t::operator/=(f2ipoly_t & that)
{
	*this = *this / that;
	return *this;
}
f2ipoly_t & f2ipoly_t::operator%=(f2ipoly_t & that)
{
	*this = *this % that;
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
// dividend = *this
// divisor  =  that

void f2ipoly_t::quot_and_rem(
	f2ipoly_t & that,
	f2ipoly_t & rquot,
	f2ipoly_t & rrem)
{
	int dividend_l1_pos;
	int divisor_l1_pos;
	int l1_diff;
	unsigned long long shift_divisor;
	int check_pos;
	int quot_pos;

	if (that == 0) {
		// Divisor is zero.
		std::cerr << "f2ipoly_t::quot_and_rem:  Divide by zero.\n";
		exit(1);
	}
	divisor_l1_pos = that.find_degree();

	if (*this == 0) {
		rquot = 0;
		rrem  = 0;
		return;
	}
	dividend_l1_pos = this->find_degree();

	l1_diff = dividend_l1_pos - divisor_l1_pos;

	if (l1_diff < 0) {
		// Dividend has lower degree than divisor.
		rquot = 0;
		rrem = *this;
		return;
	}

	shift_divisor = that.bits << l1_diff;

	rrem = *this;
	rquot = 0;
	for (
		check_pos = dividend_l1_pos, quot_pos = l1_diff;
		check_pos >= divisor_l1_pos;
		check_pos--, quot_pos--)
	{
		if (F2IPOLY_BIT_AT(rrem.bits, check_pos)) {
			rrem.bits ^= shift_divisor;
			F2IPOLY_SET_BIT(rquot.bits, quot_pos);
		}
		shift_divisor >>= 1;
	}
}

// ----------------------------------------------------------------
f2ipoly_t f2ipoly_t::gcd(f2ipoly_t & that)
{
	f2ipoly_t c, q, r;
	f2ipoly_t d;   // Return value.

	if (*this == 0)
		return that;
	if (that == 0)
		return *this;

	c = *this;
	d = that;

	while (1) {

		// Divide
		// q = c / d, r = c % d
		c.quot_and_rem(d, q, r);
		// Note:  now c =  < d

		if (r == 0)
			break;
		// Recycle
		c = d;
		d = r;
	}
	return d;
}

// ----------------------------------------------------------------
// Blankinship's algorithm.

f2ipoly_t f2ipoly_t::ext_gcd(f2ipoly_t & that, f2ipoly_t & rm, f2ipoly_t & rn)
{
	f2ipoly_t mprime, nprime, c, q, r, t, qm, qn;
	f2ipoly_t d;   // Return value.

	if (*this == 0) {
		rm.bits = 0LL;
		rn.bits = 1LL;
		return that;
	}
	if (that == 0) {
		rm.bits = 1LL;
		rn.bits = 0LL;
		return *this;
	}

	// Initialize
	mprime.bits = 1LL;
	rn    .bits = 1LL;
	rm    .bits = 0LL;
	nprime.bits = 0LL;
	c = *this;
	d = that;

	while (1) {

		// Divide
		// q = c / d, r = c % d
		c.quot_and_rem(d, q, r);
		// Note:  now c = qd + r and 0 <= r < d

		// Remainder zero?
		if (r == 0)
			break;

		// Recycle
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
f2ipoly_t f2ipoly_t::exp(int e)
{
	int deg = this->find_degree();
	f2ipoly_t xp = *this;
	f2ipoly_t zero(0);
	f2ipoly_t one(1);
	f2ipoly_t rv = one;

	if (*this == zero) {
		if (e == 0) {
			std::cerr << "f2ipoly_t::exp:  0 ^ 0 undefined.\n";
			exit(1);
		}
		else if (e < 0) {
			std::cerr << "f2ipoly_t::exp:  division by zero.\n";
			exit(1);
		}
		else {
			return zero;
		}
	}
	else if (deg == 0) {
		// Unit
		return one;
	}
	else {
		// Degree 1 or higher.
		if (e < 0) {
			std::cerr << "f2ipoly_t::exp:  division by non-unit.\n";
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
f2ipoly_t f2ipoly_t::deriv(void)
{
	f2ipoly_t rv = *this;
	rv.bits >>= 1;
	rv.bits &= 0x5555555555555555LL;
	return rv;
}

// ----------------------------------------------------------------
// Relies on the fact that f(x^p) = f^p(x) over Fp[x].
//
// in  = a4 x^4 + a2 x^2 + a0
// out = a4 x^2 + a2 x   + a0

int f2ipoly_t::square_root(f2ipoly_t & rroot)
{
	int deg = this->find_degree();
	int si, di;
	rroot.bits = 0LL;
	f2ipoly_t inbit(1), outbit(1);

	for (si = 0, di = 0; si <= deg; si+=2, di++) {
		if (this->bits & inbit.bits)
			rroot.bits |= outbit.bits;
		inbit.bits <<= 1;
		if (this->bits & inbit.bits)
			return 0;
		inbit.bits <<= 1;
		outbit.bits <<= 1;
	}

	return 1;
}

// ----------------------------------------------------------------
bit_t f2ipoly_t::eval(bit_t c)
{
	return bit_t(this->eval(c.get_residue()));
}

// ----------------------------------------------------------------
int f2ipoly_t::eval(int c)
{
	if (c & 1)
		return this->zcount_one_bits();
	else
		return this->bits & 1LL;
}

// ----------------------------------------------------------------
int f2ipoly_t::zcount_one_bits(void)
{
	return 1 & count_one_bits((unsigned char *)&this->bits,
		sizeof(this->bits));
}

// ----------------------------------------------------------------
int f2ipoly_t::find_degree(void) const
{
	return find_msb_64(this->bits);
}

// ----------------------------------------------------------------
int f2ipoly_t::get_coeff(int deg) const
{
	this->bounds_check(deg);
	return (this->bits >> deg) & 1;
}

// ----------------------------------------------------------------
int f2ipoly_t::bit_at(int deg) const
{
	this->bounds_check(deg);
	return (this->bits >> deg) & 1;
}

// ----------------------------------------------------------------
void f2ipoly_t::set_bit(int deg)
{
	this->bounds_check(deg);
	this->bits |= 1LL << deg;
}

// ----------------------------------------------------------------
int f2ipoly_t::operator==(int v) const
{
	return this->bits == (unsigned long long)(v & 1);
}

// ----------------------------------------------------------------
int f2ipoly_t::operator!=(int v) const
{
	return !(*this == v);
}

// ----------------------------------------------------------------
int f2ipoly_t::operator==(f2ipoly_t that) const
{
	return this->bits == that.bits;
}

// ----------------------------------------------------------------
int f2ipoly_t::operator!=(f2ipoly_t that) const
{
	return this->bits != that.bits;
}

// ----------------------------------------------------------------
int  f2ipoly_t::operator< (f2ipoly_t that) const
{
	return this->bits < that.bits;
}

// ----------------------------------------------------------------
int  f2ipoly_t::operator> (f2ipoly_t that) const
{
	return this->bits > that.bits;
}

// ----------------------------------------------------------------
int  f2ipoly_t::operator<=(f2ipoly_t that) const
{
	return this->bits <= that.bits;
}

// ----------------------------------------------------------------
int  f2ipoly_t::operator>=(f2ipoly_t that) const
{
	return this->bits >= that.bits;
}

// ----------------------------------------------------------------
void f2ipoly_t::increment(void)
{
	this->bits++;
}

// ----------------------------------------------------------------
void f2ipoly_t::bounds_check(int deg) const
{
	if ((deg < 0) || (deg > (int)F2IPOLY_MAX_DEGREE)) {
		std::cerr
			<< "f2ipoly_t: degree "
			<< deg
			<< " out of bounds 0:"
			<< F2IPOLY_MAX_DEGREE
			<< ".\n";
		exit(1);
	}
}

// ----------------------------------------------------------------
std::ostream & operator<<(
	std::ostream & os,
	const f2ipoly_t & poly)
{
	std::ios_base::fmtflags svflags = os.flags();
	os.flags(std::ios_base::hex);
	os << poly.bits;
	os.flags(svflags);
	return os;
}

// ----------------------------------------------------------------
std::istream & operator>>(
	std::istream & is,
	f2ipoly_t & poly)
{
	std::ios_base::fmtflags svflags = is.flags();
	is.flags(std::ios_base::hex);
	is >> poly.bits;
	is.flags(svflags);

	return is;
}

// ----------------------------------------------------------------
std::istringstream & operator>>(
	std::istringstream & iss,
	f2ipoly_t & poly)
{
	std::ios_base::fmtflags svflags = iss.flags();
	iss.flags(std::ios_base::hex);

	// Attempt to skip over whitespace.
	// The istringstream class appears to permit no way to ignore a set of
	// characters.  E.g. if the input is 0, space, tab, space, 1, then the
	// following won't suffice.

	while (iss.peek() == ' ') iss.ignore(1, ' ');
	while (iss.peek() == '\t') iss.ignore(1, '\t');
	while (iss.peek() == '\n') iss.ignore(1, '\n');

	iss >> poly.bits;
	iss.flags(svflags);

	return iss;
}

//// ----------------------------------------------------------------
// Can't get this to compile.
//std::ostringstream & operator<<(
//	std::ostringstream & oss,
//	const f2ipoly_t & poly)
//{
//	std::ios_base::fmtflags svflags = oss.flags();
//	oss.flags(std::ios_base::hex);
//	oss << poly.bits;
//	oss.flags(svflags);
//	return oss;
//}
