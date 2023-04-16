// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2npolymod_random.h"
#include "f2npoly_random.h"

// ----------------------------------------------------------------
f2npolymod_t f2npolymod_random(f2poly_t im, f2npoly_t om)
{
	int deg = om.find_degree();
	f2npoly_t r = f2npoly_random(im, deg);
	return f2npolymod_t(r, om);
}
