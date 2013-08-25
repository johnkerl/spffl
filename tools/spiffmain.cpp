// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// ================================================================
// Data type      Prefix  Description
// ---------      ------  -----------------------------------
// int            z       Z                        Ring
// bit_t          f2      Z/<2> = F_2              Residue field, p=2
// intmod_t       fp      Z/<p> = F_p              Residue field
// intrat_t       q       Q                        Quotient field
//
// f2poly_t       f2p     F2[x]                    Ring
// f2polymod_t    f2pm    F2[x]/<f(x)> = F_{2^n}   Residue field
// f2polyrat_t    f2pr    F2(x)                    Quotient field
//
// fppoly_t       fpp     F_p[x]                   Ring
// fppolymod_t    fppm    F_p[x]/<f(x)>            Residue field
// fppolyrat_t    fppr    F_p(x)                   Quotient field
//
// f2npoly_t      f2np    F_{2^n}[y]               Ring
// f2npolymod_t   f2npm   F_{2^n}[y]/<g(y)>        Residue field
// f2npolyrat_t   f2npr   F_{2^n}(y)               Quotient field
//
// fpnpoly_t      fpnp    F_{p^n}[y]               Ring
// fpnpolymod_t   fpnpm   F_{p^n}[y]/<g(y)>        Residue field
// fpnpolyrat_t   fpnpr   F_{p^n}(y)               Quotient field

// ----------------------------------------------------------------
// Rings:

// *          z    f2p  f2np fpp  fpnp
// ---------- ---- ---- ---- ---- ----
// op         o    o    o    o    o
// eval       -    o    o    o    -
// rand       -    o    o    o    .
// deg        -    o    o    o    .
// gcd        o    o    o    o    .
// lcm        o    o    o    o    .
// totient    o    o    o    o    .
// test       o    o    o    o    .
// find       -    o    o    o    .
// period     -    o    .    .    .
// factor     o    o    o    o    .
// divisors   o    o    o    o    .
// list       -    o    o    o    .
// compmx     -    o    o    o    .

// ----------------------------------------------------------------
// Fields:

// *        q    fp   f2   f2pm f2pr f2npm f2npr fppm fppr fpnpm fpnpr
// -        ---- ---- ---- ---- ---- ----- ----- ---- ---- ----- -----
// op       o    o    .    o    o    o     o     o    o    o     .
// tbl      -    o    -    o    -    o     -     o    -    .     -
// ord      -    o    -    o    -    o     -     r    -    .     -
// findgen  -    o    -    o    -    o     -     .    -    .     -
// log      -    o    -    o    -    o     -     .    -    .     -
// rand     -    o    o    o    o    o     .     o    .    .     .
// chpol    -    -    -    o    -    -     -     .    -    -     -
// minpol   -    -    -    o    -    -     -     .    -    -     -
// list     -    o    -    o    -    o     -     o    -    .     -
// matop    o    o    o    o    o    o     o     o    o    .     .
// matord   -    o    o    o    -    .     -     o    -    .     .
// matrand  -    o    o    o    o    .     .     o    .    .     .
// matchpol -    o    o    o    -    -     -     .    -    -     -
// dable    .    .    .    .    .    .     .     .    .    .     .
// eisys    .    .    .    .    .    .     .     .    .    .     .
// jordan   .    .    .    .    .    .     .     .    .    .     .
// ratcanon .    .    .    .    .    .     .     .    .    .     .

// ----------------------------------------------------------------
// f2p_to_f2np fpp_to_fpnp
// orbit frobit eval
// matminpoly, matcharpoly
// f*chart f*polylist
// row-reduce over an ED, non-field.

#include <iostream>
#include <stdio.h>
#include "cmdinterp.h"

#include "tmatrix.h"

#include "int_gcd.h"
#include "int_totient.h"
#include "int_random.h"
#include "int_factor.h"
#include "isprime.h"

#include "bit_t.h"
#include "intmod_t.h"
#include "intrat_t.h"
#include "intmod_random.h"
#include "fp_units.h"

#include "spminchar.h"

#include "f2linalg.h"
#include "f2poly_t.h"
#include "f2polymod_t.h"
#include "f2polyrat_t.h"
#include "f2poly_random.h"
#include "f2poly_factor.h"
#include "f2poly_totient.h"
#include "f2polymod_random.h"
#include "f2polymod_units.h"
#include "f2polymod_convert.h"

#include "f2npoly_t.h"
#include "f2npolymod_t.h"
#include "f2npolyrat_t.h"
#include "f2npoly_random.h"
#include "f2npoly_factor.h"
#include "f2npoly_totient.h"
#include "f2pmlinalg.h"

#include "f2npolymod_random.h"
#include "f2npolymod_units.h"

#include "fppoly_t.h"
#include "fppolymod_t.h"
#include "fppolyrat_t.h"
#include "fplinalg.h"
#include "fppoly_random.h"
#include "fppoly_factor.h"
#include "fppoly_totient.h"
#include "fppolymod_random.h"

#include "fpnpoly_t.h"
#include "fpnpolymod_t.h"

#include "cmdlineops.h"
#include "cmdlinematops.h"
#include "cmdlineedmatops.h"
#include "cmdlinevecops.h"

#include "sp_list_elts.h"

#include "qff.h"
#include "cyclopoly.h"

#define TBL_TYPE_PLUS     10
#define TBL_TYPE_MINUS    11
#define TBL_TYPE_MUL      12
#define TBL_TYPE_UNIT_MUL 13
#define TBL_TYPE_UNIT_DIV 14
#define TBL_TYPE_LOG      15
#define TBL_TYPE_ALOG     16

typedef void usage_t(char * argv0);
typedef int main_t (int argc, char ** argv, usage_t * pusage);

// ================================================================
static int qop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_parse<intrat_t>(argc-1, argv+1, intrat_t(0), intrat_t(1));
	return 0;
}

static int qmatop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_mat_parse<intrat_t>(argc-1, argv+1, intrat_t(0), intrat_t(1));
	return 0;
}

static int qvecop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_vec_parse<intrat_t>(argc-1, argv+1, intrat_t(0), intrat_t(1));
	return 0;
}

static void qcyclo_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {n}\n";
	exit(1);
}

static int qpop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_parse<qpoly_t>(argc-1, argv+1,
		qpoly_t(intrat_t(0)), qpoly_t(intrat_t(1)));
	return 0;
}

static int qcyclo_main(int argc, char ** argv, usage_t * pusage)
{
	int n;
	if (argc < 2)
		pusage(argv[0]);
	for (int argi = 1; argi < argc; argi++) {
		if (sscanf(argv[argi], "%d", &n) != 1)
			pusage(argv[0]);
		std::cout << get_cyclo_qpoly(n) << std::endl;
	}
	return 0;
}

static int zop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_parse<int>(argc-1, argv+1, 0, 1);
	return 0;
}

static int zmatop_main(int argc, char ** argv, usage_t * pusage)
{
	ed_cmd_line_mat_parse<int>(argc-1, argv+1, 0, 1);
	return 0;
}

static void zgcd_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-e] {a} {b}\n";
	exit(1);
}

static int zgcd_main(int argc, char ** argv, usage_t * pusage)
{
	if ((argc >= 2) && (strcmp(argv[1], "-e") == 0)) {
		int a, b, g, r, s;
		if (argc != 4)
			pusage(argv[0]);
		if (sscanf(argv[2], "%d", &a) != 1)
			pusage(argv[0]);
		if (sscanf(argv[3], "%d", &b) != 1)
			pusage(argv[0]);

		g = int_ext_gcd(a, b, &r, &s);
		std::cout
			<< g << " = "
			<< r << " * "
			<< a << " + "
			<< s << " * "
			<< b << std::endl;

		int check = a * r + b * s;
		if (g != check) {
			std::cerr << "Coding error in extended GCD.\n";
			exit(1);
		}
	}
	else {
		int a, g;
		if (argc < 2)
			pusage(argv[0]);
		if (sscanf(argv[1], "%d", &a) != 1)
			pusage(argv[0]);
		g = a;
		for (int argi = 2; argi < argc; argi++) {
			if (sscanf(argv[argi], "%d", &a) != 1)
				pusage(argv[0]);
			g = int_gcd(g, a);
		}
		std::cout << g << std::endl;
	}
	return 0;
}

static void zlcm_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {integers ...}\n";
	exit(1);
}

static int zlcm_main(int argc, char ** argv, usage_t * pusage)
{
	int a, l;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &a) != 1)
		pusage(argv[0]);
	l = a;
	for (int argi = 2; argi < argc; argi++) {
		if (sscanf(argv[argi], "%d", &a) != 1)
			pusage(argv[0]);
		l = int_lcm(l, a);
	}
	std::cout << l << std::endl;
	return 0;
}

static void ztotient_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {integers ...}\n";
	exit(1);
}

static int ztotient_main(int argc, char ** argv, usage_t * pusage)
{
	int a, phi;
	if (argc < 2)
		pusage(argv[0]);
	for (int argi = 1; argi < argc; argi++) {
		if (sscanf(argv[argi], "%d", &a) != 1)
			pusage(argv[0]);
		phi = int_totient(a);
		if (argc > 2)
			std::cout << a << ": ";
		std::cout << phi << std::endl;
	}
	return 0;
}

static void ztestprime_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {integers ...}\n";
	exit(1);
}

static int ztestprime_main(int argc, char ** argv, usage_t * pusage)
{
	int a;
	for (int argi = 1; argi < argc; argi++) {
		if (sscanf(argv[argi], "%d", &a) != 1)
			pusage(argv[0]);
		if (argc > 2)
			std::cout << a << ": ";
		if (isprime(a))
			std::cout << "PRIME\n";
		else
			std::cout << "not prime\n";
	}
	return 0;
}

static void nthprime_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {n[-m]}\n";
	exit(1);
}

static int nthprime_main(int argc, char ** argv, usage_t * pusage)
{
	if (argc < 2)
		pusage(argv[0]);
	for (int argi = 1; argi < argc; argi++) {
		int lo, hi;
		if (sscanf(argv[argi], "%d-%d", &lo, &hi) == 2)
			;
		else if (sscanf(argv[argi], "%d", &lo) == 1)
			hi = lo;
		else
			pusage(argv[0]);
		for (int n = lo; n <= hi; n++) {
			std::cout << nthprime(n) << std::endl;
		}
	}
	return 0;
}

static void zlist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {start [reps [stride]]}\n";
	exit(1);
}

static int zlist_main(int argc, char ** argv, usage_t * pusage)
{
	int walker  = 1;
	int reps   = 1;
	int stride = 1;

	if (argc < 2 || argc > 4)
		pusage(argv[0]);
	if (argc >= 2) {
		if (sscanf(argv[1], "%d", &walker) != 1)
		pusage(argv[0]);
	}
	if (argc >= 3) {
		if (sscanf(argv[2], "%d", &reps) != 1)
		pusage(argv[0]);
	}
	if (argc >= 4) {
		if (sscanf(argv[3], "%d", &stride) != 1)
		pusage(argv[0]);
	}

	while (reps > 0) {
		printf("%d\n", walker);
		walker += stride;
		reps --;
	}

	return 0;
}

static void zfactor_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {integers ...}\n";
	exit(1);
}

static int zfactor_main(int argc, char ** argv, usage_t * pusage)
{
	int a;
	for (int argi = 1; argi < argc; argi++) {
		if (sscanf(argv[argi], "%d", &a) != 1)
			pusage(argv[0]);
		if (argc > 2)
			std::cout << a << " = ";
		tfacinfo<int> finfo = int_factor(a);
		std::cout << finfo << std::endl;

		int check = finfo.unfactor(1);
		if (check != a) {
			std::cerr << "Coding error in zfactor.\n";
			std::cerr << "  Input: " << a << std::endl;
			std::cerr << "  Check: " << check << std::endl;
			std::cerr << "  Factors: " << finfo << std::endl;
			exit(1);
		}
	}
	return 0;
}

static void zdivisors_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-mp] {integers ...}\n";
	exit(1);
}

static int zdivisors_main(int argc, char ** argv, usage_t * pusage)
{
	int a;
	int argb = 1;
	int maximal_proper_only = 0;
	if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
		argb++;
		maximal_proper_only = 1;
	}
	if ((argc - argb) < 1)
			pusage(argv[0]);
	for (int argi = argb; argi < argc; argi++) {
		if (sscanf(argv[argi], "%d", &a) != 1)
			pusage(argv[0]);
		if ((argc - argb) > 1)
			std::cout << a << ": ";
		tfacinfo<int> finfo = int_factor(a);
		tvector<int> divisors;
		if (maximal_proper_only) {
			if (!finfo.get_maximal_proper_divisors(divisors, 1)) {
				std::cout << "(none)\n";
				continue;
			}
		}
		else {
			divisors = finfo.get_all_divisors(1);
		}
		int nd = divisors.get_num_elements();
		for (int k = 0; k < nd; k++) {
			if (k > 0)
				std::cout << " ";
			std::cout << divisors[k];
		}
		std::cout << std::endl;
	}
	return 0;
}

static int f2op_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_parse<bit_t>(argc-1, argv+1, bit_t(0), bit_t(1));
	return 0;
}

