#include "spffl/tmvpoly.h"
#include "spffl/tmvpolyscan.h"
#include "spffl/f2_polymod_t.h"
#include "spffl/list_elements.h"
#include "spffl/f2_poly_factor.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {f} {extension degrees ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
static tmvpoly<f2_polymod_t> F2_Fq_embed(
	tmvpoly<f2_polymod_t> & f,
	f2_polymod_t          & Fq_zero,
	f2_polymod_t          & Fq_one)
{
	int nm = f.get_num_monoms();
	tmvpoly<f2_polymod_t> g(f);
	for (int i = 0; i < nm; i++) {
		f2_polymod_t c = g.get_coeff(i);
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
int main(int argc, char ** argv)
{
	int argb = 1;
	int print_all_elts = 0;

	if (argc < 2)
		usage(argv[0]);
	while ((argb < argc) && (argv[argb][0] == '-')) {
		if (strcmp(argv[argb], "--help") == 0)
			usage(argv[0]);
		else if (strcmp(argv[argb], "-a") == 0)
			print_all_elts = 1;
		else
			usage(argv[0]);
		argb++;
	}

	if ((argc - argb) < 2)
		usage(argv[0]);
	const char * fstring = argv[argb];
	argb++;

	f2_poly_t    F2_m    = f2_poly_t::from_base_rep(3);
	f2_polymod_t F2_zero = f2_polymod_t::prime_subfield_element(0, F2_m);
	f2_polymod_t F2_one  = f2_polymod_t::prime_subfield_element(1, F2_m);

	tmvpoly<f2_polymod_t> F2_f;
	if (!tmvpoly_f2_polymod_from_string(F2_f, fstring, F2_m)) {
		std::cerr << "Couldn't scan polynomial.\n";
		exit(1);
	}
	tmvpoly<f2_polymod_t> F2_F = F2_f.homogenize();
	std::cout << "f = " << F2_f << "\n";
	std::cout << "F = " << F2_F << "\n";
	F2_f.pretty_print(std::cout); std::cout << "\n";
	F2_F.pretty_print(std::cout); std::cout << "\n";

	for (int argi = argb; argi < argc; argi++) {
		int num_affine = 0;
		int num_projective = 0;

		f2_poly_t Fq_m;
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
			Fq_m = f2_poly_find_irreducible(deg);
		}

		f2_polymod_t Fq_zero = f2_polymod_t::prime_subfield_element(0, Fq_m);
		f2_polymod_t Fq_one  = f2_polymod_t::prime_subfield_element(1, Fq_m);

		tmvpoly<f2_polymod_t> f = F2_Fq_embed(F2_f, Fq_zero, Fq_one);
		tmvpoly<f2_polymod_t> F = f.homogenize();

		int q = 2;
		int k = Fq_m.find_degree();
		int n = f.get_nvars();

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout
			<< "m = " << Fq_m
			<< " q = " << q
			<< " k = " << k
			<< " n = " << n
			<< "\n";

		if (print_all_elts) {
			std::cout << "\n";
			std::cout << "Affine zeroes:\n";
		}

		tmatrix<f2_polymod_t> Fq_n = f2_polymod_An_list(Fq_m, n);
		int qn = Fq_n.get_num_rows();

		for (int i = 0; i < qn; i++) {
			f2_polymod_t fx = f.eval(Fq_n[i]);
			if (fx == Fq_zero) {
				if (print_all_elts)
					std::cout << Fq_n[i] << "\n";
				num_affine++;
			}
		}

		if (print_all_elts) {
			std::cout << "\n";
			std::cout << "Projective zeroes:\n";
		}

		tmatrix<f2_polymod_t> Pn_Fq = f2_polymod_Pn_list(Fq_m, n);
		int oP = Pn_Fq.get_num_rows();

		for (int i = 0; i < oP; i++) {
			f2_polymod_t FX = F.eval(Pn_Fq[i]);
			if (FX == Fq_zero) {
				if (print_all_elts)
					std::cout << Pn_Fq[i] << "\n";
				num_projective++;
			}
		}
		if (print_all_elts)
			std::cout << "\n";
		printf("# affine     = %5d / %5d\n",
			num_affine, Fq_n.get_num_rows());
		printf("# projective = %5d / %5d\n",
			num_projective, Pn_Fq.get_num_rows());
	}

	return 0;
}
