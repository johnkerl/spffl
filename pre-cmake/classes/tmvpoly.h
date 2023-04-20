// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// Template class for multivariate polynomials.

#ifndef TMVPOLY_H
#define TMVPOLY_H

#define TMVPOLY_MAX_VARS    8
#define TMVPOLY_ALLOC_SIZE 10

#include <iostream>
#include "tvector.h"
#include "tokenize.h"

#include "bit_t.h"
#include "intmod_t.h"
#include "f2polymod_t.h"
#include "f2npolymod_t.h"
#include "fppolymod_t.h"

template <typename ktype> class tmvpoly;
template <typename ktype> class tmvmonom;

template <typename ktype>
static std::ostream & operator<< (std::ostream & os,
	const tmvpoly<ktype> & poly);

template <typename ktype>
static std::ostream & operator<< (std::ostream & os,
	const tmvmonom<ktype> & poly);

// ================================================================
template<typename ktype>
class tmvmonom
{
		friend class tmvpoly<ktype>;

private:
		ktype coeff;
		int   nvars;
		int   expts[TMVPOLY_MAX_VARS];

	// ----------------------------------------------------------------
public:
	tmvmonom(void)
	{
		this->nvars = 0;
	}

	// ----------------------------------------------------------------
	tmvmonom(ktype c)
	{
		this->coeff = c;
		this->nvars = 0;
	}

	// ----------------------------------------------------------------
	tmvmonom(ktype c, int expt0)
	{
		this->coeff = c;
		this->nvars = 1;
		this->expts[0] = expt0;
	}

	// ----------------------------------------------------------------
	tmvmonom(ktype c, int expt0, int expt1)
	{
		this->coeff = c;
		this->nvars = 2;
		this->expts[0] = expt0;
		this->expts[1] = expt1;
	}

	// ----------------------------------------------------------------
	tmvmonom(ktype c, int expt0, int expt1, int expt2)
	{
		this->coeff = c;
		this->nvars = 3;
		this->expts[0] = expt0;
		this->expts[1] = expt1;
		this->expts[2] = expt2;
	}

	// ----------------------------------------------------------------
	tmvmonom(ktype c, int expt0, int expt1, int expt2, int expt3)
	{
		this->coeff = c;
		this->nvars = 4;
		this->expts[0] = expt0;
		this->expts[1] = expt1;
		this->expts[2] = expt2;
		this->expts[3] = expt3;
	}

	// ----------------------------------------------------------------
	tmvmonom(ktype c, int * arg_expts, int num_expts)
	{
		if (num_expts > TMVPOLY_MAX_VARS) {
			std::cerr << "tmvmonom ctor:  out of variables.\n";
			exit(1);
		}
		if (num_expts < 1) {
			std::cerr << "tmvmonom ctor:  need at least 1 variable; got "
				<< num_expts << ".\n";
			exit(1);
		}

		this->coeff = c;
		this->nvars = num_expts;
		for (int i = 0; i < num_expts; i++)
			this->expts[i] = arg_expts[i];
	}

	// ----------------------------------------------------------------
	tmvmonom(const tmvmonom & that)
	{
		this->coeff = that.coeff;
		this->nvars = that.nvars;
		for (int i = 0; i < that.nvars; i++)
			this->expts[i] = that.expts[i];
	}

	// ----------------------------------------------------------------
	tmvmonom & operator=(const tmvmonom & that)
	{
		this->coeff = that.coeff;
		this->nvars = that.nvars;
		for (int i = 0; i < that.nvars; i++)
			this->expts[i] = that.expts[i];
		return *this;
	}

	// ----------------------------------------------------------------
	~tmvmonom(void)
	{
		this->nvars = 0;
	}

	// ----------------------------------------------------------------
	// 3 x^2 y^4  *  7 x y^3  =  21 x^3 y^7
	tmvmonom operator*(const tmvmonom & that)
	{
		this->check_nvars(that.nvars);
		tmvmonom prod;
		prod.coeff = this->coeff * that.coeff;
		prod.nvars = this->nvars;
		for (int i = 0; i < this->nvars; i++)
			prod.expts[i] = this->expts[i] + that.expts[i];
		return prod;
	}

