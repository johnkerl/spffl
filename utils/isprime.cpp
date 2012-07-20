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
#include <stdlib.h>
#include "isprime.h"
#include "primes16.h"

// ----------------------------------------------------------------
int isprime_trial(int n)
{
	int d, q;

	if (n == -n)
		return 0;
	else if (n < 0)
		n = -n;

	if (n <= 1)
		return 0;
	else if (n <= 3)
		return 1;
	else if ((n & 1) == 0)
		return 0;

	for (d = 3, q = n; d <= q; d += 2) {
		q = n / d;
		if (n == q * d)
			return 0;
	}

	return 1;
}

// ----------------------------------------------------------------
int isprime_table(int n)
{
	int i;
	unsigned un;

	if (n == -n)
		return 0;
	else if (n < 0)
		n = -n;

	if (n <= 1)
		return 0;

	un = (unsigned) n;
	for (i = 0; i < numprimes16; i++) {
		if ((un % primes16[i]) == 0) {
			if (un == primes16[i])
				return 1;
			else
				return 0;
		}
		if (primes16[i] * primes16[i] > un)
			return 1;
	}
	return 1;
}

// ----------------------------------------------------------------
int isprime(int n)
{
	//return isprime_trial(n);
	return isprime_table(n);
}

// ----------------------------------------------------------------
int nthprime(int n)
{
	if (n > numprimes16) {
		std::cerr << "nthprime:  n=" << n << " past end of table.\n";
		exit(1);
	}
	else if (n < 1) {
		std::cerr << "nthprime:  n=" << n << " should have been positive.\n";
		exit(1);
	}
	return (int)primes16[n-1];
}
