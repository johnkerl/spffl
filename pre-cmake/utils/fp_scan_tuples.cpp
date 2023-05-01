#include <stdio.h>
#include "spffl/fp_scan_tuples.h"

// ----------------------------------------------------------------
int fp_scan_triple(
	char     * input,
	int        p,
	intmod_t & a,
	intmod_t & b,
	intmod_t & c)
{
	int ai, bi, ci;

	if (sscanf(input, "%d,%d,%d", &ai, &bi, &ci) != 3)
		return 0;
	a = intmod_t(ai, p);
	b = intmod_t(bi, p);
	c = intmod_t(ci, p);
	return 1;
}
