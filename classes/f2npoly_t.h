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

// Elements of the ring F_q[x], with q a power of 2.

#ifndef F2NPOLY_T_H
#define F2NPOLY_T_H

#include <iostream>
#include <iomanip>
#include "f2polymod_t.h"

class f2npoly_t
{
public:
	f2npoly_t(void);

	f2npoly_t(f2polymod_t c0);
	f2npoly_t(f2polymod_t c1, f2polymod_t c0);
	f2npoly_t(f2polymod_t c2, f2polymod_t c1, f2polymod_t c0);
	f2npoly_t(f2polymod_t c3, f2polymod_t c2, f2polymod_t c1,
		f2polymod_t c0);
	f2npoly_t(f2polymod_t c4, f2polymod_t c3, f2polymod_t c2,
		f2polymod_t c1, f2polymod_t c0);
	f2npoly_t(f2polymod_t c5, f2polymod_t c4, f2polymod_t c3,
		f2polymod_t c2, f2polymod_t c1, f2polymod_t c0);

	f2npoly_t(int c0, f2poly_t m);
	f2npoly_t(int c1, int c0, f2poly_t m);
	f2npoly_t(int c2, int c1, int c0, f2poly_t m);
	f2npoly_t(int c3, int c2, int c1, int c0, f2poly_t m);
	f2npoly_t(int c4, int c3, int c2, int c1, int c0, f2poly_t m);
	f2npoly_t(int c5, int c4, int c3, int c2, int c1, int c0, f2poly_t m);

	static f2npoly_t from_base_rep(int b, f2poly_t m);

	f2npoly_t(const f2npoly_t & that);
	~f2npoly_t(void);

	f2npoly_t   prime_sfld_elt(int v) const;
	static f2npoly_t   prime_sfld_elt(int v, f2poly_t m);
	int get_char(void);

	f2npoly_t & operator=(f2npoly_t that);
	f2npoly_t   operator+(f2npoly_t that) const;
	f2npoly_t   operator+(f2polymod_t a)  const;
	f2npoly_t   operator-(f2npoly_t that) const;
	f2npoly_t   operator-(f2polymod_t a)  const;
	f2npoly_t   operator-(void) const;
	f2npoly_t   operator*(f2npoly_t that) const;
	f2npoly_t   operator*(f2polymod_t a);
	f2npoly_t   operator/(f2npoly_t that);
	f2npoly_t   operator%(f2npoly_t that);
	f2npoly_t   operator/(f2polymod_t a);

	f2npoly_t & operator+=(f2npoly_t that);
	f2npoly_t & operator+=(f2polymod_t a);
	f2npoly_t & operator-=(f2npoly_t that);
	f2npoly_t & operator-=(f2polymod_t a);
	f2npoly_t & operator*=(f2npoly_t that);
	f2npoly_t & operator*=(f2polymod_t a);
	f2npoly_t & operator/=(f2npoly_t & that);
	f2npoly_t & operator%=(f2npoly_t & that);
	f2npoly_t & operator/=(f2polymod_t a);

	void quot_and_rem(f2npoly_t & that, f2npoly_t & rquot, f2npoly_t & rrem);
	f2npoly_t gcd(f2npoly_t & that);
	f2npoly_t ext_gcd(f2npoly_t & that, f2npoly_t & rm, f2npoly_t & rn);
	f2npoly_t exp(int power);
	f2npoly_t deriv(void);
	int  square_root(f2npoly_t & rroot);
	f2polymod_t eval(f2polymod_t c);

	int find_degree(void) const; // deg(0) is defined to be 0.
	f2polymod_t get_coeff(int deg) const;
	void set_coeff(int pos, f2polymod_t c);
	void change_modulus(f2poly_t new_modulus);

	int operator==(int v) const;
	int operator!=(int v) const;
	int operator==(f2npoly_t that) const;
	int operator!=(f2npoly_t that) const;
	// Fq[x] is *not* totally ordered.  Nonetheless, these methods are
	// handy for looping and sorting.
	int operator< (f2npoly_t that) const;
	int operator> (f2npoly_t that) const;
	int operator<=(f2npoly_t that) const;
	int operator>=(f2npoly_t that) const;
	void increment(void);

	friend std::ostream & operator<<(std::ostream & os,
		const f2npoly_t & poly);
	// Modulus must have already been set:
	friend std::istream & operator>>(std::istream & is,
		f2npoly_t & poly);
	friend std::istringstream & operator>>(std::istringstream & iss,
		f2npoly_t & poly);
	int from_string(char * string, f2poly_t m);

	void promote(void);
	void promote_and_add(f2polymod_t c0);

private:
	f2polymod_t * coeffs;
	int degree;

	int cmp(int cmp, f2npoly_t & that) const;
	void bounds_check(int deg) const;
	void recompute_degree();
};

// Same as the gcd method, but overloaded.  This is important for template use.
f2npoly_t gcd(f2npoly_t a, f2npoly_t b);

#endif // F2NPOLY_T_H
