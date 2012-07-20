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

#ifndef TSTACK_H
#define TSTACK_H

#include <iostream>
#include <sstream>
#include <fstream>

#define TSTACK_INIT_SIZE 10
#define TSTACK_INCR_SIZE 10

// ================================================================
template <class element_type>
class tstack
{
public:
// ----------------------------------------------------------------
tstack(void)
{
	this->num_allocated = TSTACK_INIT_SIZE;
	this->elements = new element_type[this->num_allocated];
	this->freeidx = 0;
}

// ----------------------------------------------------------------
tstack(const tstack<element_type> & that)
{
	this->num_allocated = that.num_allocated;
	this->freeidx = that.freeidx;
	this->elements = new element_type[that.num_allocated];
	for (int i = 0; i < that.freeidx; i++)
		this->elements[i] = that.elements[i];
}

// ----------------------------------------------------------------
~tstack(void)
{
	if (this->elements != 0) {
		delete [] this->elements;
		this->elements = 0;
	}
	this->num_allocated = 0;
	this->freeidx = 0;
}

// ----------------------------------------------------------------
tstack<element_type> &
operator=(tstack<element_type> that)
{
	if (this->elements != 0)
		delete [] this->elements;
	this->num_allocated = that.num_allocated;
	this->freeidx = that.freeidx;
	this->elements = new element_type[that.num_allocated];
	for (int i = 0; i < that.freeidx; i++)
		this->elements[i] = that.elements[i];
}

// ----------------------------------------------------------------
void push(element_type & re)
{
	if (this->freeidx >= this->num_allocated) {
		element_type * temp = this->elements;
		this->num_allocated += TSTACK_INCR_SIZE;
		this->elements = new element_type[this->num_allocated];
		for (int i = 0; i < this->freeidx; i++)
			this->elements[i] = temp[i];
		delete [] temp;
	}
	this->elements[this->freeidx] = re;
	this->freeidx++;
}

// ----------------------------------------------------------------
int pop(element_type & re)
{
	if (this->freeidx > 0) {
		this->freeidx--;
		re = this->elements[freeidx];
		return 1;
	}
	else {
		return 0;
	}
}

// ================================================================
private:
element_type * elements;
int            num_allocated;
int            freeidx;

};

// ================================================================
template <class element_type>
static
std::ostream & operator<< (
	std::ostream & os,
	const tstack<element_type> & v)
{
	for (int i = 0; i < v.num_elements; i++) {
		os << v.elements[i];
		if (i < (v.num_elements - 1))
			os << " ";
	}
	return os;
}

// ----------------------------------------------------------------
// See comment for istringstream >>:  stack must already have one element.

template <class element_type>
static
std::istream & operator>> (
	std::istream & is,
	tstack<element_type> & v)
{
	// Read a line and use istringstream >>.
	char line[2048];
	is.getline(line, sizeof(line));
	std::istringstream iss(line, std::ios_base::in);
	iss >> v;
	if (iss.fail()) {
		is.setstate(std::ios::failbit);
	}
	return is;
}

// ----------------------------------------------------------------
// The stack must already contain at least one element, even though it
// will be discarded.  I know no other way to set the modulus for mod types,
// other than requiring all input data to have moduli for each and every
// element (yuk).

template <class element_type>
static
std::istringstream & operator>> (
	std::istringstream & iss,
	tstack<element_type> & v)
{
	const int init_size = 10;
	const int more_size = 10;
	int alloc_size = init_size;

	if (!v.elements || (v.num_elements < 1)) {
		iss.setstate(std::ios::badbit);
		std::cerr <<
			"tstack string >>:  must already have one element.\n";
		return iss;
	}

	element_type zero = v.elements[0] - v.elements[0];
	if (v.elements)
		delete [] v.elements;
	v.elements = 0;
	v.num_elements = 0;

	v.elements = new element_type[alloc_size];
	while (1) {
		if (iss.eof()) {
			break;
		}

		// xxx append method w/ optional #growth arg
		if (v.num_elements >= alloc_size) {
			alloc_size += more_size;
			element_type * ptemp = new element_type[alloc_size];
			for (int i = 0; i < v.num_elements; i++)
				ptemp[i] = v.elements[i];
			delete [] v.elements;
			v.elements = ptemp;
		}
		v.elements[v.num_elements] = zero; // E.g. set modulus.
		iss >> v.elements[v.num_elements];
		if (iss.fail()) {
			std::cerr
				<< "tstack istringstream >>: scan failure"
				<< " at stack element " << v.num_elements
				<< ".\n";
			std::cerr << "String: <<" << iss.str() << ">>\n";
			std::cerr << "Position: " << iss.tellg() << "\n";
			return iss;
		}
		v.num_elements++;
	}

	return iss;
}

#endif // TSTACK_H
