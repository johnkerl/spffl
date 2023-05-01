#include <stdio.h>
#include "spffl/ft_scan_tuples.h"

// ----------------------------------------------------------------
int ft_scan_triple(
	char        * input,
	f2_poly_t      m,
	f2_polymod_t & a,
	f2_polymod_t & b,
	f2_polymod_t & c)
{
	unsigned ai, bi, ci;
	f2_poly_t ar, br, cr;

	if (sscanf(input, "%x,%x,%x", &ai, &bi, &ci) != 3)
		return 0;
	ar = f2_poly_t::from_base_rep(ai);
	br = f2_poly_t::from_base_rep(bi);
	cr = f2_poly_t::from_base_rep(ci);

	a = f2_polymod_t(ar, m);
	b = f2_polymod_t(br, m);
	c = f2_polymod_t(cr, m);
	return 1;
}

// ----------------------------------------------------------------
int ft_scan_quintuple(
	char        * input,
	f2_poly_t      m,
	f2_polymod_t & a,
	f2_polymod_t & b,
	f2_polymod_t & c,
	f2_polymod_t & d,
	f2_polymod_t & e)
{
	unsigned ai, bi, ci, di, ei;
	f2_poly_t ar, br, cr, dr, er;

	if (sscanf(input, "%x,%x,%x,%x,%x", &ai, &bi, &ci, &di, &ei) != 5)
		return 0;
	ar = f2_poly_t::from_base_rep(ai);
	br = f2_poly_t::from_base_rep(bi);
	cr = f2_poly_t::from_base_rep(ci);
	dr = f2_poly_t::from_base_rep(di);
	er = f2_poly_t::from_base_rep(ei);

	a = f2_polymod_t(ar, m);
	b = f2_polymod_t(br, m);
	c = f2_polymod_t(cr, m);
	d = f2_polymod_t(dr, m);
	e = f2_polymod_t(er, m);
	return 1;
}
