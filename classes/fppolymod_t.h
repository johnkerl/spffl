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

#ifndef FPPOLYMOD_T_H
#define FPPOLYMOD_T_H

#include <iostream>
#include <iomanip>
#include "fppoly_t.h"

class fppolymod_t {
public:
	fppolymod_t(fppoly_t residue, fppoly_t modulus);
	fppolymod_t(void);
	fppolymod_t(const fppolymod_t & that);
	~fppolymod_t(void);

	fppolymod_t   prime_sfld_elt(int v) const;
	static fppolymod_t prime_sfld_elt(int v, fppoly_t m);
	int get_char(void);

	fppolymod_t & operator=(fppolymod_t that);
	fppolymod_t   operator+(fppolymod_t that);
	fppolymod_t   operator-(fppolymod_t that);
	fppolymod_t   operator-(void);
	fppolymod_t   operator*(fppolymod_t that);
	fppolymod_t   operator*(int a); // Repeated addition.
	fppolymod_t   operator*(intmod_t a);
	fppolymod_t   operator/(fppolymod_t that);
	fppolymod_t   operator%(fppolymod_t that);
	int           recip(fppolymod_t & rinv);
	fppolymod_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const fppolymod_t & a);
	// Modulus must have already been set:  this sets only the residue.
	friend std::istream & operator>>(std::ostream & os,
		const fppolymod_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		fppolymod_t & a);
	int from_string(char * string, fppoly_t & m);

	fppolymod_t & operator+=(fppolymod_t that);
	fppolymod_t & operator-=(fppolymod_t that);
	fppolymod_t & operator*=(fppolymod_t that);
	fppolymod_t & operator*=(int a);
	fppolymod_t & operator*=(intmod_t a);
	fppolymod_t & operator/=(fppolymod_t that);
	fppolymod_t & operator%=(fppolymod_t that);

	int operator==(fppolymod_t that) const;
	int operator!=(fppolymod_t that) const;
	int operator==(int that) const;
	int operator!=(int that) const;
	// Polynomial quotient rings are *not* totally ordered.
	// Nonetheless, these methods are handy for looping and sorting.
	int operator< (fppolymod_t that) const;
	int operator> (fppolymod_t that) const;
	int operator<=(fppolymod_t that) const;
	int operator>=(fppolymod_t that) const;

	fppoly_t get_residue(void) const;
	fppoly_t get_modulus(void) const;

private:
	fppoly_t residue;
	fppoly_t modulus;

	void check_moduli(fppolymod_t & that) const;
};

#endif // FPPOLYMOD_T_H