static void f2random_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [count]\n";
	exit(1);
}

static int f2random_main(int argc, char ** argv, usage_t * pusage)
{
	int count = 1;

	if ((argc != 1) && (argc != 2))
		pusage(argv[0]);
	if (argc == 2) {
		if (sscanf(argv[1], "%d", &count) != 1)
			pusage(argv[0]);
	}

	for (int i = 0; i < count; i++)
		std::cout << (get_random_int() & 1) << std::endl;

	return 0;
}

static int f2matop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_mat_parse<bit_t>(argc-1, argv+1, bit_t(0), bit_t(1));
	return 0;
}

static int f2vecop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_vec_parse<bit_t>(argc-1, argv+1, bit_t(0), bit_t(1));
	return 0;
}

static void f2matchpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {goes here}\n";
	exit(1);
}

static int f2matchpol_main(int argc, char ** argv, usage_t * pusage)
{
	tmatrix<bit_t> A;

	if (argc != 2)
		pusage(argv[0]);
	A = bit_t(0);
	if (!A.load_from_file(argv[1]))
		pusage(argv[0]);
	f2poly_t chpol = f2_char_poly(A);
	std::cout << chpol << std::endl;

	return 0;
}

static void f2matord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {goes here}\n";
	exit(1);
}

static int f2matord_main(int argc, char ** argv, usage_t * pusage)
{
	tmatrix<bit_t> A;

	if (argc != 1)
		pusage(argv[0]);

	bit_t zero(0);
	bit_t one (1);

	A = zero;
	std::cin >> A;
	bit_t d = A.det();

	if (d == zero) {
		std::cout << 0 << std::endl;
	}
	else {
		tmatrix<bit_t> I = A.make_I(zero, one);
		int order;
		tmatrix<bit_t> Apower = A;

		for (order = 1; ; order++) {
			if (Apower == I) {
				std::cout << order << std::endl;
				return 0;
			}
			Apower *= A;
		}

		std::cout << order << std::endl;
	}

	return 0;
}

static void f2matrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {# rows} {# cols}\n";
	exit(1);
}

static int f2matrandom_main(int argc, char ** argv, usage_t * pusage)
{
	int nr, nc;

	if (argc != 3)
		pusage(argv[0]);

	if (sscanf(argv[1], "%d", &nr) != 1)
		pusage(argv[0]);
	if (sscanf(argv[2], "%d", &nc) != 1)
		pusage(argv[0]);
	tmatrix<bit_t> A(nr, nc);
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			A[i][j] = bit_t(get_random_unsigned() & 1);
	std::cout << A;
	return 0;
}

static void f2plist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {deglo[-deghi]}\n";
	exit(1);
}

int f2plist_main(int argc, char ** argv, usage_t * pusage)
{
	int deglo, deghi;
	if (argc != 2)
		pusage(argv[0]);

	if (sscanf(argv[1], "%d-%d", &deglo, &deghi) == 2)
		;
	else if (sscanf(argv[1], "%d", &deglo) == 1)
		deghi = deglo;
	else
		pusage(argv[0]);

	for (int deg = deglo; deg <= deghi; deg++) {
		tvector<f2poly_t> elts = f2poly_list(deg);
		elts.crout(std::cout);
	}
	return 0;
}

static int f2pop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_parse<f2poly_t>(argc-1, argv+1, f2poly_t(0), f2poly_t(1));
	return 0;
}

static int f2pmatop_main(int argc, char ** argv, usage_t * pusage)
{
	ed_cmd_line_mat_parse<f2poly_t>(argc-1, argv+1, f2poly_t(0), f2poly_t(1));
	return 0;
}

static void f2pcompmx_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {f2 chpoly}\n";
	exit(1);
}

static int f2pcompmx_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t chpol;

	if (argc != 2)
		pusage(argv[0]);
	if (!chpol.from_string(argv[1]))
		pusage(argv[0]);

	tmatrix<bit_t> A = f2_companion_matrix(chpol);
	std::cout << A << std::endl;

	return 0;
}

static void f2pdeg_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {polys ...}\n";
	exit(1);
}

static int f2pdeg_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t a;
	for (int argi = 1; argi < argc; argi++) {
		if (!a.from_string(argv[argi]))
			pusage(argv[0]);
		if (argc > 2)
			std::cout << a << ": ";
		std::cout << a.find_degree() << std::endl;
	}
	return 0;
}

static void f2pgcd_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-e] {poly1} {poly2}\n";
	exit(1);
}

static int f2pgcd_main(int argc, char ** argv, usage_t * pusage)
{
	if ((argc >= 2) && (strcmp(argv[1], "-e") == 0)) {
		f2poly_t a, b, g, r, s;
		if (argc != 4)
			pusage(argv[0]);
		if (!a.from_string(argv[2]))
			pusage(argv[0]);
		if (!b.from_string(argv[3]))
			pusage(argv[0]);

		g = a.ext_gcd(b, r, s);
		std::cout
			<< g << " = "
			<< r << " * "
			<< a << " + "
			<< s << " * "
			<< b << std::endl;

		f2poly_t check = a * r + b * s;
		if (g != check) {
			std::cerr << "Coding error in extended GCD.\n";
			exit(1);
		}
	}
	else {
		f2poly_t a, g;
		if (argc < 2)
			pusage(argv[0]);
		if (!a.from_string(argv[1]))
			pusage(argv[0]);
		g = a;
		for (int argi = 2; argi < argc; argi++) {
			if (!a.from_string(argv[argi]))
				pusage(argv[0]);
			g = g.gcd(a);
		}
		std::cout << g << std::endl;
	}
	return 0;
}

static void f2plcm_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {polys ...}\n";
	exit(1);
}

static int f2plcm_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t a, l;

	if (argc < 2)
		pusage(argv[0]);
	if (!a.from_string(argv[1]))
		pusage(argv[0]);
	l = a;
	for (int argi = 2; argi < argc; argi++) {
		if (!a.from_string(argv[argi]))
			pusage(argv[0]);
		l = (l * a) / l.gcd(a);
	}
	std::cout << l << std::endl;
	return 0;
}

static void f2ptotient_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {polys ...}\n";
	exit(1);
}

static int f2ptotient_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t a;
	int phi;
	if (argc < 2)
		pusage(argv[0]);
	for (int argi = 1; argi < argc; argi++) {
		if (!a.from_string(argv[argi]))
			pusage(argv[0]);
		phi = f2poly_totient(a);
		if (argc > 2)
			std::cout << a << ": ";
		std::cout << phi << std::endl;
	}
	return 0;
}

static void f2ptest_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {-i|-p|-ip} {polys ...}\n";
	std::cerr << "-i: irreducible; -p: primitive.\n";
	exit(1);
}

static int f2ptest_main(int argc, char ** argv, usage_t * pusage)
{
	int do_irr = 0, do_prim = 0;
	if (argc < 3)
		pusage(argv[0]);

	if (strcmp(argv[1], "-i") == 0) {
		do_irr  = 1;
		do_prim = 0;
	}
	else if (strcmp(argv[1], "-p") == 0) {
		do_irr  = 0;
		do_prim = 1;
	}
	else if (strcmp(argv[1], "-ip") == 0) {
		do_irr  = 1;
		do_prim = 1;
	}
	else {
		pusage(argv[0]);
	}

	for (int argi = 2; argi < argc; argi++) {
		f2poly_t a;
		if (!a.from_string(argv[argi]))
			pusage(argv[0]);
		if (argc > 2)
			std::cout << a << ": ";
		if (do_irr) {
			if (f2poly_is_irreducible(a))
				std::cout << "IRREDUCIBLE";
			else
				std::cout << "reducible";
		}
		if (do_irr && do_prim)
			std::cout << " ";
		if (do_prim) {
			if (f2poly_is_primitive(a))
				std::cout << "PRIMITIVE";
			else
				std::cout << "imprimitive";
		}
		std::cout << std::endl;
	}
	return 0;
}

static void f2pfind_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {-1|-r} {-i|-p|-ip} {deglo[-deghi]}\n";
	std::cerr << "-1: lowest degree; -r: random\n";
	std::cerr << "-i: irreducible; -p: primitive\n";
	exit(1);
}

static int f2pfind_main(int argc, char ** argv, usage_t * pusage)
{
	int do_random = 0, deglo, deghi;
	int do_irr = 0, do_prim = 0;

	if (argc != 4)
		pusage(argv[0]);
	if (strcmp(argv[1], "-1") == 0)
		do_random = 0;
	else if (strcmp(argv[1], "-r") == 0)
		do_random = 1;
	else
		pusage(argv[0]);

	if (strcmp(argv[2], "-i") == 0) {
		do_irr  = 1;
		do_prim = 0;
	}
	else if (strcmp(argv[2], "-p") == 0) {
		do_irr  = 0;
		do_prim = 1;
	}
	else if (strcmp(argv[2], "-ip") == 0) {
		do_irr  = 1;
		do_prim = 1;
	}
	else {
		pusage(argv[0]);
	}

	if (sscanf(argv[3], "%d-%d", &deglo, &deghi) == 2)
		;
	else if (sscanf(argv[3], "%d", &deglo) == 1)
		deghi = deglo;
	else
		pusage(argv[0]);

	for (int deg = deglo; deg <= deghi; deg++) {
		f2poly_t a;
		if (do_prim) {
			a = do_random ? f2poly_random_prim(deg, do_irr)
				: f2poly_find_prim(deg, do_irr);
		}
		else {
			a = do_random ? f2poly_random_irr(deg)
				: f2poly_find_irr(deg);
		}
		std::cout << a << std::endl;
	}
	return 0;
}

static void f2pperiod_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {polys ...}\n";
	exit(1);
}

static int f2pperiod_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t a;
	for (int argi = 1; argi < argc; argi++) {
		if (!a.from_string(argv[argi]))
			pusage(argv[0]);
		if (argc > 2)
			std::cout << a << ": ";
		std::cout << f2poly_period(a) << std::endl;
	}
	return 0;
}

static void f2pfactor_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {polys ...}\n";
	exit(1);
}

static int f2pfactor_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t a;
	for (int argi = 1; argi < argc; argi++) {
		if (!a.from_string(argv[argi]))
			pusage(argv[0]);
		if (argc > 2)
			std::cout << a << " = ";
		tfacinfo<f2poly_t> finfo = f2poly_factor(a);
		std::cout << finfo << std::endl;

		f2poly_t check = finfo.unfactor(f2poly_t(1));
		if (check != a) {
			std::cerr << "Coding error in f2poly_factor.\n";
			std::cerr << "  Input: " << a << std::endl;
			std::cerr << "  Check: " << check << std::endl;
			std::cerr << "  Factors: " << finfo << std::endl;
			exit(1);
		}
	}
	return 0;
}

static void f2pdivisors_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-mp] {polys ...}\n";
	exit(1);
}

static int f2pdivisors_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t a;
	int argb = 1;
	int maximal_proper_only = 0;
	if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
		maximal_proper_only = 1;
		argb++;
	}
	for (int argi = argb; argi < argc; argi++) {
		if (!a.from_string(argv[argi]))
			pusage(argv[0]);
		if ((argc - argb) > 1)
			std::cout << a << ": ";
		tfacinfo<f2poly_t> finfo = f2poly_factor(a);
		tvector<f2poly_t> divisors;
		if (maximal_proper_only) {
			if (!finfo.get_maximal_proper_divisors(divisors, f2poly_t(1))) {
				std::cout << "(none)\n";
				continue;
			}
		}
		else {
			divisors = finfo.get_all_divisors(f2poly_t(1));
		}
		int nd = divisors.get_num_elements();
		for (int k = 0; k < nd; k++) {
			if (k > 0)
				std::cout << " ";
			std::cout << divisors[k];
		}
		std::cout << std::endl;
	}
	return 0;
}

static void f2peval_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {f} {elements of F2 ...}\n";
	exit(1);
}

static int f2peval_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t f;
	bit_t a, b;

	if (argc < 3)
		pusage(argv[0]);
	if (!f.from_string(argv[1]))
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!a.from_string(argv[argi]))
			pusage(argv[0]);
		b = f.eval(a);
		std::cout << b << std::endl;
	}

	return 0;
}

static void f2prandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {deg} [count]\n";
	exit(1);
}

static int f2prandom_main(int argc, char ** argv, usage_t * pusage)
{
	int deg, count = 1;

	if ((argc != 2) && (argc != 3))
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &deg) != 1)
		pusage(argv[0]);
	if (argc == 3) {
		if (sscanf(argv[2], "%d", &count) != 1)
			pusage(argv[0]);
	}

	for (int i = 0; i < count; i++)
		std::cout << f2poly_random(deg) << std::endl;

	return 0;
}

static void f2pqp_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {qpolys ...}\n";
	exit(1);
}

static int f2pqp_main(int argc, char ** argv, usage_t * pusage)
{
	qpoly_t qp;
	f2poly_t f2p;
	if (argc < 2)
		pusage(argv[0]);
	for (int argi = 1; argi < argc; argi++) {
		if (!qp.from_string(argv[argi]))
			pusage(argv[0]);
		f2p = f2poly_from_qpoly(qp);
		std::cout << f2p << std::endl;
	}
	return 0;
}

