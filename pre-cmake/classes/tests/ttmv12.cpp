#include "spffl/tmvpoly.h"
#include "spffl/tmvpolyscan.h"
#include "spffl/f2_polymod_t.h"
#include "spffl/list_elements.h"
#include "spffl/f2_poly_factor.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} {f} {points ... }\n";
	exit(1);
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	f2_poly_t m;
	tmvpoly<f2_polymod_t> f;
	f2_polymod_t zero;

	if (argc < 4)
		usage(argv[0]);
	if (!m.from_string(argv[1]))
		usage(argv[0]);
	if (!tmvpoly_f2_polymod_from_string(f, argv[2], m))
		usage(argv[0]);
	zero = f2_polymod_t::prime_subfield_element(0, m);

	for (int argi = 3; argi < argc; argi++) {
		tvector<f2_polymod_t> c(zero, 1);
		f2_polymod_t fc;

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
