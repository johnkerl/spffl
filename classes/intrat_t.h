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

#ifndef INTRAT_T_H
#define INTRAT_T_H

#include <iostream>
#include <sstream>
#include <iomanip>

class intrat_t {
public:
	intrat_t(int numerator, int denominator);
	intrat_t(int numerator);
	intrat_t(void);
	intrat_t(const intrat_t & that);
	~intrat_t(void);

	intrat_t & operator=(intrat_t that);
	intrat_t & operator=(int numer);
	intrat_t   operator+(intrat_t that) const;
	intrat_t   operator-(intrat_t that) const;
	intrat_t   operator-(void) const;
	intrat_t   operator*(intrat_t that);
	intrat_t   operator/(intrat_t that);
	intrat_t   operator%(intrat_t that);
	intrat_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const intrat_t & a);
	friend std::istream & operator>>(std::istream & is,
		intrat_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		intrat_t & a);
	int from_string(char * string);

	intrat_t & operator+=(intrat_t that);
	intrat_t & operator-=(intrat_t that);
	intrat_t & operator*=(intrat_t that);
	intrat_t & operator/=(intrat_t that);
	intrat_t & operator%=(intrat_t that);

	int operator==(intrat_t that) const;
	int operator!=(intrat_t that) const;
	int operator==(int that) const;
	int operator!=(int that) const;

	int operator< (intrat_t that) const;
	int operator> (intrat_t that) const;
	int operator<=(intrat_t that) const;
	int operator>=(intrat_t that) const;

	int get_numerator(void) const;
	int get_denominator(void) const;

private:
	int numer;
	int denom;

	void simplify();
};

#endif // INTRAT_T_H
