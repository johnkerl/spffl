#ifndef QFF_H
#define QFF_H
#include "f2n_poly_t.h"
#include "f2_poly_t.h"
#include "fpn_poly_t.h"
#include "fp_poly_t.h"
#include "intmod_t.h"
#include "intrat_t.h"
#include "qpoly_t.h"

bit_t bit_from_rat(intrat_t r);
intmod_t intmod_from_rat(intrat_t r, int p);

f2_poly_t f2poly_from_qpoly(qpoly_t q);
fp_poly_t fppoly_from_qpoly(qpoly_t q, int p);
f2n_poly_t f2npoly_from_qpoly(qpoly_t q, f2_poly_t im);
fpn_poly_t fpnpoly_from_qpoly(qpoly_t q, fp_poly_t im);

#endif // QFF_H
