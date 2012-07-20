#ifndef QFF_H
#define QFF_H
#include "intmod_t.h"
#include "intrat_t.h"
#include "qpoly_t.h"
#include "f2poly_t.h"
#include "fppoly_t.h"
#include "f2npoly_t.h"
#include "fpnpoly_t.h"

bit_t     bit_from_rat   (intrat_t r);
intmod_t  intmod_from_rat(intrat_t r, int p);

f2poly_t  f2poly_from_qpoly (qpoly_t q);
fppoly_t  fppoly_from_qpoly (qpoly_t q, int p);
f2npoly_t f2npoly_from_qpoly(qpoly_t q, f2poly_t im);
fpnpoly_t fpnpoly_from_qpoly(qpoly_t q, fppoly_t im);

#endif // QFF_H
