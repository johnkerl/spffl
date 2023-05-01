#include "spffl/libspffl.h"

// y^2 + xy = x^3 + ax + b

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cout << "Usage: " << argv0 << " {p} {a,b} {x1,y1,z1} {x2,y2,z2}\n";
	exit(1);
}

// ----------------------------------------------------------------
static void check_point(
	const char * desc,
	intmod_t a,
	intmod_t b,
	intmod_t c,
	intmod_t x,
	intmod_t y,
	intmod_t z)
{
	intmod_t f = y * y - x * (x * (x - a) - b) - c;
	intmod_t zero = y - y;
	if (f != zero) {
#if 1
		std::cerr
			<< "The " << desc << " point [" << x << "," << y << "," << z
			<< "] is not on the curve y^2 = x^3 + "
			<< a << "x + "
			<< b << "x + "
			<< c << ".\n";
		exit(1);
#else
		std::cout << "#";
#endif
	}
	else {
#if 1
#else
		std::cout << " ";
#endif
	}
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	int p;
	intmod_t a, b, c;
	intmod_t x1, y1, z1;
	intmod_t x2, y2, z2;
	intmod_t x3, y3, z3;
	intmod_t lambda, nu;

	if (argc != 5)
		usage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		usage(argv[0]);
	if (!fp_scan_triple(argv[2], p, a, b, c))
		usage(argv[0]);
	if (!fp_scan_triple(argv[3], p, x1, y1, z1))
		usage(argv[0]);
	if (!fp_scan_triple(argv[4], p, x2, y2, z2))
		usage(argv[0]);

	intmod_t zero(0, p);
	intmod_t one (1, p);
	check_point("input", a, b, c, x1, y1, z1);
	check_point("input", a, b, c, x2, y2, z2);

	if (x1 == zero && y1 == one && z1 == zero) {
		// P1 is O
		x3 = x2;
		y3 = y2;
		z3 = z2;
	}
	else if (x2 == zero && y2 == one && z2 == zero) {
		// P2 is O
		x3 = x1;
		y3 = y1;
		z3 = z1;
	}
	else if (x1 == x2 && y1 == y2 && z1 == z2) {
		if (y1 == 0) {
			x3 = zero;
			y3 = one;
			z3 = zero;
		}
		else {
			// Duplication formula
			lambda = (x1*x1*3 + a*x1*2 + b) / (y1*2);
			nu = y1 - lambda * x1;
			x3 = lambda*lambda - a - x1 - x1;
			y3 = -(lambda*x3 + nu);
			z3 = one;
		}
	}
	else if (x1 == x2) {
		// Vertical line
		x3 = zero;
		y3 = one;
		z3 = zero;
	}
	else {
		// Product formula
		lambda = (y2 - y1) / (x2 - x1);
		nu = y1 - lambda * x1;
		x3 = lambda*lambda - a - x1 - x2;
		y3 = -(lambda*x3 + nu);
		z3 = one;
	}

	check_point("computed", a, b, c, x3, y3, z3);

	std::cout << x3 << "," << y3 << "," << z3 << "\n";

	return 0;
}
