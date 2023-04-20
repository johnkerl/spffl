#include "tmvpoly.h"
#include "tmvpolyscan.h"
#include "f2polymod_t.h"
#include "sp_list_elts.h"
#include "f2_poly_factor.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {f} {points ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	f2poly_t m;
	tmvpoly<f2polymod_t> f;
	f2polymod_t zero;

	if (argc < 4)
		usage(argv[0]);
	if (!m.from_string(argv[1]))
		usage(argv[0]);
	if (!tmvpoly_f2polymod_from_string(f, argv[2], m))
		usage(argv[0]);
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
