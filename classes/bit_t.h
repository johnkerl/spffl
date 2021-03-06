// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef BIT_T_H
#define BIT_T_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <stdlib.h>

// Bit operations are more efficiently done a machine word at a time.
// This class exists solely to be able to re-use code by using the tmatrix
// template class.
//
// The same functionality is provided as with intmod_t, using modulus 2.
// However, the current is more efficient since it eschews the C mod operator,
// which is time-expensive at the instruction level.

class bit_t {
public:

	bit_t(int arg_residue)
	{
		this->residue = arg_residue & 1;
	}

	bit_t(const bit_t & that)
	{
		this->residue = that.residue;
	}

	bit_t(void)
	{
		this->residue = 0;
	}

	bit_t & operator=(bit_t that)
	{
		this->residue = that.residue;
		return *this;
	}

	bit_t & operator=(int e)
	{
		this->residue = e;
		return *this;
	}

	bit_t operator+(bit_t that)
	{
		bit_t rv;
		rv.residue = this->residue ^ that.residue;
		return rv;
	}

	bit_t operator-(bit_t that)
	{
		bit_t rv;
		rv.residue = this->residue ^ that.residue;
		return rv;
	}

	bit_t operator-(void)
	{
		return *this;
	}

	bit_t operator*(bit_t that)
	{
		bit_t rv;
		rv.residue = this->residue & that.residue;
		return rv;
	}

	bit_t exp(int power)
	{
		return *this;
	}

	bit_t operator/(bit_t that)
	{
		if (that.residue == 0) {
			std::cerr << "bit_t::operator/:  division by zero.\n";
			exit(1);
		}
		return *this;
	}

	bit_t operator%(bit_t that)
	{
		if (that.residue == 0) {
			std::cerr << "bit_t::operator%:  division by zero.\n";
			exit(1);
		}
		return bit_t(0);
	}

	bit_t & operator+=(bit_t that)
	{
		this->residue ^= that.residue;
		return *this;
	}

	bit_t & operator-=(bit_t that)
	{
		this->residue ^= that.residue;
		return *this;
	}

	bit_t & operator*=(bit_t that)
	{
		this->residue &= that.residue;
		return *this;
	}

	bit_t & operator/=(bit_t that)
	{
		if (that.residue == 0) {
			std::cerr << "bit_t::operator/:  division by zero.\n";
			exit(1);
		}
		return *this;
	}

	bit_t & operator%=(bit_t that)
	{
		if (that.residue == 0) {
			std::cerr << "bit_t::operator/:  division by zero.\n";
			exit(1);
		}
		this->residue = 0;
		return *this;
	}

	int operator==(bit_t that) const
	{
		return this->residue == that.residue;
	}

	int operator!=(bit_t that) const
	{
		return this->residue != that.residue;
	}

	int operator==(int that) const
	{
		return this->residue == that;
	}

	int operator!=(int that) const
	{
		return this->residue != that;
	}

	// Z/mZ is *not* totally ordered.  Nonetheless, these methods are
	// handy for looping and sorting.
	int operator<(bit_t that) const
	{
		return this->residue < that.residue;
	}

	int operator<=(bit_t that) const
	{
		return this->residue <= that.residue;
	}

	int operator>(bit_t that) const
	{
		return this->residue > that.residue;
	}

	int operator>=(bit_t that) const
	{
		return this->residue >= that.residue;
	}

	int get_residue(void) const
	{
		return this->residue;
	}

	friend std::ostream & operator<<(std::ostream & os,
		const bit_t & a);
	friend std::istream & operator>>(std::istream & is,
		bit_t & a);
	int from_string(char * string);

private:
	unsigned char residue;
};

#endif // BIT_T_H
