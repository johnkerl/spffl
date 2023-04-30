#ifndef QFF_H
#define QFF_H
#include "f2_poly_t.h"
#include "f2n_poly_t.h"
#include "fp_poly_t.h"
#include "fpn_poly_t.h"
#include "intmod_t.h"
#include "intrat_t.h"
#include "qpoly_t.h"

namespace spffl::q_cyclo {

spffl::bits::bit_t bit_from_rat(const spffl::rationals::intrat_t &r);
spffl::intmath::intmod_t intmod_from_rat(const spffl::rationals::intrat_t &r, int p);

spffl::polynomials::f2_poly_t f2_poly_from_q_poly(const spffl::rationals::qpoly_t &q);
spffl::polynomials::fp_poly_t fp_poly_from_qpoly(
    const spffl::rationals::qpoly_t &q, int p);
spffl::polynomials::f2n_poly_t f2n_poly_from_qpoly(
    const spffl::rationals::qpoly_t &q, const spffl::polynomials::f2_poly_t &im);
spffl::polynomials::fpn_poly_t fpn_poly_from_qpoly(
    const spffl::rationals::qpoly_t &q, const spffl::polynomials::fp_poly_t &im);

} // namespace spffl::q_cyclo

#endif // QFF_H
