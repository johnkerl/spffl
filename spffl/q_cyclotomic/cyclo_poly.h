#ifndef CYCLOPOLY_H
#define CYCLOPOLY_H

#include "polynomials/f2_poly_t.h"
#include "polynomials/f2n_poly_t.h"
#include "polynomials/fp_poly_t.h"
#include "polynomials/fpn_poly_t.h"
#include "polynomials/q_poly_t.h"

namespace spffl::q_cyclotomic {

spffl::rationals::q_poly_t get_cyclo_qpoly(int n);
spffl::polynomials::f2_poly_t get_cyclo_f2_poly(int n);
spffl::polynomials::fp_poly_t get_cyclo_fp_poly(int n, int p);
spffl::polynomials::f2n_poly_t get_cyclo_f2n_poly(
    int n, const spffl::polynomials::f2_poly_t &im);
spffl::polynomials::fpn_poly_t get_cyclo_fpn_poly(
    int n, const spffl::polynomials::fp_poly_t &im);

} // namespace spffl::q_cyclotomic

#endif // CYCLOPOLY_H
