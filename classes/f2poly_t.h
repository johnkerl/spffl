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

// Elements of the ring Z_2[x].

#ifndef F2POLY_T_H
#define F2POLY_T_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include "bit_t.h"
#include "count_bits.h"
#include "log2.h"

// One may uncomment this, and/or use -DF2POLY_SMALL on the compile line.
//#define F2POLY_SMALL

// ================================================================
#ifdef F2POLY_SMALL
#define F2POLY_MAX_DEGREE ((int)(8 * sizeof(unsigned) - 1))
#define F2POLY_BIT_AT(p,j)    ( ((p) >> (j)) & 1 )
#define F2POLY_SET_BIT(p,j)   ( (p) |=  ((unsigned )1 << (j)) )
#define F2POLY_CLEAR_BIT(p,j) ( (p) &= ~((unsigned )1 << (j)) )
#endif

// ================================================================
class f2poly_t
{
public:
	f2poly_t(void);

	f2poly_t(int c0);
	f2poly_t(int c1, int c0);
	f2poly_t(int c2, int c1, int c0);
	f2poly_t(int c3, int c2, int c1, int c0);
	f2poly_t(int c4, int c3, int c2, int c1, int c0);
	f2poly_t(int c5, int c4, int c3, int c2, int c1, int c0);

	static f2poly_t from_base_rep(unsigned b);
	f2poly_t   prime_sfld_elt(int v) const;
	int from_string(char * string);
	int get_char(void);

	f2poly_t(const f2poly_t & that);
	~f2poly_t(void);

	f2poly_t & operator=(f2poly_t that);
	f2poly_t & operator=(int bit); // 0 or 1; other bits ignored.
	f2poly_t   operator+(f2poly_t that) const;
	f2poly_t   operator-(f2poly_t that) const;
	f2poly_t   operator-(void) const;
	f2poly_t   operator*(f2poly_t that) const;
	f2poly_t   operator*(int bit); // 0 or 1; other bits ignored.
	f2poly_t   operator/(f2poly_t that);
	f2poly_t   operator%(f2poly_t that);

	f2poly_t & operator+=(f2poly_t that);
	f2poly_t & operator-=(f2poly_t that);
	f2poly_t & operator*=(f2poly_t that);
	f2poly_t & operator*=(int bit); // 0 or 1; other bits ignored.
	f2poly_t & operator/=(f2poly_t & that);
	f2poly_t & operator%=(f2poly_t & that);

	void quot_and_rem(f2poly_t & that, f2poly_t & rquot,
		f2poly_t & rrem);
	f2poly_t gcd(f2poly_t & that);
	f2poly_t ext_gcd(f2poly_t & that, f2poly_t & rm, f2poly_t & rn);
	f2poly_t exp(int power);
	f2poly_t deriv(void);
	int  square_root(f2poly_t & rroot);
	int  eval(int c);
	bit_t  eval(bit_t c);
	int  zcount_one_bits(void);

	int find_degree(void) const; // deg(0) is defined to be 0.

	int operator==(int v) const;
	int operator!=(int v) const;
	int operator==(f2poly_t that) const;
	int operator!=(f2poly_t that) const;
	// F2[x] is *not* totally ordered.  Nonetheless, these methods are
	// handy for looping and sorting.
	int operator< (f2poly_t that) const;
	int operator> (f2poly_t that) const;
	int operator<=(f2poly_t that) const;
	int operator>=(f2poly_t that) const;
	void increment(void);

	friend std::ostream & operator<<(std::ostream & os,
		const f2poly_t & poly);
	friend std::istream & operator>>(std::istream & is,
		f2poly_t & poly);
	friend std::istringstream & operator>>(std::istringstream & iss,
		f2poly_t & poly);

	// If the polynomial's degree is less than deg, zero-padding is done.
	// This facilitates nice tabular output in certain situations.
	void dprint(std::ostream & os, int deg) const;

	void set_coeff(int pos, bit_t b);
	void set_bit(int pos);
	int  bit_at(int pos) const;

private:
#ifdef F2POLY_SMALL
	unsigned bits;
#else
	unsigned * parts;
	int num_parts;
#endif

#ifdef F2POLY_SMALL
	void bounds_check(int deg) const;
	void bounds_check_abend(int deg) const;
#else
	int  cmp(int op, f2poly_t & that) const;
	void promote_n(unsigned shamt);
	void promote_4(void);
	void promote_1(void);
	void demote_1(void);
	void extend_parts(int new_num_parts);
	void trim_parts(void);
	void check_neg_pos(int pos) const;
#endif
	void debug_print(std::ostream & os);
};

// Same as the gcd method, but overloaded.  This is important for template use.
f2poly_t gcd(f2poly_t a, f2poly_t b);

// ================================================================
#ifdef F2POLY_SMALL
inline f2poly_t::f2poly_t(void)
{
	this->bits = 0;
}