	// ----------------------------------------------------------------
	// 3.1.4
	friend std::ostream & operator<< <>(std::ostream & os,
		const tmvmonom & monom);


	// ----------------------------------------------------------------
	// 3 x_0 x_1^4
	void tex_or_pretty_print(std::ostream & os, bool do_tex)
	{
		ktype c = this->coeff;
		ktype zero = c - c;
		if (c == zero) {
			os << c;
			return;
		}
		ktype one = c / c;
		int num_printed = 0;

		// If all exponents are zero, then always print coeff.
		// Else print coeff only when it's not 1
		int has_non_zero_expt = 0;
		for (int i = 0; i < this->nvars; i++) {
			if (this->expts[i] != 0) {
				has_non_zero_expt = 1;
				break;
			}
		}
		if ((!has_non_zero_expt) || (c != one)) {
			os << c;
			num_printed++;
		}

		// If an exponent is zero, omit it.
		// If an exponent is 1, print just the variable.
		for (int i = 0; i < this->nvars; i++) {
			if (num_printed > 0)
				os << " ";
			if (this->expts[i] != 0) {
				if (do_tex)
					os << "x_{" << i << "}";
				else
					os << "x_" << i;
				if (this->expts[i] != 1) {
					if (do_tex)
						os << "^{" << expts[i] << "}";
					else
						os << "^" << expts[i];
				}
				num_printed++;
			}
		}
	}

	void tex_print(std::ostream & os)
	{
		this->tex_or_pretty_print(os, 1);
	}
	void pretty_print(std::ostream & os)
	{
		this->tex_or_pretty_print(os, 0);
	}

	// ----------------------------------------------------------------
	int find_degree(void)
	{
		int sum = 0;
		for (int i = 0; i < this->nvars; i++)
			sum += this->expts[i];
		return sum;
	}

	// ----------------------------------------------------------------
private:
	ktype partial_eval(ktype input, ktype c, int exptidx)
	{
		ktype rv = input;
		if (this->expts[exptidx] < 0) {
			for (int i = 0; i > this->expts[exptidx]; i--)
				rv /= c;
		}
		else {
			for (int i = 0; i < this->expts[exptidx]; i++)
				rv *= c;
		}
		return rv;
	}
public:

	// ----------------------------------------------------------------
private:
	void check_nvars(int n)
	{
		if (this->nvars != n) {
			std::cerr << "nvars must be " << this->nvars << "; got " << n << "\n";
			exit(1);
		}
	}
public:

private:
	void check_varidx(int i)
	{
		if ((i < 0) || (i >= this->nvars)) {
			std::cerr << "varidx must be 0:" << this->nvars-1 << "; got "
				<< i << "\n";
			exit(1);
		}
	}
public:

	// ----------------------------------------------------------------
private:
	int expts_match(const tmvmonom & that)
	{
		this->check_nvars(that.nvars);
		for (int i = 0; i < this->nvars; i++)
			if (this->expts[i] != that.expts[i])
				return 0;
		return 1;
	}
public:

	// ----------------------------------------------------------------
	// 4 x^3
	ktype eval(ktype c0)
	{
		this->check_nvars(1);
		return this->partial_eval(this->coeff, c0, 0);
	}

	// ----------------------------------------------------------------
	// 4 x^3 y^5
	ktype eval(ktype c0, ktype c1)
	{
		this->check_nvars(2);
		ktype rv = this->coeff;
		rv = this->partial_eval(rv, c0, 0);
		rv = this->partial_eval(rv, c1, 1);
		return rv;
	}

	// ----------------------------------------------------------------
	ktype eval(ktype c0, ktype c1, ktype c2)
	{
		this->check_nvars(3);
		ktype rv = this->coeff;
		rv = this->partial_eval(rv, c0, 0);
		rv = this->partial_eval(rv, c1, 1);
		rv = this->partial_eval(rv, c2, 2);
		return rv;
	}

