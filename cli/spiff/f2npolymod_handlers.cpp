#include <string.h>

#include "f2npolymod_handlers.h"
#include "cmdlineops.h"
#include "cmdlinematops.h"
#include "cmdlinevecops.h"
#include "f2npolymod_t.h"
#include "f2npolymod_units.h"
#include "f2npolymod_random.h"
#include "tbl_types.h"
#include "sp_list_elts.h"
#include "spminchar.h"

void f2npmlist_usage(char * argv0)
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

void f2npmop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
	exit(1);
}

int f2npmop_main(int argc, char ** argv, usage_t * pusage)
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


void f2npmtbl_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0
		<< " {im} {om} {+|-|*|u*|/|log[:g]|alog[:g]}\n";
	exit(1);
}

int f2npmtbl_main(int argc, char ** argv, usage_t * pusage)
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

void f2npmord_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {om} {a}\n";
	exit(1);
}

int f2npmord_main(int argc, char ** argv, usage_t * pusage)
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

void f2npmfindgen_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {om}\n";
	exit(1);
}

int f2npmfindgen_main(int argc, char ** argv, usage_t * pusage)
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

void f2npmlog_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {om} {g} {a}\n";
	exit(1);
}

int f2npmlog_main(int argc, char ** argv, usage_t * pusage)
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

void f2npmchpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {m} {residues ...}\n";
	exit(1);
}

int f2npmchpol_main(int argc, char ** argv, usage_t * pusage)
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

void f2npmminpol_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {im} {m} {residues ...}\n";
	exit(1);
}

int f2npmminpol_main(int argc, char ** argv, usage_t * pusage)
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

void f2npmrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} [count]\n";
	exit(1);
}

int f2npmrandom_main(int argc, char ** argv, usage_t * pusage)
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

void f2npmmatop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
	exit(1);
}

int f2npmmatop_main(int argc, char ** argv, usage_t * pusage)
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

void f2npmvecop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
	exit(1);
}

int f2npmvecop_main(int argc, char ** argv, usage_t * pusage)
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

void f2npmmatrandom_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0
		<< " {inner m} {outer m} {# rows} {# cols}\n";
	exit(1);
}

int f2npmmatrandom_main(int argc, char ** argv, usage_t * pusage)
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

