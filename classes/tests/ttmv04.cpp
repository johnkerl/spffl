#include "tmvpoly.h"
#include "f2polymod_t.h"
#include "sp_list_elts.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {reductors ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
static int is_canon_rep_hack(
	f2polymod_t & X,
	f2polymod_t & Y,
	f2polymod_t & Z,
	f2polymod_t & zero,
	f2polymod_t & one)
{
	if (Z == one)
		return 1;
	if (Z != zero)
		return 0;
	if (Y == one)
		return 1;
	if (Y != zero)
		return 0;
	if (X == one)
		return 1;
	if (X != zero)
		return 0;
	return 1;
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	if (argc < 2)
		usage(argv[0]);

	for (int argi = 1; argi < argc; argi++) {
		unsigned im;
		if (sscanf(argv[argi], "%x", &im) != 1) {
			std::cerr << "Couldn't parse \"" << argi << "\".\n";
			exit(1);
		}

		f2poly_t m = f2poly_t::from_base_rep(im);
		f2polymod_t zero = f2polymod_t::prime_sfld_elt(0, m);
		f2polymod_t one  = f2polymod_t::prime_sfld_elt(1, m);
		std::cout <<
		"----------------------------------------------------------------\n";
		std::cout << "m = " << m << "\n";

#if 1
		// Cubic
		tmvpoly<f2polymod_t> f =
			tmvpoly<f2polymod_t>(one, 3, 0) +
			tmvpoly<f2polymod_t>(one, 0, 3) +
			tmvpoly<f2polymod_t>(one, 0, 0);
#endif

#if 0
		// Klein quartic
		tmvpoly<f2polymod_t> f =
			tmvpoly<f2polymod_t>(one, 3, 1) +
			tmvpoly<f2polymod_t>(one, 0, 3) +
			tmvpoly<f2polymod_t>(one, 1, 0);
#endif

#if 0
		// Quintic
		tmvpoly<f2polymod_t> f =
			tmvpoly<f2polymod_t>(one, 5, 0) +
			tmvpoly<f2polymod_t>(one, 0, 5) +
			tmvpoly<f2polymod_t>(one, 0, 0);
#endif

#if 0
		// HW 2.13.7
		tmvpoly<f2polymod_t> f =
			tmvpoly<f2polymod_t>(one, 5, 0) +
			tmvpoly<f2polymod_t>(one, 0, 4) +
			tmvpoly<f2polymod_t>(one, 0, 1);
#endif

#if 0
		// HW 2.13.8
		tmvpoly<f2polymod_t> f =
			tmvpoly<f2polymod_t>(one, 7, 0) +
			tmvpoly<f2polymod_t>(one, 0, 7) +
			tmvpoly<f2polymod_t>(one, 0, 0);
#endif

		tmvpoly<f2polymod_t> F = f.homogenize();

		std::cout << "\n";
		std::cout << "Affine zeroes:\n";
		std::cout << "f = " << f << "\n";

		tvector<f2polymod_t> Fq = f2polymod_list(m, 0);
		int oFq = Fq.get_num_elements();

		for (int i = 0; i < oFq; i++) {
			for (int j = 0; j < oFq; j++) {
				f2polymod_t x = Fq[i];
				f2polymod_t y = Fq[j];
				f2polymod_t fxy = f.eval(x, y);
				if (fxy == zero)
				std::cout << "f(" << x << "," << y << ") = " << fxy << "\n";
			}
		}

		std::cout << "\n";
		std::cout << "Projective zeroes:\n";
		std::cout << "F = " << F << "\n";

		for (int i = 0; i < oFq; i++) {
			for (int j = 0; j < oFq; j++) {
				for (int k = 0; k < oFq; k++) {
					f2polymod_t X = Fq[i];
					f2polymod_t Y = Fq[j];
					f2polymod_t Z = Fq[k];

					// xxx need to limit to one rep per equiv class!
					// xxx see if leader is 1 or 0
					if (!is_canon_rep_hack(X, Y, Z, zero, one))
						continue;

					f2polymod_t FXYZ = F.eval(X, Y, Z);
					if (FXYZ == zero)
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
