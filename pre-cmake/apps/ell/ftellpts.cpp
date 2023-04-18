#include "libspffl.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cout << "Usage: " << argv0 << " {m} {a1,a2,a3,a4,a6}\n";
	std::cout << "Where y^2 + a1 x y + a3 y = x^3 + a2 x^2 + a4 x + a6\n";
	exit(1);
}

// ----------------------------------------------------------------
void checkf(
	f2polymod_t a1,
	f2polymod_t a2,
	f2polymod_t a3,
	f2polymod_t a4,
	f2polymod_t a6,
	f2polymod_t x,
	f2polymod_t y,
	f2polymod_t z)
{
	f2polymod_t lhs = y*y*z + a1*x*y*z + a3*y*z*z;
	f2polymod_t rhs = x*x*x + a2*x*x*z + a4*x*z*z + a6*z*z*z;
	if (lhs == rhs) {
		std::cout << x << "," << y << "," << z << "\n";
	}
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	f2poly_t m;
	f2polymod_t a1, a2, a3, a4, a6;
	f2polymod_t x, y, z;

	if (argc != 3)
		usage(argv[0]);
	if (!m.from_string(argv[1]))
		usage(argv[0]);
	if (!ft_scan_quintuple(argv[2], m, a1, a2, a3, a4, a6))
		usage(argv[0]);

	tvector<f2polymod_t> Fq = f2polymod_list(m, SP_LIST_ALL);
	int q = Fq.get_num_elements();

	// x=* y=1 z=0
	// x=1 y=0 z=0
	// x=* y=* z=1

	f2polymod_t zero = f2polymod_t::prime_sfld_elt(0, m);
	f2polymod_t one  = f2polymod_t::prime_sfld_elt(1, m);

	y = one;
	z = zero;
	for (int i = 0; i < q; i++) {
		checkf(a1, a2, a3, a4, a6, Fq[i], y, z);
	}

	x = one;
	y = zero;
	z = zero;
	checkf(a1, a2, a3, a4, a6, x, y, z);

	z = one;
	for (int i = 0; i < q; i++) {
		for (int j = 0; j < q; j++) {
			checkf(a1, a2, a3, a4, a6, Fq[i], Fq[j], z);
		}
	}

	return 0;
}

//	check_point("input", a1, a2, a3, a4, a6, x1, y1, z1);
//	check_point("input", a1, a2, a3, a4, a6, x2, y2, z2);
//
//	if (x1 == zero && y1 == one && z1 == zero) {
//		// P1 is O
//		x3 = x2;
//		y3 = y2;
//		z3 = z2;
//	}
//	else if (x2 == zero && y2 == one && z2 == zero) {
//		// P2 is O
//		x3 = x1;
//		y3 = y1;
//		z3 = z1;
//	}
//	else if (x1 == x2 && y1 == y2 && z1 == z2) {
//		if (y1 == zero) {
//			x3 = zero;
//			y3 = one;
//			z3 = zero;
//		}
//		else {
//			// Duplication formula
//			lambda = (x1*x1 + a4 + a1*y1) / (a1*x1 + a3);
//			nu = (x1*x1*x1 + a4*x1 + a3*y1) / (a1*x1 + a3);
//
//			x3 = lambda*lambda + a1*lambda- a2 - x1 - x2;
//			y3 = -(lambda + a1)*x3 - nu - a3;
//			z3 = one;
//		}
//	}
//	else if (x1 == x2) {
//		// Vertical line
//		x3 = zero;
//		y3 = one;
//		z3 = zero;
//	}
//	else {
//		// Product formula:  Silverman pp. 58-59.
//		lambda = (y2 - y1) / (x2 - x1);
//		nu = (y1*x2 - y2*x1) / (x2 - x1);
//
//		x3 = lambda*lambda + a1*lambda- a2 - x1 - x2;
//		y3 = -(lambda + a1)*x3 - nu - a3;
//		z3 = one;
//	}
//
//	check_point("computed", a1, a2, a3, a4, a6, x3, y3, z3);
//
//	std::cout << x3 << "," << y3 << "," << z3 << "\n";
//
//	return 0;
//}
