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

#ifndef INTMOD_T_H
#define INTMOD_T_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>
#include "int_totient.h"

class intmod_t {
public:
	intmod_t(int residue, int modulus);
	intmod_t(void);
	intmod_t(const intmod_t & that);
	~intmod_t(void);

	intmod_t   prime_sfld_elt(int v) const;

	intmod_t & operator=(intmod_t that);
	intmod_t   operator+(intmod_t that);
	intmod_t   operator+(int a);
	intmod_t   operator-(intmod_t that);
	intmod_t   operator-(void);
	intmod_t   operator-(int a);
	intmod_t   operator*(intmod_t that);
	intmod_t   operator*(int a);
	intmod_t   operator/(intmod_t that);
	intmod_t   operator%(intmod_t that);
	int        recip(intmod_t & rinv);
	intmod_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const intmod_t & a);
	// Modulus must have already been set:  this sets only the residue.
	friend std::istream & operator>>(std::istream & is,
		intmod_t & a);
	int from_string(char * string, int modulus);

	intmod_t & operator+=(intmod_t that);
	intmod_t & operator-=(intmod_t that);
	intmod_t & operator*=(intmod_t that);
	intmod_t & operator/=(intmod_t that);
	intmod_t & operator%=(intmod_t that);

	int operator==(intmod_t that) const;
	int operator!=(intmod_t that) const;
	int operator==(int that) const;
	int operator!=(int that) const;
	// Z/mZ is *not* totally ordered.  Nonetheless, these methods are
	// handy for looping and sorting.
	int operator< (intmod_t that) const;
	int operator> (intmod_t that) const;
	int operator<=(intmod_t that) const;
	int operator>=(intmod_t that) const;


	int get_residue(void) const;
	int get_modulus(void) const;

private:
	int residue;
	int modulus;

	void check_moduli(intmod_t & that) const;
	void check_modulus(void) const;
};

// ----------------------------------------------------------------
inline intmod_t::intmod_t(int arg_residue, int arg_modulus)
{
	if (arg_modulus <= 0) {
		std::cerr
			<< "intmod_t: non-positive modulus "
			<< arg_modulus
			<< " disallowed.";
		std::cerr << std::endl;
		exit(1);
	}
	this->residue = arg_residue;
	this->modulus = arg_modulus;
	this->residue = this->residue % this->modulus;
	if (this->residue < 0) // Wacky C mod operator.
		this->residue += this->modulus;
}

// ----------------------------------------------------------------
inline intmod_t::intmod_t(const intmod_t & that)
{
	this->residue = that.residue;
	this->modulus = that.modulus;
}

// ----------------------------------------------------------------
inline intmod_t::intmod_t(void)
{
	this->residue = -1;
	this->modulus =  0;
}

// ----------------------------------------------------------------
inline intmod_t::~intmod_t(void)
{
}

// ----------------------------------------------------------------
inline void intmod_t::check_moduli(intmod_t & that) const
{
	this->check_modulus();
	that.check_modulus();
	if (this->modulus != that.modulus) {
		std::cerr
			<< "intmod_t: mixed moduli "
			<< this->modulus
			<< ", "
			<< that.modulus
			<< ".";
		std::cerr << std::endl;
		exit(1);
	}
}

// ----------------------------------------------------------------
// Unfortunately a default ctor is sometimes necessary (e.g. for matrices
// and vectors): the modulus must sometimes be specified *after* construction.
// Yet we don't want such data being used for arithmetic.
inline void intmod_t::check_modulus(void) const
{
	if (this->modulus == 0) {
		std::cerr << "intmod_t: unspecified modulus.\n";
		exit(1);
	}
}


// ----------------------------------------------------------------
inline intmod_t & intmod_t::operator=(intmod_t that)
{
	this->residue = that.residue;
	this->modulus = that.modulus;
	return *this;
}

// ----------------------------------------------------------------
inline intmod_t intmod_t::operator+(intmod_t that)
{
	this->check_moduli(that);
	intmod_t rv(this->residue + that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
inline intmod_t intmod_t::operator+(int a)
{
	intmod_t rv(this->residue + a, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
inline intmod_t intmod_t::operator-(intmod_t that)
{
	this->check_moduli(that);
	intmod_t rv(this->modulus + this->residue - that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
inline intmod_t intmod_t::operator-(int a)
{
	intmod_t rv(this->modulus + this->residue - a, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
inline intmod_t intmod_t::operator-(void)
{
	this->check_modulus();
	intmod_t rv(this->modulus - this->residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
inline intmod_t intmod_t::operator*(intmod_t that)
{
	this->check_moduli(that);
	intmod_t rv(this->residue * that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
inline intmod_t intmod_t::operator*(int a)
{
	intmod_t rv(this->residue * a, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
inline intmod_t intmod_t::operator/(intmod_t that)
{
	this->check_moduli(that);

	intmod_t bi;
	if (!that.recip(bi)) {
		std::cerr
			<< "intmod_t::operator/:  zero or zero divisor: "
			<< that.residue
			<< " mod "
			<< that.modulus
			<< ".\n";
		exit(1);
	}

	return *this * bi;
}

// ----------------------------------------------------------------
inline intmod_t intmod_t::operator%(intmod_t that)
{
	this->check_moduli(that);

	intmod_t bi;
	if (!that.recip(bi)) {
		std::cerr
			<< "intmod_t::operator%:  zero or zero divisor: "
			<< that.residue
			<< " mod "
			<< that.modulus
			<< ".\n";
		exit(1);
	}

	return *this - *this;
}

// ----------------------------------------------------------------
inline int intmod_t::recip(intmod_t & rinv)
{
	this->check_modulus();

	if (this->modulus == 2) {
		if (this->residue == 0) {
			return 0;
		}
		else {
			rinv = *this;
			return 1;
		}
	}

	static int mlast = 2;
	static int phi = 1;
	if (this->modulus != mlast) { // Cache
		mlast = this->modulus;
		phi = int_totient(this->modulus);
	}

	intmod_t rv = this->exp(phi-1);
	int check = (this->residue * rv.residue) % this->modulus;
	if (check != 1) {
		return 0;
	}
	else {
		rinv = rv;
		return 1;
	}
}

#endif // INTMOD_T_H
