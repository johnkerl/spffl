// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLYMOD_T_H
#define F2POLYMOD_T_H

#include <iostream>
#include <iomanip>
#include "f2poly_t.h"

class f2polymod_t {
public:
	f2polymod_t(f2poly_t residue, f2poly_t modulus);
	f2polymod_t(void);
	f2polymod_t(const f2polymod_t & that);
	~f2polymod_t(void);

	f2polymod_t   prime_sfld_elt(int v) const;
	static f2polymod_t   prime_sfld_elt(int v, f2poly_t m);
	int get_char(void);

	f2polymod_t & operator=(f2polymod_t that);
	f2polymod_t   operator+(f2polymod_t that);
	f2polymod_t   operator-(f2polymod_t that);
	f2polymod_t   operator-(void);
	f2polymod_t   operator*(f2polymod_t that);
	f2polymod_t   operator*(int a); // Repeated addition.
	f2polymod_t   operator/(f2polymod_t that);
	f2polymod_t   operator%(f2polymod_t that);
	int           recip(f2polymod_t & rinv);
	f2polymod_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const f2polymod_t & a);
	// Modulus must have already been set:  this sets only the residue.
	friend std::istream & operator>>(std::istream & is,
		f2polymod_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		f2polymod_t & a);
	int from_string(char * string, f2poly_t m);

	f2polymod_t & operator+=(f2polymod_t that);
	f2polymod_t & operator-=(f2polymod_t that);
	f2polymod_t & operator*=(f2polymod_t that);
	f2polymod_t & operator*=(int a);
	f2polymod_t & operator/=(f2polymod_t that);
	f2polymod_t & operator%=(f2polymod_t that);

	int operator==(f2polymod_t that) const;
	int operator!=(f2polymod_t that) const;
	int operator==(int that) const;
	int operator!=(int that) const;
	// Polynomial quotient rings are *not* totally ordered.
	// Nonetheless, these methods are handy for looping and sorting.
	int operator< (f2polymod_t that) const;
	int operator> (f2polymod_t that) const;
	int operator<=(f2polymod_t that) const;
	int operator>=(f2polymod_t that) const;

	f2poly_t get_residue(void) const;
	f2poly_t get_modulus(void) const;
	void change_modulus(f2poly_t new_modulus);

private:
	f2poly_t residue;
	f2poly_t modulus;

	void check_moduli(f2polymod_t & that) const;
};

inline f2polymod_t::f2polymod_t(void)
{
	// Use default ctors for residue and modulus.
}

inline f2polymod_t::~f2polymod_t(void)
{
}

#endif // F2POLYMOD_T_H
