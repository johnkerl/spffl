#include <iostream>
#include "int_gcd.h"
#include "tmatrix.h"

int main(void)
{
	int zero(0);
	tmatrix<int> A;
	A = zero;
	std::cin >> A;
	std::cerr << A << "\n";

	A.ed_row_echelon_form();
	std::cout << A << "\n";

	return 0;
}