static void f2pmlist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-a|-u] {m}\n";
	exit(1);
}

int f2pmlist_main(int argc, char ** argv, usage_t * pusage)
{
	sp_list_type_t type = SP_LIST_ALL;
	f2poly_t m;
	if (argc == 3) {
		if (strcmp(argv[1], "-a") == 0)
			type = SP_LIST_ALL;
		else if (strcmp(argv[1], "-u") == 0)
			type = SP_LIST_UNITS;
		else if (strcmp(argv[1], "-nu") == 0)
			type = SP_LIST_NON_UNITS;
		else
			pusage(argv[0]);
		if (!m.from_string(argv[2]))
			pusage(argv[0]);
		tvector<f2polymod_t> elts = f2polymod_list(m, type);
		elts.crout(std::cout);
	}
	else if (argc == 4) {
		f2polymod_t g;
		if (strcmp(argv[1], "-m") == 0)
			type = SP_LIST_MULTIPLES;
		else if (strcmp(argv[1], "-rp") == 0)
			type = SP_LIST_REL_PRIME;
		else
			pusage(argv[0]);
		if (!m.from_string(argv[3]))
			pusage(argv[0]);
		if (!g.from_string(argv[2], m))
			pusage(argv[0]);
		tvector<f2polymod_t> elts = f2polymod_glist(g, type);
		elts.crout(std::cout);
	}
	else {
		pusage(argv[0]);
	}
	return 0;
}

static void f2pmop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {a} {b}\n";
	exit(1);
}

static int f2pmop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	cmd_line_parse<f2polymod_t>(argc-2, argv+2,
		f2polymod_t(f2poly_t(0), m),
		f2polymod_t(f2poly_t(1), m));
	return 0;
}

static void f2pmtbl_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {+|-|*|u*|/|log[:g]|alog[:g]}\n";
	exit(1);
}

static int f2pmtbl_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2polymod_t g;
	int tbl_type = TBL_TYPE_PLUS;
	if (argc != 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);

	if (strcmp(argv[2], "+") == 0)
		tbl_type = TBL_TYPE_PLUS;
	else if (strcmp(argv[2], "-") == 0)
		tbl_type = TBL_TYPE_MINUS;
	else if (strcmp(argv[2], "*") == 0)
		tbl_type = TBL_TYPE_MUL;
	else if (strcmp(argv[2], ".") == 0)
		tbl_type = TBL_TYPE_MUL;
	else if (strcmp(argv[2], "u*") == 0)
		tbl_type = TBL_TYPE_UNIT_MUL;
	else if (strcmp(argv[2], "u.") == 0)
		tbl_type = TBL_TYPE_UNIT_MUL;
	else if (strcmp(argv[2], "/") == 0)
		tbl_type = TBL_TYPE_UNIT_DIV;

	else if (strncmp(argv[2], "log:", 4) == 0) {
		if (!g.from_string(&argv[2][4], m))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strcmp(argv[2], "log") == 0) {
		if (!f2polymod_find_generator(m, g)) {
			std::cerr << "Couldn't find generator mod "
				<< m << std::endl;
			exit(1);
		}
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strncmp(argv[2], "alog:", 5) == 0) {
		if (!g.from_string(&argv[2][5], m))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_ALOG;
	}
	else if (strcmp(argv[2], "alog") == 0) {
		if (!f2polymod_find_generator(m, g)) {
			std::cerr << "Couldn't find generator mod "
				<< m << std::endl;
			exit(1);
		}
		tbl_type = TBL_TYPE_ALOG;
	}
	else
		pusage(argv[0]);

	tvector<f2polymod_t> elts;
	if ((tbl_type == TBL_TYPE_UNIT_MUL)
	|| (tbl_type == TBL_TYPE_UNIT_DIV)
	|| (tbl_type == TBL_TYPE_LOG)
	|| (tbl_type == TBL_TYPE_ALOG))
		elts = f2polymod_list(m, SP_LIST_UNITS);
	else
		elts = f2polymod_list(m, SP_LIST_ALL);
	int n = elts.get_num_elements();

	if (tbl_type == TBL_TYPE_LOG) {
		std::cout << "element power\n";
		std::cout << "------- -----\n";
		for (int i = 0; i < n; i++) {
			int e = f2polymod_log(g, elts[i]);
			std::cout << elts[i] << " " << e << std::endl;
		}
		return 0;
	}
	if (tbl_type == TBL_TYPE_ALOG) {
		std::cout << "power element\n";
		std::cout << "----- -------\n";
		f2polymod_t gp = g / g;
		for (int i = 0; i < n; i++) {
			std::cout << i << " " << gp << std::endl;
			gp *= g;
		}
		return 0;
	}

	f2polymod_t a, b, c;

	for (int i = 0; i < n; i++) {
		a = elts[i];
		for (int j = 0; j < n; j++) {
			b = elts[j];
			switch (tbl_type) {
			case TBL_TYPE_PLUS:     c = a + b; break;
			case TBL_TYPE_MINUS:    c = a - b; break;
			case TBL_TYPE_MUL:      c = a * b; break;
			case TBL_TYPE_UNIT_MUL: c = a * b; break;
			case TBL_TYPE_UNIT_DIV: c = a / b; break;
			}
			if (j > 0)
				std::cout << " ";
			std::cout << c;
		}
		std::cout << std::endl;
	}

	return 0;
}

static void f2pmord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {a}\n";
	exit(1);
}

static int f2pmord_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2polymod_t a;
	if (argc < 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		if (argc > 3)
			std::cout << a << ": ";
		std::cout << f2polymod_order(a) << std::endl;
	}
	return 0;
}

static void f2pmfindgen_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m}\n";
	exit(1);
}

static int f2pmfindgen_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2polymod_t g;
	int rv = 0;
	if (argc < 2)
		pusage(argv[0]);
	for (int argi = 1; argi < argc; argi++) {
		if (!m.from_string(argv[argi]))
			pusage(argv[0]);
		if (argc > 2)
			std::cout << m << ": ";
		if (f2polymod_find_generator(m, g)) {
			std::cout << g << std::endl;
		}
		else {
			std::cout << "Generator not found.\n";
			rv = 1;
		}
	}
	return rv;
}

static void f2pmlog_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {g} {a}\n";
	exit(1);
}

static int f2pmlog_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2polymod_t g, a;
	if (argc < 4)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	if (!g.from_string(argv[2], m))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		if (argc > 4)
			std::cout << a << ": ";
		std::cout << f2polymod_log(g, a) << std::endl;
	}
	return 0;
}

static void f2pmchpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {residues ...}\n";
	exit(1);
}

static int f2pmchpol_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2polymod_t a;

	if (argc < 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		f2poly_t cp = f2pm_char_poly(a);
		if (argc > 3)
			std::cout << a << ": ";
		std::cout << cp << std::endl;
	}

	return 0;
}

static void f2pmminpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {residues ...}\n";
	exit(1);
}

static int f2pmminpol_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2polymod_t a;

	if (argc < 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		f2poly_t mp = f2pm_min_poly(a);
		if (argc > 3)
			std::cout << a << ": ";
		std::cout << mp << std::endl;
	}

	return 0;
}

static void f2pmconvert_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m1} {m2} {residues ...}\n";
	exit(1);
}

static int f2pmconvert_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m1, m2;
	f2polymod_t a1, a2, g1, g2;

	if (argc < 4)
		pusage(argv[0]);
	if (!m1.from_string(argv[1]))
		pusage(argv[0]);
	if (!m2.from_string(argv[2]))
		pusage(argv[0]);
	if (!f2polymod_find_generator(m1, g1)) {
		std::cerr << "Can't find generator mod " << m1 << ".\n";
		exit(1);
	}
	if (!f2polymod_convert_prep(g1, m2, g2)) {
		std::cerr << "Can't find generator mod " << m2 << ".\n";
		exit(1);
	}
	for (int argi = 3; argi < argc; argi++) {
		if (!a1.from_string(argv[argi], m1))
			pusage(argv[0]);
		a2 = f2polymod_convert_scalar(g1, g2, a1);
		if (argc > 4)
			std::cout << a1 << ": ";
		std::cout << a2 << std::endl;
	}

	return 0;
}

static void f2pmrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} [count]\n";
	exit(1);
}

static int f2pmrandom_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	int count = 1;

	if ((argc != 2) && (argc != 3))
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	if (argc == 3) {
		if (sscanf(argv[2], "%d", &count) != 1)
			pusage(argv[0]);
	}

	for (int i = 0; i < count; i++)
		std::cout << f2polymod_random(m) << std::endl;

	return 0;
}

static void f2pmmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
	exit(1);
}

static int f2pmmatop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m = 0;
	f2polymod_t zero, one;

	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	zero = f2polymod_t(m.prime_sfld_elt(0), m);
	one  = f2polymod_t(m.prime_sfld_elt(1), m);
	cmd_line_mat_parse<f2polymod_t>(argc-2, argv+2, zero, one);
	return 0;
}

static void f2pmvecop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
	exit(1);
}

static int f2pmvecop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m = 0;
	f2polymod_t zero, one;

	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	zero = f2polymod_t(m.prime_sfld_elt(0), m);
	one  = f2polymod_t(m.prime_sfld_elt(1), m);
	cmd_line_vec_parse<f2polymod_t>(argc-2, argv+2, zero, one);
	return 0;
}

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
	std::cout << x << std::endl;
	return 0;
}

static void f2pmmatchpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
	exit(1);
}

static int f2pmmatchpol_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	tmatrix<f2polymod_t> A;

	if (argc != 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	A = f2polymod_t(f2poly_t(0), m);
	if (!A.load_from_file(argv[2]))
		pusage(argv[0]);

	f2npoly_t chpol = f2pm_char_poly(A);
	std::cout << chpol << std::endl;

	return 0;
}

static void f2pmmatdable_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
	exit(1);
}

static int f2pmmatdable_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	tmatrix<f2polymod_t> A;

	if (argc != 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	A = f2polymod_t(f2poly_t(0), m);
	if (!A.load_from_file(argv[2]))
		pusage(argv[0]);

	f2poly_t splitter_modulus;
	tvector<f2polymod_t> eigenvalues;
	if (f2pm_matrix_is_dable(A, splitter_modulus, eigenvalues))
		std::cout << "Diagonalizable.\n";
	else
		std::cout << "Non-diagonalizable.\n";
	std::cout << std::endl;
	std::cout << "Splitter modulus: " << splitter_modulus << std::endl;
	std::cout << "Eigenvalues:\n";
	int nei = eigenvalues.get_num_elements();
	for (int i = 0; i < nei; i++) {
		std::cout << "  " << eigenvalues[i] << std::endl;
	}

	return 0;
}

static void f2pmmatord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
	exit(1);
}

static int f2pmmatord_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	tmatrix<f2polymod_t> A;

	if (argc != 2)
		pusage(argv[0]);

	if (!m.from_string(argv[1]))
		pusage(argv[0]);

	f2polymod_t zero(f2poly_t(0), m);
	f2polymod_t one (f2poly_t(1), m);

	A = zero;
	std::cin >> A;
	f2polymod_t d = A.det();

	if (d == zero) {
		std::cout << 0 << std::endl;
	}
	else {
		tmatrix<f2polymod_t> I = A.make_I(zero, one);
		int order;
		tmatrix<f2polymod_t> Apower = A;

		for (order = 1; ; order++) {
			if (Apower == I) {
				std::cout << order << std::endl;
				return 0;
			}
			Apower *= A;
		}

		std::cout << order << std::endl;
	}

	return 0;
}

static void f2pmmatrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {# rows} {# cols}\n";
	exit(1);
}

static int f2pmmatrandom_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	int nr, nc;

	if (argc != 4)
		pusage(argv[0]);

	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	if (sscanf(argv[2], "%d", &nr) != 1)
		pusage(argv[0]);
	if (sscanf(argv[3], "%d", &nc) != 1)
		pusage(argv[0]);
	tmatrix<f2polymod_t> A(nr, nc);
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			A[i][j] = f2polymod_random(m);
	std::cout << A;
	return 0;
}

static int f2prop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_parse<f2polyrat_t>(argc-1, argv+1,
		f2polyrat_t(0), f2polyrat_t(1));
	return 0;
}

static void f2prrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {deg} [count]\n";
	exit(1);
}

static int f2prrandom_main(int argc, char ** argv, usage_t * pusage)
{
	int deg, count = 1;

	if ((argc != 2) && (argc != 3))
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &deg) != 1)
		pusage(argv[0]);
	if (argc == 3) {
		if (sscanf(argv[2], "%d", &count) != 1)
			pusage(argv[0]);
	}

	f2poly_t zero(0);
	f2poly_t one(1);
	for (int i = 0; i < count; i++) {
		f2poly_t numer = f2poly_random(deg);
		f2poly_t denom = f2poly_random(deg);
		if (denom == zero)
			denom = one;
		f2polyrat_t q(numer, denom);
		std::cout << q << std::endl;
	}

	return 0;
}

