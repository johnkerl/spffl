#include <iostream>
#include "f2poly_t.h"
#include "tmatrix.h"

int main(void)
{
	f2poly_t zero(0);
	tmatrix<f2poly_t> A;
	A = zero;
	std::cin >> A;
	std::cerr << A << "\n";

	f2poly_t det = A.ed_det();
	std::cerr << "d=" << det << "\n";

	return 0;
}
