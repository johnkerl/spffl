// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2LINALG_H
#define F2LINALG_H

#include "spffl/bits/bit_t.h"
#include "spffl/polynomials/f2_poly_t.h"
#include "spffl/polynomials/f2n_poly_t.h"
#include "spffl/containers/tmatrix.h"

namespace spffl::linalg {

tvector<spffl::bits::bit_t> f2_vector_from_base_rep(int base_rep, int len);

tmatrix<spffl::bits::bit_t> f2_matrix_from_base_rep(
    int base_rep, int num_rows, int num_cols);

spffl::polynomials::f2_poly_t f2_char_poly(tmatrix<spffl::bits::bit_t> &A);

tmatrix<spffl::bits::bit_t> f2_companion_matrix(
    spffl::polynomials::f2_poly_t chpol);

spffl::polynomials::f2n_poly_t f2_polymod_min_poly(
    spffl::polynomials::f2_polymod_t a);

spffl::polynomials::f2n_poly_t f2_polymod_char_poly(
    spffl::polynomials::f2_polymod_t a);

} // namespace spffl::linalg

#endif // F2LINALG_H
