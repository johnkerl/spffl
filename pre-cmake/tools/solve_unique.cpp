// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <stdio.h>

#include "tmatrix.h"
#include "bit_matrix_t.h"

#include "int_gcd.h"
#include "int_random.h"
#include "int_factor.h"

#include "bit_t.h"
#include "intmod_t.h"
#include "intrat_t.h"
#include "intmod_random.h"

#include "f2poly_t.h"
#include "f2polymod_t.h"
#include "f2polyrat_t.h"
#include "f2_poly_factor.h"
#include "f2poly_random.h"
#include "f2polymod_random.h"
#include "f2polymod_units.h"
#include "f2polymod_convert.h"
#include "f2_polymod_linear_algebra.h"

#include "f2npoly_t.h"
#include "f2npolymod_t.h"

#include "fppoly_t.h"
#include "fppolymod_t.h"
#include "fppolyrat_t.h"
#include "fp_poly_factor.h"
#include "fppoly_random.h"
#include "fppolymod_random.h"

#include "fpnpoly_t.h"
#include "fpnpolymod_t.h"

#include "cmd_line_ops.h"

typedef void usage_t(char * argv0);
typedef int main_t (int argc, char ** argv, usage_t * pusage);


static void f2pmmatsolve_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {A} {b}\n";
	std::cerr << "Solves A x = b for x, only when a unique solution exists.\n";
	exit(1);
}

static int f2pmmatsolve_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m = 0;
	f2polymod_t zero, one;

	if (argc != 4)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);

	zero = f2polymod_t(m.prime_sfld_elt(0), m);
	one  = f2polymod_t(m.prime_sfld_elt(1), m);

	tmatrix<f2polymod_t> A;
	tvector<f2polymod_t> x;
	tvector<f2polymod_t> b;

	A = f2polymod_t(zero);
	b = f2polymod_t(zero);
	if (!A.load_from_file(argv[2]))
		pusage(argv[0]);
	if (!b.load_from_file(argv[3]))
		pusage(argv[0]);

	if (!A.solve_unique(x, b, zero, one)) {
		std::cerr << "No unique solution.\n";
		return 1;
	}
	std::cout << x << "\n";
	return 0;
}

int main(int argc, char ** argv)
{
	return f2pmmatsolve_main(argc, argv, f2pmmatsolve_usage);
}
