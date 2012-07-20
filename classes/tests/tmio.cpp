#include "tmatrix.h"
#include "mod_t.h"

// ----------------------------------------------------------------
void vector_from_string(void)
{
	tvector<mod_t> u(1);
	u[0] = mod_t(0, 2);

	std::istringstream iss("0 1 1 0 1", std::ios_base::in);
	iss >> u;
	if (iss.fail()) {
		std::cerr << "Vector scan error.\n";
		exit(1);
	}
	std::cout << u << std::endl;
}

// ----------------------------------------------------------------
void vector_from_stream(void)
{
	tvector<mod_t> u(1);
	u[0] = mod_t(0, 2);

	std::cout << "Vector: ";
	std::cout.flush();
	std::cin >> u;
	if (std::cin.fail()) {
		std::cerr << "Vector scan error.\n";
		exit(1);
	}
	std::cout << u << std::endl;
}

// ----------------------------------------------------------------
int main()
{
	//vector_from_string();
	vector_from_stream();

	return 0;
}
