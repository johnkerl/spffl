// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYRAT_T_H
#define F2POLYRAT_T_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include "f2poly_t.h"

class f2polyrat_t {
public:
	f2polyrat_t(f2poly_t numerator, f2poly_t denominator);
	f2polyrat_t(f2poly_t numerator);
	f2polyrat_t(int inumer);
	f2polyrat_t(void);
	f2polyrat_t(const f2polyrat_t & that);
	~f2polyrat_t(void);

	f2polyrat_t   prime_sfld_elt(int v) const;
	int get_char(void);

	f2polyrat_t & operator=(f2polyrat_t that);
	f2polyrat_t & operator=(f2poly_t numer);
	f2polyrat_t   operator+(f2polyrat_t that) const;
	f2polyrat_t   operator-(f2polyrat_t that) const;
	f2polyrat_t   operator-(void) const;
	f2polyrat_t   operator*(f2polyrat_t that);
	f2polyrat_t   operator/(f2polyrat_t that);
	f2polyrat_t   operator%(f2polyrat_t that);
	f2polyrat_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const f2polyrat_t & a);
	friend std::istream & operator>>(std::istream & is,
		f2polyrat_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		f2polyrat_t & a);
	int from_string(char * string);

	f2polyrat_t & operator+=(f2polyrat_t that);
	f2polyrat_t & operator-=(f2polyrat_t that);
	f2polyrat_t & operator*=(f2polyrat_t that);
	f2polyrat_t & operator/=(f2polyrat_t that);
	f2polyrat_t & operator%=(f2polyrat_t that);

	int operator==(f2polyrat_t that) const;
	int operator!=(f2polyrat_t that) const;
	int operator==(f2poly_t that) const;
	int operator!=(f2poly_t that) const;

	int operator< (f2polyrat_t that) const;
	int operator> (f2polyrat_t that) const;
	int operator<=(f2polyrat_t that) const;
	int operator>=(f2polyrat_t that) const;

	f2poly_t get_numerator(void) const;
	f2poly_t get_denominator(void) const;

private:
	f2poly_t numer;
	f2poly_t denom;

	void simplify();
};

#endif // F2POLYRAT_T_H
