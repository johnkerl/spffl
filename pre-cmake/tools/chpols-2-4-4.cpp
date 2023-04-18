// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <stdio.h>

#include "tmatrix.h"
#include "bit_t.h"
#include "f2linalg.h"

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	for (int i = 0; i < 65536; i++) {
		tmatrix<bit_t> A = f2_matrix_from_base_rep(i, 4, 4);
		f2poly_t d = f2_char_poly(A);
		std::cout << d << "\n";
	}
	return 0;
}

//   1344 13:  13
//   1344 19:  19
//   1344 1f:  1f
//   1792 15:  7^2
//   2880 16:  2 b
//   2880 17:  3 d
//   2880 1a:  2 d
//   2880 1d:  3 b
//   4096 10:  2^4
//   4096 11:  3^4
//   4480 1b:  3^2 7
//   4480 1c:  2^2 7
//   6720 12:  2 3 7
//   7680 18:  2^3 3
//   7680 1e:  2 3^3
//   8960 14:  2^2 3^2
