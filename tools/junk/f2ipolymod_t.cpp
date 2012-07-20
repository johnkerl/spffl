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
#include "f2ipolymod_t.h"

// ----------------------------------------------------------------
f2ipolymod_t::f2ipolymod_t(f2ipoly_t arg_residue, f2ipoly_t arg_modulus)
{
	this->residue = arg_residue;
	this->modulus = arg_modulus;
	this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
f2ipolymod_t::f2ipolymod_t(const f2ipolymod_t & that)
{
	this->residue = that.residue;
	this->modulus = that.modulus;
}

// ----------------------------------------------------------------
f2ipolymod_t::f2ipolymod_t(void)
{
	// Use default ctors for residue and modulus.
}

// ----------------------------------------------------------------
f2ipolymod_t::~f2ipolymod_t(void)
{
	f2ipoly_t invalid;
	this->residue = invalid;
	this->modulus = invalid;
}

// ----------------------------------------------------------------
f2ipolymod_t f2ipolymod_t::prime_sfld_elt(int v) const
{
	f2ipoly_t m = this->modulus;
	f2ipoly_t r(v & 1);
	return f2ipolymod_t(r, m);
}

// ----------------------------------------------------------------
f2ipolymod_t & f2ipolymod_t::operator=(f2ipolymod_t that)
{
	this->residue = that.residue;
	this->modulus = that.modulus;
	return *this;
}

// ----------------------------------------------------------------
f2ipolymod_t f2ipolymod_t::operator+(f2ipolymod_t that)
{
	this->check_moduli(that);
	f2ipolymod_t rv(this->residue + that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
f2ipolymod_t f2ipolymod_t::operator-(f2ipolymod_t that)
{
	this->check_moduli(that);
	f2ipolymod_t rv(this->residue - that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
f2ipolymod_t f2ipolymod_t::operator-(void)
{
	f2ipolymod_t rv(- this->residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
f2ipolymod_t f2ipolymod_t::operator*(f2ipolymod_t that)
{
	this->check_moduli(that);
	f2ipolymod_t rv(this->residue * that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
f2ipolymod_t f2ipolymod_t::operator/(f2ipolymod_t that)
{
	this->check_moduli(that);

	f2ipolymod_t bi;
	if (!that.recip(bi)) {
		std::cerr
			<< "f2ipolymod_t::operator/:  zero or zero divisor: "
			<< that.residue
			<< " mod "
			<< that.modulus
			<< ".\n";
		exit(1);
	}

	return *this * bi;
}

// ----------------------------------------------------------------
f2ipolymod_t f2ipolymod_t::operator%(f2ipolymod_t that)
{
	this->check_moduli(that);

	f2ipolymod_t bi;
	if (!that.recip(bi)) {
		std::cerr
			<< "f2ipolymod_t::operator%:  zero or zero divisor: "
			<< that.residue << " mod " << that.modulus << ".\n";
		exit(1);
	}

	return *this - *this;
}

// ----------------------------------------------------------------
int f2ipolymod_t::recip(f2ipolymod_t & rinv)
{
	f2ipoly_t g, a, b;
	g = this->residue.ext_gcd(this->modulus, a, b);

	// Error check:
	if (g.find_degree() != 0) {
		//std::cerr << "f2ipolymod recip: zero or zero divisor.\n";
		return 0;
	}
	else {
		rinv = f2ipolymod_t(a, this->modulus);
		return 1;
	}
}

// ----------------------------------------------------------------
f2ipolymod_t f2ipolymod_t::exp(int e)
{
	f2ipoly_t xp = this->residue;
	f2ipolymod_t zero(f2ipoly_t(0), this->modulus);
	f2ipolymod_t one(f2ipoly_t(1), this->modulus);
	f2ipolymod_t rv = one;

	if (e == 0) {
		if (*this == zero) {
			std::cerr << "f2ipolymod_t::exp:  0 ^ 0 undefined.\n";
			exit(1);
		}
		return one;
	}
	else if (e < 0) {
		if (*this == zero) {
			std::cerr << "f2ipolymod_t::exp:  division by zero.\n";
			exit(1);
		}
		if (e == -e) {
			std::cerr << "f2ipolymod_t::exp:  can't handle "
				"MIN_INT.\n";
			exit(1);
		}
		f2ipolymod_t inv = one/ *this;
		xp = inv.residue;
		e = -e;
	}

	while (e != 0) {
		if (e & 1) {
			rv.residue = (rv.residue * xp) % this->modulus;
		}
		e = (unsigned)e >> 1;
		xp = (xp * xp) % this->modulus;
	}

	return rv;
}

// ----------------------------------------------------------------
std::ostream & operator<<(std::ostream & os, const f2ipolymod_t & a)
{
#if 0
// xxx match deg & do field width

	int adeg = a.residue.find_degree();
	int rdeg = a.modulus.find_degree();
	int max = adeg > rdeg ? adeg : rdeg;
	int modulus = a.residue.get_coeff(0).get_modulus();

	for (int i = max; i >= 0; i--) {
		if (modulus > 9)
			if (i < max)
				os << ",";
		os << a.residue.get_coeff(i).get_residue();
	}

#endif
	os << a.residue;

	return os;
}

// ----------------------------------------------------------------
std::istream & operator>>(std::istream & is, f2ipolymod_t & a)
{
	is >> a.residue; // Modulus must be already set.
	return is;
}

// ----------------------------------------------------------------
std::istringstream & operator>>(std::istringstream & iss, f2ipolymod_t & a)
{
	iss >> a.residue; // Modulus must be already set.
	return iss;
}

// ----------------------------------------------------------------
int f2ipolymod_t::from_string(char * string, f2ipoly_t m)
{
	f2ipoly_t r;
	std::istringstream iss(string, std::ios_base::in);
	iss >> r;
	if (iss.fail()) {
		return 0;
	}
	else {
		*this = f2ipolymod_t(r, m);
		return 1;
	}
}

// ----------------------------------------------------------------
f2ipolymod_t & f2ipolymod_t::operator+=(f2ipolymod_t that)
{
	*this = *this + that;
	return *this;
}

// ----------------------------------------------------------------
f2ipolymod_t & f2ipolymod_t::operator-=(f2ipolymod_t that)
{
	*this = *this - that;
	return *this;
}

// ----------------------------------------------------------------
f2ipolymod_t & f2ipolymod_t::operator*=(f2ipolymod_t that)
{
	*this = *this * that;
	return *this;
}

// ----------------------------------------------------------------
f2ipolymod_t & f2ipolymod_t::operator/=(f2ipolymod_t that)
{
	*this = *this / that;
	return *this;
}

// ----------------------------------------------------------------
f2ipolymod_t & f2ipolymod_t::operator%=(f2ipolymod_t that)
{
	*this = *this % that;
	return *this;
}

// ----------------------------------------------------------------
int f2ipolymod_t::operator==(f2ipolymod_t that) const
{
	if (this->residue != that.residue)
		return 0;
	if (this->modulus != that.modulus)
		return 0;
	return 1;
}

// ----------------------------------------------------------------
int f2ipolymod_t::operator!=(f2ipolymod_t that) const
{
	return ! (*this == that);
}

// ----------------------------------------------------------------
int f2ipolymod_t::operator==(int that) const
{
	return this->residue == that;
}

// ----------------------------------------------------------------
int f2ipolymod_t::operator!=(int that) const
{
	return this->residue != that;
}

// ----------------------------------------------------------------
int f2ipolymod_t::operator<(f2ipolymod_t that) const
{
	this->check_moduli(that);
	return this->residue < that.residue;
}

// ----------------------------------------------------------------
int f2ipolymod_t::operator<=(f2ipolymod_t that) const
{
	this->check_moduli(that);
	return this->residue <= that.residue;
}

// ----------------------------------------------------------------
int f2ipolymod_t::operator>(f2ipolymod_t that) const
{
	this->check_moduli(that);
	return this->residue > that.residue;
}

// ----------------------------------------------------------------
int f2ipolymod_t::operator>=(f2ipolymod_t that) const
{
	this->check_moduli(that);
	return this->residue >= that.residue;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipolymod_t::get_residue(void) const
{
	return this->residue;
}

// ----------------------------------------------------------------
f2ipoly_t f2ipolymod_t::get_modulus(void) const
{
	return this->modulus;
}

// ----------------------------------------------------------------
void f2ipolymod_t::check_moduli(f2ipolymod_t & that) const
{
	if (this->modulus != that.modulus) {
		std::cerr
			<< "f2ipolymod_t: mixed moduli "
			<< this->modulus
			<< ", "
			<< that.modulus
			<< ".";
		std::cerr << std::endl;
		exit(1);
	}
}
