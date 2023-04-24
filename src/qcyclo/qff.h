#ifndef QFF_H
#define QFF_H
#include "f2n_poly_t.h"
#include "f2_poly_t.h"
#include "fpn_poly_t.h"
#include "fp_poly_t.h"
#include "intmod_t.h"
#include "intrat_t.h"
#include "qpoly_t.h"

namespace spffl::qcyclo {

spffl::bits::bit_t bit_from_rat(spffl::rationals::intrat_t r);
spffl::intmath::intmod_t intmod_from_rat(spffl::rationals::intrat_t r, int p);

spffl::polynomials::f2_poly_t f2poly_from_qpoly(spffl::rationals::qpoly_t q);
spffl::polynomials::fp_poly_t fppoly_from_qpoly(spffl::rationals::qpoly_t q, int p);
spffl::polynomials::f2n_poly_t f2npoly_from_qpoly(spffl::rationals::qpoly_t q, spffl::polynomials::f2_poly_t im);
spffl::polynomials::fpn_poly_t fpnpoly_from_qpoly(spffl::rationals::qpoly_t q, spffl::polynomials::fp_poly_t im);

} // namespace

#endif // QFF_H
