// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <stdio.h>
#include <string.h>

#include "cmd_interp.h"

#include "handlers.h"

#include "q_handlers.h"
#include "z_handlers.h"

#include "f2_handlers.h"

#include "f2_poly_handlers.h"
#include "f2_polymod_handlers.h"
#include "f2_polyrat_handlers.h"

#include "f2n_poly_handlers.h"
#include "f2n_polymod_handlers.h"
#include "f2n_polyrat_handlers.h"

#include "fp_handlers.h"

#include "fp_poly_handlers.h"
#include "fp_polymod_handlers.h"
#include "fp_polyrat_handlers.h"

#include "fpn_poly_handlers.h"
#include "fpn_polymod_handlers.h"

// ----------------------------------------------------------------
// TODO: add another level here

typedef struct _lookup_t {
  const char *name;
  main_t *pmain;
  usage_t *pusage;
} lookup_t;

lookup_t lookups[] = {

    {"z_op", z_op_main, 0 /*zop_usage*/},
    {"z_gcd", z_gcd_main, z_gcd_usage},
    {"z_lcm", z_lcm_main, z_lcm_usage},
    {"z_totient", z_totient_main, z_totient_usage},
    {"z_test_prime", z_test_prime_main, z_test_prime_usage},
    {"spffl::intmath::nth_prime", nth_prime_main, nth_prime_usage},
    {"z_list", z_list_main, z_list_usage},
    {"z_factor", z_factor_main, z_factor_usage},
    {"z_divisors", z_divisors_main, z_divisors_usage},
    {"z_mat_op", z_mat_op_main, 0 /*zmatop_usage*/},

    {"q_op", q_op_main, 0 /*qop_usage*/},
    {"q_vec_op", q_vec_op_main, 0 /*qvecop_usage*/},
    {"q_mat_op", q_mat_op_main, 0 /*qmatop_usage*/},

    {"q_cyclo", q_cyclo_main, q_cyclo_usage},
    {"q_p_op", q_p_op_main, 0 /*q_cyclo_usage*/},

    {"f2op", f2op_main, 0 /*f2op_usage*/},
    {"f2random", f2random_main, f2random_usage},

    {"f2vecop", f2vecop_main, 0 /*f2vecop_usage*/},
    {"f2_mat_op", f2_mat_op_main, 0 /*f2matop_usage*/},
    {"f2_mat_ch_pol", f2_mat_ch_pol_main, f2_mat_ch_pol_usage},
    {"f2_mat_ord", f2_mat_ord_main, f2_mat_ord_usage},
    {"f2_mat_random", f2_mat_random_main, f2_mat_random_usage},

    {"f2plist", f2plist_main, f2plist_usage},
    {"f2pop", f2pop_main, 0 /*f2pop_usage*/},
    {"f2pdeg", f2pdeg_main, f2pdeg_usage},
    {"f2pgcd", f2pgcd_main, f2pgcd_usage},
    {"f2plcm", f2plcm_main, f2plcm_usage},
    {"f2ptotient", f2ptotient_main, f2ptotient_usage},
    {"f2ptest", f2ptest_main, f2ptest_usage},
    {"f2pfind", f2pfind_main, f2pfind_usage},
    {"f2pperiod", f2pperiod_main, f2pperiod_usage},
    {"f2pfactor", f2pfactor_main, f2pfactor_usage},
    {"f2pdivisors", f2pdivisors_main, f2pdivisors_usage},
    {"f2peval", f2peval_main, f2peval_usage},
    {"f2prandom", f2prandom_main, f2prandom_usage},
    {"f2pqp", f2pqp_main, f2pqp_usage},
    {"f2pmatop", f2pmatop_main, 0 /*f2pmatop_usage*/},
    {"f2pcompmx", f2pcompmx_main, f2pcompmx_usage},

    {"f2pmlist", f2pmlist_main, f2pmlist_usage},
    {"f2pmop", f2pmop_main, f2pmop_usage},
    {"f2pmtbl", f2pmtbl_main, f2pmtbl_usage},
    {"f2pmord", f2pmord_main, f2pmord_usage},
    {"f2pmfindgen", f2pmfindgen_main, f2pmfindgen_usage},
    {"f2pmlog", f2pmlog_main, f2pmlog_usage},
    {"f2pmchpol", f2pmchpol_main, f2pmchpol_usage},
    {"f2pmminpol", f2pmminpol_main, f2pmminpol_usage},
    {"f2pmconvert", f2pmconvert_main, f2pmconvert_usage},
    {"f2pmrandom", f2pmrandom_main, f2pmrandom_usage},

    {"f2pmmatop", f2pmmatop_main, f2pmmatop_usage},
    {"f2pmvecop", f2pmvecop_main, f2pmvecop_usage},
    {"f2pmmatsolve", f2pmmatsolve_main, f2pmmatsolve_usage},
    {"f2pmmatchpol", f2pmmatchpol_main, f2pmmatchpol_usage},
    {"f2pmmatdable", f2pmmatdable_main, f2pmmatdable_usage},
    {"f2pmmatord", f2pmmatord_main, f2pmmatord_usage},
    {"f2pmmatrandom", f2pmmatrandom_main, f2pmmatrandom_usage},

    {"f2prop", f2prop_main, 0 /*f2prop_usage*/},
    {"f2prrandom", f2prrandom_main, f2prrandom_usage},
    {"f2prmatop", f2prmatop_main, 0 /*f2prmatop_usage*/},
    {"f2prmatrandom", f2prmatrandom_main, f2prmatrandom_usage},

    {"f2n_p_list", f2n_p_list_main, f2n_p_list_usage},
    {"f2npop", f2npop_main, f2npop_usage},
    {"f2n_p_mat_op", f2n_p_mat_op_main, f2n_p_mat_op_usage},
    {"f2n_p_deg", f2n_p_deg_main, f2n_p_deg_usage},
    {"f2n_p_gcd", f2n_p_gcd_main, f2n_p_gcd_usage},
    {"f2n_p_lcm", f2n_p_lcm_main, f2n_p_lcm_usage},
    {"f2nptotient", f2nptotient_main, f2nptotient_usage},
    {"f2nptest", f2nptest_main, f2nptest_usage},
    {"f2n_p_find", f2n_p_find_main, f2n_p_find_usage},
    {"f2n_p_factor", f2n_p_factor_main, f2n_p_factor_usage},
    {"f2n_p_divisors", f2n_p_divisors_main, f2n_p_divisors_usage},
    {"f2n_p_eval", f2n_p_eval_main, f2n_p_eval_usage},
    {"f2nprandom", f2nprandom_main, f2nprandom_usage},
    {"f2n_p_comp_mx", f2n_p_comp_mx_main, f2n_p_comp_mx_usage},

    {"f2n_pm_list", f2n_pm_list_main, f2n_pm_list_usage},
    {"f2n_pm_op", f2n_pm_op_main, f2n_pm_op_usage},
    {"f2n_pm_tbl", f2n_pm_tbl_main, f2n_pm_tbl_usage},
    {"f2n_pm_ord", f2n_pm_ord_main, f2n_pm_ord_usage},
    {"f2n_pm_find_gen", f2n_pm_find_gen_main, f2n_pm_find_gen_usage},
    {"f2n_pm_log", f2n_pm_log_main, f2n_pm_log_usage},
    {"f2n_pm_ch_pol", f2n_pm_ch_pol_main, f2n_pm_ch_pol_usage},
    {"f2n_pm_min_pol", f2n_pm_min_pol_main, f2n_pm_min_pol_usage},
    {"f2n_pm_random", f2n_pm_random_main, f2n_pm_random_usage},
    {"f2npqp", f2npqp_main, f2npqp_usage},

    {"f2n_pm_mat_op", f2n_pm_mat_op_main, f2n_pm_mat_op_usage},
    {"f2n_pm_vec_op", f2n_pm_vec_op_main, f2n_pm_vec_op_usage},
    {"f2n_pm_mat_random", f2n_pm_mat_random_main, f2n_pm_mat_random_usage},

    {"f2nprop", f2nprop_main, f2nprop_usage},
    {"f2nprmatop", f2nprmatop_main, f2nprmatop_usage},

    {"fplist", fplist_main, fplist_usage},
    {"fpop", fpop_main, fpop_usage},
    {"fptbl", fptbl_main, fptbl_usage},
    {"fpord", fpord_main, fpord_usage},
    {"fpmaxord", fpmaxord_main, fpmaxord_usage},
    {"fporbit", fporbit_main, fporbit_usage},
    {"fpfindgen", fpfindgen_main, fpfindgen_usage},
    {"fplog", fplog_main, fplog_usage},
    {"fprandom", fprandom_main, fprandom_usage},

    {"fpmatop", fpmatop_main, fpmatop_usage},
    {"fpvecop", fpvecop_main, fpvecop_usage},
    {"fpmatchpol", fpmatchpol_main, fpmatchpol_usage},
    {"fpmatord", fpmatord_main, fpmatord_usage},
    {"fpmatrandom", fpmatrandom_main, fpmatrandom_usage},

    {"fpplist", fpplist_main, fpplist_usage},
    {"fppop", fppop_main, fppop_usage},
    {"fppmatop", fppmatop_main, fppmatop_usage},
    {"fppcompmx", fppcompmx_main, fppcompmx_usage},
    {"fppdeg", fppdeg_main, fppdeg_usage},
    {"fppgcd", fppgcd_main, fppgcd_usage},
    {"fpplcm", fpplcm_main, fpplcm_usage},
    {"fpptotient", fpptotient_main, fpptotient_usage},
    {"fpptest", fpptest_main, fpptest_usage},
    {"fppfind", fppfind_main, fppfind_usage},
    {"fppfactor", fppfactor_main, fppfactor_usage},
    {"fppdivisors", fppdivisors_main, fppdivisors_usage},
    {"fppeval", fppeval_main, fppeval_usage},
    {"fpprandom", fpprandom_main, fpprandom_usage},
    {"fppqp", fppqp_main, fppqp_usage},

    {"fppmlist", fppmlist_main, fppmlist_usage},
    {"fppmop", fppmop_main, fppmop_usage},
    {"fppmtbl", fppmtbl_main, fppmtbl_usage},
    {"fppmord", fppmord_main, fppmord_usage},
    {"fppmchpol", fppmchpol_main, fppmchpol_usage},
    {"fppmminpol", fppmminpol_main, fppmminpol_usage},
    {"fppmrandom", fppmrandom_main, fppmrandom_usage},

    {"fppmmatop", fppmmatop_main, 0 /*fppmmatop_usage*/},
    {"fppmvecop", fppmvecop_main, 0 /*fppmvecop_usage*/},
    {"fppmmatord", fppmmatord_main, fppmmatord_usage},
    {"fppmmatrandom", fppmmatrandom_main, fppmmatrandom_usage},

    {"fpprop", fpprop_main, fpprop_usage},
    {"fpprmatop", fpprmatop_main, fpprmatop_usage},

    {"fpnpop", fpnpop_main, fpnpop_usage},
    {"fpnpmatop", fpnpmatop_main, fpnpmatop_usage},
    {"fpnpgcd", fpnpgcd_main, fpnpgcd_usage},
    {"fpnpqp", fpnpqp_main, fpnpqp_usage},

    // To do:
    //{"fpnplist",        fpnplist_main,        fpnplist_usage},
    //{"fpnpcompmx",      fpnpcompmx_main,      fpnpcompmx_usage},
    //{"fpnpdeg",         fpnpdeg_main,         fpnpdeg_usage},
    //{"fpnplcm",         fpnplcm_main,         fpnplcm_usage},
    //{"fpnptotient",     fpnptotient_main,     fpnptotient_usage},
    //{"fpnptest",        fpnptest_main,        fpnptest_usage},
    //{"fpnpfind",        fpnpfind_main,        fpnpfind_usage},
    //{"fpnpfactor",      fpnpfactor_main,      fpnpfactor_usage},
    //{"fpnpdivisors",    fpnpdivisors_main,    fpnpdivisors_usage},
    //{"fpnpeval",        fpnpeval_main,        fpnpeval_usage},
    //{"fpnprandom",      fpnprandom_main,      fpnprandom_usage},

    {"fpnpmop", fpnpmop_main, fpnpmop_usage},
    {"fpnpmmatop", fpnpmmatop_main, fpnpmmatop_usage},

    // To do:
    //{"fpnpmlist",       fpnpmlist_main,       fpnpmlist_usage},
    //{"fpnpmtbl",        fpnpmtbl_main,        fpnpmtbl_usage},
    //{"fpnpmord",        fpnpmord_main,        fpnpmord_usage},
    //{"fpnpmchpol",      fpnpmchpol_main,      fpnpmchpol_usage},
    //{"fpnpmminpol",     fpnpmminpol_main,     fpnpmminpol_usage},
    //{"fpnpmrandom",     fpnpmrandom_main,     fpnpmrandom_usage},
    //{"fpnpmmatrandom",  fpnpmmatrandom_main,  fpnpmmatrandom_usage},

    {0, 0, 0} // MUST be null-terminated.
};

// ----------------------------------------------------------------
void main_usage(char *argv0) {
  std::cerr << "Usage: " << argv0
            << " {cmd} {command-specific arguments ...}\n";
  for (int i = 0; lookups[i].name; i++) {
    std::cerr << " " << lookups[i].name;
  }
  std::cerr << "\n";
  exit(1);
}

int main(int argc, char **argv) {
  char *exename = argv[0];
  argc--, argv++;

  // Recursively invokes this program to handle {} pairs, e.g.
  //   spiff f2pdeg { f2pfactor { f2pop 2 ^ 127 - 1 } }
  spffl::cliparser::cmd_interpolate(exename, argc, argv);

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
  std::cerr << exename << ": subcommand \"" << argv[0] << "\" not found.\n";
  return 1;
}
