#include <iostream>
#include <sstream>
#include "cmdlineops.h"
#include "f2ipoly_t.h"
#include "intmod_t.h"

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	//cmd_line_parse<int>(argc, argv, 0);
	//cmd_line_parse<f2ipoly_t>(argc, argv, f2ipoly_t(0));
	cmd_line_parse<intmod_t>(argc-1, argv+1, intmod_t(0, 11));
	return 0;
}
