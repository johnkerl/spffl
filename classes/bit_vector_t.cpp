// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <string.h>
#include "bit_vector_t.h"
#include "log2.h"
#include "count_bits.h"

// ----------------------------------------------------------------
bit_vector_t::bit_vector_t(void)
{
	this->words = 0;
	this->num_words = 0;
	this->num_bits = 0;
}

// ----------------------------------------------------------------
bit_vector_t::bit_vector_t(int init_num_elements)
{
	if (init_num_elements <= 0) {
		std::cerr
			<< "bit_vector_t::bit_vector_t():  Vector size must be"
			<< " > 0; got " << init_num_elements << ".  Exiting."
			<< std::endl;
		exit(1);
	}

	this->num_bits = init_num_elements;
	this->num_words = NWORDS_FROM_NBITS(this->num_bits);
	this->words = new unsigned[this->num_words];
	memset(this->words, 0, this->num_words * sizeof(unsigned));
}

// ----------------------------------------------------------------
bit_vector_t::bit_vector_t(bit_t scalar, int init_num_elements)
{
	if (init_num_elements <= 0) {
		std::cerr
			<< "bit_vector_t::bit_vector_t():  Vector size must be"
			<< " > 0; got "
			<< init_num_elements
			<< ".  Exiting."
			<< std::endl;
		exit(1);
	}

	this->num_bits = init_num_elements;
	this->num_words = NWORDS_FROM_NBITS(this->num_bits);
	this->words = new unsigned[this->num_words];
	unsigned fill = 0;
	if (scalar == bit_t(1))
		fill = ~fill;
	for (int i = 0; i < this->num_words; i++)
		this->words[i] = fill;
	this->trim();
}

// ----------------------------------------------------------------
bit_vector_t::bit_vector_t(int scalar, int init_num_elements)
{
	if (init_num_elements <= 0) {
		std::cerr
			<< "bit_vector_t::bit_vector_t():  Vector size must be"
			<< " > 0; got "
			<< init_num_elements
			<< ".  Exiting."
			<< std::endl;
		exit(1);
	}

	this->num_bits = init_num_elements;
	this->num_words = NWORDS_FROM_NBITS(this->num_bits);
	this->words = new unsigned[this->num_words];
	unsigned fill = 0;
	if (scalar == 1)
		fill = ~fill;
	for (int i = 0; i < this->num_words; i++)
		this->words[i] = fill;
	this->trim();
}

// ----------------------------------------------------------------
bit_vector_t::bit_vector_t(const bit_vector_t & that)
{
	this->num_bits = that.num_bits;
	this->num_words = that.num_words;
	this->words = new unsigned[that.num_words];
	memcpy(this->words, that.words, that.num_words * sizeof(unsigned));
}

// ----------------------------------------------------------------
bit_vector_t::~bit_vector_t(void)
{
	if (this->words != 0) {
		delete [] this->words;
		this->words = 0;
	}
	this->num_bits = 0;
	this->num_words = 0;
}

// ----------------------------------------------------------------
bit_vector_t & bit_vector_t::operator=(bit_vector_t that)
{
	this->num_bits = that.num_bits;
	this->num_words = that.num_words;
	if (this->words == 0) {
		this->words = new unsigned[that.num_words];
	}
	else if (this->num_words < that.num_words) {
		delete [] this->words;
		this->words = new unsigned[that.num_words];
	}
	memcpy(this->words, that.words, that.num_words * sizeof(unsigned));
	return *this;
}

// ----------------------------------------------------------------
bit_vector_t & bit_vector_t::operator=(const bit_t scalar)
{
	if (this->words) {
		unsigned fill = 0;
		if (scalar == bit_t(1))
			fill = ~fill;
		for (int i = 0; i < this->num_words; i++)
			this->words[i] = fill;
		this->trim();
	}
	else {
		this->num_bits = 1;
		this->num_words = 1;
		this->words = new unsigned[1];
		this->words[0] = 0;
		if (scalar == bit_t(1))
			this->words[0] = 1 << WORD_POS_FROM_BIT_INDEX(0);
		this->trim();
	}
	return *this;
}

// ----------------------------------------------------------------
std::ostream & operator<<(
	std::ostream & os,
	const bit_vector_t & v)
{
	for (int i = 0; i < v.num_bits; i++) {
		os << GET_BIT(v.words, i);
		if (i < (v.num_bits - 1))
			os << " ";
	}
	return os;
}

