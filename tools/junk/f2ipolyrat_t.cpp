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

#include <iostream>
#include <iomanip>
#include "f2ipolyrat_t.h"
#include "cmps.h"

// ----------------------------------------------------------------
f2ipolyrat_t::f2ipolyrat_t(f2ipoly_t numerator, f2ipoly_t denominator)
{
	this->numer = numerator;
	this->denom = denominator;
	this->simplify();
}

// ----------------------------------------------------------------
f2ipolyrat_t::f2ipolyrat_t(f2ipoly_t numerator)
{
	this->numer = numerator;
	this->denom = 1;
	this->simplify();
}

// ----------------------------------------------------------------
f2ipolyrat_t::f2ipolyrat_t(int inumer)
{
	this->numer = f2ipoly_t(inumer);
	this->denom = 1;
	this->simplify();
}

// ----------------------------------------------------------------
f2ipolyrat_t::f2ipolyrat_t(const f2ipolyrat_t & that)
{
	this->numer = that.numer;
	this->denom = that.denom;
}

// ----------------------------------------------------------------
f2ipolyrat_t::f2ipolyrat_t(void)
{
	this->numer = 0;
	this->denom = 1;
}

// ----------------------------------------------------------------
f2ipolyrat_t::~f2ipolyrat_t(void)
{
	this->numer = 0;
	this->denom = 1;
}

// ----------------------------------------------------------------
f2ipolyrat_t f2ipolyrat_t::prime_sfld_elt(int v) const
{
	return f2ipolyrat_t(v & 1);
}

// ----------------------------------------------------------------
f2ipolyrat_t & f2ipolyrat_t::operator=(f2ipolyrat_t that)
{
	this->numer = that.numer;
	this->denom = that.denom;
	return *this;
}

// ----------------------------------------------------------------
f2ipolyrat_t & f2ipolyrat_t::operator=(f2ipoly_t numerator)
{
	this->numer = numerator;
	this->denom = 1;
	this->simplify();
	return *this;
}

// ----------------------------------------------------------------
//  a     c    ad + bc
// --- + --- = -------
//  b     d      bd

f2ipolyrat_t f2ipolyrat_t::operator+(f2ipolyrat_t that) const
{
	f2ipolyrat_t rv;
	rv.numer = this->numer * that.denom + this->denom * that.numer;
	rv.denom = this->denom * that.denom;
	rv.simplify();
	return rv;
}

// ----------------------------------------------------------------
f2ipolyrat_t f2ipolyrat_t::operator-(f2ipolyrat_t that) const
{
	f2ipolyrat_t rv;
	rv.numer = this->numer * that.denom - this->denom * that.numer;
	rv.denom = this->denom * that.denom;
	rv.simplify();
	return rv;
}

// ----------------------------------------------------------------
f2ipolyrat_t f2ipolyrat_t::operator-(void) const
{
	f2ipolyrat_t rv;
	rv.numer = - this->numer;
	rv.denom =   this->denom;
	return rv;
}

// ----------------------------------------------------------------
f2ipolyrat_t f2ipolyrat_t::operator*(f2ipolyrat_t that)
{
	f2ipolyrat_t rv;
	rv.numer = this->numer * that.numer;
	rv.denom = this->denom * that.denom;
	rv.simplify();
	return rv;
}

// ----------------------------------------------------------------
f2ipolyrat_t f2ipolyrat_t::operator/(f2ipolyrat_t that)
{
	f2ipolyrat_t rv;
	rv.numer = this->numer * that.denom;
	rv.denom = this->denom * that.numer;
	rv.simplify();
	return rv;
}

// ----------------------------------------------------------------
f2ipolyrat_t f2ipolyrat_t::operator%(f2ipolyrat_t that)
{
	f2ipolyrat_t rv;
	f2ipolyrat_t zero = that - that;
	if (that == zero) {
		std::cerr << "f2ipolyrat_t: Divide by zero.\n";
		exit(1);
	}
	return zero;
}

// ----------------------------------------------------------------
f2ipolyrat_t f2ipolyrat_t::exp(int e)
{
	f2ipolyrat_t xp = *this;
	f2ipolyrat_t zero(0);
	f2ipolyrat_t one (1);
	f2ipolyrat_t rv = one;

	if (e == 0) {
		if (*this == zero) {
			std::cerr << "f2ipolyrat_t::exp:  0 ^ 0 undefined.\n";
			exit(1);
		}
		return one;
	}
	else if (e < 0) {
		if (*this == zero) {
			std::cerr << "f2ipolyrat_t::exp:  division by zero.\n";
			exit(1);
		}
		if (e == -e) {
			std::cerr << "f2ipolyrat_t::exp:  can't handle "
				"MIN_F2IPOLY.\n";
			exit(1);
		}
		xp = one / xp;
		e = -e;
	}

	while (e != 0) {
		if (e & 1)
			rv *= xp;
		e = (unsigned)e >> 1;
		xp *= xp;
	}

	return rv;
}

// ----------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const f2ipolyrat_t & a)
{
	os << a.numer;
	if (a.denom != 1)
		os << "/" << a.denom;
	return os;
}

