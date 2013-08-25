// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fppoly_random.h"
#include "intmod_random.h"

// ----------------------------------------------------------------
fppoly_t fppoly_random(int p, int deg)
{
	if (deg < 0) {
		std::cerr << "fppoly_random:  degree " << deg
			<< " must be non-negative.\n";
		exit(1);
	}

	intmod_t zero(0, p);
	intmod_t one(1, p);
	fppoly_t rv(zero);
	for (int i = deg; i >= 0; i--) {
		intmod_t c = intmod_random(p);
		if ((i == deg) && (c == zero))
			c = one;
		rv.set_coeff(i, c);
	}
	return rv;
}