inline f2poly_t::f2poly_t(int c0)
{
	this->bits = (c0 & 1);
}
inline f2poly_t::f2poly_t(int c1, int c0)
{
	this->bits =
		((c1 & 1) << 1) |
		(c0 & 1);
}
inline f2poly_t::f2poly_t(int c2, int c1, int c0)
{
	this->bits =
		((c2 & 1) << 2) |
		((c1 & 1) << 1) |
		(c0 & 1);
}
inline f2poly_t::f2poly_t(int c3, int c2, int c1, int c0)
{
	this->bits =
		((c3 & 1) << 3) |
		((c2 & 1) << 2) |
		((c1 & 1) << 1) |
		(c0 & 1);
}
inline f2poly_t::f2poly_t(int c4, int c3, int c2, int c1, int c0)
{
	this->bits =
		((c4 & 1) << 4) |
		((c3 & 1) << 3) |
		((c2 & 1) << 2) |
		((c1 & 1) << 1) |
		(c0 & 1);
}
inline f2poly_t::f2poly_t(int c5, int c4, int c3, int c2, int c1, int c0)
{
	this->bits =
		((c5 & 1) << 5) |
		((c4 & 1) << 4) |
		((c3 & 1) << 3) |
		((c2 & 1) << 2) |
		((c1 & 1) << 1) |
		(c0 & 1);
}

inline f2poly_t f2poly_t::from_base_rep(unsigned b)
{
	f2poly_t rv;
	rv.bits = b;
	return rv;
}

inline f2poly_t::f2poly_t(const f2poly_t & that)
{
	this->bits = that.bits;
}

inline f2poly_t::~f2poly_t(void)
{
}

inline f2poly_t f2poly_t::prime_sfld_elt(int v) const
{
	f2poly_t rv(v & 1);
	return rv;
}

inline int f2poly_t::get_char(void)
{
	return 2;
}

inline f2poly_t & f2poly_t::operator=(int bit)
{
	this->bits = (unsigned)(bit & 1);
	return *this;
}

inline f2poly_t & f2poly_t::operator=(f2poly_t that)
{
	this->bits = that.bits;
	return *this;
}

inline f2poly_t f2poly_t::operator+(f2poly_t that) const
{
	f2poly_t rv;
	rv.bits = this->bits ^ that.bits;
	return rv;
}

inline f2poly_t f2poly_t::operator*(int bit)
{
	f2poly_t rv;
	if (bit & 1)
		rv.bits = this->bits;
	else
		rv.bits = 0;
	return rv;
}

inline f2poly_t f2poly_t::deriv(void)
{
	f2poly_t rv = *this;
	rv.bits >>= 1;
	rv.bits &= 0x55555555;
	return rv;
}

inline int f2poly_t::eval(int c)
{
	if (c & 1)
		return this->zcount_one_bits();
	else
		return this->bits & 1;
}

inline int f2poly_t::zcount_one_bits(void)
{
	return 1 & count_one_bits((unsigned char *)&this->bits,
		sizeof(this->bits));
}

inline int f2poly_t::find_degree(void) const
{
	return find_msb_32(this->bits);
}

inline int f2poly_t::operator==(int v) const
{
	return this->bits == (unsigned)(v & 1);
}

inline int f2poly_t::operator!=(int v) const
{
	return !(*this == v);
}

inline int f2poly_t::operator==(f2poly_t that) const
{
	return this->bits == that.bits;
}

inline int f2poly_t::operator!=(f2poly_t that) const
{
	return this->bits != that.bits;
}

inline int  f2poly_t::operator< (f2poly_t that) const
{
	return this->bits < that.bits;
}

inline int  f2poly_t::operator> (f2poly_t that) const
{
	return this->bits > that.bits;
}

inline int  f2poly_t::operator<=(f2poly_t that) const
{
	return this->bits <= that.bits;
}

inline int  f2poly_t::operator>=(f2poly_t that) const
{
	return this->bits >= that.bits;
}

inline void f2poly_t::increment(void)
{
	this->bits++;
}

inline int f2poly_t::bit_at(int deg) const
{
	this->bounds_check(deg);
	return (this->bits >> deg) & 1;
}

inline void f2poly_t::set_bit(int deg)
{
	this->bounds_check(deg);
	this->bits |= 1 << deg;
}

inline void f2poly_t::set_coeff(int deg, bit_t b)
{
	this->bounds_check(deg);
	if (b.get_residue())
		this->bits |= 1 << deg;
	else
		this->bits &= ~(1 << deg);
}

inline void f2poly_t::bounds_check(int deg) const
{
	if ((deg < 0) || (deg > (int)F2POLY_MAX_DEGREE))
		this->bounds_check_abend(deg);
}

#endif // F2POLY_SMALL

// ================================================================
#endif // F2POLY_T_H
