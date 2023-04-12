#include <stdio.h>
#include "ft_scan_tuples.h"

// ----------------------------------------------------------------
int ft_scan_triple(
	char        * input,
	f2poly_t      m,
	f2polymod_t & a,
	f2polymod_t & b,
	f2polymod_t & c)
{
	unsigned ai, bi, ci;
	f2poly_t ar, br, cr;

	if (sscanf(input, "%x,%x,%x", &ai, &bi, &ci) != 3)
		return 0;
	ar = f2poly_t::from_base_rep(ai);
	br = f2poly_t::from_base_rep(bi);
	cr = f2poly_t::from_base_rep(ci);

	a = f2polymod_t(ar, m);
	b = f2polymod_t(br, m);
	c = f2polymod_t(cr, m);
	return 1;
}

// ----------------------------------------------------------------
int ft_scan_quintuple(
	char        * input,
	f2poly_t      m,
	f2polymod_t & a,
	f2polymod_t & b,
	f2polymod_t & c,
	f2polymod_t & d,
	f2polymod_t & e)
{
	unsigned ai, bi, ci, di, ei;
	f2poly_t ar, br, cr, dr, er;

	if (sscanf(input, "%x,%x,%x,%x,%x", &ai, &bi, &ci, &di, &ei) != 5)
		return 0;
	ar = f2poly_t::from_base_rep(ai);
	br = f2poly_t::from_base_rep(bi);
	cr = f2poly_t::from_base_rep(ci);
	dr = f2poly_t::from_base_rep(di);
	er = f2poly_t::from_base_rep(ei);

	a = f2polymod_t(ar, m);
	b = f2polymod_t(br, m);
	c = f2polymod_t(cr, m);
	d = f2polymod_t(dr, m);
	e = f2polymod_t(er, m);
	return 1;
}
