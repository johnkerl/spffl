#include "spffl/libspffl.h"

// ----------------------------------------------------------------
static void usage(char * argv0)
{
	std::cout << "Usage: " << argv0 << " {m} {n}\n";
	exit(1);
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	int m, n, mn;

	if (argc != 3)
		usage(argv[0]);
	if (sscanf(argv[1], "%d", &m) != 1)
		usage(argv[0]);
	if (sscanf(argv[2], "%d", &n) != 1)
		usage(argv[0]);
	mn = m * n;

	for (int x = 0; x < mn; x++) {
		intmod_t xmn(x, mn);
		intmod_t xm(x, m);
		intmod_t xn(x, n);

		int a = xm.get_residue();
		int b = xn.get_residue();

		// Solve y == 2 (mod 7), 5 (mod 13):
		// 13 (2/13)(mod 7) + 7(5/7)(mod 13)

		// Solve y == a (mod m), b (mod n):
		// n * (a/n) (mod m)  +  m * (b/m) (mod n)

		intmod_t anm = intmod_t(a, m) / intmod_t(n, m);
		intmod_t bmn = intmod_t(b, n) / intmod_t(m, n);

		intmod_t ymn(n * anm.get_residue() + m * bmn.get_residue(), mn);

		std::cout << xmn << " |--> (" << xm << ", " << xn << ") |--> " << ymn << " ck " << ymn-xmn << "\n";
	}

	return 0;
}