	// ----------------------------------------------------------------
	ktype eval(ktype c0, ktype c1, ktype c2, ktype c3)
	{
		this->check_nvars(4);
		ktype rv = this->coeff;
		rv = this->partial_eval(rv, c0, 0);
		rv = this->partial_eval(rv, c1, 1);
		rv = this->partial_eval(rv, c2, 2);
		rv = this->partial_eval(rv, c3, 3);
		return rv;
	}

	// ----------------------------------------------------------------
	ktype eval(tvector<ktype> c)
	{
		int n = c.get_num_elements();
		this->check_nvars(n);
		ktype rv = this->coeff;
		for (int i = 0; i < n; i++)
			rv = this->partial_eval(rv, c[i], i);
		return rv;
	}

	// ----------------------------------------------------------------
	// x y^3 (deg = 4) raise to degree 6:  need x y^3 z^2
	tmvmonom homogenize(int d)
	{
		tmvmonom rv;
		rv.coeff = this->coeff;
		rv.nvars = this->nvars + 1;
		if (rv.nvars > TMVPOLY_MAX_VARS) {
			std::cerr << "tmvmonom::homogenize:  out of variables.\n";
			exit(1);
		}
		int curd = 0;
		for (int i = 0; i < this->nvars; i++) {
			rv.expts[i] = this->expts[i];
			curd += rv.expts[i];
		}
		rv.expts[this->nvars] = d - curd;
		return rv;
	}

	// ----------------------------------------------------------------
	// x y^3 (deg = 4) raise to degree 6:  need x y^3 z^2
	void deriv_in_place(int varidx)
	{
		this->check_varidx(varidx);
		this->coeff *= this->expts[varidx]--;
	}

};

// ----------------------------------------------------------------
template <class element_type>
static
std::ostream & operator<< (
	std::ostream & os,
	const tmvmonom<element_type> & monom)
{
	os << monom.coeff;
	for (int i = 0; i < monom.nvars; i++) {
		os << "." << monom.expts[i];
	}
	return os;
}

