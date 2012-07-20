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

#ifndef F2POLYMOD_T_H
#define F2POLYMOD_T_H

#include <iostream>
#include <iomanip>
#include "f2poly_t.h"

class f2polymod_t {
public:
	f2polymod_t(f2poly_t residue, f2poly_t modulus);
	f2polymod_t(void);
	f2polymod_t(const f2polymod_t & that);
	~f2polymod_t(void);

	f2polymod_t   prime_sfld_elt(int v) const;
	static f2polymod_t   prime_sfld_elt(int v, f2poly_t m);
	int get_char(void);

	f2polymod_t & operator=(f2polymod_t that);
	f2polymod_t   operator+(f2polymod_t that);
	f2polymod_t   operator-(f2polymod_t that);
	f2polymod_t   operator-(void);
	f2polymod_t   operator*(f2polymod_t that);
	f2polymod_t   operator*(int a); // Repeated addition.
	f2polymod_t   operator/(f2polymod_t that);
	f2polymod_t   operator%(f2polymod_t that);
	int           recip(f2polymod_t & rinv);
	f2polymod_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const f2polymod_t & a);
	// Modulus must have already been set:  this sets only the residue.
	friend std::istream & operator>>(std::istream & is,
		f2polymod_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		f2polymod_t & a);
	int from_string(char * string, f2poly_t m);

	f2polymod_t & operator+=(f2polymod_t that);
	f2polymod_t & operator-=(f2polymod_t that);
	f2polymod_t & operator*=(f2polymod_t that);
	f2polymod_t & operator*=(int a);
	f2polymod_t & operator/=(f2polymod_t that);
	f2polymod_t & operator%=(f2polymod_t that);

	int operator==(f2polymod_t that) const;
	int operator!=(f2polymod_t that) const;
	int operator==(int that) const;
	int operator!=(int that) const;
	// Polynomial quotient rings are *not* totally ordered.
	// Nonetheless, these methods are handy for looping and sorting.
	int operator< (f2polymod_t that) const;
	int operator> (f2polymod_t that) const;
	int operator<=(f2polymod_t that) const;
	int operator>=(f2polymod_t that) const;

	f2poly_t get_residue(void) const;
	f2poly_t get_modulus(void) const;
	void change_modulus(f2poly_t new_modulus);

private:
	f2poly_t residue;
	f2poly_t modulus;

	void check_moduli(f2polymod_t & that) const;
};

inline f2polymod_t::f2polymod_t(void)
{
	// Use default ctors for residue and modulus.
}

inline f2polymod_t::~f2polymod_t(void)
{
}

#endif // F2POLYMOD_T_H