// ----------------------------------------------------------------
std::istream & operator>>(
	std::istream & is,
	bit_vector_t & v)
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
std::istringstream & operator>> (
	std::istringstream & iss,
	bit_vector_t & v)
{
	const int init_size = 8;
	const int more_size = 8;
	int alloc_size = init_size;
	int bit;

	if (v.words)
		delete [] v.words;
	v.words = new unsigned[alloc_size];
	v.num_words = 0;
	v.num_bits  = 0;
	for (int i = 0; i < alloc_size; i++)
		v.words[i] = 0;
	while (1) {
		if (iss.eof())
			break;
		if (v.num_words >= alloc_size) {
			alloc_size += more_size;
			unsigned * ptemp = new unsigned[alloc_size];
			for (int i = 0; i < v.num_words; i++)
				ptemp[i] = v.words[i];
			for (int i = v.num_words; i < alloc_size; i++)
				ptemp[i] = 0;
			delete [] v.words;
			v.words = ptemp;
		}
		iss >> bit;
		if (iss.fail()) {
			std::cerr
				<< "bit_vector_t istringstream >>: scan failure"
				<< " at vector element " << v.num_bits
				<< ".\n";
			std::cerr << "String: <<" << iss.str() << ">>\n";
			std::cerr << "Position: " << iss.tellg() << "\n";
			return iss;
		}
		if (bit & 1)
			SET_BIT(v.words, v.num_bits);
		v.num_bits++;
		v.num_words = (v.num_bits + BITS_PER_WORD - 1) >> BITS_SHIFT;
	}
	return iss;
}

// ----------------------------------------------------------------
// No spaces between elements.  (Instead, perhaps I could implement a
// derived iomanip, and then just use ostream <<.)
void bit_vector_t::sqzout(
	std::ostream & os)
{
	for (int i = 0; i < this->num_bits; i++)
		os << GET_BIT(this->words, i);
}

// ----------------------------------------------------------------
// Carriage return between elements.
void bit_vector_t::crout(
	std::ostream & os)
{
	for (int i = 0; i < this->num_bits; i++) {
		os << GET_BIT(this->words, i);
		os << "\n";
	}
}

// ----------------------------------------------------------------
void bit_vector_t::toggle_element(int index)
{
	if ((index < 0) || (index >= this->num_bits))
		this->bounds_check(index);
	TOGGLE_BIT(this->words, index);
}

// ----------------------------------------------------------------
int bit_vector_t::is_zero(void)
{
	for (int i = 0; i < this->num_words; i++)
		if (this->words[i])
			return 0;
	return 1;
}

// ----------------------------------------------------------------
bit_vector_t bit_vector_t::operator+(
	bit_vector_t that)
{
	this->check_equal_lengths(that);
	bit_vector_t rv(this->num_bits);
	for (int i = 0; i < this->num_words; i++)
		rv.words[i] = this->words[i] ^ that.words[i];
	return rv;
}

// ----------------------------------------------------------------
bit_vector_t bit_vector_t::operator-(
	bit_vector_t that)
{
	this->check_equal_lengths(that);
	bit_vector_t rv(this->num_bits);
	for (int i = 0; i < this->num_words; i++)
		rv.words[i] = this->words[i] ^ that.words[i];
	return rv;
}

// ----------------------------------------------------------------
bit_vector_t bit_vector_t::operator*(
	bit_t s)
{
	bit_vector_t rv(*this);
	if (s == bit_t(0))
		memset(rv.words, 0, rv.num_words * sizeof(unsigned));
	return rv;
}

// ----------------------------------------------------------------
// This is componentwise multiplication (u * v), useful for implementing
// direct products of rings.
//
// Use dot() (e.g. u.dot(v)) for inner product, or tmatrix's outer() (e.g.
// tmatrix::outer(u, v)) for outer product.

bit_vector_t bit_vector_t::operator*(
	bit_vector_t that)
{
	this->check_equal_lengths(that);
	bit_vector_t rv(this->num_bits);
	for (int i = 0; i < this->num_words; i++)
		rv.words[i] = this->words[i] & that.words[i];
	return rv;
}

// ----------------------------------------------------------------
bit_t bit_vector_t::dot(
	bit_vector_t that)
{
	if (this->num_bits != that.num_bits)
		this->check_equal_lengths(that);
	unsigned accum = 0;
	for (int i = 0; i < this->num_words; i++)
		accum ^= this->words[i] & that.words[i];
	int num_ones = count_one_bits((unsigned char *)&accum, sizeof(accum));
	bit_t rv(num_ones & 1);
	return rv;
}

