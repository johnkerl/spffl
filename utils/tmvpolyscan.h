#ifndef TMVPOLYSCAN_H
#define TMVPOLYSCAN_H

#include "bit_t.h"
#include "intmod_t.h"
#include "f2polymod_t.h"
#include "f2npolymod_t.h"
#include "fppolymod_t.h"
#include "tmvpoly.h"

int tmvpoly_f2polymod_from_string(
	tmvpoly<f2polymod_t> & f,
	const char           * string,
	f2poly_t               m);

int tmvpoly_fppolymod_from_string(
	tmvpoly<fppolymod_t> & f,
	const char           * string,
	fppoly_t               m);

// xxx Code up the remaining data types as well.

#endif // TMVPOLYSCAN_H
