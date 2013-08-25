// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "tfacinfo.h"

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	tfacinfo<int> finfo;
	int f;
	for (int argi = 1; argi < argc; argi++) {
		(void)sscanf(argv[argi], "%d", &f);
		finfo.insert_factor(f);
		std::cout << finfo << "\n";
	}

	return 0;
}
