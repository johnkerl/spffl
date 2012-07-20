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

#ifndef FPPOLYRAT_T_H
#define FPPOLYRAT_T_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include "fppoly_t.h"

class fppolyrat_t {
public:
	fppolyrat_t(fppoly_t numerator, fppoly_t denominator);
	fppolyrat_t(fppoly_t numerator);
	fppolyrat_t(void);
	fppolyrat_t(const fppolyrat_t & that);
	~fppolyrat_t(void);

	fppolyrat_t   prime_sfld_elt(int v) const;
	static fppolyrat_t prime_sfld_elt(int v, int p);
	int get_char(void);

	fppolyrat_t & operator=(fppolyrat_t that);
	fppolyrat_t & operator=(fppoly_t numer);
	fppolyrat_t   operator+(fppolyrat_t that) const;
	fppolyrat_t   operator-(fppolyrat_t that) const;
	fppolyrat_t   operator-(void) const;
	fppolyrat_t   operator*(fppolyrat_t that);
	fppolyrat_t   operator/(fppolyrat_t that);
	fppolyrat_t   operator%(fppolyrat_t that);
	fppolyrat_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const fppolyrat_t & a);
	friend std::istream & operator>>(std::istream & is,
		fppolyrat_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		fppolyrat_t & a);
	int from_string(char * string, int p);

	fppolyrat_t & operator+=(fppolyrat_t that);
	fppolyrat_t & operator-=(fppolyrat_t that);
	fppolyrat_t & operator*=(fppolyrat_t that);
	fppolyrat_t & operator/=(fppolyrat_t that);
	fppolyrat_t & operator%=(fppolyrat_t that);

	int operator==(fppolyrat_t that) const;
	int operator!=(fppolyrat_t that) const;
	int operator==(fppoly_t that) const;
	int operator!=(fppoly_t that) const;

	int operator< (fppolyrat_t that) const;
	int operator> (fppolyrat_t that) const;
	int operator<=(fppolyrat_t that) const;
	int operator>=(fppolyrat_t that) const;

	fppoly_t get_numerator(void) const;
	fppoly_t get_denominator(void) const;

private:
	fppoly_t numer;
	fppoly_t denom;

	void simplify();
};

#endif // FPPOLYRAT_T_H
