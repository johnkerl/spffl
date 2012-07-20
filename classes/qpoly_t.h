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

// Elements of the ring Q[x].

//#error under construction

#ifndef QPOLY_T_H
#define QPOLY_T_H

#include <iostream>
#include <iomanip>
#include "intrat_t.h"

class qpoly_t {
public:
	qpoly_t(void);

	qpoly_t(intrat_t c0);
	qpoly_t(intrat_t c1, intrat_t c0);
	qpoly_t(intrat_t c2, intrat_t c1, intrat_t c0);
	qpoly_t(intrat_t c3, intrat_t c2, intrat_t c1, intrat_t c0);
	qpoly_t(intrat_t c4, intrat_t c3, intrat_t c2, intrat_t c1, intrat_t c0);
	qpoly_t(intrat_t c5, intrat_t c4, intrat_t c3, intrat_t c2, intrat_t c1,
		intrat_t c0);
	static qpoly_t binomial(intrat_t ci, int i, intrat_t cj, int j);

	qpoly_t(const qpoly_t & that);
	~qpoly_t(void);

	qpoly_t & operator=(qpoly_t that);
	qpoly_t   operator+(qpoly_t that) const;
	qpoly_t   operator+(intrat_t a)    const;
	qpoly_t   operator-(qpoly_t that) const;
	qpoly_t   operator-(intrat_t a)    const;
	qpoly_t   operator-(void) const;
	qpoly_t   operator*(qpoly_t that) const;
	qpoly_t   operator*(intrat_t a);
	qpoly_t   operator/(qpoly_t that);
	qpoly_t   operator%(qpoly_t that);
	qpoly_t   operator/(intrat_t a);

	qpoly_t & operator+=(qpoly_t that);
	qpoly_t & operator+=(intrat_t a);
	qpoly_t & operator-=(qpoly_t that);
	qpoly_t & operator-=(intrat_t a);
	qpoly_t & operator*=(qpoly_t that);
	qpoly_t & operator*=(intrat_t a);
	qpoly_t & operator/=(qpoly_t & that);
	qpoly_t & operator%=(qpoly_t & that);
	qpoly_t & operator/=(intrat_t a);

	void quot_and_rem(qpoly_t & that, qpoly_t & rquot, qpoly_t & rrem);
	qpoly_t gcd(qpoly_t & that);
	qpoly_t ext_gcd(qpoly_t & that, qpoly_t & rm, qpoly_t & rn);
	qpoly_t exp(int power);
	qpoly_t deriv(void);
	intrat_t eval(intrat_t c);

	int find_degree(void) const; // deg(0) is defined to be 0.
	intrat_t get_coeff(int deg) const;
	void set_coeff(int pos, intrat_t c);

	int operator==(int v) const;
	int operator!=(int v) const;
	int operator==(qpoly_t that) const;
	int operator!=(qpoly_t that) const;
	// Q[x] is *not* totally ordered.  Nonetheless, these methods are
	// handy for looping and sorting.
	int operator< (qpoly_t that) const;
	int operator> (qpoly_t that) const;
	int operator<=(qpoly_t that) const;
	int operator>=(qpoly_t that) const;

	friend std::ostream & operator<<(std::ostream & os,
		const qpoly_t & poly);
	friend std::istream & operator>>(std::istream & is,
		qpoly_t & poly);
	int from_string(char * string);

	void promote(void);
	void promote_and_add(intrat_t c0);

private:
	intrat_t * coeffs;
	int degree;

	int cmp(int cmp, qpoly_t & that) const;
	void bounds_check(int deg) const;
	void recompute_degree();
};

#endif // QPOLY_T_H
