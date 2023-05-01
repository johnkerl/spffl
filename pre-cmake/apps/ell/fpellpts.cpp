#include "spffl/libspffl.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cout << "Usage: " << argv0 << " {p} {a,b,c}\n";
	exit(1);
}

// ----------------------------------------------------------------
void checkf(
	intmod_t a,
	intmod_t b,
	intmod_t c,
	intmod_t x,
	intmod_t y,
	intmod_t z)
{
	intmod_t lhs = y*y*z;
	intmod_t rhs = x*x*x + a*x*x*z + b*x*z*z + c*z*z*z;
	if (lhs == rhs) {
		std::cout << x << "," << y << "," << z << "\n";
	}
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	int p;
	intmod_t a, b, c;
	intmod_t x, y, z;

	if (argc != 3)
		usage(argv[0]);
	if (sscanf(argv[1], "%d", &p) != 1)
		usage(argv[0]);
	if (!fp_scan_triple(argv[2], p, a, b, c))
		usage(argv[0]);

	// x=* y=1 z=0
	// x=1 y=0 z=0
	// x=* y=* z=1

	y = intmod_t(1, p);
	z = intmod_t(0, p);
	for (int xi = 0; xi < p; xi++) {
		x = intmod_t(xi, p);
		checkf(a, b, c, x, y, z);
	}

	x = intmod_t(1, p);
	y = intmod_t(0, p);
	z = intmod_t(0, p);
	checkf(a, b, c, x, y, z);

	z = intmod_t(1, p);
	for (int xi = 0; xi < p; xi++) {
		x = intmod_t(xi, p);
		for (int yi = 0; yi < p; yi++) {
			y = intmod_t(yi, p);
			checkf(a, b, c, x, y, z);
		}
	}

	return 0;
}
