// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <iomanip>
#include "f2polyrat_t.h"
#include "cmps.h"

// ----------------------------------------------------------------
f2polyrat_t::f2polyrat_t(f2poly_t numerator, f2poly_t denominator)
{
	this->numer = numerator;
	this->denom = denominator;
	this->simplify();
}

// ----------------------------------------------------------------
f2polyrat_t::f2polyrat_t(f2poly_t numerator)
{
	this->numer = numerator;
	this->denom = 1;
	this->simplify();
}

// ----------------------------------------------------------------
f2polyrat_t::f2polyrat_t(int inumer)
{
	this->numer = f2poly_t(inumer);
	this->denom = 1;
	this->simplify();
}

// ----------------------------------------------------------------
f2polyrat_t::f2polyrat_t(const f2polyrat_t & that)
{
	this->numer = that.numer;
	this->denom = that.denom;
}

// ----------------------------------------------------------------
f2polyrat_t::f2polyrat_t(void)
{
	this->numer = 0;
	this->denom = 1;
}

// ----------------------------------------------------------------
f2polyrat_t::~f2polyrat_t(void)
{
	this->numer = 0;
	this->denom = 1;
}

// ----------------------------------------------------------------
f2polyrat_t f2polyrat_t::prime_sfld_elt(int v) const
{
	return f2polyrat_t(v & 1);
}

// ----------------------------------------------------------------
int f2polyrat_t::get_char(void)
{
	return 2;
}

// ----------------------------------------------------------------
f2polyrat_t & f2polyrat_t::operator=(f2polyrat_t that)
{
	this->numer = that.numer;
	this->denom = that.denom;
	return *this;
}

// ----------------------------------------------------------------
f2polyrat_t & f2polyrat_t::operator=(f2poly_t numerator)
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

f2polyrat_t f2polyrat_t::operator+(f2polyrat_t that) const
{
	f2polyrat_t rv;
	rv.numer = this->numer * that.denom + this->denom * that.numer;
	rv.denom = this->denom * that.denom;
	rv.simplify();
	return rv;
}

// ----------------------------------------------------------------
f2polyrat_t f2polyrat_t::operator-(f2polyrat_t that) const
{
	f2polyrat_t rv;
	rv.numer = this->numer * that.denom - this->denom * that.numer;
	rv.denom = this->denom * that.denom;
	rv.simplify();
	return rv;
}

// ----------------------------------------------------------------
f2polyrat_t f2polyrat_t::operator-(void) const
{
	f2polyrat_t rv;
	rv.numer = - this->numer;
	rv.denom =   this->denom;
	return rv;
}

// ----------------------------------------------------------------
f2polyrat_t f2polyrat_t::operator*(f2polyrat_t that)
{
	f2polyrat_t rv;
	rv.numer = this->numer * that.numer;
	rv.denom = this->denom * that.denom;
	rv.simplify();
	return rv;
}

// ----------------------------------------------------------------
f2polyrat_t f2polyrat_t::operator/(f2polyrat_t that)
{
	f2polyrat_t rv;
	rv.numer = this->numer * that.denom;
	rv.denom = this->denom * that.numer;
	rv.simplify();
	return rv;
}

// ----------------------------------------------------------------
f2polyrat_t f2polyrat_t::operator%(f2polyrat_t that)
{
	f2polyrat_t rv;
	f2polyrat_t zero = that - that;
	if (that == zero) {
		std::cerr << "f2polyrat_t: Divide by zero.\n";
		exit(1);
	}
	return zero;
}

// ----------------------------------------------------------------
f2polyrat_t f2polyrat_t::exp(int e)
{
	f2polyrat_t xp = *this;
	f2polyrat_t zero(0);
	f2polyrat_t one (1);
	f2polyrat_t rv = one;

	if (e == 0) {
		if (*this == zero) {
			std::cerr << "f2polyrat_t::exp:  0 ^ 0 undefined.\n";
			exit(1);
		}
		return one;
	}
	else if (e < 0) {
		if (*this == zero) {
			std::cerr << "f2polyrat_t::exp:  division by zero.\n";
			exit(1);
		}
		if (e == -e) {
			std::cerr << "f2polyrat_t::exp:  can't handle "
				"MIN_F2POLY.\n";
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
std::ostream & operator<<(std::ostream & os, const f2polyrat_t & a)
{
	os << a.numer;
	if (a.denom != 1)
		os << "/" << a.denom;
	return os;
}

// ----------------------------------------------------------------
std::istream & operator>>(std::istream & is, f2polyrat_t & a)
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
std::istringstream & operator>>(std::istringstream & iss, f2polyrat_t & a)
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
int f2polyrat_t::from_string(char * string)
{
	std::istringstream iss(string, std::ios_base::in);
	iss >> *this;
	return iss.fail() ? 0 : 1;
}

// ----------------------------------------------------------------
f2polyrat_t & f2polyrat_t::operator+=(f2polyrat_t that)
{
	*this = *this + that;
	return *this;
}

// ----------------------------------------------------------------
f2polyrat_t & f2polyrat_t::operator-=(f2polyrat_t that)
{
	*this = *this - that;
	return *this;
}

// ----------------------------------------------------------------
f2polyrat_t & f2polyrat_t::operator*=(f2polyrat_t that)
{
	*this = *this * that;
	return *this;
}

// ----------------------------------------------------------------
f2polyrat_t & f2polyrat_t::operator/=(f2polyrat_t that)
{
	*this = *this / that;
	return *this;
}

// ----------------------------------------------------------------
f2polyrat_t & f2polyrat_t::operator%=(f2polyrat_t that)
{
	*this = *this % that;
	return *this;
}

// ----------------------------------------------------------------
int f2polyrat_t::operator==(f2polyrat_t that) const
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
int f2polyrat_t::operator!=(f2polyrat_t that) const
{
	return ! (*this == that);
}

// ----------------------------------------------------------------
int f2polyrat_t::operator==(f2poly_t that) const
{
	if (this->denom != f2poly_t(1))
		return 0;
	return this->numer == that;
}

// ----------------------------------------------------------------
int f2polyrat_t::operator!=(f2poly_t that) const
{
	return !(*this == that);
}

// ----------------------------------------------------------------
int f2polyrat_t::operator<(f2polyrat_t that) const
{
	return ((this->numer * that.denom) <  (this->denom * that.numer));
}

// ----------------------------------------------------------------
int f2polyrat_t::operator<=(f2polyrat_t that) const
{
	return ((this->numer * that.denom) <= (this->denom * that.numer));
}

// ----------------------------------------------------------------
int f2polyrat_t::operator>(f2polyrat_t that) const
{
	return ((this->numer * that.denom) >  (this->denom * that.numer));
}

// ----------------------------------------------------------------
int f2polyrat_t::operator>=(f2polyrat_t that) const
{
	return ((this->numer * that.denom) >= (this->denom * that.numer));
}

// ----------------------------------------------------------------
f2poly_t f2polyrat_t::get_numerator(void) const
{
	return this->numer;
}

// ----------------------------------------------------------------
f2poly_t f2polyrat_t::get_denominator(void) const
{
	return this->denom;
}

// ----------------------------------------------------------------
// * Check denominator != 0
// * Divide numerator and denominator by their GCD

void f2polyrat_t::simplify(void)
{
	f2poly_t g;
	if (this->denom == 0) {
		std::cerr << "rat: Divide by zero.\n";
		exit(1);
	}
	g = this->numer.gcd(this->denom);
	this->numer /= g;
	this->denom /= g;
}
