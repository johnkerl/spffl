// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2NPOLYMOD_T_H
#define F2NPOLYMOD_T_H

#include <iostream>
#include <iomanip>
#include "f2npoly_t.h"

class f2npolymod_t {
public:
	f2npolymod_t(f2npoly_t residue, f2npoly_t modulus);
	f2npolymod_t(void);
	f2npolymod_t(const f2npolymod_t & that);
	~f2npolymod_t(void);

	f2npolymod_t   prime_sfld_elt(int v) const;
	static f2npolymod_t prime_sfld_elt(int v, f2npoly_t om);
	int get_char(void);

	f2npolymod_t & operator=(f2npolymod_t that);
	f2npolymod_t   operator+(f2npolymod_t that);
	f2npolymod_t   operator-(f2npolymod_t that);
	f2npolymod_t   operator-(void);
	f2npolymod_t   operator*(f2npolymod_t that);
	f2npolymod_t   operator*(int a); // Repeated addition.
	f2npolymod_t   operator/(f2npolymod_t that);
	f2npolymod_t   operator%(f2npolymod_t that);
	int            recip(f2npolymod_t & rinv);
	f2npolymod_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const f2npolymod_t & a);
	// Modulus must have already been set:  this sets only the residue.
	friend std::istream & operator>>(std::ostream & os,
		const f2npolymod_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		f2npolymod_t & a);
	int from_string(char * string, f2npoly_t & m);

	f2npolymod_t & operator+=(f2npolymod_t that);
	f2npolymod_t & operator-=(f2npolymod_t that);
	f2npolymod_t & operator*=(f2npolymod_t that);
	f2npolymod_t & operator*=(int a);
	f2npolymod_t & operator/=(f2npolymod_t that);
	f2npolymod_t & operator%=(f2npolymod_t that);

	int operator==(f2npolymod_t that) const;
	int operator!=(f2npolymod_t that) const;
	int operator==(int that) const;
	int operator!=(int that) const;
	// Polynomial quotient rings are *not* totally ordered.
	// Nonetheless, these methods are handy for looping and sorting.
	int operator< (f2npolymod_t that) const;
	int operator> (f2npolymod_t that) const;
	int operator<=(f2npolymod_t that) const;
	int operator>=(f2npolymod_t that) const;

	f2npoly_t get_residue(void) const;
	f2npoly_t get_modulus(void) const;

private:
	f2npoly_t residue;
	f2npoly_t modulus;

	void check_moduli(f2npolymod_t & that) const;
};

#endif // F2NPOLYMOD_T_H
