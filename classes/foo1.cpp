#include <iostream>
#include "int_gcd.h"
#include "tmatrix.h"

int main(void)
{
	tmatrix<int> A;
	A = 0;
	std::cin >> A;
	std::cerr << A << "\n";

	int sn, sd;
	A.ed_row_reduce_below_with_scalar(sn, sd);
	std::cout << A << "\n";
	std::cerr << "sn=" << sn << " sd=" << sd << "\n";

	return 0;
}
