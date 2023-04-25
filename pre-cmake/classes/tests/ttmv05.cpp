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
static bool is_canon_rep_hack(
	f2_polymod_t & X,
	f2_polymod_t & Y,
	f2_polymod_t & Z,
	f2_polymod_t & zero,
	f2_polymod_t & one)
{
	if (Z == one)
		return true;
	if (Z != zero)
		return false;
	if (Y == one)
		return true;
	if (Y != zero)
		return false;
	if (X == one)
		return true;
	if (X != zero)
		return false;
	return true;
}

// ----------------------------------------------------------------
tmvpoly<f2_polymod_t> get_f(
	f2_polymod_t & F2_zero,
	f2_polymod_t & F2_one)
{
#if 1
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

		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout << "m = " << Fq_m << "\n";

		std::cout << "\n";
		std::cout << "Affine zeroes:\n";
		std::cout << "f = " << f << "\n";

		tvector<f2_polymod_t> Fq = f2_polymod_list(Fq_m, 0);
		int oFq = Fq.get_num_elements();

		tmatrix<f2_polymod_t> Fq_n = f2_polymod_An_list(Fq_m, 2);

		for (int i = 0; i < oFq; i++) {
			for (int j = 0; j < oFq; j++) {
				f2_polymod_t x = Fq[i];
				f2_polymod_t y = Fq[j];
				f2_polymod_t fxy = f.eval(x, y);
				if (fxy == Fq_zero)
					std::cout << "f(" << x << "," << y << ") = " << fxy << "\n";
			}
		}

		std::cout << "\n";
		std::cout << "Projective zeroes:\n";
		std::cout << "F = " << F << "\n";
		// xxx get_Pn_Fq

		for (int i = 0; i < oFq; i++) {
			for (int j = 0; j < oFq; j++) {
				for (int k = 0; k < oFq; k++) {
					f2_polymod_t X = Fq[i];
					f2_polymod_t Y = Fq[j];
					f2_polymod_t Z = Fq[k];

					// xxx need to limit to one rep per equiv class!
					// xxx see if leader is 1 or 0
					if (!is_canon_rep_hack(X, Y, Z, Fq_zero, Fq_one))
						continue;

					f2_polymod_t FXYZ = F.eval(X, Y, Z);
					if (FXYZ == Fq_zero)
					std::cout << "F("
						<< X << ","
						<< Y << ","
						<< Z << ") = "
						<< FXYZ << "\n";
				}
			}
		}
	}

	return 0;
}
