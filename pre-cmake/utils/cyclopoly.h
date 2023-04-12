#ifndef CYCLOPOLY_H
#define CYCLOPOLY_H

#include "qpoly_t.h"
#include "f2poly_t.h"
#include "fppoly_t.h"
#include "f2npoly_t.h"
#include "fpnpoly_t.h"

qpoly_t   get_cyclo_qpoly  (int n);
f2poly_t  get_cyclo_f2poly (int n);
fppoly_t  get_cyclo_fppoly (int n, int p);
f2npoly_t get_cyclo_f2npoly(int n, f2poly_t im);
fpnpoly_t get_cyclo_fpnpoly(int n, fppoly_t im);

#endif // CYCLOPOLY_H
