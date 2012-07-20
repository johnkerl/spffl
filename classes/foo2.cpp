#include <iostream>
#include "int_gcd.h"
#include "tmatrix.h"

int main(void)
{
	tmatrix<int> A;
	A = 0;
	std::cin >> A;
	std::cerr << A << "\n";

	int det = A.ed_det();
	std::cerr << "d=" << det << "\n";

	return 0;
}
