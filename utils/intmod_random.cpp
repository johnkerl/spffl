// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "intmod_random.h"
#include "int_random.h"

// ----------------------------------------------------------------
intmod_t intmod_random(int m)
{
	if (m < 2) {
		std::cerr << "intmod_random:  modulus " << m
			<< " should be >= 2.\n";
		exit(1);
	}
	return intmod_t(get_random_int(), m);
}
