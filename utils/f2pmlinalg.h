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

#ifndef F2PMLINALG_H
#define F2PMLINALG_H

#include "tmatrix.h"
#include "f2npoly_t.h"

f2npoly_t f2pm_char_poly(
	tmatrix<f2polymod_t> & A);

tmatrix<f2polymod_t> f2np_companion_matrix(
	f2npoly_t chpol);

// Test for diagonalizability over a splitting field.  (Diagonalizability over
// the base field is rare enough to be non-interesting, so we do not have a
// function for that.  If in fact the matrix is diagonalizable over the base
// field, then the splitter modulus will be set equal to the original modulus.)
int f2pm_matrix_is_dable(
	tmatrix<f2polymod_t> & A,
	f2poly_t & rsplitter_modulus,
	tvector<f2polymod_t> & reigenvalues);

tvector<f2polymod_t>
ft_vector_from_base_rep(
	int base_rep,
	f2poly_t m,
	int len);

#endif // F2PMLINALG_H