static int f2prmatop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_mat_parse<f2polyrat_t>(argc-1, argv+1,
		f2polyrat_t(f2poly_t(0)), f2polyrat_t(f2poly_t(1)));
	return 0;
}

static void f2prmatrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {deg} {num_rows} {num_cols}\n";
	exit(1);
}

static int f2prmatrandom_main(int argc, char ** argv, usage_t * pusage)
{
	int deg, nr, nc;

	if (argc != 4)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &deg) != 1)
		pusage(argv[0]);
	if (sscanf(argv[2], "%d", &nr) != 1)
		pusage(argv[0]);
	if (sscanf(argv[3], "%d", &nc) != 1)
		pusage(argv[0]);

	tmatrix<f2polyrat_t> A(nr, nc);

	f2poly_t zero(0);
	f2poly_t one(1);
	for (int i = 0; i < nr; i++) {
		for (int j = 0; j < nc; j++) {
			f2poly_t numer = f2poly_random(deg);
			f2poly_t denom = f2poly_random(deg);
			if (denom == zero)
				denom = one;
			A[i][j] = f2polyrat_t(numer, denom);
		}
	}
	std::cout << A << std::endl;

	return 0;
}

static void f2nplist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {deglo[-deghi]}\n";
	exit(1);
}

int f2nplist_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	int deglo, deghi;
	if (argc != 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);

	if (sscanf(argv[2], "%d-%d", &deglo, &deghi) == 2)
		;
	else if (sscanf(argv[2], "%d", &deglo) == 1)
		deghi = deglo;
	else
		pusage(argv[0]);
	for (int deg = deglo; deg <= deghi; deg++) {
		tvector<f2npoly_t> elts = f2npoly_list(m, deg);
		elts.crout(std::cout);
	}
	return 0;
}

static void f2npop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {...}\n";
	exit(1);
}

static int f2npop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	f2npoly_t zero = f2npoly_t::prime_sfld_elt(0, m);
	f2npoly_t one  = f2npoly_t::prime_sfld_elt(1, m);
	cmd_line_parse<f2npoly_t>(argc-2, argv+2, zero, one);
	return 0;
}

static void f2npmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {...}\n";
	exit(1);
}

static int f2npmatop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	f2npoly_t zero = f2npoly_t::prime_sfld_elt(0, m);
	f2npoly_t one  = f2npoly_t::prime_sfld_elt(1, m);
	ed_cmd_line_mat_parse<f2npoly_t>(argc-2, argv+2, zero, one);
	return 0;
}

static void f2npdeg_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
	exit(1);
}

static int f2npdeg_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);

	for (int argi = 2; argi < argc; argi++) {
		f2npoly_t a;
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		if (argc > 3)
			std::cout << a << ": ";
		std::cout << a.find_degree() << std::endl;
	}
	return 0;
}

static void f2npgcd_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-e] {m} {a} {b}\n";
	exit(1);
}

static int f2npgcd_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2npoly_t a, b, g, r, s;

	if (argc == 4) {
		if (!m.from_string(argv[1]))
			pusage(argv[0]);
		if (!a.from_string(argv[2], m))
			pusage(argv[0]);
		if (!b.from_string(argv[3], m))
			pusage(argv[0]);
		g = a.gcd(b);
		std::cout << g << std::endl;

	}
	else if (argc == 5) {
		if (strcmp(argv[1], "-e") != 0)
			pusage(argv[0]);
		if (!m.from_string(argv[2]))
			pusage(argv[0]);
		if (!a.from_string(argv[3], m))
			pusage(argv[0]);
		if (!b.from_string(argv[4], m))
			pusage(argv[0]);

		g = a.ext_gcd(b, r, s);
		std::cout
			<< g << " = "
			<< r << " * "
			<< a << " + "
			<< s << " * "
			<< b << std::endl;

		f2npoly_t check = a * r + b * s;
		if (g != check) {
			std::cerr << "Coding error in extended GCD.\n";
			exit(1);
		}
	}
	else {
		pusage(argv[0]);
	}

	return 0;
}

static void f2nplcm_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
	exit(1);
}

static int f2nplcm_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2npoly_t a, l;

	if (argc < 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	if (!a.from_string(argv[2], m))
		pusage(argv[0]);
	l = a;
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		l = (l * a) / l.gcd(a);
	}
	std::cout << l << std::endl;
	return 0;
}

static void f2nptotient_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
	exit(1);
}

static int f2nptotient_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2npoly_t a;
	int phi;
	if (argc < 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		phi = f2npoly_totient(a);
		if (argc > 3)
			std::cout << a << ": ";
		std::cout << phi << std::endl;
	}
	return 0;
}

static void f2nptest_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
	exit(1);
}

static int f2nptest_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);

	for (int argi = 2; argi < argc; argi++) {
		f2npoly_t a;
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		if (argc > 3)
			std::cout << a << ": ";
		if (f2npoly_is_irreducible(a))
			std::cout << "IRREDUCIBLE\n";
		else
			std::cout << "reducible\n";
	}
	return 0;
}

static void f2npfind_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-1|-r] {m} {deglo[-deghi]}\n";
	exit(1);
}

static int f2npfind_main(int argc, char ** argv, usage_t * pusage)
{
	int do_random = 0, deglo, deghi;
	f2poly_t m;

	if (argc != 4)
		pusage(argv[0]);
	if (strcmp(argv[1], "-1") == 0)
		do_random = 0;
	else if (strcmp(argv[1], "-r") == 0)
		do_random = 1;
	else
		pusage(argv[0]);
	if (!m.from_string(argv[2]))
		pusage(argv[0]);

	if (sscanf(argv[3], "%d-%d", &deglo, &deghi) == 2)
		;
	else if (sscanf(argv[3], "%d", &deglo) == 1)
		deghi = deglo;
	else
		pusage(argv[0]);

	for (int deg = deglo; deg <= deghi; deg++) {
		f2npoly_t a;
		if (do_random)
			a = f2npoly_random_irr(m, deg);
		else
			a = f2npoly_find_irr(m, deg);
		std::cout << a << std::endl;
	}
	return 0;
}

static void f2npfactor_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
	exit(1);
}

static int f2npfactor_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);

	for (int argi = 2; argi < argc; argi++) {
		f2npoly_t a;
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		if (argc > 3)
			std::cout << a << " = ";
		tfacinfo<f2npoly_t> finfo = f2npoly_factor(a);
		std::cout << finfo << std::endl;

		f2poly_t z(1);
		f2npoly_t one(f2polymod_t(z, m));
		f2npoly_t check = finfo.unfactor(one);
		if (check != a) {
			std::cerr << "Coding error in f2npoly_factor.\n";
			std::cerr << "  Input: " << a << std::endl;
			std::cerr << "  Check: " << check << std::endl;
			std::cerr << "  Factors: " << finfo << std::endl;
			exit(1);
		}
	}
	return 0;
}

static void f2npdivisors_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-mp] {m} {polys ...}\n";
	exit(1);
}

static int f2npdivisors_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2npoly_t a;
	int argb = 1;
	int maximal_proper_only = 0;
	if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
		maximal_proper_only = 1;
		argb++;
	}
	if ((argc - argb) < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[argb]))
		pusage(argv[0]);
	argb++;
	f2polymod_t c1(f2poly_t(1), m);
	f2npoly_t one(c1);
	for (int argi = argb; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		if ((argc - argb) > 1)
			std::cout << a << ": ";
		tfacinfo<f2npoly_t> finfo = f2npoly_factor(a);
		tvector<f2npoly_t> divisors;
		if (maximal_proper_only) {
			if (!finfo.get_maximal_proper_divisors(divisors, one)) {
				std::cout << "(none)\n";
				continue;
			}
		}
		else {
			divisors = finfo.get_all_divisors(one);
		}
		int nd = divisors.get_num_elements();
		for (int k = 0; k < nd; k++) {
			if (k > 0)
				std::cout << " ";
			std::cout << divisors[k];
		}
		std::cout << std::endl;
	}
	return 0;
}

static void f2npeval_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {f} {elements of Fq ...}\n";
	exit(1);
}

static int f2npeval_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2npoly_t f;
	f2polymod_t a, b;

	if (argc < 4)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	if (!f.from_string(argv[2], m))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		b = f.eval(a);
		std::cout << b << std::endl;
	}

	return 0;
}

static void f2nprandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {deg} [count]\n";
	exit(1);
}

static int f2nprandom_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	int deg, count = 1;

	if ((argc != 3) && (argc != 4))
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	if (sscanf(argv[2], "%d", &deg) != 1)
		pusage(argv[0]);
	if (argc == 4) {
		if (sscanf(argv[3], "%d", &count) != 1)
			pusage(argv[0]);
	}

	for (int i = 0; i < count; i++)
		std::cout << f2npoly_random(m, deg) << std::endl;

	return 0;
}

static void f2npcompmx_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {poly}\n";
	exit(1);
}

static int f2npcompmx_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	f2npoly_t chpol;

	if (argc != 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	if (!chpol.from_string(argv[2], m))
		pusage(argv[0]);

	tmatrix<f2polymod_t> A = f2np_companion_matrix(chpol);
	std::cout << A << std::endl;

	return 0;
}

static void f2npqp_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {qpolys ...}\n";
	exit(1);
}

static int f2npqp_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	qpoly_t qp;
	f2npoly_t f2np;
	if (argc < 3)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!qp.from_string(argv[argi]))
			pusage(argv[0]);
		f2np = f2npoly_from_qpoly(qp, m);
		std::cout << f2np << std::endl;
	}
	return 0;
}

static void f2nprop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {...}\n";
	exit(1);
}

static int f2nprop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	f2npolyrat_t zero = f2npolyrat_t::prime_sfld_elt(0, m);
	f2npolyrat_t one  = f2npolyrat_t::prime_sfld_elt(1, m);
	cmd_line_parse<f2npolyrat_t>(argc-2, argv+2, zero, one);
	return 0;
}

static void f2npmlist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-a|-u] {im} {om}\n";
	exit(1);
}

int f2npmlist_main(int argc, char ** argv, usage_t * pusage)
{
	sp_list_type_t type = SP_LIST_ALL;
	f2poly_t  im;
	f2npoly_t om;
	if (argc != 4)
		pusage(argv[0]);
	if (strcmp(argv[1], "-a") == 0)
		type = SP_LIST_ALL;
	else if (strcmp(argv[1], "-u") == 0)
		type = SP_LIST_UNITS;
	else if (strcmp(argv[1], "-nu") == 0)
		type = SP_LIST_NON_UNITS;
	else
		pusage(argv[0]);
	if (!im.from_string(argv[2]))
		pusage(argv[0]);
	if (!om.from_string(argv[3], im))
		pusage(argv[0]);
	tvector<f2npolymod_t> elts = f2npolymod_list(om, type);
	elts.crout(std::cout);
	return 0;
}

static void f2npmop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
	exit(1);
}

static int f2npmop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t om;
	if (argc < 3)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!om.from_string(argv[2], im))
		pusage(argv[0]);
	f2npolymod_t zero = f2npolymod_t::prime_sfld_elt(0, om);
	f2npolymod_t one  = f2npolymod_t::prime_sfld_elt(1, om);
	cmd_line_parse<f2npolymod_t>(argc-3, argv+3, zero, one);
	return 0;
}


static void f2npmtbl_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0
		<< " {im} {om} {+|-|*|u*|/|log[:g]|alog[:g]}\n";
	exit(1);
}

