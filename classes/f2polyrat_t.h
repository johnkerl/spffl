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

#ifndef F2POLYRAT_T_H
#define F2POLYRAT_T_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include "f2poly_t.h"

class f2polyrat_t {
public:
	f2polyrat_t(f2poly_t numerator, f2poly_t denominator);
	f2polyrat_t(f2poly_t numerator);
	f2polyrat_t(int inumer);
	f2polyrat_t(void);
	f2polyrat_t(const f2polyrat_t & that);
	~f2polyrat_t(void);

	f2polyrat_t   prime_sfld_elt(int v) const;
	int get_char(void);

	f2polyrat_t & operator=(f2polyrat_t that);
	f2polyrat_t & operator=(f2poly_t numer);
	f2polyrat_t   operator+(f2polyrat_t that) const;
	f2polyrat_t   operator-(f2polyrat_t that) const;
	f2polyrat_t   operator-(void) const;
	f2polyrat_t   operator*(f2polyrat_t that);
	f2polyrat_t   operator/(f2polyrat_t that);
	f2polyrat_t   operator%(f2polyrat_t that);
	f2polyrat_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const f2polyrat_t & a);
	friend std::istream & operator>>(std::istream & is,
		f2polyrat_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		f2polyrat_t & a);
	int from_string(char * string);

	f2polyrat_t & operator+=(f2polyrat_t that);
	f2polyrat_t & operator-=(f2polyrat_t that);
	f2polyrat_t & operator*=(f2polyrat_t that);
	f2polyrat_t & operator/=(f2polyrat_t that);
	f2polyrat_t & operator%=(f2polyrat_t that);

	int operator==(f2polyrat_t that) const;
	int operator!=(f2polyrat_t that) const;
	int operator==(f2poly_t that) const;
	int operator!=(f2poly_t that) const;

	int operator< (f2polyrat_t that) const;
	int operator> (f2polyrat_t that) const;
	int operator<=(f2polyrat_t that) const;
	int operator>=(f2polyrat_t that) const;

	f2poly_t get_numerator(void) const;
	f2poly_t get_denominator(void) const;

private:
	f2poly_t numer;
	f2poly_t denom;

	void simplify();
};

#endif // F2POLYRAT_T_H
