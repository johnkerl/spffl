#include "tmvpoly.h"
#include "tmvpolyscan.h"
#include "f2polymod_t.h"
#include "sp_list_elts.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {reductors ... }\n";
	exit(1);
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
tmvpoly<f2polymod_t> get_f(
	f2polymod_t & F2_zero,
	f2polymod_t & F2_one,
	f2poly_t    & F2_m)
{
	tmvpoly<f2polymod_t> F2_f;
	if (!tmvpoly_f2polymod_from_string(F2_f, "1.3.0+1.0.3+1.0.0", F2_m)) {
		std::cerr << "b&d!!\n";
		exit(1);
	}

#if 0
	// Cubic
	tmvpoly<f2polymod_t> F2_f =
		tmvpoly<f2polymod_t>(F2_one, 3, 0) +
		tmvpoly<f2polymod_t>(F2_one, 0, 3) +
		tmvpoly<f2polymod_t>(F2_one, 0, 0);
#endif

#if 0
	// Klein quartic
	tmvpoly<f2polymod_t> F2_f =
		tmvpoly<f2polymod_t>(F2_one, 3, 1) +
		tmvpoly<f2polymod_t>(F2_one, 0, 3) +
		tmvpoly<f2polymod_t>(F2_one, 1, 0);
#endif

#if 0
	// Quintic
	tmvpoly<f2polymod_t> F2_f =
		tmvpoly<f2polymod_t>(F2_one, 5, 0) +
		tmvpoly<f2polymod_t>(F2_one, 0, 5) +
		tmvpoly<f2polymod_t>(F2_one, 0, 0);
#endif

#if 0
	// HW 2.13.7
	tmvpoly<f2polymod_t> F2_f =
		tmvpoly<f2polymod_t>(F2_one, 5, 0) +
		tmvpoly<f2polymod_t>(F2_one, 0, 4) +
		tmvpoly<f2polymod_t>(F2_one, 0, 1);
#endif

#if 0
	// HW 2.13.8
	tmvpoly<f2polymod_t> F2_f =
		tmvpoly<f2polymod_t>(F2_one, 7, 0) +
		tmvpoly<f2polymod_t>(F2_one, 0, 7) +
		tmvpoly<f2polymod_t>(F2_one, 0, 0);
#endif

#if 0
	tmvpoly<f2polymod_t> F2_f =
		tmvpoly<f2polymod_t>(F2_one, 3, 0, 0) +
		tmvpoly<f2polymod_t>(F2_one, 0, 2, 0) +
		tmvpoly<f2polymod_t>(F2_one, 0, 0, 1) +
		tmvpoly<f2polymod_t>(F2_one, 0, 0, 0);
#endif

#if 0
	tmvpoly<f2polymod_t> F2_f =
		tmvpoly<f2polymod_t>(F2_one, 0, 2) +
		tmvpoly<f2polymod_t>(F2_one, 3, 0) +
		tmvpoly<f2polymod_t>(F2_one, 1, 0) +
		tmvpoly<f2polymod_t>(F2_one, 0, 0);
#endif

	return F2_f;
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

	if ((argc - argb) < 1)
		usage(argv[0]);

	f2poly_t    F2_m    = f2poly_t::from_base_rep(3);
	f2polymod_t F2_zero = f2polymod_t::prime_sfld_elt(0, F2_m);
	f2polymod_t F2_one  = f2polymod_t::prime_sfld_elt(1, F2_m);

	tmvpoly<f2polymod_t> F2_f = get_f(F2_zero, F2_one, F2_m);
	tmvpoly<f2polymod_t> F2_F = F2_f.homogenize();

	for (int argi = argb; argi < argc; argi++) {
		int num_affine = 0;
		int num_projective = 0;
		unsigned im;
		if (sscanf(argv[argi], "%x", &im) != 1) {
			std::cerr << "Couldn't parse \"" << argi << "\".\n";
			exit(1);
		}
		f2poly_t Fq_m       = f2poly_t::from_base_rep(im);
		f2polymod_t Fq_zero = f2polymod_t::prime_sfld_elt(0, Fq_m);
		f2polymod_t Fq_one  = f2polymod_t::prime_sfld_elt(1, Fq_m);

		tmvpoly<f2polymod_t> f = F2_Fq_embed(F2_f, Fq_zero, Fq_one);
		tmvpoly<f2polymod_t> F = f.homogenize();

		int n = f.get_nvars();

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout << "m = " << Fq_m << "\n";

		if (print_all_elts) {
			std::cout << "\n";
			std::cout << "Affine zeroes:\n";
		}
		std::cout << "f = " << f << "\n";

		tmatrix<f2polymod_t> Fq_n = f2polymod_An_list(Fq_m, n);
		int qn = Fq_n.get_num_rows();

		for (int i = 0; i < qn; i++) {
			f2polymod_t fx = f.eval(Fq_n[i]);
			if (fx == Fq_zero) {
				if (print_all_elts)
					std::cout << "f(" << Fq_n[i] << ") = " << fx << "\n";
				num_affine++;
			}
		}

		if (print_all_elts) {
			std::cout << "\n";
			std::cout << "Projective zeroes:\n";
		}
		std::cout << "F = " << F << "\n";

		tmatrix<f2polymod_t> Pn_Fq = f2polymod_Pn_list(Fq_m, n);
		int oP = Pn_Fq.get_num_rows();

		for (int i = 0; i < oP; i++) {
			f2polymod_t FX = F.eval(Pn_Fq[i]);
			if (FX == Fq_zero) {
				if (print_all_elts)
					std::cout << "F(" << Pn_Fq[i] << ") = " << FX << "\n";
				num_projective++;
			}
		}
		int q = 1 << Fq_m.find_degree();
		printf("q = %d n = %d\n", q, n);
		printf("# affine     = %5d / %5d\n",
			num_affine, Fq_n.get_num_rows());
		printf("# projective = %5d / %5d\n",
			num_projective, Pn_Fq.get_num_rows());
	}

	return 0;
}
