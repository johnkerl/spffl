// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <stdlib.h>
#include <iostream>
#include "int_sqrt.h"

// ----------------------------------------------------------------
int int_sqrt(
	int nsigned,
	int want_ceil)
{
	unsigned n = (unsigned)nsigned;
	unsigned nsv, half_log;
	unsigned lower, upper, diff;
	unsigned half_diff, middle, middle_sq;

	if (nsigned < 0) {
		std::cerr << "int_sqrt:  Can't handle negative input "
			<< nsigned << "\n";
		exit(1);
	}

	if (nsigned == 0)
		return 0;

	for (nsv = n, half_log = 0; nsv != 0; nsv >>= 2, half_log++)
		;
	half_log--;
	lower = 1 << half_log;
	upper = lower << 1;
	diff  = upper - lower;

	while (diff > 0) {
		half_diff = diff >> 1;
		middle = lower + half_diff;
		middle_sq = middle * middle;
		if (middle_sq == n)
			return middle;
		else if (middle_sq < n)
			lower += half_diff;
		else
			upper -= half_diff;
		diff = half_diff;
	}
	if (want_ceil == ICEIL)
		return upper;
	else
		return lower;
}
