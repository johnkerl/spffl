#ifndef TMVRATSCAN_H
#define TMVRATSCAN_H

#include "bit_t.h"
#include "intmod_t.h"
#include "f2polymod_t.h"
#include "f2npolymod_t.h"
#include "fppolymod_t.h"
#include "tmvrat.h"

int tmvrat_f2polymod_from_string(
	tmvrat<f2polymod_t> & f,
	char                * string,
	f2poly_t              m);

int tmvrat_f2polymods_from_file(
	char                           * file_name,
	tvector< tmvrat<f2polymod_t> > & rats,
	f2poly_t                         m);

int tmvrat_f2polymods_from_stream(
	std::istream                   & is,
	tvector< tmvrat<f2polymod_t> > & rats,
	f2poly_t                         m);

int tmvrat_fppolymod_from_string(
	tmvrat<fppolymod_t> & f,
	char                * string,
	fppoly_t              m);

// xxx Code up the remaining data types as well.

#endif // TMVRATSCAN_H
