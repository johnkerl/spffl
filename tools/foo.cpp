#include "tvector.h"
#include "f2npolymod_units.h"
#include "sp_list_elts.h"

static void pusage(char * argv0)
{
	std::cerr << "feh!\n";
	exit(1);
}

int main(int argc, char ** argv)
{
	f2poly_t im;
	f2npoly_t om;
	f2npolymod_t g;
	if (argc != 3)
		pusage(argv[0]);
	if (!im.from_string(argv[1]))
		pusage(argv[0]);
	if (!om.from_string(argv[2], im))
		pusage(argv[0]);

	if (!f2npolymod_find_generator(om, g)) {
		std::cerr << "Couldn't find generator mod "
			<< om << "\n";
		exit(1);
	}

	tvector<f2npolymod_t> elts = f2npolymod_list(om, SP_LIST_UNITS);
	int n = elts.get_num_elements();

	std::cout << "element power\n";
	std::cout << "------- -----\n";
	for (int i = 0; i < n; i++) {
		int e = f2npolymod_log(g, elts[i]);
		std::cout << elts[i] << " " << e << "\n";
	}
	return 0;
}
