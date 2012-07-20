#ifndef FT_SCAN_TUPLES_H
#define FT_SCAN_TUPLES_H

#include "f2polymod_t.h"

int ft_scan_triple(
	char        * input,
	f2poly_t      m,
	f2polymod_t & a,
	f2polymod_t & b,
	f2polymod_t & c);

int ft_scan_quintuple(
	char        * input,
	f2poly_t      m,
	f2polymod_t & a,
	f2polymod_t & b,
	f2polymod_t & c,
	f2polymod_t & d,
	f2polymod_t & e);

#endif // FT_SCAN_TUPLES_H
