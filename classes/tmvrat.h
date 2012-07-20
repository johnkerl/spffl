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

// Template class for multivariate rational functions.

#ifndef TMVRAT_H
#define TMVRAT_H

#include "tmvpoly.h"

template <class ktype> class tmvrat;
template <class ktype>
std::ostream & operator<< (std::ostream & os,
	const tmvrat<ktype> & rat);

// ================================================================
template<class ktype>
class tmvrat
{
private:
	tmvpoly<ktype> numer;
	tmvpoly<ktype> denom;

// ----------------------------------------------------------------
public:
tmvrat(void)
{
}

// ----------------------------------------------------------------
tmvrat(tmvpoly<ktype> n, tmvpoly<ktype> d)
{
	this->numer = n;
	this->denom = d;
	this->check_equal_nvars();
}

// ----------------------------------------------------------------
tmvrat(const tmvrat & that)
{
	this->numer = that.numer;
	this->denom = that.denom;
}

// ----------------------------------------------------------------
tmvrat & operator=(const tmvrat & that)
{
	this->numer = that.numer;
	this->denom = that.denom;
	return *this;
}

// ----------------------------------------------------------------
~tmvrat(void)
{
}

// ----------------------------------------------------------------
//tmvrat operator+(tmvrat that)
//{
//}

// ----------------------------------------------------------------
// Unary negation
//tmvrat operator-(void)
//{
//}

// ----------------------------------------------------------------
//tmvrat operator-(tmvrat that)
//{
//}

// ----------------------------------------------------------------
//tmvrat operator*(tmvrat that)
//{
//}

//tmvrat operator+=(tmvrat that)
//{
//	*this = *this + that;
//	return *this;
//}
//tmvrat operator-=(tmvrat that)
//{
//	*this = *this - that;
//	return *this;
//}
//tmvrat operator*=(tmvrat that)
//{
//	*this = *this * that;
//	return *this;
//}

// ----------------------------------------------------------------
// For input, please use tmvratscan.h.

friend std::ostream & operator<< <>(std::ostream & os,
	const tmvrat & rat);

// ----------------------------------------------------------------
void tex_or_pretty_print(std::ostream & os, int do_tex)
{
	this->numer.tex_or_pretty_print(os, do_tex);
	os << "/";
	this->denom.tex_or_pretty_print(os, do_tex);
}

void tex_print(std::ostream & os)
{
	this->numer.tex_print(os);
	os << "/";
	this->denom.tex_print(os);
}
void pretty_print(std::ostream & os)
{
	this->numer.pretty_print(os);
	os << "/";
	this->denom.pretty_print(os);
}

// ----------------------------------------------------------------
int get_nvars(void)
{
	int nnv = this->numer.get_nvars();
	int dnv = this->denom.get_nvars();
	if (nnv != dnv) {
		exit(1);
	}
	return nnv;
}

// ----------------------------------------------------------------
ktype eval(ktype c0)
{
	return this->numer.eval(c0) / this->denom.eval(c0);
}

// ----------------------------------------------------------------
ktype eval(ktype c0, ktype c1)
{
	return this->numer.eval(c0, c1) / this->denom.eval(c0, c1);
}

// ----------------------------------------------------------------
ktype eval(ktype c0, ktype c1, ktype c2)
{
	return this->numer.eval(c0, c1, c2) / this->denom.eval(c0, c1, c2);
}

// ----------------------------------------------------------------
ktype eval(tvector<ktype> c)
{
	return this->numer.eval(c) / this->denom.eval(c);
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
tmvrat homogenize(void)
{
	tmvpoly<ktype> hnumer = this->numer.homogenize();
	tmvpoly<ktype> hdenom = this->denom.homogenize();
	tmvrat rv(hnumer, hdenom);
	return rv;
}

// ----------------------------------------------------------------
private:
void check_equal_nvars(void)
{
	int nnv = this->numer.get_nvars();
	int dnv = this->denom.get_nvars();
	if (nnv != dnv) {
		std::cerr << "tmvrat:  numerator #vars (" << nnv << ") != denominator #vars ("
			<< dnv << ").\n";
		exit(1);
	}
}

};

// ----------------------------------------------------------------
template <class element_type>
static
std::ostream & operator<< (
	std::ostream & os,
	const tmvrat<element_type> & rat)
{
	os << rat.numer << "/" << rat.denom;
	return os;
}

#endif // TMVRAT_H
