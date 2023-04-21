#ifndef CYCLOPOLY_H
#define CYCLOPOLY_H

#include "f2n_poly_t.h"
#include "f2_poly_t.h"
#include "fpn_poly_t.h"
#include "fp_poly_t.h"
#include "qpoly_t.h"

qpoly_t get_cyclo_qpoly(int n);
f2_poly_t get_cyclo_f2poly(int n);
fp_poly_t get_cyclo_fppoly(int n, int p);
f2n_poly_t get_cyclo_f2npoly(int n, f2_poly_t im);
fpn_poly_t get_cyclo_fpnpoly(int n, fp_poly_t im);

#endif // CYCLOPOLY_H
