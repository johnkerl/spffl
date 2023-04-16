// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef FPNPOLYMOD_T_H
#define FPNPOLYMOD_T_H

#include <iostream>
#include <iomanip>
#include "fpnpoly_t.h"

class fpnpolymod_t {
public:
	fpnpolymod_t(fpnpoly_t residue, fpnpoly_t modulus);
	fpnpolymod_t(void);
	fpnpolymod_t(const fpnpolymod_t & that);
	~fpnpolymod_t(void);

	fpnpolymod_t   prime_sfld_elt(int v) const;
	static fpnpolymod_t prime_sfld_elt(int v, fpnpoly_t om);
	int get_char(void);

	fpnpolymod_t & operator=(fpnpolymod_t that);
	fpnpolymod_t   operator+(fpnpolymod_t that);
	fpnpolymod_t   operator-(fpnpolymod_t that);
	fpnpolymod_t   operator-(void);
	fpnpolymod_t   operator*(fpnpolymod_t that);
	fpnpolymod_t   operator*(int a); // Repeated addition.
	fpnpolymod_t   operator/(fpnpolymod_t that);
	fpnpolymod_t   operator%(fpnpolymod_t that);
	int            recip(fpnpolymod_t & rinv);
	fpnpolymod_t   exp(int e);
	friend std::ostream & operator<<(std::ostream & os,
		const fpnpolymod_t & a);
	// Modulus must have already been set:  this sets only the residue.
	friend std::istream & operator>>(std::ostream & os,
		const fpnpolymod_t & a);
	friend std::istringstream & operator>>(std::istringstream & iss,
		fpnpolymod_t & a);
	int from_string(char * string, fpnpoly_t & m);

	fpnpolymod_t & operator+=(fpnpolymod_t that);
	fpnpolymod_t & operator-=(fpnpolymod_t that);
	fpnpolymod_t & operator*=(fpnpolymod_t that);
	fpnpolymod_t & operator*=(int a);
	fpnpolymod_t & operator/=(fpnpolymod_t that);
	fpnpolymod_t & operator%=(fpnpolymod_t that);

	int operator==(fpnpolymod_t that) const;
	int operator!=(fpnpolymod_t that) const;
	int operator==(int that) const;
	int operator!=(int that) const;
	// Polynomial quotient rings are *not* totally ordered.
	// Nonetheless, these methods are handy for looping and sorting.
	int operator< (fpnpolymod_t that) const;
	int operator> (fpnpolymod_t that) const;
	int operator<=(fpnpolymod_t that) const;
	int operator>=(fpnpolymod_t that) const;

	fpnpoly_t get_residue(void) const;
	fpnpoly_t get_modulus(void) const;

private:
	fpnpoly_t residue;
	fpnpoly_t modulus;

	void check_moduli(fpnpolymod_t & that) const;
};

#endif // FPNPOLYMOD_T_H