// ================================================================
template<typename ktype>
class tmvpoly
{
private:
	int nmonoms;
	int nallocd;
	tmvmonom<ktype> * monoms;

// ----------------------------------------------------------------
public:
tmvpoly(void)
{
	this->nmonoms = 0;
	this->nallocd = TMVPOLY_ALLOC_SIZE;
	this->monoms  = new tmvmonom<ktype>[this->nallocd];
}

// ----------------------------------------------------------------
tmvpoly(ktype c, int expt0)
{
	this->nallocd = TMVPOLY_ALLOC_SIZE;
	this->monoms  = new tmvmonom<ktype>[this->nallocd];
	this->nmonoms = 1;
	this->monoms[0] = tmvmonom<ktype>(c, expt0);
	this->strip_zero_monoms();
}

// ----------------------------------------------------------------
tmvpoly(ktype c, int expt0, int expt1)
{
	this->nallocd = TMVPOLY_ALLOC_SIZE;
	this->monoms  = new tmvmonom<ktype>[this->nallocd];
	this->nmonoms = 1;
	this->monoms[0] = tmvmonom<ktype>(c, expt0, expt1);
	this->strip_zero_monoms();
}

// ----------------------------------------------------------------
tmvpoly(ktype c, int expt0, int expt1, int expt2)
{
	this->nallocd = TMVPOLY_ALLOC_SIZE;
	this->monoms  = new tmvmonom<ktype>[this->nallocd];
	this->nmonoms = 1;
	this->monoms[0] = tmvmonom<ktype>(c, expt0, expt1, expt2);
	this->strip_zero_monoms();
}

// ----------------------------------------------------------------
tmvpoly(ktype c, int * expts, int num_expts)
{
	this->nallocd = TMVPOLY_ALLOC_SIZE;
	this->monoms  = new tmvmonom<ktype>[this->nallocd];
	this->nmonoms = 1;
	this->monoms[0] = tmvmonom<ktype>(c, expts, num_expts);
	this->strip_zero_monoms();
}

// ----------------------------------------------------------------
tmvpoly(tmvmonom<ktype> m0)
{
	this->nmonoms = 1;
	this->nallocd = TMVPOLY_ALLOC_SIZE;
	this->monoms  = new tmvmonom<ktype>[this->nallocd];
	this->monoms[0] = m0;
	this->strip_zero_monoms();
}

// ----------------------------------------------------------------
tmvpoly(tmvmonom<ktype> m0, tmvmonom<ktype> m1)
{
	this->nmonoms = 2;
	this->nallocd = TMVPOLY_ALLOC_SIZE;
	this->monoms  = new tmvmonom<ktype>[this->nallocd];
	this->monoms[0] = m0;
	this->monoms[1] = m1;
	this->strip_zero_monoms();
}

// ----------------------------------------------------------------
tmvpoly(tmvmonom<ktype> m0, tmvmonom<ktype> m1, tmvmonom<ktype> m2)
{
	this->nmonoms = 2;
	this->nallocd = TMVPOLY_ALLOC_SIZE;
	this->monoms  = new tmvmonom<ktype>[this->nallocd];
	this->monoms[0] = m0;
	this->monoms[1] = m1;
	this->monoms[2] = m2;
	this->strip_zero_monoms();
}

// ----------------------------------------------------------------
void strip_zero_monoms(void)
{
	int i, j;
	if (this->nmonoms == 0)
		return;
	ktype c = this->monoms[0].coeff;
	ktype zero = c - c;
	for (i = 0; i < this->nmonoms; i++) {
		while ((i < this->nmonoms) && (this->monoms[i].coeff == zero)) {
			for (j = i+1; j < this->nmonoms; j++)
				this->monoms[j-1] = this->monoms[j];
			this->nmonoms--;
		}
	}
}

// ----------------------------------------------------------------
tmvpoly(const tmvpoly & that)
{
	this->nmonoms = that.nmonoms;
	this->nallocd = that.nallocd;
	this->monoms = new tmvmonom<ktype>[that.nmonoms];
	for (int i = 0; i < that.nmonoms; i++)
		this->monoms[i] = that.monoms[i];
}

// ----------------------------------------------------------------
tmvpoly & operator=(const tmvpoly & that)
{
	if (this->monoms == 0) {
		this->monoms = new tmvmonom<ktype>[that.nmonoms];
	}
	else {
		if (this->nmonoms < that.nmonoms) {
			delete [] this->monoms;
			this->monoms = new tmvmonom<ktype>[that.nmonoms];
		}
	}
	this->nmonoms = that.nmonoms;
	this->nallocd = that.nallocd;
	for (int i = 0; i < that.nmonoms; i++)
		this->monoms[i] = that.monoms[i];
	return *this;
}

// ----------------------------------------------------------------
~tmvpoly(void)
{
	if (this->monoms)
		delete [] this->monoms;
	this->monoms = 0;
	this->nmonoms = 0;
	this->nallocd = 0;
}

// ----------------------------------------------------------------
private:
int find(tmvmonom<ktype> & monom, int & midx)
{
	for (int i = 0; i < this->nmonoms; i++) {
		if (this->monoms[i].expts_match(monom)) {
			midx = i;
			return 1;
		}
	}
	return 0;
}
public:

// ----------------------------------------------------------------
// Assumes a matching term isn't already present.
private:
void insert(tmvmonom<ktype> & monom)
{
	if (this->nmonoms >= this->nallocd) {
		this->nallocd += TMVPOLY_ALLOC_SIZE;
		tmvmonom<ktype> * temp = this->monoms;
		this->monoms  = new tmvmonom<ktype>[this->nallocd];
		for (int i = 0; i < this->nmonoms; i++)
			this->monoms[i] = temp[i];
		delete [] temp;
	}
	this->monoms[this->nmonoms++] = monom;
}
public:

// ----------------------------------------------------------------
private:
void bounds_check_monomi(int monomi)
{
	if ((monomi < 0) || (monomi >= this->nmonoms)) {
		std::cerr << "tmvpoly:  monomial index " << monomi
			<< " out of bounds 0:" << this->nmonoms - 1 << ".\n";
		exit(1);
	}
}
public:

// ----------------------------------------------------------------
ktype get_coeff(int monomi)
{
	this->bounds_check_monomi(monomi);
	return this->monoms[monomi].coeff;
}

// ----------------------------------------------------------------
void set_coeff(int monomi, ktype c)
{
	this->bounds_check_monomi(monomi);
	this->monoms[monomi].coeff = c;
}

// ----------------------------------------------------------------
int get_num_monoms(void)
{
	return this->nmonoms;
}

// ----------------------------------------------------------------
int get_nvars(void)
{
	if (this->nmonoms == 0) {
		std::cerr
			<< "tmvpoly::get_nvars:  doesn't apply to zero polynomial.\n";
		exit(1);
	}
	return this->monoms[0].nvars;
}

// ----------------------------------------------------------------
tmvpoly operator+(tmvpoly that)
{
	if (this->nmonoms == 0) // 0 + f = f
		return that;
	if (that.nmonoms  == 0) // g + 0 = 0
		return *this;

	tmvpoly sum;
	ktype zero = this->monoms[0].coeff - this->monoms[0].coeff;
	int i, j;
	unsigned char * marks = new unsigned char[that.nmonoms];
	for (j = 0; j < that.nmonoms; j++)
		marks[j] = 0;

	// We assume *this and that have unique monomials.  We need only to gather
	// like monomials between *this and that.
	for (i = 0; i < this->nmonoms; i++) {
		if (!that.find(this->monoms[i], j)) {
			// That object doesn't have this monomial, so insert it into
			// the sum.
			sum.insert(this->monoms[i]);
		}
		else {
			// Other object does have this monomial, but the coefficients
			// might sum to zero.
			marks[j] = 1;
			ktype thisc = this->monoms[i].coeff;
			ktype thatc =  that.monoms[j].coeff;
			ktype sumc  = thisc + thatc;
			if (sumc != zero) {
				tmvmonom<ktype> summ = this->monoms[i];
				summ.coeff = sumc;
				sum.insert(summ);
			}
		}
	}
	// Monomials which are in that object, but not in this one.
	for (j = 0; j < that.nmonoms; j++)
		if (marks[j] == 0)
			sum.insert(that.monoms[j]);
	delete [] marks;
	return sum;
}

// ----------------------------------------------------------------
// Unary negation
tmvpoly operator-(void)
{
	tmvpoly neg(*this);
	for (int i = 0; i < neg.nmonoms; i++)
		neg.monoms[i].coeff = -neg.monoms[i].coeff;
	return neg;
}

// ----------------------------------------------------------------
tmvpoly operator-(tmvpoly that)
{
	tmvpoly neg = -that;
	return *this + neg;
}

// ----------------------------------------------------------------
tmvpoly operator*(tmvpoly that)
{
	if (this->nmonoms == 0) // 0 * f = 0
		return *this;
	if (that.nmonoms  == 0) // g * 0 = 0
		return that;

	tmvpoly prod;
	int i, j, k;

	// m0 + m1 + m2
	//      n0 + n1
	// ------------
	// m0n0 + m1n0 + m2n0 + m0n1 + m1n1 + m2n1
	// Then collect like terms.

	for (i = 0; i < this->nmonoms; i++) {
		tmvmonom<ktype> & thisi = this->monoms[i];
		for (j = 0; j < that.nmonoms; j++) {
			tmvmonom<ktype> & thatj = that.monoms[j];
			tmvmonom<ktype> pprod = thisi * thatj;

			if (prod.find(pprod, k)) {
				prod.monoms[k].coeff += pprod.coeff;
			}
			else {
				prod.insert(pprod);
			}
		}
	}

	return prod;
}

tmvpoly operator+=(tmvpoly that)
{
	*this = *this + that;
	return *this;
}
tmvpoly operator-=(tmvpoly that)
{
	*this = *this - that;
	return *this;
}
tmvpoly operator*=(tmvpoly that)
{
	*this = *this * that;
	return *this;
}

// ----------------------------------------------------------------
// For input, please use tmvpolyscan.h.

friend std::ostream & operator<< <>(std::ostream & os,
	const tmvpoly & poly);

// ----------------------------------------------------------------
void tex_or_pretty_print(std::ostream & os, bool do_tex)
{
	for (int i = 0; i < this->nmonoms; i++) {
		if (i > 0)
			os << " + ";
		ktype c = this->monoms[i].coeff;
		if (c == (c-c)) {
			std::cerr << "tmvpoly: coding error: found zero term.\n";
			exit(1);
		}
		this->monoms[i].tex_or_pretty_print(os, do_tex);
	}
}

void tex_print(std::ostream & os)
{
	this->tex_or_pretty_print(os, 1);
}
void pretty_print(std::ostream & os)
{
	this->tex_or_pretty_print(os, 0);
}

// ----------------------------------------------------------------
int find_degree(void)
{
	if (this->nmonoms == 0) {
		return 0;
	}
	int max = this->monoms[0].find_degree();
	for (int i = 1; i < this->nmonoms; i++) {
		int curdeg = this->monoms[i].find_degree();
		if (curdeg > max)
			max = curdeg;
	}
	return max;
}

// ----------------------------------------------------------------
ktype eval(ktype c0)
{
	ktype sum = c0 - c0;
	for (int i = 0; i < this->nmonoms; i++)
		sum += this->monoms[i].eval(c0);
	return sum;
}

// ----------------------------------------------------------------
ktype eval(ktype c0, ktype c1)
{
	ktype sum = c0 - c0;
	for (int i = 0; i < this->nmonoms; i++)
		sum += this->monoms[i].eval(c0, c1);
	return sum;
}

// ----------------------------------------------------------------
ktype eval(ktype c0, ktype c1, ktype c2)
{
	ktype sum = c0 - c0;
	for (int i = 0; i < this->nmonoms; i++)
		sum += this->monoms[i].eval(c0, c1, c2);
	return sum;
}

// ----------------------------------------------------------------
ktype eval(tvector<ktype> c)
{
	ktype sum = c[0] - c[0];
	for (int i = 0; i < this->nmonoms; i++)
		sum += this->monoms[i].eval(c);
	return sum;
}

// ----------------------------------------------------------------
// The matrix argument is to be thought of as an array of vectors.
tvector<ktype> eval(tmatrix<ktype> & m)
{
	int n = m.get_num_rows();
	tvector<ktype> rv(n);
	for (int i = 0; i < n; i++)
		rv[i] = this->eval(m[i]);
	return rv;
}

// ----------------------------------------------------------------
tmvpoly homogenize(void)
{
	if (this->is_homogeneous())
		return *this;
	int d = this->find_degree();
	tmvpoly rv(*this);
	for (int i = 0; i < this->nmonoms; i++)
		rv.monoms[i] = this->monoms[i].homogenize(d);
	return rv;
}

// ----------------------------------------------------------------
bool is_homogeneous(void)
{
	if (this->nmonoms == 0)
		return true;
	int d0 = this->monoms[0].find_degree();
	for (int i = 1; i < this->nmonoms; i++)
		if (this->monoms[i].find_degree() != d0)
			return false;
	return true;
}

// ----------------------------------------------------------------
tmvpoly deriv(int varidx)
{
	tmvpoly rv(*this);
	for (int i = 0; i < this->nmonoms; i++)
		rv.monoms[i].deriv_in_place(varidx);
	rv.strip_zero_monoms();
	return rv;
}

};

// ----------------------------------------------------------------
template <class element_type>
static
std::ostream & operator<< (
	std::ostream & os,
	const tmvpoly<element_type> & poly)
{
	if (poly.nmonoms == 0) {
		os << "0";
	}
	else {
		for (int i = 0; i < poly.nmonoms; i++) {
			os << poly.monoms[i];
			if (i < (poly.nmonoms - 1))
				os << "+";
		}
	}
	return os;
}

#endif // TMVPOLY_H
