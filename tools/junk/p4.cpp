#include <iostream>
#include <sstream>
//#include "cmdlineops.h"

template <class element_type>
struct atom_t {
	element_type type_val;
	int int_val;
};

//#define element_type int
template <class element_type>
void foo(int argc, char ** argv)
{
	element_type a;
	for (int argi = 1; argi < argc; argi++) {
		std::istringstream iss(argv[argi], std::ios_base::in);
		iss >> a;
		if (iss.fail()) {
			std::cerr << "Scan failure at " << argv[argi]
				<< ".\n";
			exit(1);
		}
		std::cout << "{" << a << "}\n";
	}
}

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	//parse<int>(argc, argv);
	//foo(argc, argv);
	//foo<int>(argc, argv);
	foo<float>(argc, argv);
	return 0;
}