static int f2npmtbl_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t om;
	f2npolymod_t g;
	int tbl_type = TBL_TYPE_PLUS;
	if (argc != 4)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!om.from_string(argv[2], im))
		pusage(argv[0]);

	if (strcmp(argv[3], "+") == 0)
		tbl_type = TBL_TYPE_PLUS;
	else if (strcmp(argv[3], "-") == 0)
		tbl_type = TBL_TYPE_MINUS;
	else if (strcmp(argv[3], "*") == 0)
		tbl_type = TBL_TYPE_MUL;
	else if (strcmp(argv[3], ".") == 0)
		tbl_type = TBL_TYPE_MUL;
	else if (strcmp(argv[3], "u*") == 0)
		tbl_type = TBL_TYPE_UNIT_MUL;
	else if (strcmp(argv[3], "u.") == 0)
		tbl_type = TBL_TYPE_UNIT_MUL;
	else if (strcmp(argv[3], "/") == 0)
		tbl_type = TBL_TYPE_UNIT_DIV;

	else if (strncmp(argv[3], "log:", 4) == 0) {
		if (!g.from_string(&argv[3][4], om))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strcmp(argv[3], "log") == 0) {
		if (!f2npolymod_find_generator(om, g)) {
			std::cerr << "Couldn't find generator mod "
				<< om << "\n";
			exit(1);
		}
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strncmp(argv[3], "alog:", 5) == 0) {
		if (!g.from_string(&argv[3][5], om))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_ALOG;
	}
	else if (strcmp(argv[3], "alog") == 0) {
		if (!f2npolymod_find_generator(om, g)) {
			std::cerr << "Couldn't find generator mod "
				<< om << "\n";
			exit(1);
		}
		tbl_type = TBL_TYPE_ALOG;
	}
	else
		pusage(argv[0]);

	tvector<f2npolymod_t> elts;
	if ((tbl_type == TBL_TYPE_UNIT_MUL)
	|| (tbl_type == TBL_TYPE_UNIT_DIV)
	|| (tbl_type == TBL_TYPE_LOG)
	|| (tbl_type == TBL_TYPE_ALOG))
		elts = f2npolymod_list(om, SP_LIST_UNITS);
	else
		elts = f2npolymod_list(om, SP_LIST_ALL);
	int n = elts.get_num_elements();

	if (tbl_type == TBL_TYPE_LOG) {
		std::cout << "element power\n";
		std::cout << "------- -----\n";
		for (int i = 0; i < n; i++) {
			int e = f2npolymod_log(g, elts[i]);
			std::cout << elts[i] << " " << e << "\n";
		}
		return 0;
	}
	if (tbl_type == TBL_TYPE_ALOG) {
		std::cout << "power element\n";
		std::cout << "----- -------\n";
		f2npolymod_t gp = g / g;
		for (int i = 0; i < n; i++) {
			std::cout << i << " " << gp << "\n";
			gp *= g;
		}
		return 0;
	}

	f2npolymod_t a, b, c;

	for (int i = 0; i < n; i++) {
		a = elts[i];
		for (int j = 0; j < n; j++) {
			b = elts[j];
			switch (tbl_type) {
			case TBL_TYPE_PLUS:     c = a + b; break;
			case TBL_TYPE_MINUS:    c = a - b; break;
			case TBL_TYPE_MUL:      c = a * b; break;
			case TBL_TYPE_UNIT_MUL: c = a * b; break;
			case TBL_TYPE_UNIT_DIV: c = a / b; break;
			}
			if (j > 0)
				std::cout << " ";
			std::cout << c;
		}
		std::cout << "\n";
	}

	return 0;
}

static void f2npmord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {om} {a}\n";
	exit(1);
}

static int f2npmord_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t om;
	f2npolymod_t a;
	if (argc < 4)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!om.from_string(argv[2], im))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], om))
			pusage(argv[0]);
		if (argc > 4)
			std::cout << a << ": ";
		std::cout << f2npolymod_order(a) << "\n";
	}
	return 0;
}

static void f2npmfindgen_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {om}\n";
	exit(1);
}

static int f2npmfindgen_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t om;
	f2npolymod_t g;
	int rv = 0;
	if (argc < 3)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!om.from_string(argv[argi], im))
			pusage(argv[0]);
		if (argc > 3)
			std::cout << om << ": ";
		if (f2npolymod_find_generator(om, g)) {
			std::cout << g << "\n";
		}
		else {
			std::cout << "Generator not found.\n";
			rv = 1;
		}
	}
	return rv;
}

static void f2npmlog_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {om} {g} {a}\n";
	exit(1);
}

static int f2npmlog_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t om;
	f2npolymod_t g, a;
	if (argc < 5)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!om.from_string(argv[2], im))
		pusage(argv[0]);
	if (!g.from_string(argv[3], om))
		pusage(argv[0]);
	for (int argi = 4; argi < argc; argi++) {
		if (!a.from_string(argv[argi], om))
			pusage(argv[0]);
		if (argc > 5)
			std::cout << a << ": ";
		std::cout << f2npolymod_log(g, a) << "\n";
	}
	return 0;
}

static void f2npmchpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {m} {residues ...}\n";
	exit(1);
}

static int f2npmchpol_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t m;
	f2npolymod_t a;

	if (argc < 4)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!m.from_string(argv[2], im))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		f2npoly_t cp = f2npm_char_poly(a);
		if (argc > 4)
			std::cout << a << ": ";
		std::cout << cp << "\n";
	}

	return 0;
}

static void f2npmminpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {m} {residues ...}\n";
	exit(1);
}

static int f2npmminpol_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t m;
	f2npolymod_t a;

	if (argc < 4)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!m.from_string(argv[2], im))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		f2npoly_t mp = f2npm_min_poly(a);
		if (argc > 4)
			std::cout << a << ": ";
		std::cout << mp << "\n";
	}

	return 0;
}

static void f2npmrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} [count]\n";
	exit(1);
}

static int f2npmrandom_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t om;
	int count = 1;

	if ((argc != 3) && (argc != 4))
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!om.from_string(argv[2], im))
		pusage(argv[0]);
	if (argc == 4) {
		if (sscanf(argv[3], "%d", &count) != 1)
			pusage(argv[0]);
	}

	for (int i = 0; i < count; i++)
		std::cout << f2npolymod_random(im, om) << std::endl;

	return 0;
}

static void f2npmmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
	exit(1);
}

static int f2npmmatop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t om;
	if (argc < 3)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!om.from_string(argv[2], im))
		pusage(argv[0]);
	f2npolymod_t zero = f2npolymod_t::prime_sfld_elt(0, om);
	f2npolymod_t one  = f2npolymod_t::prime_sfld_elt(1, om);
	cmd_line_mat_parse<f2npolymod_t>(argc-3, argv+3, zero, one);
	return 0;
}

static void f2npmvecop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
	exit(1);
}

static int f2npmvecop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t om;
	if (argc < 3)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!om.from_string(argv[2], im))
		pusage(argv[0]);
	f2npolymod_t zero = f2npolymod_t::prime_sfld_elt(0, om);
	f2npolymod_t one  = f2npolymod_t::prime_sfld_elt(1, om);
	cmd_line_vec_parse<f2npolymod_t>(argc-3, argv+3, zero, one);
	return 0;
}

static void f2npmmatrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0
		<< " {inner m} {outer m} {# rows} {# cols}\n";
	exit(1);
}

static int f2npmmatrandom_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t im;
	f2npoly_t om;
	int nr, nc;

	if (argc != 5)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!om.from_string(argv[2], im))
		pusage(argv[0]);
	if (sscanf(argv[3], "%d", &nr) != 1)
		pusage(argv[0]);
	if (sscanf(argv[4], "%d", &nc) != 1)
		pusage(argv[0]);

	tmatrix<f2npolymod_t> A(nr, nc);
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			A[i][j] = f2npolymod_random(im, om);
	std::cout << A << "\n";

	return 0;
}

static void f2nprmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {inner m} {...}\n";
	exit(1);
}

static int f2nprmatop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	f2npolyrat_t zero = f2npolyrat_t::prime_sfld_elt(0, m);
	f2npolyrat_t one  = f2npolyrat_t::prime_sfld_elt(1, m);
	cmd_line_mat_parse<f2npolyrat_t>(argc-2, argv+2, zero, one);
	return 0;
}

static void fplist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-a|-u] {p}\n";
	exit(1);
}

int fplist_main(int argc, char ** argv, usage_t * pusage)
{
	sp_list_type_t type = SP_LIST_ALL;
	int m;
	// -g
	// -o {spec}
	if (argc == 3) {
		if (strcmp(argv[1], "-a") == 0)
			type = SP_LIST_ALL;
		else if (strcmp(argv[1], "-u") == 0)
			type = SP_LIST_UNITS;
		else if (strcmp(argv[1], "-nu") == 0)
			type = SP_LIST_NON_UNITS;
		else
			pusage(argv[0]);
		if (sscanf(argv[2], "%d", &m) != 1)
			pusage(argv[0]);
		tvector<intmod_t> elts = intmod_list(m, type);
		elts.crout(std::cout);
	}
	else if (argc == 4) {
		intmod_t g;
		if (strcmp(argv[1], "-m") == 0)
			type = SP_LIST_MULTIPLES;
		else if (strcmp(argv[1], "-rp") == 0)
			type = SP_LIST_REL_PRIME;
		else
			pusage(argv[0]);
		if (sscanf(argv[3], "%d", &m) != 1)
			pusage(argv[0]);
		if (!g.from_string(argv[2], m))
			pusage(argv[0]);
		tvector<intmod_t> elts = intmod_glist(g, type);
		elts.crout(std::cout);
	}
	else {
		pusage(argv[0]);
	}
	return 0;
}
static void fpop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {...}\n";
	exit(1);
}

static int fpop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	cmd_line_parse<intmod_t>(argc-2, argv+2,
		intmod_t(0, p), intmod_t(1, p));
	return 0;
}

static void fptbl_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {+|-|*|u*|/|log[:g]|alog[:g]}\n";
	exit(1);
}

static int fptbl_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	int tbl_type = TBL_TYPE_PLUS;
	intmod_t g;

	if (argc != 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);

	if (strcmp(argv[2], "+") == 0)
		tbl_type = TBL_TYPE_PLUS;
	else if (strcmp(argv[2], "-") == 0)
		tbl_type = TBL_TYPE_MINUS;
	else if (strcmp(argv[2], "*") == 0)
		tbl_type = TBL_TYPE_MUL;
	else if (strcmp(argv[2], ".") == 0)
		tbl_type = TBL_TYPE_MUL;
	else if (strcmp(argv[2], "u*") == 0)
		tbl_type = TBL_TYPE_UNIT_MUL;
	else if (strcmp(argv[2], "u.") == 0)
		tbl_type = TBL_TYPE_UNIT_MUL;
	else if (strcmp(argv[2], "/") == 0)
		tbl_type = TBL_TYPE_UNIT_DIV;

	else if (strncmp(argv[2], "log:", 4) == 0) {
		if (!g.from_string(&argv[2][4], p))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strcmp(argv[2], "log") == 0) {
		if (!fp_find_generator(p, g)) {
			std::cerr << "Couldn't find generator mod "
				<< p << "\n";
			exit(1);
		}
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strncmp(argv[2], "alog:", 5) == 0) {
		if (!g.from_string(&argv[2][5], p))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_ALOG;
	}
	else if (strcmp(argv[2], "alog") == 0) {
		if (!fp_find_generator(p, g)) {
			std::cerr << "Couldn't find generator mod "
				<< p << "\n";
			exit(1);
		}
		tbl_type = TBL_TYPE_ALOG;
	}
	else
		pusage(argv[0]);

	tvector<intmod_t> elts;
	if ((tbl_type == TBL_TYPE_UNIT_MUL)
	|| (tbl_type == TBL_TYPE_UNIT_DIV)
	|| (tbl_type == TBL_TYPE_LOG)
	|| (tbl_type == TBL_TYPE_ALOG))
		elts = intmod_list(p, SP_LIST_UNITS);
	else
		elts = intmod_list(p, SP_LIST_ALL);
	int n = elts.get_num_elements();

	if (tbl_type == TBL_TYPE_LOG) {
		std::cout << "element power\n";
		std::cout << "------- -----\n";
		for (int i = 0; i < n; i++) {
			int e = fp_log(g, elts[i]);
			std::cout << elts[i] << " " << e << "\n";
		}
		return 0;
	}
	if (tbl_type == TBL_TYPE_ALOG) {
		std::cout << "power element\n";
		std::cout << "----- -------\n";
		intmod_t gp = g / g;
		for (int i = 0; i < n; i++) {
			std::cout << i << " " << gp << "\n";
			gp *= g;
		}
		return 0;
	}

	intmod_t a, b, c;

	for (int i = 0; i < n; i++) {
		a = elts[i];
		for (int j = 0; j < n; j++) {
			b = elts[j];
			switch (tbl_type) {
			case TBL_TYPE_PLUS:     c = a + b; break;
			case TBL_TYPE_MINUS:    c = a - b; break;
			case TBL_TYPE_MUL:      c = a * b; break;
			case TBL_TYPE_UNIT_MUL: c = a * b; break;
			case TBL_TYPE_UNIT_DIV: c = a / b; break;
			}
			if (j > 0)
				std::cout << " ";
			std::cout << c;
		}
		std::cout << "\n";
	}

	return 0;
}

static void fpord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {a}\n";
	exit(1);
}

static int fpord_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	intmod_t a;
	if (argc < 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!a.from_string(argv[argi], p))
			pusage(argv[0]);
		if (argc > 3)
			std::cout << a << ": ";
		std::cout << fp_order(a) << "\n";
	}
	return 0;
}

static void fpmaxord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p}\n";
	exit(1);
}

static int fpmaxord_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	if (argc != 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	tvector<intmod_t> elts = intmod_list(p, SP_LIST_UNITS);
	int n = elts.get_num_elements();
	int max = 0;
	for (int i = 0; i < n; i++) {
		int cur = fp_order(elts[i]);
		if (cur > max)
			max = cur;
	}
	std::cout << max << "\n";
	return 0;
}

static void fporbit_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {a} [a0]\n";
	exit(1);
}

static int fporbit_main(int argc, char ** argv, usage_t * pusage)
{
	int p, a, apower;
	int a0 = 1;
	if ((argc != 3) && (argc != 4))
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (sscanf(argv[2], "%d", &a) != 1)
		pusage(argv[0]);
	if (argc == 4) {
		if (sscanf(argv[3], "%d", &a0) != 1)
			pusage(argv[0]);
	}
	if (gcd(a, p) != 1) {
		std::cerr << "fporbit_main: a must be coprime to p.\n";
		exit(1);
	}

	a  %= p;
	a0 %= p;
	apower = a;

	int counter = 0;
	while (1) {
		std::cout << ((apower*a0)%p) << "\n";

		if (apower == 1)
			break;

		counter++;
		if (counter > p) {
			std::cerr << "Internal error finding orbit of "
				<< a0 << " mod " << p << "\n";
			exit(1);
		}

		apower = (apower * a) % p;
	}

	return 0;
}

