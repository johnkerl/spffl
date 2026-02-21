#ifndef FT_SCAN_TUPLES_H
#define FT_SCAN_TUPLES_H

#include "spffl/f2_polymod_t.h"

int ft_scan_triple(char *input, f2_poly_t m, f2_polymod_t &a, f2_polymod_t &b, f2_polymod_t &c);

int ft_scan_quintuple(char *input, f2_poly_t m, f2_polymod_t &a, f2_polymod_t &b, f2_polymod_t &c,
  f2_polymod_t &d, f2_polymod_t &e);

#endif // FT_SCAN_TUPLES_H
