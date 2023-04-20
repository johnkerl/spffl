// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <stdio.h>

#include "f2polymod_t.h"
#include "cmd_line_ops.h"

typedef void usage_t(char * argv0);
typedef int main_t (int argc, char ** argv, usage_t * pusage);

static void f2pmop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {m} ...\n";
	exit(1);
}

static int f2pmop_main(int argc, char ** argv, usage_t * pusage)
{
	f2poly_t m;
	if (argc < 2)
		pusage(argv[0]);
	if (!m.from_string(argv[1]))
		pusage(argv[0]);
	cmd_line_parse<f2polymod_t>(argc-2, argv+2,
		f2polymod_t(f2poly_t(0), m),
		f2polymod_t(f2poly_t(1), m));
	return 0;
}

int main(int argc, char ** argv)
{
	return f2pmop_main(argc, argv, f2pmop_usage);
}