static void fpfindgen_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p}\n";
	exit(1);
}

static int fpfindgen_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	intmod_t g;
	int rv = 0;
	if (argc < 2)
		pusage(argv[0]);
	for (int argi = 1; argi < argc; argi++) {
		if (sscanf(argv[argi], "%d", &p) != 1)
			pusage(argv[0]);
		if (argc > 2)
			std::cout << p << ": ";
		if (fp_find_generator(p, g)) {
			std::cout << g << "\n";
		}
		else {
			std::cout << "Generator not found.\n";
			rv = 1;
		}
	}
	return rv;
}

static void fplog_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {g} {a}\n";
	exit(1);
}

static int fplog_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	intmod_t g, a;
	if (argc < 4)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!g.from_string(argv[2], p))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], p))
			pusage(argv[0]);
		if (argc > 4)
			std::cout << a << ": ";
		std::cout << fp_log(g, a) << "\n";
	}
	return 0;
}

static void fprandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} [count]\n";
	exit(1);
}

static int fprandom_main(int argc, char ** argv, usage_t * pusage)
{
	int m, count = 1;

	if ((argc != 2) && (argc != 3))
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &m) != 1)
		pusage(argv[0]);
	if (argc == 3) {
		if (sscanf(argv[2], "%d", &count) != 1)
			pusage(argv[0]);
	}

	for (int i = 0; i < count; i++)
		std::cout << intmod_random(m) << std::endl;

	return 0;
}

static void fpmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
	exit(1);
}

static int fpmatop_main(int argc, char ** argv, usage_t * pusage)
{
	int p = 0;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	cmd_line_mat_parse<intmod_t>(argc-2, argv+2,
		intmod_t(0, p), intmod_t(1, p));
	return 0;
}

static void fpvecop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
	exit(1);
}

static int fpvecop_main(int argc, char ** argv, usage_t * pusage)
{
	int p = 0;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	cmd_line_vec_parse<intmod_t>(argc-2, argv+2,
		intmod_t(0, p), intmod_t(1, p));
	return 0;
}

static void fpmatchpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
	exit(1);
}

static int fpmatchpol_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	tmatrix<intmod_t> A;

	if (argc != 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	A = intmod_t(0, p);
	if (!A.load_from_file(argv[2]))
		pusage(argv[0]);

	fppoly_t chpol = fp_char_poly(A);
	std::cout << chpol << std::endl;

	return 0;
}

static void fpmatord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
	exit(1);
}

static int fpmatord_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	tmatrix<intmod_t> A;

	if (argc != 2)
		pusage(argv[0]);

	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	intmod_t zero(0, p);
	intmod_t one (1, p);

	A = zero;
	std::cin >> A;
	intmod_t d = A.det();

	if (d == zero) {
		std::cout << 0 << std::endl;
	}
	else {
		tmatrix<intmod_t> I = A.make_I(zero, one);
		int order;
		tmatrix<intmod_t> Apower = A;

		for (order = 1; ; order++) {
			if (Apower == I) {
				std::cout << order << std::endl;
				return 0;
			}
			Apower *= A;
		}

		std::cout << order << std::endl;
	}

	return 0;
}

static void fpmatrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {# rows} {# cols}\n";
	exit(1);
}

static int fpmatrandom_main(int argc, char ** argv, usage_t * pusage)
{
	int p, nr, nc;

	if (argc != 4)
		pusage(argv[0]);

	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (sscanf(argv[2], "%d", &nr) != 1)
		pusage(argv[0]);
	if (sscanf(argv[3], "%d", &nc) != 1)
		pusage(argv[0]);
	tmatrix<intmod_t> A(nr, nc);
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			A[i][j] = intmod_random(p);
	std::cout << A;
	return 0;
}

static void fpplist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {deglo[-deghi]}\n";
	exit(1);
}

int fpplist_main(int argc, char ** argv, usage_t * pusage)
{
	int p, deglo, deghi;
	if (argc != 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (sscanf(argv[2], "%d-%d", &deglo, &deghi) == 2)
		;
	else if (sscanf(argv[2], "%d", &deglo) == 1)
		deghi = deglo;
	else
		pusage(argv[0]);
	for (int deg = deglo; deg <= deghi; deg++) {
		tvector<fppoly_t> elts = fppoly_list(p, deg);
		elts.crout(std::cout);
	}
	return 0;
}

static void fppop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
	exit(1);
}

static int fppop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	cmd_line_parse<fppoly_t>(argc-2, argv+2,
		fppoly_t(0, p), fppoly_t(1, p));
	return 0;
}

static void fppmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
	exit(1);
}

static int fppmatop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	ed_cmd_line_mat_parse<fppoly_t>(argc-2, argv+2,
		fppoly_t(0, p), fppoly_t(1, p));
	return 0;
}

static void fppcompmx_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {poly}\n";
	exit(1);
}

static int fppcompmx_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t chpol;

	if (argc != 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!chpol.from_string(argv[2], p))
		pusage(argv[0]);

	tmatrix<intmod_t> A = fp_companion_matrix(chpol);
	std::cout << A << "\n";

	return 0;
}

static void fppdeg_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
	exit(1);
}

static int fppdeg_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);

	for (int argi = 2; argi < argc; argi++) {
		fppoly_t a;
		if (!a.from_string(argv[argi], p))
			pusage(argv[0]);
		if (argc > 3)
			std::cout << a << ": ";
		std::cout << a.find_degree() << "\n";
	}
	return 0;
}

static void fppgcd_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} [-e] {a} {b}\n";
	exit(1);
}

static int fppgcd_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t a, b, g, r, s;

	if (argc == 4) {
		if (sscanf(argv[1], "%d", &p) != 1)
			pusage(argv[0]);
		if (!a.from_string(argv[2], p))
			pusage(argv[0]);
		if (!b.from_string(argv[3], p))
			pusage(argv[0]);
		g = a.gcd(b);
		std::cout << g << std::endl;
	}
	else if (argc == 5) {
		if (strcmp(argv[1], "-e") != 0)
			pusage(argv[0]);
		if (sscanf(argv[2], "%d", &p) != 1)
			pusage(argv[0]);
		if (!a.from_string(argv[3], p))
			pusage(argv[0]);
		if (!b.from_string(argv[4], p))
			pusage(argv[0]);
		g = a.ext_gcd(b, r, s);
		std::cout
			<< g << " = "
			<< r << " * "
			<< a << " + "
			<< s << " * "
			<< b << std::endl;
	}
	else {
		pusage(argv[0]);
	}

	return 0;
}

static void fpplcm_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
	exit(1);
}

static int fpplcm_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t a, l;

	if (argc < 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!a.from_string(argv[2], p))
		pusage(argv[0]);
	l = a;
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], p))
			pusage(argv[0]);
		l = (l * a) / l.gcd(a);
	}
	std::cout << l << std::endl;
	return 0;
}

static void fpptotient_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
	exit(1);
}

static int fpptotient_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t a;
	int phi;
	if (argc < 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!a.from_string(argv[argi], p))
			pusage(argv[0]);
		phi = fppoly_totient(a);
		if (argc > 3)
			std::cout << a << ": ";
		std::cout << phi << std::endl;
	}
	return 0;
}

static void fpptest_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
	exit(1);
}

static int fpptest_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);

	for (int argi = 2; argi < argc; argi++) {
		fppoly_t a;
		if (!a.from_string(argv[argi], p))
			pusage(argv[0]);
		if (argc > 3)
			std::cout << a << ": ";
		if (fppoly_is_irreducible(a))
			std::cout << "IRREDUCIBLE\n";
		else
			std::cout << "reducible\n";
	}
	return 0;
}

static void fppfind_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-1|-r] {p} {deglo[-deghi]}\n";
	exit(1);
}

static int fppfind_main(int argc, char ** argv, usage_t * pusage)
{
	int do_random = 0, deglo, deghi;
	int p;

	if (argc != 4)
		pusage(argv[0]);
	if (strcmp(argv[1], "-1") == 0)
		do_random = 0;
	else if (strcmp(argv[1], "-r") == 0)
		do_random = 1;
	else
		pusage(argv[0]);
	if (sscanf(argv[2], "%d", &p) != 1)
		pusage(argv[0]);

	if (sscanf(argv[3], "%d-%d", &deglo, &deghi) == 2)
		;
	else if (sscanf(argv[3], "%d", &deglo) == 1)
		deghi = deglo;
	else
		pusage(argv[0]);

	for (int deg = deglo; deg <= deghi; deg++) {
		fppoly_t a;
		if (do_random)
			a = fppoly_random_irr(p, deg);
		else
			a = fppoly_find_irr(p, deg);
		std::cout << a << "\n";
	}
	return 0;
}

static void fppfactor_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
	exit(1);
}

static int fppfactor_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t a;

	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);

	for (int argi = 2; argi < argc; argi++) {
		if (!a.from_string(argv[argi], p))
			pusage(argv[0]);
		if (argc > 3)
			std::cout << a << " = ";
		tfacinfo<fppoly_t> finfo = fppoly_factor(a);
		std::cout << finfo << "\n";

		fppoly_t check = finfo.unfactor(fppoly_t(intmod_t(1, p)));
		if (check != a) {
			std::cerr << "Coding error in fppoly_factor.\n";
			std::cerr << "  Input: " << a << "\n";
			std::cerr << "  Check: " << check << "\n";
			std::cerr << "  Factors: " << finfo << "\n";
			exit(1);
		}
	}
	return 0;
}

static void fppdivisors_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-mp] {p} {polys ...}\n";
	exit(1);
}

static int fppdivisors_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t a;
	int argb = 1;
	int maximal_proper_only = 0;
	if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
		maximal_proper_only = 1;
		argb++;
	}
	if ((argc - argb) < 2)
		pusage(argv[0]);
	if (sscanf(argv[argb], "%d", &p) != 1)
		pusage(argv[0]);
	argb++;
	fppoly_t one(intmod_t(1, p));
	for (int argi = argb; argi < argc; argi++) {
		if (!a.from_string(argv[argi], p))
			pusage(argv[0]);
		if ((argc - argb) > 1)
			std::cout << a << ": ";
		tfacinfo<fppoly_t> finfo = fppoly_factor(a);
		tvector<fppoly_t> divisors;
		if (maximal_proper_only) {
			if (!finfo.get_maximal_proper_divisors(divisors, one)) {
				std::cout << "(none)\n";
				continue;
			}
		}
		else {
			divisors = finfo.get_all_divisors(one);
		}
		int nd = divisors.get_num_elements();
		for (int k = 0; k < nd; k++) {
			if (k > 0)
				std::cout << " ";
			std::cout << divisors[k];
		}
		std::cout << "\n";
	}
	return 0;
}

static void fppeval_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {f} {elements of Fp ...}\n";
	exit(1);
}

static int fppeval_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t f;
	intmod_t a, b;

	if (argc < 4)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!f.from_string(argv[2], p))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], p))
			pusage(argv[0]);
		b = f.eval(a);
		std::cout << b << "\n";
	}

	return 0;
}

static void fpprandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {deg} [count]\n";
	exit(1);
}

static int fpprandom_main(int argc, char ** argv, usage_t * pusage)
{
	int p, deg, count = 1;

	if ((argc != 3) && (argc != 4))
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (sscanf(argv[2], "%d", &deg) != 1)
		pusage(argv[0]);
	if (argc == 4) {
		if (sscanf(argv[3], "%d", &count) != 1)
			pusage(argv[0]);
	}

	for (int i = 0; i < count; i++)
		std::cout << fppoly_random(p, deg) << std::endl;

	return 0;
}

static void fppqp_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {qpolys ...}\n";
	exit(1);
}

static int fppqp_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	qpoly_t qp;
	fppoly_t fpp;
	if (argc < 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	for (int argi = 2; argi < argc; argi++) {
		if (!qp.from_string(argv[argi]))
			pusage(argv[0]);
		fpp = fppoly_from_qpoly(qp, p);
		std::cout << fpp << "\n";
	}
	return 0;
}

static void fppmlist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-a|-u] {p} {m}\n";
	exit(1);
}

int fppmlist_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;
	sp_list_type_t type = SP_LIST_ALL;
	if (argc != 4)
		pusage(argv[0]);
	if (strcmp(argv[1], "-a") == 0)
		type = SP_LIST_ALL;
	else if (strcmp(argv[1], "-u") == 0)
		type = SP_LIST_UNITS;
	else if (strcmp(argv[1], "-nu") == 0)
		type = SP_LIST_NON_UNITS;
	else
		pusage(argv[0]);
	if (sscanf(argv[2], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[3], p))
		pusage(argv[0]);
	tvector<fppolymod_t> elts = fppolymod_list(m, type);
	elts.crout(std::cout);
	return 0;
}

static void fppmop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {m} {...}\n";
	exit(1);
}

