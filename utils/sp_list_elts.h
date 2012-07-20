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

#ifndef SP_LIST_ELTS_H
#define SP_LIST_ELTS_H

#include "intmod_t.h"
#include "f2polymod_t.h"
#include "f2npolymod_t.h"
#include "fppolymod_t.h"
#include "tvector.h"

enum sp_list_type_t {
	SP_LIST_ALL,
	SP_LIST_UNITS,
	SP_LIST_NON_UNITS,
	SP_LIST_MULTIPLES,
	SP_LIST_REL_PRIME,
};

// Monics only
tvector<f2poly_t>     f2poly_list(int deg);
tvector<f2npoly_t>    f2npoly_list(f2poly_t m, int deg);
tvector<fppoly_t>     fppoly_list(int p, int deg);

tvector<intmod_t>     intmod_list(int p, sp_list_type_t type);
tvector<f2polymod_t>  f2polymod_list(f2poly_t m, sp_list_type_t);
tvector<f2npolymod_t> f2npolymod_list(f2npoly_t m, sp_list_type_t);
tvector<fppolymod_t>  fppolymod_list(fppoly_t m, sp_list_type_t);

tvector<intmod_t>     intmod_glist(intmod_t g, sp_list_type_t type);
tvector<f2polymod_t>  f2polymod_glist(f2polymod_t g, sp_list_type_t);
tvector<f2npolymod_t> f2npolymod_glist(f2npolymod_t g, sp_list_type_t);
tvector<fppolymod_t>  fppolymod_glist(fppolymod_t g, sp_list_type_t);

// Lists all n-tuples over Fq.
tmatrix<f2polymod_t>  f2polymod_An_list(f2poly_t m, int n);
tmatrix<fppolymod_t>  fppolymod_An_list(fppoly_t m, int n);

// xxx do it for for other types too

// Lists a representative for each equivalence class in projective n-space
// over Fq.
tmatrix<f2polymod_t>  f2polymod_Pn_list(f2poly_t m, int n);
tmatrix<fppolymod_t>  fppolymod_Pn_list(fppoly_t m, int n);

// xxx do it for for other types too


#endif // SP_LIST_ELTS_H
