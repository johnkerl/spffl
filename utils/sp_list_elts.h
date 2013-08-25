// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
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
