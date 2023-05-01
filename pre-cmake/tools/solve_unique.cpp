// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <stdio.h>

#include "spffl/tmatrix.h"
#include "spffl/bit_matrix_t.h"

#include "spffl/int_gcd.h"
#include "spffl/int_random.h"
#include "spffl/int_factor.h"

#include "spffl/bit_t.h"
#include "spffl/intmod_t.h"
#include "spffl/intrat_t.h"
#include "spffl/intmod_random.h"

#include "spffl/f2_poly_t.h"
#include "spffl/f2_polymod_t.h"
#include "spffl/f2_polyrat_t.h"
#include "spffl/f2_poly_factor.h"
#include "spffl/f2_poly_random.h"
#include "spffl/f2_polymod_random.h"
#include "spffl/f2_polymod_units.h"
#include "spffl/f2_polymod_convert.h"
#include "spffl/f2_polymod_linear_algebra.h"

#include "spffl/f2n_poly_t.h"
#include "spffl/f2n_polymod_t.h"

#include "spffl/fp_poly_t.h"
#include "spffl/fp_polymod_t.h"
#include "spffl/fp_polyrat_t.h"
#include "spffl/fp_poly_factor.h"
#include "spffl/fp_poly_random.h"
#include "spffl/fp_polymod_random.h"

#include "spffl/fpn_poly_t.h"
#include "spffl/fpn_polymod_t.h"

#include "spffl/cmd_line_ops.h"

typedef void usage_t(char * argv0);
typedef int main_t (int argc, char ** argv, usage_t * pusage);


static void f2_pm_mat_solve_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {A} {b}\n";
	std::cerr << "Solves A x = b for x, only when a unique solution exists.\n";
	exit(1);
}

static int f2_pm_mat_solve_main(int argc, char ** argv, usage_t * pusage)
{
	f2_poly_t m = 0;
	f2_polymod_t zero, one;

	if (argc != 4)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);

	zero = f2_polymod_t(m.prime_subfield_element(0), m);
	one  = f2_polymod_t(m.prime_subfield_element(1), m);

	tmatrix<f2_polymod_t> A;
	tvector<f2_polymod_t> x;
	tvector<f2_polymod_t> b;

	A = f2_polymod_t(zero);
	b = f2_polymod_t(zero);
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
	return f2_pm_mat_solve_main(argc, argv, f2_pm_mat_solve_usage);
}
