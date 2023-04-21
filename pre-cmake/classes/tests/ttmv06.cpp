#include "tmvpoly.h"
#include "f2_polymod_t.h"
#include "list_elements.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {reductors ... }\n";
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
tmvpoly<f2_polymod_t> get_f(
	f2_polymod_t & F2_zero,
	f2_polymod_t & F2_one)
{

#if 0
	// Cubic
	tmvpoly<f2_polymod_t> F2_f =
		tmvpoly<f2_polymod_t>(F2_one, 3, 0) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 3) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 0);
#endif

#if 0
	// Klein quartic
	tmvpoly<f2_polymod_t> F2_f =
		tmvpoly<f2_polymod_t>(F2_one, 3, 1) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 3) +
		tmvpoly<f2_polymod_t>(F2_one, 1, 0);
#endif

#if 0
	// Quintic
	tmvpoly<f2_polymod_t> F2_f =
		tmvpoly<f2_polymod_t>(F2_one, 5, 0) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 5) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 0);
#endif

#if 0
	// HW 2.13.7
	tmvpoly<f2_polymod_t> F2_f =
		tmvpoly<f2_polymod_t>(F2_one, 5, 0) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 4) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 1);
#endif

#if 0
	// HW 2.13.8
	tmvpoly<f2_polymod_t> F2_f =
		tmvpoly<f2_polymod_t>(F2_one, 7, 0) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 7) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 0);
#endif

#if 1
	tmvpoly<f2_polymod_t> F2_f =
		tmvpoly<f2_polymod_t>(F2_one, 3, 0, 0) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 2, 0) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 0, 1) +
		tmvpoly<f2_polymod_t>(F2_one, 0, 0, 0);
#endif

	return F2_f;
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	f2_poly_t    F2_m    = f2_poly_t::from_base_rep(3);
	f2_polymod_t F2_zero = f2_polymod_t::prime_sfld_elt(0, F2_m);
	f2_polymod_t F2_one  = f2_polymod_t::prime_sfld_elt(1, F2_m);

	tmvpoly<f2_polymod_t> F2_f = get_f(F2_zero, F2_one);
	tmvpoly<f2_polymod_t> F2_F = F2_f.homogenize();

	if (argc < 2)
		usage(argv[0]);

	for (int argi = 1; argi < argc; argi++) {
		unsigned im;
		if (sscanf(argv[argi], "%x", &im) != 1) {
			std::cerr << "Couldn't parse \"" << argi << "\".\n";
			exit(1);
		}
		f2_poly_t Fq_m       = f2_poly_t::from_base_rep(im);
		f2_polymod_t Fq_zero = f2_polymod_t::prime_sfld_elt(0, Fq_m);
		f2_polymod_t Fq_one  = f2_polymod_t::prime_sfld_elt(1, Fq_m);

		tmvpoly<f2_polymod_t> f = F2_Fq_embed(F2_f, Fq_zero, Fq_one);
		tmvpoly<f2_polymod_t> F = f.homogenize();

		int n = f.get_nvars();

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout << "m = " << Fq_m << "\n";

		std::cout << "\n";
		std::cout << "Affine zeroes:\n";
		std::cout << "f = " << f << "\n";

		tmatrix<f2_polymod_t> Fq_n = f2polymod_An_list(Fq_m, n);
		int qn = Fq_n.get_num_rows();

		for (int i = 0; i < qn; i++) {
			f2_polymod_t fx = f.eval(Fq_n[i]);
			if (fx == Fq_zero)
				std::cout << "f(" << Fq_n[i] << ") = " << fx << "\n";
		}

		std::cout << "\n";
		std::cout << "Projective zeroes:\n";
		std::cout << "F = " << F << "\n";

		tmatrix<f2_polymod_t> Pn_Fq = f2polymod_Pn_list(Fq_m, n);
		int oP = Pn_Fq.get_num_rows();

		for (int i = 0; i < oP; i++) {
			f2_polymod_t FX = F.eval(Pn_Fq[i]);
			if (FX == Fq_zero)
				std::cout << "F(" << Pn_Fq[i] << ") = " << FX << "\n";
		}
	}

	return 0;
}
