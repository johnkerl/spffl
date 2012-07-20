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

#ifndef BIT_VECTOR_T_H
#define BIT_VECTOR_T_H

#define BITS_PER_WORD (8 * sizeof(unsigned))

#define WORD_MASK (BITS_PER_WORD - 1)

// Need to make this a macro.  Currently hard-coded for 32-bit ints.
// Recall that you can't do sizeof in a macro (the latter are handled by
// the preprocessor, the former aren't seen until the compiler per se).
#define BITS_SHIFT 5

#define WORD_INDEX_FROM_BIT_INDEX(bi) ((bi) >> BITS_SHIFT)
#define WORD_POS_FROM_BIT_INDEX(bi) (31 - ((bi) & WORD_MASK))

#define GET_BIT(wordptr,bi) \
((wordptr[WORD_INDEX_FROM_BIT_INDEX(bi)] >> WORD_POS_FROM_BIT_INDEX(bi)) & 1)

#define SET_BIT(wordptr,bi) \
(wordptr[WORD_INDEX_FROM_BIT_INDEX(bi)] |= (1 << WORD_POS_FROM_BIT_INDEX(bi)))

#define CLEAR_BIT(wordptr,bi) \
(wordptr[WORD_INDEX_FROM_BIT_INDEX(bi)] &= ~(1 << WORD_POS_FROM_BIT_INDEX(bi)))

#define TOGGLE_BIT(wordptr,bi) \
(wordptr[WORD_INDEX_FROM_BIT_INDEX(bi)] ^= (1 << WORD_POS_FROM_BIT_INDEX(bi)))

#define NWORDS_FROM_NBITS(nb) (((nb) + BITS_PER_WORD - 1) >> BITS_SHIFT)


#include <iostream>
#include <sstream>
#include <fstream>
#include "bit_t.h"

class bit_vector_t
{
public:
	bit_vector_t(void);
	bit_vector_t(int init_num_elements);
	bit_vector_t(bit_t scalar, int init_num_elements);
	bit_vector_t(int   scalar, int init_num_elements);
	bit_vector_t(const bit_vector_t & that);
	~bit_vector_t(void);

	bit_vector_t & operator=(bit_vector_t that);
	bit_vector_t & operator=(const bit_t scalar);

	// I/O format:  all elements on one line, delimited by whitespace.
	friend std::ostream & operator<< (
		std::ostream & os,
		const bit_vector_t & v);

	friend std::istream & operator>> (
		std::istream & is,
		bit_vector_t & v);

	friend std::istringstream & operator>> (
		std::istringstream & is,
		bit_vector_t & v);

	// No spaces between elements.  (Instead, perhaps I could implement a
	// derived iomanip, and then just use ostream <<.)
	void sqzout(std::ostream & os);

	// Carriage return between elements.
	void crout(std::ostream & os);

	bit_t get(int index)
	{
		if ((index < 0) || (index >= this->num_bits))
			this->bounds_check(index);
		return bit_t(GET_BIT(this->words, index));
	}

	void set(int index, bit_t value)
	{
		if ((index < 0) || (index >= this->num_bits))
			this->bounds_check(index);
		if (value.get_residue())
			SET_BIT(this->words, index);
		else
			CLEAR_BIT(this->words, index);
	}

	void set(int index, int value)
	{
		if ((index < 0) || (index >= this->num_bits))
			this->bounds_check(index);
		if (value & 1)
			SET_BIT(this->words, index);
		else
			CLEAR_BIT(this->words, index);
	}

	void toggle_element(int index);
	int is_zero(void);

	bit_vector_t operator+(bit_vector_t that);
	bit_vector_t operator-(bit_vector_t that);
	bit_vector_t operator*(bit_t s);

	// This is componentwise multiplication (u * v), useful for
	// implementing direct products of rings.
	//
	// Use dot() (e.g. u.dot(v)) for inner product, or bit_matrix_t's
	// outer() (e.g.  bit_matrix_t::outer(u, v)) for outer product.
	bit_vector_t operator*(bit_vector_t that);
	bit_t dot(bit_vector_t that);

	// Componentwise division.
	bit_vector_t operator/(bit_vector_t that);
	bit_vector_t operator+=(bit_vector_t that);
	bit_vector_t operator-=(bit_vector_t that);
	bit_vector_t operator*=(bit_t scalar);
	bit_vector_t operator*=(bit_vector_t that);

	int operator==(bit_vector_t & that);
	int operator!=(bit_vector_t & that);
	int operator==(bit_t scalar);
	int operator!=(bit_t scalar);

	// Warning:  trusts the caller to remain in bounds!
	int get_bit(int index) { return GET_BIT(this->words, index); }

	void accum_row(bit_vector_t & that);
	int get_num_elements(void);
	void ptrswap(bit_vector_t & that);
	int find_leader_pos(int & rpos);

	unsigned * expose() { return this->words; }

// ----------------------------------------------------------------
private:
	unsigned * words;
	int        num_words;
	int        num_bits;

	// Return value:  True/false.  rpos:  index, if found.
	void check_equal_lengths(bit_vector_t & that);
	void bounds_check(int index);
	void trim(void);
};


#endif // BIT_VECTOR_T_H
