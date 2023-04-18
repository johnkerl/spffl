// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <iomanip>
#include "fppolymod_t.h"

// ----------------------------------------------------------------
fppolymod_t::fppolymod_t(fppoly_t arg_residue, fppoly_t arg_modulus)
{
	this->residue = arg_residue;
	this->modulus = arg_modulus;
	this->residue = this->residue % this->modulus;
}

// ----------------------------------------------------------------
fppolymod_t::fppolymod_t(const fppolymod_t & that)
{
	this->residue = that.residue;
	this->modulus = that.modulus;
}

// ----------------------------------------------------------------
fppolymod_t::fppolymod_t(void)
{
	fppoly_t invalid;
	this->residue = invalid;
	this->modulus = invalid;
}

// ----------------------------------------------------------------
fppolymod_t::~fppolymod_t(void)
{
	fppoly_t invalid;
	this->residue = invalid;
	this->modulus = invalid;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::prime_sfld_elt(int v) const
{
	fppoly_t m = this->modulus;
	fppoly_t r = this->residue.prime_sfld_elt(v);
	return fppolymod_t(r, m);
}

// ----------------------------------------------------------------
// This is a static method.
fppolymod_t fppolymod_t::prime_sfld_elt(int v, fppoly_t m)
{
	return fppolymod_t(m.prime_sfld_elt(v), m);
}

// ----------------------------------------------------------------
int fppolymod_t::get_char(void)
{
	return this->residue.get_char();
}

// ----------------------------------------------------------------
fppolymod_t & fppolymod_t::operator=(fppolymod_t that)
{
	this->residue = that.residue;
	this->modulus = that.modulus;
	return *this;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::operator+(fppolymod_t that)
{
	this->check_moduli(that);
	fppolymod_t rv(this->residue + that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::operator-(fppolymod_t that)
{
	this->check_moduli(that);
	fppolymod_t rv(this->residue - that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::operator-(void)
{
	fppolymod_t rv(- this->residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::operator*(fppolymod_t that)
{
	this->check_moduli(that);
	fppolymod_t rv(this->residue * that.residue, this->modulus);
	return rv;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::operator*(int a)
{
	fppolymod_t rv(*this);
	int p = this->get_char();
	a %= p;
	if (a == 0) {
		rv = rv - rv;
	}
	else {
		for (int i = 1; i < a; i++)
			rv += *this;
	}
	return rv;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::operator*(intmod_t a)
{
	fppolymod_t rv(*this);
	rv.modulus *= a;
	return rv;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::operator/(fppolymod_t that)
{
	this->check_moduli(that);

	fppolymod_t bi;
	if (!that.recip(bi)) {
		std::cerr
			<< "fppolymod_t::operator/:  zero or zero divisor: "
			<< that.residue
			<< " mod "
			<< that.modulus
			<< ".\n";
		exit(1);
	}

	return *this * bi;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::operator%(fppolymod_t that)
{
	this->check_moduli(that);

	fppolymod_t bi;
	if (!that.recip(bi)) {
		std::cerr
			<< "fppolymod_t::operator%:  zero or zero divisor: "
			<< that.residue
			<< " mod "
			<< that.modulus
			<< ".\n";
		exit(1);
	}

	return *this - *this;
}

// ----------------------------------------------------------------
int fppolymod_t::recip(fppolymod_t & rinv)
{
	fppoly_t g, a, b;
	g = this->residue.ext_gcd(this->modulus, a, b);

	// Error check:
	if (g.find_degree() != 0) {
		//std::cerr << "fppolymod recip: zero or zero divisor.\n";
		return 0;
	}

	// Ext. GCD actually returns a scalar multiple of 1.  Divide this out.
	intmod_t c0i;
	if (!g.get_coeff(0).recip(c0i)) {
		std::cerr
			<< "fppolymod_t::recip:  zero or zero divisor "
			<< " in GCD "
			<< g
			<< ".\n";
		exit(1);
	}
	a *= c0i;
	fppolymod_t rv(a, this->modulus);
	rinv = rv;
	return 1;
}

// ----------------------------------------------------------------
fppolymod_t fppolymod_t::exp(int e)
{
	fppoly_t xp = this->residue;
	fppolymod_t zero(this->residue.prime_sfld_elt(0), this->modulus);
	fppolymod_t one(this->residue.prime_sfld_elt(1), this->modulus);
	fppolymod_t rv = one;

	if (e == 0) {
		if (*this == zero) {
			std::cerr << "fppolymod_t::exp:  0 ^ 0 undefined.\n";
			exit(1);
		}
		return one;
	}
	else if (e < 0) {
		if (*this == zero) {
			std::cerr << "fppolymod_t::exp:  division by zero.\n";
			exit(1);
		}
		if (e == -e) {
			std::cerr << "fppolymod_t::exp:  can't handle "
				"MIN_INT.\n";
			exit(1);
		}
		fppolymod_t inv = one/ *this;
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
std::ostream & operator<<(std::ostream & os, const fppolymod_t & a)
{
	int adeg = a.residue.find_degree();
	int rdeg = a.modulus.find_degree() - 1;
	int max = adeg > rdeg ? adeg : rdeg;
	int m = a.residue.get_coeff(0).get_modulus();

	for (int i = max; i >= 0; i--) {
		if (m > 9)
			if (i < max)
				os << ",";
		if (i > adeg)
			os << 0;
		else
			os << a.residue.get_coeff(i).get_residue();
	}

	return os;
}

// ----------------------------------------------------------------
std::istringstream & operator>>(std::istringstream & iss,
	fppolymod_t & a)
{
	iss >> a.residue; // Modulus must be already set.
	a.residue %= a.modulus;
	return iss;
}

// ----------------------------------------------------------------
int fppolymod_t::from_string(char * string, fppoly_t & m)
{
	fppoly_t r;
	int p = m.get_char();
	if (!r.from_string(string, p))
		return 0;
	*this = fppolymod_t(r, m);
	return 1;
}

// ----------------------------------------------------------------
fppolymod_t & fppolymod_t::operator+=(fppolymod_t that)
{
	*this = *this + that;
	return *this;
}

// ----------------------------------------------------------------
fppolymod_t & fppolymod_t::operator-=(fppolymod_t that)
{
	*this = *this - that;
	return *this;
}

// ----------------------------------------------------------------
fppolymod_t & fppolymod_t::operator*=(fppolymod_t that)
{
	*this = *this * that;
	return *this;
}

// ----------------------------------------------------------------
fppolymod_t & fppolymod_t::operator*=(int a)
{
	*this = *this * a;
	return *this;
}

// ----------------------------------------------------------------
fppolymod_t & fppolymod_t::operator*=(intmod_t a)
{
	*this = *this * a;
	return *this;
}

// ----------------------------------------------------------------
fppolymod_t & fppolymod_t::operator/=(fppolymod_t that)
{
	*this = *this / that;
	return *this;
}

// ----------------------------------------------------------------
fppolymod_t & fppolymod_t::operator%=(fppolymod_t that)
{
	*this = *this % that;
	return *this;
}

// ----------------------------------------------------------------
int fppolymod_t::operator==(fppolymod_t that) const
{
	if (this->residue != that.residue)
		return 0;
	if (this->modulus != that.modulus)
		return 0;
	return 1;
}

// ----------------------------------------------------------------
int fppolymod_t::operator!=(fppolymod_t that) const
{
	return ! (*this == that);
}

// ----------------------------------------------------------------
int fppolymod_t::operator==(int that) const
{
	return this->residue == that;
}

// ----------------------------------------------------------------
int fppolymod_t::operator!=(int that) const
{
	return this->residue != that;
}

// ----------------------------------------------------------------
int fppolymod_t::operator<(fppolymod_t that) const
{
	this->check_moduli(that);
	return this->residue < that.residue;
}

// ----------------------------------------------------------------
int fppolymod_t::operator<=(fppolymod_t that) const
{
	this->check_moduli(that);
	return this->residue <= that.residue;
}

// ----------------------------------------------------------------
int fppolymod_t::operator>(fppolymod_t that) const
{
	this->check_moduli(that);
	return this->residue > that.residue;
}

// ----------------------------------------------------------------
int fppolymod_t::operator>=(fppolymod_t that) const
{
	this->check_moduli(that);
	return this->residue >= that.residue;
}

// ----------------------------------------------------------------
fppoly_t fppolymod_t::get_residue(void) const
{
	return this->residue;
}

// ----------------------------------------------------------------
fppoly_t fppolymod_t::get_modulus(void) const
{
	return this->modulus;
}

// ----------------------------------------------------------------
void fppolymod_t::check_moduli(fppolymod_t & that) const
{
	if (this->modulus != that.modulus) {
		std::cerr
			<< "fppolymod_t: mixed moduli "
			<< this->modulus
			<< ", "
			<< that.modulus
			<< ".";
		std::cerr << std::endl;
		exit(1);
	}
}
