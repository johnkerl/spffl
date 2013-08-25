// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPPOLYRAT_T_H
#define FPPOLYRAT_T_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include "fppoly_t.h"

class fppolyrat_t {
public:
	fppolyrat_t(fppoly_t numerator, fppoly_t denominator);
	fppolyrat_t(fppoly_t numerator);
	fppolyrat_t(void);
	fppolyrat_t(const fppolyrat_t & that);
	~fppolyrat_t(void);

	fppolyrat_t   prime_sfld_elt(int v) const;
	static fppolyrat_t prime_sfld_elt(int v, int p);
	int get_char(void);

	fppolyrat_t & operator=(fppolyrat_t that);
	fppolyrat_t & operator=(fppoly_t numer);
	fppolyrat_t   operator+(fppolyrat_t that) const;
	fppolyrat_t   operator-(fppolyrat_t that) const;
	fppolyrat_t   operator-(void) const;
	fppolyrat_t   operator*(fppolyrat_t that);
	fppolyrat_t   operator/(fppolyrat_t that);
	fppolyrat_t   operator%(fppolyrat_t that);
	fppolyrat_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const fppolyrat_t & a);
	friend std::istream & operator>>(std::istream & is,
		fppolyrat_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		fppolyrat_t & a);
	int from_string(char * string, int p);

	fppolyrat_t & operator+=(fppolyrat_t that);
	fppolyrat_t & operator-=(fppolyrat_t that);
	fppolyrat_t & operator*=(fppolyrat_t that);
	fppolyrat_t & operator/=(fppolyrat_t that);
	fppolyrat_t & operator%=(fppolyrat_t that);

	int operator==(fppolyrat_t that) const;
	int operator!=(fppolyrat_t that) const;
	int operator==(fppoly_t that) const;
	int operator!=(fppoly_t that) const;

	int operator< (fppolyrat_t that) const;
	int operator> (fppolyrat_t that) const;
	int operator<=(fppolyrat_t that) const;
	int operator>=(fppolyrat_t that) const;

	fppoly_t get_numerator(void) const;
	fppoly_t get_denominator(void) const;

private:
	fppoly_t numer;
	fppoly_t denom;

	void simplify();
};

#endif // FPPOLYRAT_T_H
