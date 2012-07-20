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

// Elements of the ring F_q[x].

#ifndef FPNPOLY_T_H
#define FPNPOLY_T_H

#include <iostream>
#include <iomanip>
#include "fppolymod_t.h"

class fpnpoly_t
{
public:
	fpnpoly_t(void);

	fpnpoly_t(fppolymod_t c0);
	fpnpoly_t(fppolymod_t c1, fppolymod_t c0);
	fpnpoly_t(fppolymod_t c2, fppolymod_t c1, fppolymod_t c0);
	fpnpoly_t(fppolymod_t c3, fppolymod_t c2, fppolymod_t c1,
		fppolymod_t c0);
	fpnpoly_t(fppolymod_t c4, fppolymod_t c3, fppolymod_t c2,
		fppolymod_t c1, fppolymod_t c0);
	fpnpoly_t(fppolymod_t c5, fppolymod_t c4, fppolymod_t c3,
		fppolymod_t c2, fppolymod_t c1, fppolymod_t c0);

	static fpnpoly_t from_base_rep(int b, fppoly_t m);

	fpnpoly_t(const fpnpoly_t & that);
	~fpnpoly_t(void);

	fpnpoly_t   prime_sfld_elt(int v) const;
	static fpnpoly_t   prime_sfld_elt(int v, fppoly_t m);
	int get_char(void);

	fpnpoly_t & operator=(fpnpoly_t that);
	fpnpoly_t   operator+(fpnpoly_t that) const;
	fpnpoly_t   operator+(fppolymod_t a)  const;
	fpnpoly_t   operator-(fpnpoly_t that) const;
	fpnpoly_t   operator-(fppolymod_t a)  const;
	fpnpoly_t   operator-(void) const;
	fpnpoly_t   operator*(fpnpoly_t that) const;
	fpnpoly_t   operator*(fppolymod_t a);
	fpnpoly_t   operator*(intmod_t a);
	fpnpoly_t   operator/(fpnpoly_t that);
	fpnpoly_t   operator%(fpnpoly_t that);
	fpnpoly_t   operator/(fppolymod_t a);

	fpnpoly_t & operator+=(fpnpoly_t that);
	fpnpoly_t & operator+=(fppolymod_t a);
	fpnpoly_t & operator-=(fpnpoly_t that);
	fpnpoly_t & operator-=(fppolymod_t a);
	fpnpoly_t & operator*=(fpnpoly_t that);
	fpnpoly_t & operator*=(fppolymod_t a);
	fpnpoly_t & operator/=(fpnpoly_t & that);
	fpnpoly_t & operator%=(fpnpoly_t & that);
	fpnpoly_t & operator/=(fppolymod_t a);

	void quot_and_rem(fpnpoly_t & that, fpnpoly_t & rquot, fpnpoly_t & rrem);
	fpnpoly_t gcd(fpnpoly_t & that);
	fpnpoly_t ext_gcd(fpnpoly_t & that, fpnpoly_t & rm, fpnpoly_t & rn);
	fpnpoly_t exp(int power);
	fpnpoly_t deriv(void);
	int  pth_root(fpnpoly_t & rroot);
	fppolymod_t eval(fppolymod_t c);

	int find_degree(void) const; // deg(0) is defined to be 0.
	fppolymod_t get_coeff(int deg) const;
	void set_coeff(int pos, fppolymod_t c);

	int operator==(int v) const;
	int operator!=(int v) const;
	int operator==(fpnpoly_t that) const;
	int operator!=(fpnpoly_t that) const;
	// Fq[x] is *not* totally ordered.  Nonetheless, these methods are
	// handy for looping and sorting.
	int operator< (fpnpoly_t that) const;
	int operator> (fpnpoly_t that) const;
	int operator<=(fpnpoly_t that) const;
	int operator>=(fpnpoly_t that) const;
	void increment(void);

	friend std::ostream & operator<<(std::ostream & os,
		const fpnpoly_t & poly);
	// Modulus must have already been set:
	friend std::istream & operator>>(std::istream & is,
		fpnpoly_t & poly);
	int from_string(char * string, fppoly_t m);

	void promote(void);
	void promote_and_add(fppolymod_t c0);

private:
	fppolymod_t * coeffs;
	int degree;

	int  cmp(int cmp, fpnpoly_t & that) const;
	void bounds_check(int deg) const;
	void recompute_degree();
};

// Same as the gcd method, but overloaded.  This is important for template use.
fpnpoly_t gcd(fpnpoly_t a, fpnpoly_t b);

#endif // FPNPOLY_T_H