static int fppmop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;

	if (argc < 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);
	cmd_line_parse<fppolymod_t>(argc-3, argv+3,
		fppolymod_t::prime_sfld_elt(0, m),
		fppolymod_t::prime_sfld_elt(1, m));
	return 0;
}

static void fppmtbl_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {m} {+|-|*|u*|/}\n";
	exit(1);
}

static int fppmtbl_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;
	fppolymod_t g;

	int tbl_type = TBL_TYPE_PLUS;
	if (argc != 4)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);

	if (strcmp(argv[3], "+") == 0)
		tbl_type = TBL_TYPE_PLUS;
	else if (strcmp(argv[3], "-") == 0)
		tbl_type = TBL_TYPE_MINUS;
	else if (strcmp(argv[3], "*") == 0)
		tbl_type = TBL_TYPE_MUL;
	else if (strcmp(argv[3], ".") == 0)
		tbl_type = TBL_TYPE_MUL;
	else if (strcmp(argv[3], "u*") == 0)
		tbl_type = TBL_TYPE_UNIT_MUL;
	else if (strcmp(argv[3], "u.") == 0)
		tbl_type = TBL_TYPE_UNIT_MUL;
	else if (strcmp(argv[3], "/") == 0)
		tbl_type = TBL_TYPE_UNIT_DIV;

#if 0
	else if (strncmp(argv[3], "log:", 4) == 0) {
		if (!g.from_string(&argv[3][4], m))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strcmp(argv[3], "log") == 0) {
		if (!fppolymod_find_generator(m, g)) {
			std::cerr << "Couldn't find generator mod "
				<< m << "\n";
			exit(1);
		}
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strncmp(argv[3], "alog:", 5) == 0) {
		if (!g.from_string(&argv[3][5], m))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_ALOG;
	}
	else if (strcmp(argv[3], "alog") == 0) {
		if (!fppolymod_find_generator(m, g)) {
			std::cerr << "Couldn't find generator mod "
				<< m << "\n";
			exit(1);
		}
		tbl_type = TBL_TYPE_ALOG;
	}
#endif
	else
		pusage(argv[0]);

	tvector<fppolymod_t> elts;
	if ((tbl_type == TBL_TYPE_UNIT_MUL)
	|| (tbl_type == TBL_TYPE_UNIT_DIV)
	|| (tbl_type == TBL_TYPE_LOG)
	|| (tbl_type == TBL_TYPE_ALOG))
		elts = fppolymod_list(m, SP_LIST_UNITS);
	else
		elts = fppolymod_list(m, SP_LIST_ALL);
	int n = elts.get_num_elements();

#if 0
	if (tbl_type == TBL_TYPE_LOG) {
		std::cout << "element power\n";
		std::cout << "------- -----\n";
		for (int i = 0; i < n; i++) {
			int e = fppolymod_log(g, elts[i]);
			std::cout << elts[i] << " " << e << "\n";
		}
		return 0;
	}
	if (tbl_type == TBL_TYPE_ALOG) {
		std::cout << "power element\n";
		std::cout << "----- -------\n";
		fppolymod_t gp = g / g;
		for (int i = 0; i < n; i++) {
			std::cout << i << " " << gp << "\n";
			gp *= g;
		}
		return 0;
	}
#endif

	fppolymod_t a, b, c;

	for (int i = 0; i < n; i++) {
		a = elts[i];
		for (int j = 0; j < n; j++) {
			b = elts[j];
			switch (tbl_type) {
			case TBL_TYPE_PLUS:     c = a + b; break;
			case TBL_TYPE_MINUS:    c = a - b; break;
			case TBL_TYPE_MUL:      c = a * b; break;
			case TBL_TYPE_UNIT_MUL: c = a * b; break;
			case TBL_TYPE_UNIT_DIV: c = a / b; break;
			}
			if (j > 0)
				std::cout << " ";
			std::cout << c;
		}
		std::cout << "\n";
	}

	return 0;
}

static int fppmmatop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;

	if (argc < 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);
	cmd_line_mat_parse<fppolymod_t>(argc-3, argv+3,
		fppolymod_t::prime_sfld_elt(0, m),
		fppolymod_t::prime_sfld_elt(1, m));
	return 0;
}

static int fppmvecop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;

	if (argc < 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);
	cmd_line_vec_parse<fppolymod_t>(argc-3, argv+3,
		fppolymod_t::prime_sfld_elt(0, m),
		fppolymod_t::prime_sfld_elt(1, m));
	return 0;
}

static void fppmmatord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {m} {goes here}\n";
	exit(1);
}

static int fppmmatord_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;

	if ((argc != 3) && (argc != 4))
		pusage(argv[0]);

	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);

	fppolymod_t zero = fppolymod_t::prime_sfld_elt(0, m);
	fppolymod_t one  = fppolymod_t::prime_sfld_elt(1, m);

	tmatrix<fppolymod_t> A;
	A = zero;
	std::cin >> A;
	fppolymod_t d = A.det();

	if (d == zero) {
		std::cout << 0 << std::endl;
	}
	else {
		tmatrix<fppolymod_t> I = A.make_I(zero, one);
		int order;
		tmatrix<fppolymod_t> Apower = A;

		for (order = 1; ; order++) {
			if (Apower == I) {
				std::cout << order << std::endl;
				return 0;
			}
			Apower *= A;
		}

		std::cout << order << std::endl;
	}

	return 0;
}

static void fppmmatrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {m} {# rows} {# cols}\n";
	exit(1);
}

static int fppmmatrandom_main(int argc, char ** argv, usage_t * pusage)
{
	int p, nr, nc;
	fppoly_t m;

	if (argc != 5)
		pusage(argv[0]);

	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);
	if (sscanf(argv[3], "%d", &nr) != 1)
		pusage(argv[0]);
	if (sscanf(argv[4], "%d", &nc) != 1)
		pusage(argv[0]);

	tmatrix<fppolymod_t> A(nr, nc);
	for (int i = 0; i < nr; i++)
		for (int j = 0; j < nc; j++)
			A[i][j] = fppolymod_random(m);
	std::cout << A;
	return 0;
}

static void fppmord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {m} {a}\n";
	exit(1);
}

static int fppmord_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;
	fppolymod_t a;

	if (argc != 4)
		pusage(argv[0]);

	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);
	if (!a.from_string(argv[3], m))
		pusage(argv[0]);

	fppolymod_t ai;
	if (!a.recip(ai)) {
		std::cout << 0 << std::endl;
		return 0;
	}

	fppolymod_t zero(intmod_t(0, p), m);
	fppolymod_t one (intmod_t(1, p), m);
	int order;
	fppolymod_t apower = a;

	for (order = 1; ; order++) {
		if (apower == one) {
			std::cout << order << std::endl;
			return 0;
		}
		apower *= a;
	}

	std::cout << order << std::endl;

	return 0;
}

static void fppmchpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {m} {residues ...}\n";
	exit(1);
}

static int fppmchpol_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;
	fppolymod_t a;

	if (argc < 4)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		fppoly_t cp = fppm_char_poly(a);
		if (argc > 4)
			std::cout << a << ": ";
		std::cout << cp << "\n";
	}

	return 0;
}

static void fppmminpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {m} {residues ...}\n";
	exit(1);
}

static int fppmminpol_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;
	fppolymod_t a;

	if (argc < 4)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!a.from_string(argv[argi], m))
			pusage(argv[0]);
		fppoly_t cp = fppm_min_poly(a);
		if (argc > 4)
			std::cout << a << ": ";
		std::cout << cp << "\n";
	}

	return 0;
}

static void fppmrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {m} [count]\n";
	exit(1);
}

static int fppmrandom_main(int argc, char ** argv, usage_t * pusage)
{
	int p, count = 1;
	fppoly_t m;

	if ((argc != 3) && (argc != 4))
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);
	if (argc == 4) {
		if (sscanf(argv[3], "%d", &count) != 1)
			pusage(argv[0]);
	}

	for (int i = 0; i < count; i++)
		std::cout << fppolymod_random(m) << std::endl;

	return 0;
}

static void fpprop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {...}\n";
	exit(1);
}

static int fpprop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	cmd_line_parse<fppolyrat_t>(argc-2, argv+2,
		fppolyrat_t::prime_sfld_elt(0, p),
		fppolyrat_t::prime_sfld_elt(1, p));
	return 0;
}

static void fpprmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {...}\n";
	exit(1);
}

static int fpprmatop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	if (argc < 2)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	cmd_line_mat_parse<fppolyrat_t>(argc-2, argv+2,
		fppolyrat_t::prime_sfld_elt(0, p),
		fppolyrat_t::prime_sfld_elt(1, p));
	return 0;
}

// ----------------------------------------------------------------
static void fpnpop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {im} {...}\n";
	exit(1);
}

static int fpnpop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t im;
	if (argc < 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!im.from_string(argv[2], p))
		pusage(argv[0]);
	fpnpoly_t zero = fpnpoly_t::prime_sfld_elt(0, im);
	fpnpoly_t one  = fpnpoly_t::prime_sfld_elt(1, im);
	cmd_line_parse<fpnpoly_t>(argc-3, argv+3, zero, one);
	return 0;
}

// ----------------------------------------------------------------
static void fpnpmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {im} {...}\n";
	exit(1);
}

static int fpnpmatop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t im;
	if (argc < 3)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!im.from_string(argv[2], p))
		pusage(argv[0]);
	fpnpoly_t zero = fpnpoly_t::prime_sfld_elt(0, im);
	fpnpoly_t one  = fpnpoly_t::prime_sfld_elt(1, im);
	ed_cmd_line_mat_parse<fpnpoly_t>(argc-3, argv+3, zero, one);
	return 0;
}

static void fpnpgcd_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " [-e] {p} {im} {a} {b}\n";
	exit(1);
}

static int fpnpgcd_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t im;
	fpnpoly_t a, b, g, r, s;

	if (argc == 5) {
		if (sscanf(argv[1], "%d", &p) != 1)
			pusage(argv[0]);
		if (!im.from_string(argv[2], p))
			pusage(argv[0]);
		if (!a.from_string(argv[3], im))
			pusage(argv[0]);
		if (!b.from_string(argv[4], im))
			pusage(argv[0]);
		g = a.gcd(b);
		std::cout << g << std::endl;
	}
	else if (argc == 6) {
		if (strcmp(argv[1], "-e") != 0)
			pusage(argv[0]);
		if (sscanf(argv[2], "%d", &p) != 1)
			pusage(argv[0]);
		if (!im.from_string(argv[3], p))
			pusage(argv[0]);
		if (!a.from_string(argv[4], im))
			pusage(argv[0]);
		if (!b.from_string(argv[5], im))
			pusage(argv[0]);
		g = a.ext_gcd(b, r, s);
		std::cout
			<< g << " = "
			<< r << " * "
			<< a << " + "
			<< s << " * "
			<< b << std::endl;
	}
	else {
		pusage(argv[0]);
	}

	return 0;
}

static void fpnpqp_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {m} {qpolys ...}\n";
	exit(1);
}

static int fpnpqp_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t m;
	qpoly_t qp;
	fpnpoly_t fpnp;
	if (argc < 4)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!m.from_string(argv[2], p))
		pusage(argv[0]);
	for (int argi = 3; argi < argc; argi++) {
		if (!qp.from_string(argv[argi]))
			pusage(argv[0]);
		fpnp = fpnpoly_from_qpoly(qp, m);
		std::cout << fpnp << "\n";
	}
	return 0;
}

// ----------------------------------------------------------------
static void fpnpmop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
	exit(1);
}

static int fpnpmop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t im;
	fpnpoly_t om;
	if (argc < 4)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!im.from_string(argv[2], p))
		pusage(argv[0]);
	if (!om.from_string(argv[3], im))
		pusage(argv[0]);
	fpnpolymod_t zero = fpnpolymod_t::prime_sfld_elt(0, om);
	fpnpolymod_t one  = fpnpolymod_t::prime_sfld_elt(1, om);
	cmd_line_parse<fpnpolymod_t>(argc-4, argv+4, zero, one);
	return 0;
}

// ----------------------------------------------------------------
static void fpnpmmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
	exit(1);
}

static int fpnpmmatop_main(int argc, char ** argv, usage_t * pusage)
{
	int p;
	fppoly_t im;
	fpnpoly_t om;
	if (argc < 4)
		pusage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		pusage(argv[0]);
	if (!im.from_string(argv[2], p))
		pusage(argv[0]);
	if (!om.from_string(argv[3], im))
		pusage(argv[0]);
	fpnpolymod_t zero = fpnpolymod_t::prime_sfld_elt(0, om);
	fpnpolymod_t one  = fpnpolymod_t::prime_sfld_elt(1, om);
	cmd_line_mat_parse<fpnpolymod_t>(argc-4, argv+4, zero, one);
	return 0;
}

// ================================================================
typedef struct _lookup_t {
	const char * name;
	main_t  * pmain;
	usage_t * pusage;
} lookup_t;

