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

// Elements of the ring Z_2[x], implemented using a single 64-bit integer.

#ifndef F2IPOLY_T_H
#define F2IPOLY_T_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include "bit_t.h"

#define F2IPOLY_MAX_DEGREE ((int)(8 * sizeof(unsigned long long) - 1))

class f2ipoly_t {
public:
	f2ipoly_t(void);

	f2ipoly_t(int c0);
	f2ipoly_t(int c1, int c0);
	f2ipoly_t(int c2, int c1, int c0);
	f2ipoly_t(int c3, int c2, int c1, int c0);
	f2ipoly_t(int c4, int c3, int c2, int c1, int c0);
	f2ipoly_t(int c5, int c4, int c3, int c2, int c1, int c0);

	static f2ipoly_t from_base_rep(unsigned long long b);
	f2ipoly_t   prime_sfld_elt(int v) const;
	int from_string(char * string);

	f2ipoly_t(const f2ipoly_t & that);
	~f2ipoly_t(void);

	f2ipoly_t & operator=(int bit); // 0 or 1; other bits ignored.
	f2ipoly_t & operator=(f2ipoly_t that);
	f2ipoly_t   operator+(f2ipoly_t that) const;
	f2ipoly_t   operator-(f2ipoly_t that) const;
	f2ipoly_t   operator-(void) const;
	f2ipoly_t   operator*(f2ipoly_t that) const;
	f2ipoly_t   operator*(int bit); // 0 or 1; other bits ignored.
	f2ipoly_t   operator/(f2ipoly_t that);
	f2ipoly_t   operator%(f2ipoly_t that);

	f2ipoly_t & operator+=(f2ipoly_t that);
	f2ipoly_t & operator-=(f2ipoly_t that);
	f2ipoly_t & operator*=(f2ipoly_t that);
	f2ipoly_t & operator*=(int bit); // 0 or 1; other bits ignored.
	f2ipoly_t & operator/=(f2ipoly_t & that);
	f2ipoly_t & operator%=(f2ipoly_t & that);

	void quot_and_rem(f2ipoly_t & that, f2ipoly_t & rquot,
		f2ipoly_t & rrem);
	f2ipoly_t gcd(f2ipoly_t & that);
	f2ipoly_t ext_gcd(f2ipoly_t & that, f2ipoly_t & rm, f2ipoly_t & rn);
	f2ipoly_t exp(int power);
	f2ipoly_t deriv(void);
	int  square_root(f2ipoly_t & rroot);
	bit_t eval(bit_t c);
	int eval(int c);
	int zcount_one_bits(void);

	int find_degree(void) const; // deg(0) is defined to be 0.
	int get_coeff(int pos) const;
	int bit_at(int pos) const;
	void set_bit(int pos);

	int operator==(int v) const;
	int operator!=(int v) const;
	int operator==(f2ipoly_t that) const;
	int operator!=(f2ipoly_t that) const;
	// F2[x] is *not* totally ordered.  Nonetheless, these methods are
	// handy for looping and sorting.
	int operator< (f2ipoly_t that) const;
	int operator> (f2ipoly_t that) const;
	int operator<=(f2ipoly_t that) const;
	int operator>=(f2ipoly_t that) const;
	void increment(void);

	friend std::ostream & operator<<(std::ostream & os,
		const f2ipoly_t & poly);
	friend std::istream & operator>>(std::istream & is,
		f2ipoly_t & poly);

	//friend std::ostringstream & operator<<(std::ostringstream & oss,
		//const f2ipoly_t & poly);
	friend std::istringstream & operator>>(std::istringstream & iss,
		f2ipoly_t & poly);

private:
	unsigned long long bits;

	void bounds_check(int deg) const;
};

#endif // F2IPOLY_T_H