// ----------------------------------------------------------------
std::istream & operator>>(std::istream & is, f2ipolyrat_t & a)
{
	// Attempt to skip over whitespace.
	// The istringstream class appears to permit no way to ignore a set of
	// characters.  E.g. if the input is 0, space, tab, space, 1, then the
	// following won't suffice.

	while (is.peek() == ' ') is.ignore(1, ' ');
	while (is.peek() == '\t') is.ignore(1, '\t');
	while (is.peek() == '\n') is.ignore(1, '\n');

	is >> a.numer;
	if (is.eof()) {
		a.denom = 1;
	}
	if (is.peek() == '/') {
		(void)is.get();
		is >> a.denom;
	}
	else {
		// Clear failure code from not having found the '/'.
		is.clear();
		a.denom = 1;
	}
	a.simplify();
	return is;
}

// ----------------------------------------------------------------
std::istringstream & operator>>(std::istringstream & iss, f2ipolyrat_t & a)
{
	// Attempt to skip over whitespace.
	// The istringstream class appears to permit no way to ignore a set of
	// characters.  E.g. if the input is 0, space, tab, space, 1, then the
	// following won't suffice.

	while (iss.peek() == ' ') iss.ignore(1, ' ');
	while (iss.peek() == '\t') iss.ignore(1, '\t');
	while (iss.peek() == '\n') iss.ignore(1, '\n');

	iss >> a.numer;
	if (iss.eof()) {
		a.denom = 1;
	}
	else if (iss.peek() == '/') {
		(void)iss.get();
		iss >> a.denom;
	}
	else {
		// Clear failure code from not having found the '/'.
		iss.clear();
		a.denom = 1;
	}
	a.simplify();
	return iss;
}

// ----------------------------------------------------------------
int f2ipolyrat_t::from_string(char * string)
{
	std::istringstream iss(string, std::ios_base::in);
	iss >> *this;
	return iss.fail() ? 0 : 1;
}

// ----------------------------------------------------------------
f2ipolyrat_t & f2ipolyrat_t::operator+=(f2ipolyrat_t that)
{
	*this = *this + that;
	return *this;
}

// ----------------------------------------------------------------
f2ipolyrat_t & f2ipolyrat_t::operator-=(f2ipolyrat_t that)
{
	*this = *this - that;
	return *this;
}

// ----------------------------------------------------------------
f2ipolyrat_t & f2ipolyrat_t::operator*=(f2ipolyrat_t that)
{
	*this = *this * that;
	return *this;
}

// ----------------------------------------------------------------
f2ipolyrat_t & f2ipolyrat_t::operator/=(f2ipolyrat_t that)
{
	*this = *this / that;
	return *this;
}

// ----------------------------------------------------------------
f2ipolyrat_t & f2ipolyrat_t::operator%=(f2ipolyrat_t that)
{
	*this = *this % that;
	return *this;
}

// ----------------------------------------------------------------
int f2ipolyrat_t::operator==(f2ipolyrat_t that) const
{
	// Our constructor ensures both *this and that are already in
	// canonical form.
	if (this->numer != that.numer)
		return 0;
	if (this->denom != that.denom)
		return 0;
	return 1;
}

// ----------------------------------------------------------------
int f2ipolyrat_t::operator!=(f2ipolyrat_t that) const
{
	return ! (*this == that);
}

// ----------------------------------------------------------------
int f2ipolyrat_t::operator==(f2ipoly_t that) const
{
	if (this->denom != f2ipoly_t(1))
		return 0;
	return this->numer == that;
}

// ----------------------------------------------------------------
int f2ipolyrat_t::operator!=(f2ipoly_t that) const
{
	return !(*this == that);
}

// ----------------------------------------------------------------
int f2ipolyrat_t::operator<(f2ipolyrat_t that) const
{
	return ((this->numer * that.denom) <  (this->denom * that.numer));
}

// ----------------------------------------------------------------
int f2ipolyrat_t::operator<=(f2ipolyrat_t that) const
{
	return ((this->numer * that.denom) <= (this->denom * that.numer));
}

// ----------------------------------------------------------------
int f2ipolyrat_t::operator>(f2ipolyrat_t that) const
{
	return ((this->numer * that.denom) >  (this->denom * that.numer));
}

// ----------------------------------------------------------------
int f2ipolyrat_t::operator>=(f2ipolyrat_t that) const
{
	return ((this->numer * that.denom) >= (this->denom * that.numer));
}

// ----------------------------------------------------------------
f2ipoly_t f2ipolyrat_t::get_numerator(void) const
{
	return this->numer;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipolyrat_t::get_denominator(void) const
{
	return this->denom;
}

// ----------------------------------------------------------------
// * Check denominator != 0
// * Divide numerator and denominator by their GCD

void f2ipolyrat_t::simplify(void)
{
	f2ipoly_t g;
	if (this->denom == 0) {
		std::cerr << "rat: Divide by zero.\n";
		exit(1);
	}
	g = this->numer.gcd(this->denom);
	this->numer /= g;
	this->denom /= g;
}