lookup_t lookups[] =
{

	{"zop",            zop_main,            0 /*zop_usage*/},
	{"zgcd",           zgcd_main,           zgcd_usage},
	{"zlcm",           zlcm_main,           zlcm_usage},
	{"ztotient",       ztotient_main,       ztotient_usage},
	{"ztestprime",     ztestprime_main,     ztestprime_usage},
	{"nthprime",       nthprime_main,       nthprime_usage},
	{"zlist",          zlist_main,          zlist_usage},
	{"zfactor",        zfactor_main,        zfactor_usage},
	{"zdivisors",      zdivisors_main,      zdivisors_usage},
	{"zmatop",         zmatop_main,         0 /*zmatop_usage*/},

	{"qop",            qop_main,            0 /*qop_usage*/},
	{"qmatop",         qmatop_main,         0 /*qmatop_usage*/},
	{"qvecop",         qvecop_main,         0 /*qvecop_usage*/},

	{"qcyclo",         qcyclo_main,         qcyclo_usage},
	{"qpop",           qpop_main,           0 /*qcyclo_usage*/},

	{"f2op",           f2op_main,           0 /*f2op_usage*/},
	{"f2random",       f2random_main,       f2random_usage},

	{"f2matop",        f2matop_main,        0 /*f2matop_usage*/},
	{"f2vecop",        f2vecop_main,        0 /*f2vecop_usage*/},
	{"f2matchpol",     f2matchpol_main,     f2matchpol_usage},
	{"f2matord",       f2matord_main,       f2matord_usage},
	{"f2matrandom",    f2matrandom_main,    f2matrandom_usage},

	{"f2plist",        f2plist_main,        f2plist_usage},
	{"f2pop",          f2pop_main,          0 /*f2pop_usage*/},
	{"f2pmatop",       f2pmatop_main,       0 /*f2pmatop_usage*/},
	{"f2pcompmx",      f2pcompmx_main,      f2pcompmx_usage},
	{"f2pdeg",         f2pdeg_main,         f2pdeg_usage},
	{"f2pgcd",         f2pgcd_main,         f2pgcd_usage},
	{"f2plcm",         f2plcm_main,         f2plcm_usage},
	{"f2ptotient",     f2ptotient_main,     f2ptotient_usage},
	{"f2ptest",        f2ptest_main,        f2ptest_usage},
	{"f2pfind",        f2pfind_main,        f2pfind_usage},
	{"f2pperiod",      f2pperiod_main,      f2pperiod_usage},
	{"f2pfactor",      f2pfactor_main,      f2pfactor_usage},
	{"f2pdivisors",    f2pdivisors_main,    f2pdivisors_usage},
	{"f2peval",        f2peval_main,        f2peval_usage},
	{"f2prandom",      f2prandom_main,      f2prandom_usage},
	{"f2pqp",          f2pqp_main,          f2pqp_usage},

	{"f2pmlist",       f2pmlist_main,       f2pmlist_usage},
	{"f2pmop",         f2pmop_main,         f2pmop_usage},
	{"f2pmtbl",        f2pmtbl_main,        f2pmtbl_usage},
	{"f2pmord",        f2pmord_main,        f2pmord_usage},
	{"f2pmfindgen",    f2pmfindgen_main,    f2pmfindgen_usage},
	{"f2pmlog",        f2pmlog_main,        f2pmlog_usage},
	{"f2pmchpol",      f2pmchpol_main,      f2pmchpol_usage},
	{"f2pmminpol",     f2pmminpol_main,     f2pmminpol_usage},
	{"f2pmconvert",    f2pmconvert_main,    f2pmconvert_usage},
	{"f2pmrandom",     f2pmrandom_main,     f2pmrandom_usage},

	{"f2pmmatop",      f2pmmatop_main,      f2pmmatop_usage},
	{"f2pmvecop",      f2pmvecop_main,      f2pmvecop_usage},
	{"f2pmmatsolve",   f2pmmatsolve_main,   f2pmmatsolve_usage},
	{"f2pmmatchpol",   f2pmmatchpol_main,   f2pmmatchpol_usage},
	{"f2pmmatdable",   f2pmmatdable_main,   f2pmmatdable_usage},
	{"f2pmmatord",     f2pmmatord_main,     f2pmmatord_usage},
	{"f2pmmatrandom",  f2pmmatrandom_main,  f2pmmatrandom_usage},

	{"f2prop",         f2prop_main,         0 /*f2prop_usage*/},
	{"f2prrandom",     f2prrandom_main,     f2prrandom_usage},

	{"f2prmatop",      f2prmatop_main,      0 /*f2prmatop_usage*/},
	{"f2prmatrandom",  f2prmatrandom_main,  f2prmatrandom_usage},

	{"f2nplist",       f2nplist_main,       f2nplist_usage},
	{"f2npop",         f2npop_main,         f2npop_usage},
	{"f2npmatop",      f2npmatop_main,      f2npmatop_usage},
	{"f2npdeg",        f2npdeg_main,        f2npdeg_usage},
	{"f2npgcd",        f2npgcd_main,        f2npgcd_usage},
	{"f2nplcm",        f2nplcm_main,        f2nplcm_usage},
	{"f2nptotient",    f2nptotient_main,    f2nptotient_usage},
	{"f2nptest",       f2nptest_main,       f2nptest_usage},
	{"f2npfind",       f2npfind_main,       f2npfind_usage},
	{"f2npfactor",     f2npfactor_main,     f2npfactor_usage},
	{"f2npdivisors",   f2npdivisors_main,   f2npdivisors_usage},
	{"f2npeval",       f2npeval_main,       f2npeval_usage},
	{"f2nprandom",     f2nprandom_main,     f2nprandom_usage},
	{"f2npcompmx",     f2npcompmx_main,     f2npcompmx_usage},

	{"f2npmlist",      f2npmlist_main,      f2npmlist_usage},
	{"f2npmop",        f2npmop_main,        f2npmop_usage},
	{"f2npmtbl",       f2npmtbl_main,       f2npmtbl_usage},
	{"f2npmord",       f2npmord_main,       f2npmord_usage},
	{"f2npmfindgen",   f2npmfindgen_main,   f2npmfindgen_usage},
	{"f2npmlog",       f2npmlog_main,       f2npmlog_usage},
	{"f2npmchpol",     f2npmchpol_main,     f2npmchpol_usage},
	{"f2npmminpol",    f2npmminpol_main,    f2npmminpol_usage},
	{"f2npmrandom",    f2npmrandom_main,    f2npmrandom_usage},
	{"f2npqp",         f2npqp_main,         f2npqp_usage},

	{"f2npmmatop",     f2npmmatop_main,     f2npmmatop_usage},
	{"f2npmvecop",     f2npmvecop_main,     f2npmvecop_usage},
	{"f2npmmatrandom", f2npmmatrandom_main, f2npmmatrandom_usage},

	{"f2nprop",        f2nprop_main,        f2nprop_usage},
	{"f2nprmatop",     f2nprmatop_main,     f2nprmatop_usage},

	{"fplist",         fplist_main,         fplist_usage},
	{"fpop",           fpop_main,           fpop_usage},
	{"fptbl",          fptbl_main,          fptbl_usage},
	{"fpord",          fpord_main,          fpord_usage},
	{"fpmaxord",       fpmaxord_main,       fpmaxord_usage},
	{"fporbit",        fporbit_main,         fporbit_usage},
	{"fpfindgen",      fpfindgen_main,      fpfindgen_usage},
	{"fplog",          fplog_main,          fplog_usage},
	{"fprandom",       fprandom_main,       fprandom_usage},

	{"fpmatop",        fpmatop_main,        fpmatop_usage},
	{"fpvecop",        fpvecop_main,        fpvecop_usage},
	{"fpmatchpol",     fpmatchpol_main,     fpmatchpol_usage},
	{"fpmatord",       fpmatord_main,       fpmatord_usage},
	{"fpmatrandom",    fpmatrandom_main,    fpmatrandom_usage},

	{"fpplist",        fpplist_main,        fpplist_usage},
	{"fppop",          fppop_main,          fppop_usage},
	{"fppmatop",       fppmatop_main,       fppmatop_usage},
	{"fppcompmx",      fppcompmx_main,      fppcompmx_usage},
	{"fppdeg",         fppdeg_main,         fppdeg_usage},
	{"fppgcd",         fppgcd_main,         fppgcd_usage},
	{"fpplcm",         fpplcm_main,         fpplcm_usage},
	{"fpptotient",     fpptotient_main,     fpptotient_usage},
	{"fpptest",        fpptest_main,        fpptest_usage},
	{"fppfind",        fppfind_main,        fppfind_usage},
	{"fppfactor",      fppfactor_main,      fppfactor_usage},
	{"fppdivisors",    fppdivisors_main,    fppdivisors_usage},
	{"fppeval",        fppeval_main,        fppeval_usage},
	{"fpprandom",      fpprandom_main,      fpprandom_usage},
	{"fppqp",          fppqp_main,          fppqp_usage},

	{"fppmlist",       fppmlist_main,       fppmlist_usage},
	{"fppmop",         fppmop_main,         fppmop_usage},
	{"fppmtbl",        fppmtbl_main,        fppmtbl_usage},
	{"fppmord",        fppmord_main,        fppmord_usage},
	{"fppmchpol",      fppmchpol_main,      fppmchpol_usage},
	{"fppmminpol",     fppmminpol_main,     fppmminpol_usage},
	{"fppmrandom",     fppmrandom_main,     fppmrandom_usage},

	{"fppmmatop",      fppmmatop_main,      0 /*fppmmatop_usage*/},
	{"fppmvecop",      fppmvecop_main,      0 /*fppmvecop_usage*/},
	{"fppmmatord",     fppmmatord_main,     fppmmatord_usage},
	{"fppmmatrandom",  fppmmatrandom_main,  fppmmatrandom_usage},

	{"fpprop",         fpprop_main,         fpprop_usage},

	{"fpprmatop",      fpprmatop_main,      fpprmatop_usage},

	{"fpnpop",         fpnpop_main,         fpnpop_usage},
	{"fpnpmatop",      fpnpmatop_main,      fpnpmatop_usage},
	{"fpnpgcd",        fpnpgcd_main,        fpnpgcd_usage},
	{"fpnpqp",         fpnpqp_main,         fpnpqp_usage},

	// To do:
	//{"fpnplist",        fpnplist_main,        fpnplist_usage},
	//{"fpnpcompmx",      fpnpcompmx_main,      fpnpcompmx_usage},
	//{"fpnpdeg",         fpnpdeg_main,         fpnpdeg_usage},
	//{"fpnplcm",         fpnplcm_main,         fpnplcm_usage},
	//{"fpnptotient",     fpnptotient_main,     fpnptotient_usage},
	//{"fpnptest",        fpnptest_main,        fpnptest_usage},
	//{"fpnpfind",        fpnpfind_main,        fpnpfind_usage},
	//{"fpnpfactor",      fpnpfactor_main,      fpnpfactor_usage},
	//{"fpnpdivisors",    fpnpdivisors_main,    fpnpdivisors_usage},
	//{"fpnpeval",        fpnpeval_main,        fpnpeval_usage},
	//{"fpnprandom",      fpnprandom_main,      fpnprandom_usage},

	{"fpnpmop",        fpnpmop_main,        fpnpmop_usage},
	{"fpnpmmatop",     fpnpmmatop_main,     fpnpmmatop_usage},

	// To do:
	//{"fpnpmlist",       fpnpmlist_main,       fpnpmlist_usage},
	//{"fpnpmtbl",        fpnpmtbl_main,        fpnpmtbl_usage},
	//{"fpnpmord",        fpnpmord_main,        fpnpmord_usage},
	//{"fpnpmchpol",      fpnpmchpol_main,      fpnpmchpol_usage},
	//{"fpnpmminpol",     fpnpmminpol_main,     fpnpmminpol_usage},
	//{"fpnpmrandom",     fpnpmrandom_main,     fpnpmrandom_usage},

	//{"fpnpmmatrandom",  fpnpmmatrandom_main,  fpnpmmatrandom_usage},

	{0, 0, 0} // MUST be null-terminated.
};

// ----------------------------------------------------------------
static void main_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {cmd} {command-specific arguments ...}\n";
	int num_lookups =  sizeof(lookups) / sizeof(lookups[0]);
	for (int i = 0; i < num_lookups; i++) {
		std::cerr << " " << lookups[i].name;
	}
	std::cerr << "\n";
	exit(1);
}

int main(int argc, char ** argv)
{
	char * exename = argv[0];
	argc--, argv++;

	// Recursively invokes this program to handle {} pairs, e.g.
	//   spiff f2pdeg { f2pfactor { f2pop 2 ^ 127 - 1 } }
	cmd_interpolate(exename, argc, argv);

	if (argc < 1)
		main_usage(exename);

	if (strcmp(argv[0], "-l") == 0) {
		for (int i = 0; lookups[i].name; i++) {
			if (i > 0)
				std::cout << " ";
			std::cout << lookups[i].name;
		}
		std::cout << "\n";
		exit(1);
	}
	for (int i = 0; lookups[i].name; i++)
		if (strcmp(argv[0], lookups[i].name) == 0)
			return lookups[i].pmain(argc, argv, lookups[i].pusage);
	std::cerr << exename << ": subcommand \"" << argv[0]
		<< "\" not found.\n";
	return 1;
}
