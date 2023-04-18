#include <iostream>
#include "bit_matrix_t.h"
#include "tmatrix.h"

int main(int argc, char ** argv)
{
	int n = 1000;

	if (argc == 2) {
		tmatrix<bit_t> A(bit_t(0), 1, 1);
		std::cin >> A;
		tmatrix<bit_t> B(A);
		for (int i = 0; i < n; i++) {
			//B = B * A;
			B = A;
			//B.row_reduce_below();
			B.row_echelon_form();
		}
		std::cout << B << "\n";
	}
	else {
		bit_matrix_t A;
		std::cin >> A;
		bit_matrix_t B(A);
		for (int i = 0; i < n; i++) {
			//B = B * A;
			B = A;
			//B.row_reduce_below();
			B.row_echelon_form();
		}
		std::cout << B << "\n";
	}

	return 0;
}
