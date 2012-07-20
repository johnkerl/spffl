// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the
// "Software"), to deal in the Software without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the
// following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN
// NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
// USE OR OTHER DEALINGS IN THE SOFTWARE.
//
// This program is free software; you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation; either version 2 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program; if not, write to the Free Software Foundation, Inc., 59 Temple
// Place, Suite 330, Boston, MA  02111-1307  USA
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
