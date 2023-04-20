#include "tmvpoly.h"
#include "tmvpolyscan.h"
#include "fppolymod_t.h"
#include "sp_list_elts.h"
#include "fp_poly_factor.h"
#include "int_power.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {p} {f} {extension degrees ... }\n";
	exit(1);
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
int main(int argc, char ** argv)
{
	int p;
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

	if ((argc - argb) < 3)
		usage(argv[0]);
	if (sscanf(argv[argb], "%d", &p) != 1)
		usage(argv[0]);
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
	std::cout << "F = " << Fp_F << "\n";

	Fp_f.pretty_print(std::cout); std::cout << "\n";
	Fp_F.pretty_print(std::cout); std::cout << "\n";

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

		tmatrix<fppolymod_t> Fq_n = fppolymod_An_list(Fq_m, n);
		int qn = Fq_n.get_num_rows();

		for (int i = 0; i < qn; i++) {
			fppolymod_t fx = f.eval(Fq_n[i]);
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

		tmatrix<fppolymod_t> Pn_Fq = fppolymod_Pn_list(Fq_m, n);
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
			num_affine, Fq_n.get_num_rows());
		printf("# projective = %5d / %5d\n",
			num_projective, Pn_Fq.get_num_rows());
	}

	return 0;
}
