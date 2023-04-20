// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <stdio.h>

#include "cmd_line_ops.h"

typedef void usage_t(char * argv0);
typedef int main_t (int argc, char ** argv, usage_t * pusage);

static void zop_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " ...\n";
	exit(1);
}

static int zop_main(int argc, char ** argv, usage_t * pusage)
{
	cmd_line_parse<int>(argc-1, argv+1, 0, 1);
	return 0;
}


int main(int argc, char ** argv)
{
	return zop_main(argc, argv, zop_usage);
}
