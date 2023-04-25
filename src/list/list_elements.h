// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef SP_LIST_ELTS_H
#define SP_LIST_ELTS_H

#include "f2_polymod_t.h"
#include "f2n_polymod_t.h"
#include "fp_polymod_t.h"
#include "intmod_t.h"
#include "tvector.h"

namespace spffl::list {

enum sp_list_type_t {
  SP_LIST_ALL,
  SP_LIST_UNITS,
  SP_LIST_NON_UNITS,
  SP_LIST_MULTIPLES,
  SP_LIST_REL_PRIME,
};

// Monics only
tvector<spffl::polynomials::f2_poly_t> f2poly_list(int deg);
tvector<spffl::polynomials::f2n_poly_t>
f2npoly_list(spffl::polynomials::f2_poly_t m, int deg);
tvector<spffl::polynomials::fp_poly_t> fppoly_list(int p, int deg);

tvector<spffl::intmath::intmod_t> intmod_list(int p, sp_list_type_t type);
tvector<spffl::polynomials::f2_polymod_t>
f2polymod_list(spffl::polynomials::f2_poly_t m, sp_list_type_t);
tvector<spffl::polynomials::f2n_polymod_t>
f2npolymod_list(spffl::polynomials::f2n_poly_t m, sp_list_type_t);
tvector<spffl::polynomials::fp_polymod_t>
fppolymod_list(spffl::polynomials::fp_poly_t m, sp_list_type_t);

tvector<spffl::intmath::intmod_t> intmod_glist(spffl::intmath::intmod_t g,
                                               sp_list_type_t type);
tvector<spffl::polynomials::f2_polymod_t>
f2polymod_glist(spffl::polynomials::f2_polymod_t g, sp_list_type_t);
tvector<spffl::polynomials::f2n_polymod_t>
f2npolymod_glist(spffl::polynomials::f2n_polymod_t g, sp_list_type_t);
tvector<spffl::polynomials::fp_polymod_t>
fppolymod_glist(spffl::polynomials::fp_polymod_t g, sp_list_type_t);

// Lists all n-tuples over Fq.
tmatrix<spffl::polynomials::f2_polymod_t>
f2polymod_An_list(spffl::polynomials::f2_poly_t m, int n);
tmatrix<spffl::polynomials::fp_polymod_t>
fppolymod_An_list(spffl::polynomials::fp_poly_t m, int n);

// xxx do it for for other types too

// Lists a representative for each equivalence class in projective n-space
// over Fq.
tmatrix<spffl::polynomials::f2_polymod_t>
f2polymod_Pn_list(spffl::polynomials::f2_poly_t m, int n);
tmatrix<spffl::polynomials::fp_polymod_t>
fppolymod_Pn_list(spffl::polynomials::fp_poly_t m, int n);

// xxx do it for for other types too

} // namespace spffl::list

#endif // SP_LIST_ELTS_H
