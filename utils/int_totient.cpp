// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "int_gcd.h"
#include "int_totient.h"

// ----------------------------------------------------------------
int int_totient(int n)
{
	int phi = 0;
	int i;

	phi = 0;
	for (i = 1; i < n; i++) {
		if (int_gcd(n, i) == 1)
			phi++;
	}

	return phi;
}