// ----------------------------------------------------------------
bit_vector_t bit_vector_t::operator+=(
	bit_vector_t that)
{
	for (int i = 0; i < this->num_words; i++)
		this->words[i] ^= that.words[i];
	return *this;
}
bit_vector_t bit_vector_t::operator-=(
	bit_vector_t that)
{
	for (int i = 0; i < this->num_words; i++)
		this->words[i] ^= that.words[i];
	return *this;
}
bit_vector_t bit_vector_t::operator*=(
	bit_t scalar)
{
	if (scalar == bit_t(0)) {
		for (int i = 0; i < this->num_words; i++)
			this->words[i] = 0;
	}
	return *this;
}
bit_vector_t bit_vector_t::operator*=(
	bit_vector_t that)
{
	this->check_equal_lengths(that);
	for (int i = 0; i < this->num_words; i++)
		this->words[i] &= that.words[i];
	return *this;
}

// ----------------------------------------------------------------
int bit_vector_t::operator==(
	bit_vector_t & that)
{
	if (this->num_bits != that.num_bits)
		return 0;
	for (int i = 0; i < this->num_words - 1; i++)
		if (this->words[i] != that.words[i])
			return 0;
	return 1;
}

// ----------------------------------------------------------------
int bit_vector_t::operator!=(
	bit_vector_t & that)
{
	return !(*this == that);
}

// ----------------------------------------------------------------
int bit_vector_t::operator==(
	bit_t scalar)
{
	unsigned fill = 0;
	if (scalar == bit_t(1))
		fill = ~fill;
	for (int i = 0; i < this->num_words - 1; i++)
		if (this->words[i] != fill)
			return 0;
	return 1;
}

// ----------------------------------------------------------------
int bit_vector_t::operator!=(
	bit_t scalar)
{
	return !(*this == scalar);
}

// ----------------------------------------------------------------
// Return value:  True/false.  rpos:  index, if found.
int bit_vector_t::find_leader_pos(
	int & rpos)
{
	for (int i = 0; i < this->num_words; i++) {
		if (this->words[i]) {
			rpos = (31 - find_msb_32(this->words[i])) + (i << BITS_SHIFT);
			return 1;
		}
	}
	return 0; // Zero vector.
}

// ----------------------------------------------------------------
void bit_vector_t::ptrswap(bit_vector_t & that)
{
	if (this->num_bits != that.num_bits)
		(void)check_equal_lengths(that);
	unsigned * temp = this->words;
	this->words = that.words;
	that.words = temp;
}

// ----------------------------------------------------------------
void bit_vector_t::check_equal_lengths(bit_vector_t & that)
{
	if (this->num_bits != that.num_bits) {
		std::cerr
			<< "bit_vector_t operator+():  Incompatibly sized "
			<< "arguments (" << this->num_bits << ", "
			<< that.num_bits << ")." << std::endl;
		exit(1);
	}
}

// ----------------------------------------------------------------
// Zero out the unused bits at end of vector, for the case when
// num_bits isn't an exact multiple of the word size.  This will
// facilitate comparisons later.
void bit_vector_t::trim(void)
{
	int num_dribble_bits = (this->num_words << BITS_SHIFT) - this->num_bits;
	if (num_dribble_bits == 0)
		return;
	this->words[this->num_words - 1] &=
		((1 << (BITS_PER_WORD - num_dribble_bits)) - 1) << (32-this->num_bits);
}

// ----------------------------------------------------------------
void bit_vector_t::bounds_check(int index)
{
	if ((index < 0) || (index >= this->num_bits)) {
		std::cerr
			<< "bit_vector_t array operator: index "
			<< index
			<< " out of bounds "
			<< 0
			<< ":"
			<< (this->num_bits - 1)
			<< std::endl;
		exit(1);
	}
}

// ----------------------------------------------------------------
// This is a step in the row-reduction algorithm which benefits from
// hand-tuning.  The naive way to code it is:
//   *this = *this - that;
// which results in allocating, copying, freeing, etc.

void bit_vector_t::accum_row(
	bit_vector_t & that)
{
	if (this->num_bits != that.num_bits)
		(void)check_equal_lengths(that);
	for (int i = 0; i < this->num_words; i++)
		this->words[i] ^= that.words[i];
}


// ----------------------------------------------------------------
int bit_vector_t::get_num_elements(void)
{
	return this->num_bits;
}

// ----------------------------------------------------------------
#ifdef BVTEST
int main(void)
{
	for (int i = 1; i < 400; i++) {
		bit_vector_t v(i);
		std::cout << v << "\n";
	}
	return 0;
}
#endif
