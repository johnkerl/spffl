
#include "tmvpoly.h"
#include "tmvpolyscan.h"
#include "tmvrat.h"
#include "tmvratscan.h"

#include "f2polymod_t.h"
#include "f2_poly_factor.h"
#include "fppolymod_t.h"
#include "fp_poly_factor.h"

#include "int_power.h"
#include "sp_list_elts.h"

// xxx move to f2polymod_convert.cpp
static tmvpoly<f2polymod_t> F2_Fq_embed(
	tmvpoly<f2polymod_t> & f,
	f2polymod_t          & Fq_zero,
	f2polymod_t          & Fq_one);

// xxx move to fppolymod_convert.cpp
static tmvpoly<fppolymod_t> Fp_Fq_embed(
	tmvpoly<fppolymod_t> & f,
	fppoly_t             & m);

static tvector<f2polymod_t> F2_frob(
	tvector<f2polymod_t> & v);

static tmatrix<f2polymod_t> F2_frobit(
	tvector<f2polymod_t> & v,
	int                    n);

// ----------------------------------------------------------------
static void f2aplist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {f ...} : {extension degrees ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
int f2aplist_main(int argc, char ** argv)
{
	int print_all_elts   =  1;
	int homogenize       =  1;
	int include_partials =  0;
	int propers_only     =  0;
	int echo_F           =  0;
	int num_F            =  0;
	int num_deg          =  0;
	int argfb = 1, argdb, argi;
	int i, j;

	// Scan the options.
	if (argc < 2)
		f2aplist_usage(argv[0]);
	while ((argfb < argc) && (argv[argfb][0] == '-')) {
		if (strcmp(argv[argfb], "--help") == 0)
			f2aplist_usage(argv[0]);
		else if (strcmp(argv[argfb], "-h") == 0)
			homogenize = 1;
		else if (strcmp(argv[argfb], "-a") == 0)
			homogenize = 0;
		else if (strcmp(argv[argfb], "-d") == 0)
			include_partials = 1;
		else if (strcmp(argv[argfb], "-q") == 0)
			print_all_elts = 0;
		else if (strcmp(argv[argfb], "-p") == 0)
			propers_only = 1;
		else if (strcmp(argv[argfb], "-l") == 0)
			echo_F = 1;
		else
			f2aplist_usage(argv[0]);
		argfb++;
	}
	if ((argc - argfb) < 3)
		f2aplist_usage(argv[0]);

	// Find out how many functions and how many degrees are on the command line.
	for (num_F = 0, argi = argfb; argi < argc; argi++, num_F++) {
		if (strcmp(argv[argi], ":") == 0) {
			break;
		}
	}
	if (num_F <= 0)
		f2aplist_usage(argv[0]);
	argdb = argi + 1;
	num_deg = argc - argdb;
	if (num_deg <= 0)
		f2aplist_usage(argv[0]);

	f2poly_t    F2_m    = f2poly_t::from_base_rep(3);
	f2polymod_t F2_zero = f2polymod_t::prime_sfld_elt(0, F2_m);
	f2polymod_t F2_one  = f2polymod_t::prime_sfld_elt(1, F2_m);

	// Scan the functions.
	tvector< tmvpoly<f2polymod_t> > arg_f(num_F);
	for (argi = argfb, i = 0; i < num_F; i++, argi++) {
		if (!tmvpoly_f2polymod_from_string(arg_f[i], argv[argi], F2_m)) {
			std::cerr << "Couldn't scan polynomial.\n";
			exit(1);
		}
		if (homogenize)
			arg_f[i] = arg_f[i].homogenize();
	}
	int nv = arg_f[0].get_nvars();
	for (i = 1; i < num_F; i++) {
		if (arg_f[i].get_nvars() != nv) {
			std::cerr << argv[0]
				<< ": nvars must be the same for all functions.\n";
			std::cerr << "(Are there any non-homogeneous equations in the input?)\n";
			exit(1);
		}
	}

	// Include partials, if desired.
	tvector< tmvpoly<f2polymod_t> > F2_f;
	if (include_partials) {
		int new_num_F = num_F * (nv + 1);
		tvector< tmvpoly<f2polymod_t> > temp(new_num_F);

		int k = 0;
		for (i = 0; i < num_F; i++) {
			temp[k++] = arg_f[i];
			for (j = 0; j < nv; j++)
				temp[k++] = arg_f[i].deriv(j);
		}

		num_F = new_num_F;
		F2_f = temp;
	}
	else {
		F2_f = arg_f;
	}

	// Echo the functions.
	if (echo_F) {
		for (i = 0; i < num_F; i++) {
			std::cout << "f[" << i << "] = " << F2_f[i] << "\n";
		}
	}

	// Scan the degrees.
	for (argi = argdb; argi < argc; argi++) {

		f2poly_t Fq_m;
		if (argv[argi][0] == ':') {
			// User-specified reductor.
			if (!Fq_m.from_string(&argv[argi][1])) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
		}
		else {
			int deg;
			if (sscanf(argv[argi], "%d", &deg) != 1) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
			Fq_m = f2poly_find_irr(deg);
		}
		int n = Fq_m.find_degree();
		int q = 1 << n;

		f2polymod_t Fq_zero = f2polymod_t::prime_sfld_elt(0, Fq_m);
		f2polymod_t Fq_one  = f2polymod_t::prime_sfld_elt(1, Fq_m);
		tmvpoly<f2polymod_t> Fq_f[num_F];
		for (i = 0; i < num_F; i++)
			Fq_f[i] = F2_Fq_embed(F2_f[i], Fq_zero, Fq_one);

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout << "m = " << Fq_m << " q = " << q << "\n";

		tmatrix<f2polymod_t> space; // A^n(F_q) or P^n(F_q)
		if (homogenize)
			space = f2polymod_Pn_list(Fq_m, nv-1);
		else
			space = f2polymod_An_list(Fq_m, nv);
		int oS = space.get_num_rows();
		unsigned char * marks = new unsigned char[oS];
		for (j = 0; j < oS; j++)
			marks[j] = 0;

		int num_points = 0;
		for (j = 0; j < oS; j++) {

			int all_zero = 1;
			for (i = 0; i < num_F; i++) {
				f2polymod_t fx = Fq_f[i].eval(space[j]);
				if (fx != Fq_zero) {
					all_zero = 0;
					break;
				}
			}
			if (!all_zero)
				continue;
			if (marks[j])
				continue;
			marks[j] = 1;

			tmatrix<f2polymod_t> frobit = F2_frobit(space[j], n);
			int point_degree = frobit.get_num_rows();

			for (i = 0; i < point_degree; i++) {
				int markidx;
				if (!space.find_row(frobit[i], markidx)) {
					std::cout << "Coding error detected: file "
						<< __FILE__ << " line " << __LINE__ << ".\n";
					exit(1);
				}
				marks[markidx] = 1;
			}
			num_points += point_degree;

			if (propers_only && (point_degree != n))
				continue;

			if (print_all_elts) {
				for (i = 0; i < point_degree; i++)
					std::cout << "  " << frobit[i];
				std::cout << "\n";
			}
		}
		delete [] marks;

		if (print_all_elts)
			std::cout << "\n";
		else
			printf("# points     = %5d / %5d\n",
				num_points, space.get_num_rows());
	}

	return 0;
}

// ----------------------------------------------------------------
static void f2apolist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {f} {extension degrees ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
int f2apolist_main(int argc, char ** argv)
{
	int argb = 1;
	int print_all_elts = 0;

	if (argc < 2)
		f2apolist_usage(argv[0]);
	while ((argb < argc) && (argv[argb][0] == '-')) {
		if (strcmp(argv[argb], "--help") == 0)
			f2apolist_usage(argv[0]);
		else if (strcmp(argv[argb], "-a") == 0)
			print_all_elts = 1;
		else
			f2apolist_usage(argv[0]);
		argb++;
	}

	if ((argc - argb) < 2)
		f2apolist_usage(argv[0]);
	char * fstring = argv[argb];
	argb++;

	f2poly_t    F2_m    = f2poly_t::from_base_rep(3);
	f2polymod_t F2_zero = f2polymod_t::prime_sfld_elt(0, F2_m);
	f2polymod_t F2_one  = f2polymod_t::prime_sfld_elt(1, F2_m);

	tmvpoly<f2polymod_t> F2_f;
	if (!tmvpoly_f2polymod_from_string(F2_f, fstring, F2_m)) {
		std::cerr << "Couldn't scan polynomial.\n";
		exit(1);
	}
	tmvpoly<f2polymod_t> F2_F = F2_f.homogenize();

	std::cout << "f = " << F2_f << "\n";
	std::cout << "F = " << F2_F << "\n";

	for (int argi = argb; argi < argc; argi++) {
		int num_affine = 0;
		int num_projective = 0;

		f2poly_t Fq_m;
		if (argv[argi][0] == ':') {
			// User-specified reductor.
			if (!Fq_m.from_string(&argv[argi][1])) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
		}
		else {
			int deg;
			if (sscanf(argv[argi], "%d", &deg) != 1) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
			Fq_m = f2poly_find_irr(deg);
		}

		f2polymod_t Fq_zero = f2polymod_t::prime_sfld_elt(0, Fq_m);
		f2polymod_t Fq_one  = f2polymod_t::prime_sfld_elt(1, Fq_m);

		tmvpoly<f2polymod_t> f = F2_Fq_embed(F2_f, Fq_zero, Fq_one);
		tmvpoly<f2polymod_t> F = f.homogenize();

		int q = 2;
		int n = Fq_m.find_degree();
		int nv = f.get_nvars();

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout
			<< "m = " << Fq_m
			<< " q = " << q
			<< " n = " << n
			<< "\n";

		if (print_all_elts) {
			std::cout << "\n";
			std::cout << "Affine zeroes:\n";
		}

		tmatrix<f2polymod_t> An_Fq = f2polymod_An_list(Fq_m, nv);
		int qn = An_Fq.get_num_rows();

		for (int i = 0; i < qn; i++) {
			f2polymod_t fx = f.eval(An_Fq[i]);
			if (fx == Fq_zero) {
				if (print_all_elts)
					std::cout << An_Fq[i] << "\n";
				num_affine++;
			}
		}

		if (print_all_elts) {
			std::cout << "\n";
			std::cout << "Projective zeroes:\n";
		}

		tmatrix<f2polymod_t> Pn_Fq = f2polymod_Pn_list(Fq_m, nv);
		int oP = Pn_Fq.get_num_rows();

		for (int i = 0; i < oP; i++) {
			f2polymod_t FX = F.eval(Pn_Fq[i]);
			if (FX == Fq_zero) {
				if (print_all_elts)
					std::cout << Pn_Fq[i] << "\n";
				num_projective++;
			}
		}
		if (print_all_elts)
			std::cout << "\n";
		printf("# affine     = %5d / %5d\n",
			num_affine, An_Fq.get_num_rows());
		printf("# projective = %5d / %5d\n",
			num_projective, Pn_Fq.get_num_rows());
	}

	return 0;
}

// ----------------------------------------------------------------
static void f2apsing_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0
		<< " [-v] [-v] {f} {extension degrees ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
int f2apsing_main(int argc, char ** argv)
{
	int argb = 1;
	int verbosity = 0;

	if (argc < 2)
		f2apsing_usage(argv[0]);
	while ((argb < argc) && (argv[argb][0] == '-')) {
		if (strcmp(argv[argb], "--help") == 0)
			f2apsing_usage(argv[0]);
		else if (strcmp(argv[argb], "-v") == 0)
			verbosity++;
		else
			f2apsing_usage(argv[0]);
		argb++;
	}

	if ((argc - argb) < 2)
		f2apsing_usage(argv[0]);
	char * fstring = argv[argb];
	argb++;

	f2poly_t    F2_m    = f2poly_t::from_base_rep(3);
	f2polymod_t F2_zero = f2polymod_t::prime_sfld_elt(0, F2_m);
	f2polymod_t F2_one  = f2polymod_t::prime_sfld_elt(1, F2_m);

	tmvpoly<f2polymod_t> F2_f;
	if (!tmvpoly_f2polymod_from_string(F2_f, fstring, F2_m)) {
		std::cerr << "Couldn't scan polynomial.\n";
		exit(1);
	}
	tmvpoly<f2polymod_t> F2_F = F2_f.homogenize();

	std::cout << "f = " << F2_f << "\n";
	for (int j = 0; j < F2_f.get_nvars(); j++)
		std::cout << "  f' = " << F2_f.deriv(j) << "\n";
	std::cout << "F = " << F2_F << "\n";
	for (int j = 0; j < F2_F.get_nvars(); j++)
		std::cout << "  F' = " << F2_F.deriv(j) << "\n";

	for (int argi = argb; argi < argc; argi++) {
		int num_singular_f = 0;
		int num_singular_F = 0;

		f2poly_t Fq_m;
		if (argv[argi][0] == ':') {
			// User-specified reductor.
			if (!Fq_m.from_string(&argv[argi][1])) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
		}
		else {
			int deg;
			if (sscanf(argv[argi], "%d", &deg) != 1) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
			Fq_m = f2poly_find_irr(deg);
		}

		f2polymod_t Fq_zero = f2polymod_t::prime_sfld_elt(0, Fq_m);
		f2polymod_t Fq_one  = f2polymod_t::prime_sfld_elt(1, Fq_m);

		tmvpoly<f2polymod_t> f = F2_Fq_embed(F2_f, Fq_zero, Fq_one);
		tmvpoly<f2polymod_t> F = f.homogenize();

		int q = 2;
		int n = Fq_m.find_degree();
		int nv = f.get_nvars();

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout
			<< "m = " << Fq_m
			<< " q = " << q
			<< " n = " << n
			<< "\n";

		if (verbosity >= 1) {
			std::cout << "\n";
			std::cout << "Affine space:\n";
		}

		tmatrix<f2polymod_t> An_Fq = f2polymod_An_list(Fq_m, nv);
		int qn = An_Fq.get_num_rows();

		tmvpoly<f2polymod_t> * funcs = new tmvpoly<f2polymod_t>[nv+1];
		funcs[0] = f;
		for (int j = 0; j < nv; j++)
			funcs[j+1] = f.deriv(j);
		for (int i = 0; i < qn; i++) {
			int singular_point = 1;
			for (int j = 0; j <= nv; j++) {
				f2polymod_t fx = funcs[j].eval(An_Fq[i]);
				if (fx != Fq_zero)
					singular_point = 0;
			}
			if (singular_point)
				num_singular_f++;

			if ((verbosity >= 2) || (verbosity && singular_point)) {
				std::cout << An_Fq[i] << " |";
				for (int j = 0; j <= nv; j++)
					std::cout << " " << funcs[j].eval(An_Fq[i]);
				if (singular_point)
					std::cout << " *";
				std::cout << "\n";
			}
		}
		delete [] funcs;

		if (verbosity >= 1) {
			std::cout << "\n";
			std::cout << "Projective space:\n";
		}

		tmatrix<f2polymod_t> Pn_Fq = f2polymod_Pn_list(Fq_m, nv);
		int oP = Pn_Fq.get_num_rows();

		funcs = new tmvpoly<f2polymod_t>[nv+2];
		funcs[0] = F;
		for (int j = 0; j <= nv; j++)
			funcs[j+1] = F.deriv(j);
		for (int i = 0; i < oP; i++) {
			int singular_point = 1;
			for (int j = 0; j <= nv+1; j++) {
				f2polymod_t FX = funcs[j].eval(Pn_Fq[i]);
				if (FX != Fq_zero)
					singular_point = 0;
			}
			if (singular_point)
				num_singular_F++;

			if ((verbosity >= 2) || (verbosity && singular_point)) {
				std::cout << Pn_Fq[i] << " |";
				for (int j = 0; j <= nv+1; j++)
					std::cout << " " << funcs[j].eval(Pn_Fq[i]);
				if (singular_point)
					std::cout << " *";
				std::cout << "\n";
			}
		}
		delete [] funcs;
		std::cout << "f " << (num_singular_f ? "" : "non")
			<< "singular ("
			<< num_singular_f << " / " << An_Fq.get_num_rows()
			<< ")\n";
		std::cout << "F " << (num_singular_F ? "" : "non")
			<< "singular ("
			<< num_singular_F << " / " << Pn_Fq.get_num_rows()
			<< ")\n";
	}

	return 0;
}

// ----------------------------------------------------------------
static void f2apjac_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0
		<< " [-h] {f} {extension degree} {f file} {points file}\n";
	//xxx need f file, points file
	exit(1);
}

// ----------------------------------------------------------------
int f2apjac_main(int argc, char ** argv)
{
#if 0
	int argb = 1;
	int verbosity = 0;
	int homogenize = 0;

	if (argc < 2)
		f2apjac_usage(argv[0]);
	while ((argb < argc) && (argv[argb][0] == '-')) {
		if (strcmp(argv[argb], "--help") == 0)
			f2apjac_usage(argv[0]);
		else if (strcmp(argv[argb], "-v") == 0)
			verbosity++;
		else if (strcmp(argv[argb], "-h") == 0)
			homogenize = 1;
		else
			f2apjac_usage(argv[0]);
		argb++;
	}

	if ((argc - argb) < 3)
		f2apjac_usage(argv[0]);
	char * fstring = argv[argb];
	argb++;

	f2poly_t    F2_m    = f2poly_t::from_base_rep(3);
	f2polymod_t F2_zero = f2polymod_t::prime_sfld_elt(0, F2_m);
	f2polymod_t F2_one  = f2polymod_t::prime_sfld_elt(1, F2_m);

	tmvpoly<f2polymod_t> F2_f;
	if (!tmvpoly_f2polymod_from_string(F2_f, fstring, F2_m)) {
		std::cerr << "Couldn't scan polynomial.\n";
		exit(1);
	}
	if (homogenize)
		F2_f = F2_f.homogenize();

	std::cout << "f = " << F2_f << "\n";
	for (int j = 0; j < F2_f.get_nvars(); j++)
		std::cout << "  f' = " << F2_f.deriv(j) << "\n";

	for (int argi = argb; argi < argc; argi++) {
		int num_singular_f = 0;

		f2poly_t Fq_m;
		if (argv[argi][0] == ':') {
			// User-specified reductor.
			if (!Fq_m.from_string(&argv[argi][1])) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
		}
		else {
			int deg;
			if (sscanf(argv[argi], "%d", &deg) != 1) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
			Fq_m = f2poly_find_irr(deg);
		}

		f2polymod_t Fq_zero = f2polymod_t::prime_sfld_elt(0, Fq_m);
		f2polymod_t Fq_one  = f2polymod_t::prime_sfld_elt(1, Fq_m);

		tmvpoly<f2polymod_t> f = F2_Fq_embed(F2_f, Fq_zero, Fq_one);

		int q = 2;
		int n = Fq_m.find_degree();
		int nv = f.get_nvars();

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout
			<< "m = " << Fq_m
			<< " q = " << q
			<< " n = " << n
			<< "\n";

		if (verbosity >= 1) {
			std::cout << "\n";
			std::cout << "Affine space:\n";
		}

		tmatrix<f2polymod_t> An_Fq = f2polymod_An_list(Fq_m, nv);
		int qn = An_Fq.get_num_rows();

		tmvpoly<f2polymod_t> * funcs = new tmvpoly<f2polymod_t>[nv+1];
		funcs[0] = f;
		for (int j = 0; j < nv; j++)
			funcs[j+1] = f.deriv(j);
		for (int i = 0; i < qn; i++) {
			int singular_point = 1;
			for (int j = 0; j <= nv; j++) {
				f2polymod_t fx = funcs[j].eval(An_Fq[i]);
				if (fx != Fq_zero)
					singular_point = 0;
			}
			if (singular_point)
				num_singular_f++;

			if ((verbosity >= 2) || (verbosity && singular_point)) {
				std::cout << An_Fq[i] << " |";
				for (int j = 0; j <= nv; j++)
					std::cout << " " << funcs[j].eval(An_Fq[i]);
				if (singular_point)
					std::cout << " *";
				std::cout << "\n";
			}
		}
		delete [] funcs;

		if (verbosity >= 1) {
			std::cout << "\n";
			std::cout << "Projective space:\n";
		}

		tmatrix<f2polymod_t> Pn_Fq = f2polymod_Pn_list(Fq_m, nv);
		int oP = Pn_Fq.get_num_rows();

		funcs = new tmvpoly<f2polymod_t>[nv+2];
		funcs[0] = F;
		for (int j = 0; j <= nv; j++)
			funcs[j+1] = F.deriv(j);
		for (int i = 0; i < oP; i++) {
			int singular_point = 1;
			for (int j = 0; j <= nv+1; j++) {
				f2polymod_t FX = funcs[j].eval(Pn_Fq[i]);
				if (FX != Fq_zero)
					singular_point = 0;
			}
			if (singular_point)
				num_singular_F++;

			if ((verbosity >= 2) || (verbosity && singular_point)) {
				std::cout << Pn_Fq[i] << " |";
				for (int j = 0; j <= nv+1; j++)
					std::cout << " " << funcs[j].eval(Pn_Fq[i]);
				if (singular_point)
					std::cout << " *";
				std::cout << "\n";
			}
		}
		delete [] funcs;
		std::cout << "f " << (num_singular_f ? "" : "non")
			<< "singular ("
			<< num_singular_f << " / " << An_Fq.get_num_rows()
			<< ")\n";
		std::cout << "F " << (num_singular_F ? "" : "non")
			<< "singular ("
			<< num_singular_F << " / " << Pn_Fq.get_num_rows()
			<< ")\n";
	}

	return 0;
#else
	f2apjac_usage(argv[0]);
	std::cerr << "f2apjac stub.\n";
	return 0;
#endif
}

// ----------------------------------------------------------------
static void fpaplist_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {f} {extension degrees ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
int fpaplist_main(int argc, char ** argv)
{
	int p;
	int argb = 1;
	int print_all_elts = 0;

	if (argc < 2)
		fpaplist_usage(argv[0]);
	while ((argb < argc) && (argv[argb][0] == '-')) {
		if (strcmp(argv[argb], "--help") == 0)
			fpaplist_usage(argv[0]);
		else if (strcmp(argv[argb], "-a") == 0)
			print_all_elts = 1;
		else
			fpaplist_usage(argv[0]);
		argb++;
	}

	if ((argc - argb) < 3)
		fpaplist_usage(argv[0]);
	if (sscanf(argv[argb], "%d", &p) != 1)
		fpaplist_usage(argv[0]);
	argb++;
	const char * fstring = argv[argb];
	argb++;

	fppoly_t Fp_m = fppoly_find_irr(p, 1);

	tmvpoly<fppolymod_t> Fp_f;
	if (!tmvpoly_fppolymod_from_string(Fp_f, fstring, Fp_m)) {
		std::cerr << "Couldn't scan polynomial.\n";
		exit(1);
	}
	tmvpoly<fppolymod_t> Fp_F = Fp_f.homogenize();

	std::cout << "f = " << Fp_f << "\n";
	for (int j = 0; j < Fp_f.get_nvars(); j++)
		std::cout << "  f' = " << Fp_f.deriv(j) << "\n";
	std::cout << "F = " << Fp_F << "\n";
	for (int j = 0; j < Fp_F.get_nvars(); j++)
		std::cout << "  F' = " << Fp_F.deriv(j) << "\n";

	//Fp_f.pretty_print(std::cout); std::cout << "\n";
	//Fp_F.pretty_print(std::cout); std::cout << "\n";

	for (int argi = argb; argi < argc; argi++) {
		int num_affine = 0;
		int num_projective = 0;

		fppoly_t Fq_m;
		if (argv[argi][0] == ':') {
			// User-specified reductor.
			if (!Fq_m.from_string(&argv[argi][1], p)) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
		}
		else {
			int deg;
			if (sscanf(argv[argi], "%d", &deg) != 1) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
			Fq_m = fppoly_find_irr(p, deg);
		}
		fppolymod_t Fq_zero = fppolymod_t::prime_sfld_elt(0, Fq_m);
		tmvpoly<fppolymod_t> f = Fp_Fq_embed(Fp_f, Fq_m);
		tmvpoly<fppolymod_t> F = f.homogenize();
		int q = p;
		int n = Fq_m.find_degree();
		int nv = f.get_nvars();

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout
			<< "m = " << Fq_m
			<< " q = " << q
			<< " n = " << n
			<< "\n";

		if (print_all_elts) {
			std::cout << "\n";
			std::cout << "Affine zeroes:\n";
		}

		tmatrix<fppolymod_t> An_Fq = fppolymod_An_list(Fq_m, nv);
		int qn = An_Fq.get_num_rows();

		for (int i = 0; i < qn; i++) {
			fppolymod_t fx = f.eval(An_Fq[i]);
			if (fx == Fq_zero) {
				if (print_all_elts)
					std::cout << An_Fq[i] << "\n";
				num_affine++;
			}
		}

		if (print_all_elts) {
			std::cout << "\n";
			std::cout << "Projective zeroes:\n";
		}

		tmatrix<fppolymod_t> Pn_Fq = fppolymod_Pn_list(Fq_m, nv);
		int oP = Pn_Fq.get_num_rows();

		for (int i = 0; i < oP; i++) {
			fppolymod_t FX = F.eval(Pn_Fq[i]);
			if (FX == Fq_zero) {
				if (print_all_elts)
					std::cout << Pn_Fq[i] << "\n";
				num_projective++;
			}
		}
		if (print_all_elts)
			std::cout << "\n";
		printf("# affine     = %5d / %5d\n",
			num_affine, An_Fq.get_num_rows());
		printf("# projective = %5d / %5d\n",
			num_projective, Pn_Fq.get_num_rows());
	}

	return 0;
}

// ----------------------------------------------------------------
static void fpapsing_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0
		<< " [-v] [-v] {p} {f} {extension degrees ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
int fpapsing_main(int argc, char ** argv)
{
	int p;
	int argb = 1;
	int verbosity = 0;

	if (argc < 2)
		fpapsing_usage(argv[0]);
	while ((argb < argc) && (argv[argb][0] == '-')) {
		if (strcmp(argv[argb], "--help") == 0)
			fpapsing_usage(argv[0]);
		else if (strcmp(argv[argb], "-v") == 0)
			verbosity++;
		else
			fpapsing_usage(argv[0]);
		argb++;
	}

	if ((argc - argb) < 3)
		fpapsing_usage(argv[0]);
	if (sscanf(argv[argb], "%d", &p) != 1)
		fpapsing_usage(argv[0]);
	argb++;
	char * fstring = argv[argb];
	argb++;

	fppoly_t Fp_m = fppoly_find_irr(p, 1);

	tmvpoly<fppolymod_t> Fp_f;
	if (!tmvpoly_fppolymod_from_string(Fp_f, fstring, Fp_m)) {
		std::cerr << "Couldn't scan polynomial.\n";
		exit(1);
	}
	tmvpoly<fppolymod_t> Fp_F = Fp_f.homogenize();
	std::cout << "f = " << Fp_f << "\n";
	std::cout << "F = " << Fp_F << "\n";

	for (int argi = argb; argi < argc; argi++) {
		int num_singular_f = 0;
		int num_singular_F = 0;

		fppoly_t Fq_m;
		if (argv[argi][0] == ':') {
			// User-specified reductor.
			if (!Fq_m.from_string(&argv[argi][1], p)) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
		}
		else {
			int deg;
			if (sscanf(argv[argi], "%d", &deg) != 1) {
				std::cerr << "Couldn't parse \"" << argi << "\".\n";
				exit(1);
			}
			Fq_m = fppoly_find_irr(p, deg);
		}
		fppolymod_t Fq_zero = fppolymod_t::prime_sfld_elt(0, Fq_m);
		fppolymod_t Fq_one  = fppolymod_t::prime_sfld_elt(1, Fq_m);

		tmvpoly<fppolymod_t> f = Fp_Fq_embed(Fp_f, Fq_m);
		tmvpoly<fppolymod_t> F = f.homogenize();
		int q = p;
		int n = Fq_m.find_degree();
		int nv = f.get_nvars();

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout
			<< "m = " << Fq_m
			<< " q = " << q
			<< " n = " << n
			<< "\n";

		if (verbosity >= 1) {
			std::cout << "\n";
			std::cout << "Affine space:\n";
		}

		tmatrix<fppolymod_t> An_Fq = fppolymod_An_list(Fq_m, nv);
		int qn = An_Fq.get_num_rows();

		tmvpoly<fppolymod_t> * funcs = new tmvpoly<fppolymod_t>[nv+1];
		funcs[0] = f;
		for (int j = 0; j < nv; j++)
			funcs[j+1] = f.deriv(j);
		for (int i = 0; i < qn; i++) {
			int singular_point = 1;
			for (int j = 0; j <= nv; j++) {
				fppolymod_t fx = funcs[j].eval(An_Fq[i]);
				if (fx != Fq_zero)
					singular_point = 0;
			}
			if (singular_point)
				num_singular_f++;

			if ((verbosity >= 2) || (verbosity && singular_point)) {
				std::cout << An_Fq[i] << " |";
				for (int j = 0; j <= nv; j++)
					std::cout << " " << funcs[j].eval(An_Fq[i]);
				if (singular_point)
					std::cout << " *";
				std::cout << "\n";
			}
		}
		delete [] funcs;

		if (verbosity >= 1) {
			std::cout << "\n";
			std::cout << "Projective space:\n";
		}

		tmatrix<fppolymod_t> Pn_Fq = fppolymod_Pn_list(Fq_m, nv);
		int oP = Pn_Fq.get_num_rows();

		funcs = new tmvpoly<fppolymod_t>[nv+2];
		funcs[0] = F;
		for (int j = 0; j <= nv; j++)
			funcs[j+1] = F.deriv(j);
		for (int i = 0; i < oP; i++) {
			int singular_point = 1;
			for (int j = 0; j <= nv+1; j++) {
				fppolymod_t FX = funcs[j].eval(Pn_Fq[i]);
				if (FX != Fq_zero)
					singular_point = 0;
			}
			if (singular_point)
				num_singular_F++;

			if ((verbosity >= 2) || (verbosity && singular_point)) {
				std::cout << Pn_Fq[i] << " |";
				for (int j = 0; j <= nv+1; j++)
					std::cout << " " << funcs[j].eval(Pn_Fq[i]);
				if (singular_point)
					std::cout << " *";
				std::cout << "\n";
			}
		}
		delete [] funcs;
		std::cout << "f " << (num_singular_f ? "" : "non")
			<< "singular ("
			<< num_singular_f << " / " << An_Fq.get_num_rows()
			<< ")\n";
		std::cout << "F " << (num_singular_F ? "" : "non")
			<< "singular ("
			<< num_singular_F << " / " << Pn_Fq.get_num_rows()
			<< ")\n";
	}

	return 0;
}

// ----------------------------------------------------------------
static void f2nmvpeval_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {f} {points ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
int f2nmvpeval_main(int argc, char ** argv)
{
	f2poly_t m;
	tmvpoly<f2polymod_t> f;
	f2polymod_t zero;

	if (argc < 4)
		f2nmvpeval_usage(argv[0]);
	if (!m.from_string(argv[1]))
		f2nmvpeval_usage(argv[0]);
	if (!tmvpoly_f2polymod_from_string(f, argv[2], m))
		f2nmvpeval_usage(argv[0]);
	zero = f2polymod_t::prime_sfld_elt(0, m);

	for (int argi = 3; argi < argc; argi++) {
		tvector<f2polymod_t> c(zero, 1);
		f2polymod_t fc;

		std::istringstream iss(argv[argi], std::ios_base::in);
		iss >> c;
		if (iss.fail()) {
			std::cerr << "Couldn't scan \"" << argv[argi] << "\".\n";
			exit(1);
		}
		fc = f.eval(c);
		std::cout << fc << "\n";
	}

	return 0;
}

// ----------------------------------------------------------------
static void f2nmvreval_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {f} {points ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
int f2nmvreval_main(int argc, char ** argv)
{
	f2poly_t m;
	tmvrat<f2polymod_t> f;
	f2polymod_t zero;

	if (argc < 4)
		f2nmvreval_usage(argv[0]);
	if (!m.from_string(argv[1]))
		f2nmvreval_usage(argv[0]);
	if (!tmvrat_f2polymod_from_string(f, argv[2], m))
		f2nmvreval_usage(argv[0]);
	zero = f2polymod_t::prime_sfld_elt(0, m);

	for (int argi = 3; argi < argc; argi++) {
		tvector<f2polymod_t> c(zero, 1);
		f2polymod_t fc;

		std::istringstream iss(argv[argi], std::ios_base::in);
		iss >> c;
		if (iss.fail()) {
			std::cerr << "Couldn't scan \"" << argv[argi] << "\".\n";
			exit(1);
		}
		fc = f.eval(c);
		std::cout << fc << "\n";
	}

	return 0;
}

// ----------------------------------------------------------------
static tmvpoly<f2polymod_t> F2_Fq_embed(
	tmvpoly<f2polymod_t> & f,
	f2polymod_t          & Fq_zero,
	f2polymod_t          & Fq_one)
{
	int nm = f.get_num_monoms();
	tmvpoly<f2polymod_t> g(f);
	for (int i = 0; i < nm; i++) {
		f2polymod_t c = g.get_coeff(i);
		if (c == 0)
			c = Fq_zero;
		else if (c == 1)
			c = Fq_one;
		else {
			std::cout << "For shame!\n";
			exit(1);
		}
		g.set_coeff(i, c);
	}
	return g;
}

// ----------------------------------------------------------------
static tmvpoly<fppolymod_t> Fp_Fq_embed(
	tmvpoly<fppolymod_t> & f,
	fppoly_t             & m)
{
	int nm = f.get_num_monoms();
	tmvpoly<fppolymod_t> g(f);
	for (int i = 0; i < nm; i++) {
		fppolymod_t c = g.get_coeff(i);
		int liftc = c.get_residue().get_coeff(0).get_residue();
		fppolymod_t cn = fppolymod_t::prime_sfld_elt(liftc, m);
		g.set_coeff(i, cn);
	}
	return g;
}

// ----------------------------------------------------------------
static tvector<f2polymod_t> F2_frob(
	tvector<f2polymod_t> & v)
{
	tvector<f2polymod_t> sv(v);
	int nel = v.get_num_elements();
	for (int i = 0; i < nel; i++)
		sv[i] = v[i].exp(2);
	return sv;
}

// ----------------------------------------------------------------
static tmatrix<f2polymod_t> F2_frobit(
	tvector<f2polymod_t> & v,
	int                    n)
{
	int nv = v.get_num_elements();
	tmatrix<f2polymod_t> frobit(n, nv);
	int point_degree = 1;

	frobit[0] = v;
	for (int j = 1; j < n; j++) {
		frobit[j] = F2_frob(frobit[j-1]);
		if (frobit[j] == v) {
			break;
		}
		point_degree++;
	}
	frobit.trim_num_rows(point_degree);
	return frobit;
}

// ================================================================
static void usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " f2apolist\n";
	std::cerr << "Or:    " << argv0 << " f2aplist\n";
	std::cerr << "Or:    " << argv0 << " f2apsing\n";
	std::cerr << "Or:    " << argv0 << " f2apjac\n";
	std::cerr << "Or:    " << argv0 << " fpaplist\n";
	std::cerr << "Or:    " << argv0 << " fpapsing\n";
	std::cerr << "Or:    " << argv0 << " f2nmvpeval\n";
	std::cerr << "Or:    " << argv0 << " f2nmvreval\n";
	exit(1);
}

int main(int argc, char ** argv)
{
	if (argc < 2)
		usage(argv[0]);
	if (strcmp(argv[1], "f2apolist") == 0)
		return f2apolist_main(argc-1, argv+1);
	else if (strcmp(argv[1], "f2aplist") == 0)
		return f2aplist_main(argc-1, argv+1);
	else if (strcmp(argv[1], "f2apsing") == 0)
		return f2apsing_main(argc-1, argv+1);
	else if (strcmp(argv[1], "f2apjac") == 0)
		return f2apjac_main(argc-1, argv+1);
	else if (strcmp(argv[1], "fpaplist") == 0)
		return fpaplist_main(argc-1, argv+1);
	else if (strcmp(argv[1], "fpapsing") == 0)
		return fpapsing_main(argc-1, argv+1);
	else if (strcmp(argv[1], "f2nmvpeval") == 0)
		return f2nmvpeval_main(argc-1, argv+1);
	else if (strcmp(argv[1], "f2nmvreval") == 0)
		return f2nmvreval_main(argc-1, argv+1);
	else
		usage(argv[0]);
	return 1; // Not reached.
}
