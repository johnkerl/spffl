// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef SP_LIST_ELTS_H
#define SP_LIST_ELTS_H

#include "spffl/containers/vector_over.hpp"
#include "spffl/containers/matrix_over.hpp"
#include "spffl/intmath/intmod_t.h"
#include "spffl/polynomials/f2_polymod_t.h"
#include "spffl/polynomials/f2n_polymod_t.h"
#include "spffl/polynomials/fp_polymod_t.h"

namespace spffl::list {

enum sp_list_type_t {
  SP_LIST_ALL,
  SP_LIST_UNITS,
  SP_LIST_NON_UNITS,
  SP_LIST_MULTIPLES,
  SP_LIST_REL_PRIME,
};

using spffl::containers::vector_over;
using spffl::containers::matrix_over;

// Monics only
vector_over<spffl::polynomials::f2_poly_t> f2_poly_list(int deg);
vector_over<spffl::polynomials::f2n_poly_t> f2n_poly_list(
    spffl::polynomials::f2_poly_t m, int deg);
vector_over<spffl::polynomials::fp_poly_t> fp_poly_list(int p, int deg);

vector_over<spffl::intmath::intmod_t> intmod_list(int p, sp_list_type_t type);
vector_over<spffl::polynomials::f2_polymod_t> f2_polymod_list(
    spffl::polynomials::f2_poly_t m, sp_list_type_t);
vector_over<spffl::polynomials::f2n_polymod_t> f2n_polymod_list(
    spffl::polynomials::f2n_poly_t m, sp_list_type_t);
vector_over<spffl::polynomials::fp_polymod_t> fp_polymod_list(
    spffl::polynomials::fp_poly_t m, sp_list_type_t);

vector_over<spffl::intmath::intmod_t> intmod_glist(
    spffl::intmath::intmod_t g, sp_list_type_t type);
vector_over<spffl::polynomials::f2_polymod_t> f2_polymod_glist(
    spffl::polynomials::f2_polymod_t g, sp_list_type_t);
vector_over<spffl::polynomials::f2n_polymod_t> f2n_polymod_glist(
    spffl::polynomials::f2n_polymod_t g, sp_list_type_t);
vector_over<spffl::polynomials::fp_polymod_t> fp_polymod_glist(
    spffl::polynomials::fp_polymod_t g, sp_list_type_t);

// Lists all n-tuples over Fq.
matrix_over<spffl::polynomials::f2_polymod_t> f2_polymod_An_list(
    spffl::polynomials::f2_poly_t m, int n);
matrix_over<spffl::polynomials::fp_polymod_t> fp_polymod_An_list(
    spffl::polynomials::fp_poly_t m, int n);

// xxx do it for for other types too

// Lists a representative for each equivalence class in projective n-space
// over Fq.
matrix_over<spffl::polynomials::f2_polymod_t> f2_polymod_Pn_list(
    spffl::polynomials::f2_poly_t m, int n);
matrix_over<spffl::polynomials::fp_polymod_t> fp_polymod_Pn_list(
    spffl::polynomials::fp_poly_t m, int n);

// xxx do it for for other types too

} // namespace spffl::list

#endif // SP_LIST_ELTS_H
