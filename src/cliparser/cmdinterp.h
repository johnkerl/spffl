#ifndef CMDINTERP_H
#define CMDINTERP_H

void cmd_interpolate(
	char    * exename,
	int     & argc,
	char ** & argv);

// Example:  If exename is "proggy" and argc, argv are "a b { c d e }", this
// function runs "proggy c d e".  Say the output of that command is "hello
// there".  Then this function modifies argc, argv such that they are now
// "proggy a b hello there".
//
// Key point: the program executed is always taken from exename.  This means
// the program executes itself, rather than some other program e.g.
// "proggy a b { otherproggy c d e }".
//
// Nested pairs are handled.
//
// Sample usage:
//
// int main(int argc, char ** argv)
// {
//     char * exename = argv[0];
//     argc--, argv++;
//
//     cmd_interpolate(exename, argc, argv, interpolated);
//     handle_command(argc, argv); // in whatever way the program wishes.
//
//     return 0;
// }

#endif // CMDINTERP_H
