#ifndef TMVPOLYSCAN_H
#define TMVPOLYSCAN_H

#include "bit_t.h"
#include "intmod_t.h"
#include "f2_polymod_t.h"
#include "f2n_polymod_t.h"
#include "fp_polymod_t.h"
#include "tmvpoly.h"

int tmvpoly_f2_polymod_from_string(
	tmvpoly<f2_polymod_t> & f,
	const char           * string,
	f2_poly_t               m);

int tmvpoly_fp_polymod_from_string(
	tmvpoly<fp_polymod_t> & f,
	const char           * string,
	fp_poly_t               m);

// xxx Code up the remaining data types as well.

#endif // TMVPOLYSCAN_H
