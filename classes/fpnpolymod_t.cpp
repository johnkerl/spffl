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

#include <iostream>
#include <iomanip>
#include "fpnpolymod_t.h"

// ----------------------------------------------------------------
fpnpolymod_t::fpnpolymod_t(fpnpoly_t arg_residue, fpnpoly_t arg_modulus)
{
	this->residue = arg_residue;
	this->modulus = arg_modulus;
	this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
fpnpolymod_t::fpnpolymod_t(const fpnpolymod_t & that)
{
	this->residue = that.residue;
	this->modulus = that.modulus;
}

// ----------------------------------------------------------------
fpnpolymod_t::fpnpolymod_t(void)
{
	fpnpoly_t invalid;
	this->residue = invalid;
	this->modulus = invalid;
}

// ----------------------------------------------------------------
fpnpolymod_t::~fpnpolymod_t(void)
{
	fpnpoly_t invalid;
	this->residue = invalid;
	this->modulus = invalid;
}

// ----------------------------------------------------------------
fpnpolymod_t fpnpolymod_t::prime_sfld_elt(int v) const
{
	fpnpoly_t m = this->modulus;
	fpnpoly_t r = this->residue.prime_sfld_elt(v);
	return fpnpolymod_t(r, m);
}

// ----------------------------------------------------------------
// This is a static method.
fpnpolymod_t fpnpolymod_t::prime_sfld_elt(int v, fpnpoly_t om)
{
	fppoly_t im = om.get_coeff(0).get_modulus();
	return fpnpolymod_t(fpnpoly_t::prime_sfld_elt(v, im), om);
}

// ----------------------------------------------------------------
int fpnpolymod_t::get_char(void)
{
	return this->residue.get_char();
}

// ----------------------------------------------------------------
fpnpolymod_t & fpnpolymod_t::operator=(fpnpolymod_t that)
{
	this->residue = that.residue;
	this->modulus = that.modulus;
	return *this;
}

// ----------------------------------------------------------------
fpnpolymod_t fpnpolymod_t::operator+(fpnpolymod_t that)
{
	this->check_moduli(that);
	fpnpolymod_t rv(this->residue + that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
fpnpolymod_t fpnpolymod_t::operator-(fpnpolymod_t that)
{
	this->check_moduli(that);
	fpnpolymod_t rv(this->residue - that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
fpnpolymod_t fpnpolymod_t::operator-(void)
{
	fpnpolymod_t rv(- this->residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
fpnpolymod_t fpnpolymod_t::operator*(fpnpolymod_t that)
{
	this->check_moduli(that);
	fpnpolymod_t rv(this->residue * that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
fpnpolymod_t fpnpolymod_t::operator*(int a)
{
	// xxx get the characteristic and reduce a mod that.
	fpnpolymod_t rv = *this - *this;
	for (int i = 0; i < a; i++)
		rv += *this;
	return rv;
}

// ----------------------------------------------------------------
fpnpolymod_t fpnpolymod_t::operator/(fpnpolymod_t that)
{
	this->check_moduli(that);

	fpnpolymod_t bi;
	if (!that.recip(bi)) {
		std::cerr
			<< "fpnpolymod_t::operator/:  zero or zero divisor: "
			<< that.residue
			<< " mod "
			<< that.modulus
			<< ".\n";
		exit(1);
	}

	return *this * bi;
}

// ----------------------------------------------------------------
fpnpolymod_t fpnpolymod_t::operator%(fpnpolymod_t that)
{
	this->check_moduli(that);

	fpnpolymod_t bi;
	if (!that.recip(bi)) {
		std::cerr
			<< "fpnpolymod_t::operator%:  zero or zero divisor: "
			<< that.residue
			<< " mod "
			<< that.modulus
			<< ".\n";
		exit(1);
	}

	return *this - *this;
}

// ----------------------------------------------------------------
int fpnpolymod_t::recip(fpnpolymod_t & rinv)
{
	fpnpoly_t g, a, b;
	g = this->residue.ext_gcd(this->modulus, a, b);

	// Error check:
	if (g.find_degree() != 0) {
		//std::cerr << "fpnpolymod recip: zero or zero divisor.\n";
		return 0;
	}

	// Ext. GCD actually returns a scalar multiple of 1.  Divide this out.
	fppolymod_t c0i;
	if (!g.get_coeff(0).recip(c0i)) {
		std::cerr
			<< "fpnpolymod_t::recip:  zero or zero divisor "
			<< " in GCD "
			<< g
			<< ".\n";
		exit(1);
	}
	a *= c0i;
	fpnpolymod_t rv(a, this->modulus);
	rinv = rv;
	return 1;
}

// ----------------------------------------------------------------
fpnpolymod_t fpnpolymod_t::exp(int e)
{
	fpnpoly_t xp = this->residue;
	fpnpolymod_t zero(this->residue.prime_sfld_elt(0), this->modulus);
	fpnpolymod_t one(this->residue.prime_sfld_elt(1), this->modulus);
	fpnpolymod_t rv = one;

	if (e == 0) {
		if (*this == zero) {
			std::cerr << "fpnpolymod_t::exp:  0 ^ 0 undefined.\n";
			exit(1);
		}
		return one;
	}
	else if (e < 0) {
		if (*this == zero) {
			std::cerr << "fpnpolymod_t::exp:  division by zero.\n";
			exit(1);
		}
		if (e == -e) {
			std::cerr << "fpnpolymod_t::exp:  can't handle "
				"MIN_INT.\n";
			exit(1);
		}
		fpnpolymod_t inv = one/ *this;
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
std::ostream & operator<<(std::ostream & os, const fpnpolymod_t & a)
{
	int adeg = a.residue.find_degree();
	int rdeg = a.modulus.find_degree() - 1;
	int max = adeg > rdeg ? adeg : rdeg;
	fppoly_t m = a.residue.get_coeff(0).get_modulus();

	for (int i = max; i >= 0; i--) {
		if (i < max)
			os << ":";
		if (i > adeg)
			os << 0;
		else
			os << a.residue.get_coeff(i).get_residue();
	}

	return os;
}

// ----------------------------------------------------------------
std::istringstream & operator>>(std::istringstream & iss,
	fpnpolymod_t & a)
{
	iss >> a.residue; // Modulus must be already set.
	a.residue %= a.modulus;
	return iss;
}

// ----------------------------------------------------------------
int fpnpolymod_t::from_string(char * string, fpnpoly_t & m)
{
	fpnpoly_t r;
	fppoly_t mm = m.get_coeff(0).get_modulus();
	if (!r.from_string(string, mm))
		return 0;
	*this = fpnpolymod_t(r, m);
	return 1;
}

// ----------------------------------------------------------------
fpnpolymod_t & fpnpolymod_t::operator+=(fpnpolymod_t that)
{
	*this = *this + that;
	return *this;
}

// ----------------------------------------------------------------
fpnpolymod_t & fpnpolymod_t::operator-=(fpnpolymod_t that)
{
	*this = *this - that;
	return *this;
}

// ----------------------------------------------------------------
fpnpolymod_t & fpnpolymod_t::operator*=(fpnpolymod_t that)
{
	*this = *this * that;
	return *this;
}

// ----------------------------------------------------------------
fpnpolymod_t & fpnpolymod_t::operator*=(int a)
{
	*this = *this * a;
	return *this;
}

// ----------------------------------------------------------------
fpnpolymod_t & fpnpolymod_t::operator/=(fpnpolymod_t that)
{
	*this = *this / that;
	return *this;
}

// ----------------------------------------------------------------
fpnpolymod_t & fpnpolymod_t::operator%=(fpnpolymod_t that)
{
	*this = *this % that;
	return *this;
}

// ----------------------------------------------------------------
int fpnpolymod_t::operator==(fpnpolymod_t that) const
{
	if (this->residue != that.residue)
		return 0;
	if (this->modulus != that.modulus)
		return 0;
	return 1;
}

// ----------------------------------------------------------------
int fpnpolymod_t::operator!=(fpnpolymod_t that) const
{
	return ! (*this == that);
}

// ----------------------------------------------------------------
int fpnpolymod_t::operator==(int that) const
{
	return this->residue == that;
}

// ----------------------------------------------------------------
int fpnpolymod_t::operator!=(int that) const
{
	return this->residue != that;
}

// ----------------------------------------------------------------
int fpnpolymod_t::operator<(fpnpolymod_t that) const
{
	this->check_moduli(that);
	return this->residue < that.residue;
}

// ----------------------------------------------------------------
int fpnpolymod_t::operator<=(fpnpolymod_t that) const
{
	this->check_moduli(that);
	return this->residue <= that.residue;
}

// ----------------------------------------------------------------
int fpnpolymod_t::operator>(fpnpolymod_t that) const
{
	this->check_moduli(that);
	return this->residue > that.residue;
}

// ----------------------------------------------------------------
int fpnpolymod_t::operator>=(fpnpolymod_t that) const
{
	this->check_moduli(that);
	return this->residue >= that.residue;
}

// ----------------------------------------------------------------
fpnpoly_t fpnpolymod_t::get_residue(void) const
{
	return this->residue;
}

// ----------------------------------------------------------------
fpnpoly_t fpnpolymod_t::get_modulus(void) const
{
	return this->modulus;
}

// ----------------------------------------------------------------
void fpnpolymod_t::check_moduli(fpnpolymod_t & that) const
{
	if (this->modulus != that.modulus) {
		std::cerr
			<< "fpnpolymod_t: mixed moduli "
			<< this->modulus
			<< ", "
			<< that.modulus
			<< ".";
		std::cerr << std::endl;
		exit(1);
	}
}
