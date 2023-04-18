// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <stdio.h>
#include "cmdinterp.h"

#include "handlers.h"

#include "z_handlers.h"
#include "q_handlers.h"

#include "f2_handlers.h"
#include "f2poly_handlers.h"
#include "f2polymod_handlers.h"
#include "f2npoly_handlers.h"
#include "f2npolymod_handlers.h"

#include "fp_handlers.h"
#include "fppoly_handlers.h"
#include "fppolymod_handlers.h"

// ----------------------------------------------------------------
// TODO: add another level here

typedef struct _lookup_t {
	const char * name;
	main_t  * pmain;
	usage_t * pusage;
} lookup_t;

lookup_t lookups[] =
{

	{"zop",            zop_main,            0 /*zop_usage*/},
	{"zgcd",           zgcd_main,           zgcd_usage},
	{"zlcm",           zlcm_main,           zlcm_usage},
	{"ztotient",       ztotient_main,       ztotient_usage},
	{"ztestprime",     ztestprime_main,     ztestprime_usage},
	{"nthprime",       nthprime_main,       nthprime_usage},
	{"zlist",          zlist_main,          zlist_usage},
	{"zfactor",        zfactor_main,        zfactor_usage},
	{"zdivisors",      zdivisors_main,      zdivisors_usage},
	{"zmatop",         zmatop_main,         0 /*zmatop_usage*/},

	{"qop",            qop_main,            0 /*qop_usage*/},
	{"qvecop",         qvecop_main,         0 /*qvecop_usage*/},
	{"qmatop",         qmatop_main,         0 /*qmatop_usage*/},

	{"qcyclo",         qcyclo_main,         qcyclo_usage},
	{"qpop",           qpop_main,           0 /*qcyclo_usage*/},

	{"f2op",           f2op_main,           0 /*f2op_usage*/},
	{"f2random",       f2random_main,       f2random_usage},

	{"f2vecop",        f2vecop_main,        0 /*f2vecop_usage*/},
	{"f2matop",        f2matop_main,        0 /*f2matop_usage*/},
	{"f2matchpol",     f2matchpol_main,     f2matchpol_usage},
	{"f2matord",       f2matord_main,       f2matord_usage},
	{"f2matrandom",    f2matrandom_main,    f2matrandom_usage},

	{"f2plist",        f2plist_main,        f2plist_usage},
	{"f2pop",          f2pop_main,          0 /*f2pop_usage*/},
	{"f2pdeg",         f2pdeg_main,         f2pdeg_usage},
	{"f2pgcd",         f2pgcd_main,         f2pgcd_usage},
	{"f2plcm",         f2plcm_main,         f2plcm_usage},
	{"f2ptotient",     f2ptotient_main,     f2ptotient_usage},
	{"f2ptest",        f2ptest_main,        f2ptest_usage},
	{"f2pfind",        f2pfind_main,        f2pfind_usage},
	{"f2pperiod",      f2pperiod_main,      f2pperiod_usage},
	{"f2pfactor",      f2pfactor_main,      f2pfactor_usage},
	{"f2pdivisors",    f2pdivisors_main,    f2pdivisors_usage},
	{"f2peval",        f2peval_main,        f2peval_usage},
	{"f2prandom",      f2prandom_main,      f2prandom_usage},
	//{"f2pqp",          f2pqp_main,          f2pqp_usage},
	{"f2pmatop",       f2pmatop_main,       0 /*f2pmatop_usage*/},
	{"f2pcompmx",      f2pcompmx_main,      f2pcompmx_usage},

	{"f2pmlist",       f2pmlist_main,       f2pmlist_usage},
	{"f2pmop",         f2pmop_main,         f2pmop_usage},
	{"f2pmtbl",        f2pmtbl_main,        f2pmtbl_usage},
	{"f2pmord",        f2pmord_main,        f2pmord_usage},
	{"f2pmfindgen",    f2pmfindgen_main,    f2pmfindgen_usage},
	{"f2pmlog",        f2pmlog_main,        f2pmlog_usage},
	{"f2pmchpol",      f2pmchpol_main,      f2pmchpol_usage},
	{"f2pmminpol",     f2pmminpol_main,     f2pmminpol_usage},
	{"f2pmconvert",    f2pmconvert_main,    f2pmconvert_usage},
	{"f2pmrandom",     f2pmrandom_main,     f2pmrandom_usage},

	{"f2pmmatop",      f2pmmatop_main,      f2pmmatop_usage},
	{"f2pmvecop",      f2pmvecop_main,      f2pmvecop_usage},
	{"f2pmmatsolve",   f2pmmatsolve_main,   f2pmmatsolve_usage},
	{"f2pmmatchpol",   f2pmmatchpol_main,   f2pmmatchpol_usage},
	{"f2pmmatdable",   f2pmmatdable_main,   f2pmmatdable_usage},
	{"f2pmmatord",     f2pmmatord_main,     f2pmmatord_usage},
	{"f2pmmatrandom",  f2pmmatrandom_main,  f2pmmatrandom_usage},

//	{"f2prop",         f2prop_main,         0 /*f2prop_usage*/},
//	{"f2prrandom",     f2prrandom_main,     f2prrandom_usage},

//	{"f2prmatop",      f2prmatop_main,      0 /*f2prmatop_usage*/},
//	{"f2prmatrandom",  f2prmatrandom_main,  f2prmatrandom_usage},

	{"f2nplist",       f2nplist_main,       f2nplist_usage},
	{"f2npop",         f2npop_main,         f2npop_usage},
	{"f2npmatop",      f2npmatop_main,      f2npmatop_usage},
	{"f2npdeg",        f2npdeg_main,        f2npdeg_usage},
	{"f2npgcd",        f2npgcd_main,        f2npgcd_usage},
	{"f2nplcm",        f2nplcm_main,        f2nplcm_usage},
	{"f2nptotient",    f2nptotient_main,    f2nptotient_usage},
	{"f2nptest",       f2nptest_main,       f2nptest_usage},
	{"f2npfind",       f2npfind_main,       f2npfind_usage},
	{"f2npfactor",     f2npfactor_main,     f2npfactor_usage},
	{"f2npdivisors",   f2npdivisors_main,   f2npdivisors_usage},
	{"f2npeval",       f2npeval_main,       f2npeval_usage},
	{"f2nprandom",     f2nprandom_main,     f2nprandom_usage},
	{"f2npcompmx",     f2npcompmx_main,     f2npcompmx_usage},

	{"f2npmlist",      f2npmlist_main,      f2npmlist_usage},
	{"f2npmop",        f2npmop_main,        f2npmop_usage},
	{"f2npmtbl",       f2npmtbl_main,       f2npmtbl_usage},
	{"f2npmord",       f2npmord_main,       f2npmord_usage},
	{"f2npmfindgen",   f2npmfindgen_main,   f2npmfindgen_usage},
	{"f2npmlog",       f2npmlog_main,       f2npmlog_usage},
	{"f2npmchpol",     f2npmchpol_main,     f2npmchpol_usage},
	{"f2npmminpol",    f2npmminpol_main,    f2npmminpol_usage},
	{"f2npmrandom",    f2npmrandom_main,    f2npmrandom_usage},
	{"f2npqp",         f2npqp_main,         f2npqp_usage},

	{"f2npmmatop",     f2npmmatop_main,     f2npmmatop_usage},
	{"f2npmvecop",     f2npmvecop_main,     f2npmvecop_usage},
	{"f2npmmatrandom", f2npmmatrandom_main, f2npmmatrandom_usage},

//	{"f2nprop",        f2nprop_main,        f2nprop_usage},
//	{"f2nprmatop",     f2nprmatop_main,     f2nprmatop_usage},

	{"fplist",         fplist_main,         fplist_usage},
	{"fpop",           fpop_main,           fpop_usage},
	{"fptbl",          fptbl_main,          fptbl_usage},
	{"fpord",          fpord_main,          fpord_usage},
	{"fpmaxord",       fpmaxord_main,       fpmaxord_usage},
	{"fporbit",        fporbit_main,         fporbit_usage},
	{"fpfindgen",      fpfindgen_main,      fpfindgen_usage},
	{"fplog",          fplog_main,          fplog_usage},
	{"fprandom",       fprandom_main,       fprandom_usage},

	{"fpmatop",        fpmatop_main,        fpmatop_usage},
	{"fpvecop",        fpvecop_main,        fpvecop_usage},
	{"fpmatchpol",     fpmatchpol_main,     fpmatchpol_usage},
	{"fpmatord",       fpmatord_main,       fpmatord_usage},
	{"fpmatrandom",    fpmatrandom_main,    fpmatrandom_usage},

	{"fpplist",        fpplist_main,        fpplist_usage},
	{"fppop",          fppop_main,          fppop_usage},
	{"fppmatop",       fppmatop_main,       fppmatop_usage},
	{"fppcompmx",      fppcompmx_main,      fppcompmx_usage},
	{"fppdeg",         fppdeg_main,         fppdeg_usage},
	{"fppgcd",         fppgcd_main,         fppgcd_usage},
	{"fpplcm",         fpplcm_main,         fpplcm_usage},
	{"fpptotient",     fpptotient_main,     fpptotient_usage},
	{"fpptest",        fpptest_main,        fpptest_usage},
	{"fppfind",        fppfind_main,        fppfind_usage},
	{"fppfactor",      fppfactor_main,      fppfactor_usage},
	{"fppdivisors",    fppdivisors_main,    fppdivisors_usage},
	{"fppeval",        fppeval_main,        fppeval_usage},
	{"fpprandom",      fpprandom_main,      fpprandom_usage},
	{"fppqp",          fppqp_main,          fppqp_usage},

	{"fppmlist",       fppmlist_main,       fppmlist_usage},
	{"fppmop",         fppmop_main,         fppmop_usage},
	{"fppmtbl",        fppmtbl_main,        fppmtbl_usage},
	{"fppmord",        fppmord_main,        fppmord_usage},
	{"fppmchpol",      fppmchpol_main,      fppmchpol_usage},
	{"fppmminpol",     fppmminpol_main,     fppmminpol_usage},
	{"fppmrandom",     fppmrandom_main,     fppmrandom_usage},

	{"fppmmatop",      fppmmatop_main,      0 /*fppmmatop_usage*/},
	{"fppmvecop",      fppmvecop_main,      0 /*fppmvecop_usage*/},
	{"fppmmatord",     fppmmatord_main,     fppmmatord_usage},
	{"fppmmatrandom",  fppmmatrandom_main,  fppmmatrandom_usage},

//	{"fpprop",         fpprop_main,         fpprop_usage},

//	{"fpprmatop",      fpprmatop_main,      fpprmatop_usage},

//	{"fpnpop",         fpnpop_main,         fpnpop_usage},
//	{"fpnpmatop",      fpnpmatop_main,      fpnpmatop_usage},
//	{"fpnpgcd",        fpnpgcd_main,        fpnpgcd_usage},
//	{"fpnpqp",         fpnpqp_main,         fpnpqp_usage},

//	// To do:
//	//{"fpnplist",        fpnplist_main,        fpnplist_usage},
//	//{"fpnpcompmx",      fpnpcompmx_main,      fpnpcompmx_usage},
//	//{"fpnpdeg",         fpnpdeg_main,         fpnpdeg_usage},
//	//{"fpnplcm",         fpnplcm_main,         fpnplcm_usage},
//	//{"fpnptotient",     fpnptotient_main,     fpnptotient_usage},
//	//{"fpnptest",        fpnptest_main,        fpnptest_usage},
//	//{"fpnpfind",        fpnpfind_main,        fpnpfind_usage},
//	//{"fpnpfactor",      fpnpfactor_main,      fpnpfactor_usage},
//	//{"fpnpdivisors",    fpnpdivisors_main,    fpnpdivisors_usage},
//	//{"fpnpeval",        fpnpeval_main,        fpnpeval_usage},
//	//{"fpnprandom",      fpnprandom_main,      fpnprandom_usage},

//	{"fpnpmop",        fpnpmop_main,        fpnpmop_usage},
//	{"fpnpmmatop",     fpnpmmatop_main,     fpnpmmatop_usage},

//	// To do:
//	//{"fpnpmlist",       fpnpmlist_main,       fpnpmlist_usage},
//	//{"fpnpmtbl",        fpnpmtbl_main,        fpnpmtbl_usage},
//	//{"fpnpmord",        fpnpmord_main,        fpnpmord_usage},
//	//{"fpnpmchpol",      fpnpmchpol_main,      fpnpmchpol_usage},
//	//{"fpnpmminpol",     fpnpmminpol_main,     fpnpmminpol_usage},
//	//{"fpnpmrandom",     fpnpmrandom_main,     fpnpmrandom_usage},
//
//	//{"fpnpmmatrandom",  fpnpmmatrandom_main,  fpnpmmatrandom_usage},

	{0, 0, 0} // MUST be null-terminated.
};

// ----------------------------------------------------------------
void main_usage(char * argv0)
{
	std::cerr << "Usage: " << argv0 << " {cmd} {command-specific arguments ...}\n";
	for (int i = 0; lookups[i].name; i++) {
		std::cerr << " " << lookups[i].name;
	}
	std::cerr << "\n";
	exit(1);
}

int main(int argc, char ** argv)
{
	char * exename = argv[0];
	argc--, argv++;

	// Recursively invokes this program to handle {} pairs, e.g.
	//   spiff f2pdeg { f2pfactor { f2pop 2 ^ 127 - 1 } }
	cmd_interpolate(exename, argc, argv);

	if (argc < 1)
		main_usage(exename);

	if (strcmp(argv[0], "-l") == 0) {
		for (int i = 0; lookups[i].name; i++) {
			if (i > 0)
				std::cout << " ";
			std::cout << lookups[i].name;
		}
		std::cout << "\n";
		exit(1);
	}
	for (int i = 0; lookups[i].name; i++)
		if (strcmp(argv[0], lookups[i].name) == 0)
			return lookups[i].pmain(argc, argv, lookups[i].pusage);
	std::cerr << exename << ": subcommand \"" << argv[0]
		<< "\" not found.\n";
	return 1;
}
