// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef TEIGINFO_H
#define TEIGINFO_H

#error Under construction.

#include <iostream>
#include <sstream>
#include <fstream>
#include "spffl/tmatrix.h"

#define TEIGINFO_INIT_LENGTH 8
#define TEIGINFO_INCR_LENGTH 8

// ================================================================
template <class element_type>
class teiginfo
{
// ================================================================
private:
	struct eival_info_t {
		element_type eigenvalue;
		int multiplicity;
		tmatrix<element_type> eigenspace_basis;
	} * peival_infos;
	int num_eivals;
	int num_allocated;

// ================================================================
public:

// ----------------------------------------------------------------
teiginfo(void)
{
	this->num_eivals    = 0;
	this->num_allocated = TEIGINFO_INIT_LENGTH;
	this->peival_infos  = new eival_info_t[ this->num_allocated];
}

// ----------------------------------------------------------------
teiginfo(const teiginfo<element_type> & that)
{
	this->num_eivals    = that.num_eivals;
	this->num_allocated = that.num_eivals;
	this->peival_infos  = new eival_info_t [that.num_eivals];
	for (int i = 0; i < that.num_eivals; i++)
		this->peival_infos[i] = that.peival_infos[i];
}

// ----------------------------------------------------------------
teiginfo<element_type> &
operator=(teiginfo<element_type> that)
{
	if (this->peival_infos)
		delete [] this->peival_infos;

	this->num_eivals   = that.num_eivals;
	this->num_allocated  = that.num_eivals;
	this->peival_infos = new eival_info_t [that.num_eivals];
	for (int i = 0; i < that.num_eivals; i++)
		this->peival_infos[i] = that.peival_infos[i];
}

// ----------------------------------------------------------------
~teiginfo(void)
{
	if (this->peival_infos)
		delete [] this->peival_infos;
	this->num_eivals    = 0;
	this->num_allocated = 0;
	this->peival_infos  = 0;
}

// ----------------------------------------------------------------
// I/O format:  all elements on one line, delimited by whitespace.
friend std::ostream & operator<< <>(
	std::ostream & os,
	const teiginfo<element_type> & v);

// ----------------------------------------------------------------
int get_num_eivals(void)
{
	return this->num_eivals;
}

// ----------------------------------------------------------------
element_type get_ith_eigenvalue(int which)
{
	this->bounds_check(which);
	return this->peival_infos[which].eigenvalue;
}

// ----------------------------------------------------------------
int get_ith_multiplicity(int which)
{
	this->bounds_check(which);
	return this->peival_infos[which].multiplicity;
}

// ----------------------------------------------------------------
tmatrix<element_type> get_ith_eigenspace_basis(int which)
{
	this->bounds_check(which);
	return this->peival_infos[which].eigenspace_basis;
}

// ----------------------------------------------------------------
void bounds_check(int which)
{
	if ((which < 0) || (which >= this->num_eivals)) {
		std::cerr << "teiginfo:  index " << which
			<< " out of bounds 0:" << this->num_eivals - 1
			<< ".\n";
		exit(1);
	}
}

// ----------------------------------------------------------------
void insert_factor(
	element_type e)
{
	this->insert_factor(e, 1);
}

// ----------------------------------------------------------------
// If the element is found, returns its index.  Else, returns the index
// at which it should be located in order to preserve sorted factors.

private:
int find(
	element_type & re,
	int          & ridx)
{
#if 1
	// Binary search.
	if (this->num_eivals == 0) {
		ridx = 0;
		return 0;
	}

	int left = 0;
	int right = this->num_eivals - 1;
	int mid  = (right + left) / 2;

	if (re < this->peival_infos[left].factor) {
		ridx = left;
		return 0;
	}
	if (re > this->peival_infos[right].factor) {
		ridx = right + 1;
		return 0;
	}

	ridx = mid;
	while (1) {
		if ((left == mid) || (mid == right)) {
			ridx = mid;
			if (re == this->peival_infos[mid].factor)
				return 1;
			if (re > this->peival_infos[mid].factor)
				ridx++;
			return 0;
		}
		if (re == this->peival_infos[mid].factor) {
			ridx = mid;
			return 1;
		}
		else if (re < this->peival_infos[mid].factor) {
			right = mid;
		}
		else {
			left = mid;
		}
		mid  = (right + left) / 2;
	}
	ridx = mid;
	if (re > this->peival_infos[mid].factor)
		ridx++;
	return 0;
#else
	// Linear search.
	for (int i = 0; i < this->num_eivals; i++) {
		if (re == this->peival_infos[i].factor) {
			ridx = i;
			return 1;
		}
		if (re < this->peival_infos[i].factor) {
			ridx = i;
			return 0;
		}
	}
	ridx = this->num_eivals;
	return 0;
#endif
}
public:

// ----------------------------------------------------------------
void insert_factor(
	element_type e,
	int count)
{
	int idx = 0;

	// Insert a repeated factor.
	if (this->find(e, idx)) {
		this->peival_infos[idx].count += count;
		return;
	}

	// Need to resize the array?
	if (this->num_eivals >= this->num_allocated) {
		eival_info_t * temp = this->peival_infos;
		this->num_allocated += TEIGINFO_INCR_LENGTH;
		this->peival_infos = new eival_info_t[
			this->num_allocated];
		for (int i = 0; i < this->num_eivals; i++)
			this->peival_infos[i] = temp[i];
	}

	// Insert a new factor.  The find() method has returned the correct
	// insertion point.
	for (int i = this->num_eivals; i > idx; i--)
		this->peival_infos[i] = this->peival_infos[i-1];

	this->peival_infos[idx].factor = e;
	this->peival_infos[idx].count = count;
	this->num_eivals++;
}

};

// ================================================================
template <class element_type>
static
std::ostream & operator<< (
	std::ostream & os,
	const teiginfo<element_type> & finfo)
{
	for (int i = 0; i < finfo.num_eivals; i++) {
		os << finfo.peival_infos[i].factor;
		if (finfo.peival_infos[i].count != 1)
			os << "^" << finfo.peival_infos[i].count;
	}
	return os;
}

#endif // TEIGINFO_H
