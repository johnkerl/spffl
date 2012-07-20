#include <iostream>
#include <sstream>
#include "cmdlinematops.h"
#include "tmatrix.h"
#include "bit_t.h"

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	cmd_line_mat_parse<bit_t>(argc-1, argv+1, bit_t(0), bit_t(1));
	return 0;
}
