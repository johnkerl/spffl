// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef SP_LIST_ELTS_H
#define SP_LIST_ELTS_H

#include "f2n_polymod_t.h"
#include "f2_polymod_t.h"
#include "fp_polymod_t.h"
#include "intmod_t.h"
#include "tvector.h"

enum sp_list_type_t {
  SP_LIST_ALL,
  SP_LIST_UNITS,
  SP_LIST_NON_UNITS,
  SP_LIST_MULTIPLES,
  SP_LIST_REL_PRIME,
};

// Monics only
tvector<f2_poly_t> f2poly_list(int deg);
tvector<f2n_poly_t> f2npoly_list(f2_poly_t m, int deg);
tvector<fp_poly_t> fppoly_list(int p, int deg);

tvector<spffl::intmath::intmod_t> intmod_list(int p, sp_list_type_t type);
tvector<f2_polymod_t> f2polymod_list(f2_poly_t m, sp_list_type_t);
tvector<f2n_polymod_t> f2npolymod_list(f2n_poly_t m, sp_list_type_t);
tvector<fp_polymod_t> fppolymod_list(fp_poly_t m, sp_list_type_t);

tvector<spffl::intmath::intmod_t> intmod_glist(spffl::intmath::intmod_t g, sp_list_type_t type);
tvector<f2_polymod_t> f2polymod_glist(f2_polymod_t g, sp_list_type_t);
tvector<f2n_polymod_t> f2npolymod_glist(f2n_polymod_t g, sp_list_type_t);
tvector<fp_polymod_t> fppolymod_glist(fp_polymod_t g, sp_list_type_t);

// Lists all n-tuples over Fq.
tmatrix<f2_polymod_t> f2polymod_An_list(f2_poly_t m, int n);
tmatrix<fp_polymod_t> fppolymod_An_list(fp_poly_t m, int n);

// xxx do it for for other types too

// Lists a representative for each equivalence class in projective n-space
// over Fq.
tmatrix<f2_polymod_t> f2polymod_Pn_list(f2_poly_t m, int n);
tmatrix<fp_polymod_t> fppolymod_Pn_list(fp_poly_t m, int n);

// xxx do it for for other types too

#endif // SP_LIST_ELTS_H
