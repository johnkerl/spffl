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

    {"f2_op", f2_op_main, 0 /*f2op_usage*/},
    {"f2_random", f2_random_main, f2_random_usage},

    {"f2_vec_op", f2_vec_op_main, 0 /*f2vecop_usage*/},
    {"f2_mat_op", f2_mat_op_main, 0 /*f2matop_usage*/},
    {"f2_mat_ch_pol", f2_mat_ch_pol_main, f2_mat_ch_pol_usage},
    {"f2_mat_ord", f2_mat_ord_main, f2_mat_ord_usage},
    {"f2_mat_random", f2_mat_random_main, f2_mat_random_usage},

    {"f2_p_list", f2_p_list_main, f2_p_list_usage},
    {"f2_p_op", f2_p_op_main, 0 /*f2pop_usage*/},
    {"f2_p_deg", f2_p_deg_main, f2_p_deg_usage},
    {"f2_p_gcd", f2_p_gcd_main, f2_p_gcd_usage},
    {"f2_p_lcm", f2_p_lcm_main, f2_p_lcm_usage},
    {"f2_p_totient", f2_p_totient_main, f2_p_totient_usage},
    {"f2_p_test", f2_p_test_main, f2_p_test_usage},
    {"f2_p_find", f2_p_find_main, f2_p_find_usage},
    {"f2_p_period", f2_p_period_main, f2_p_period_usage},
    {"f2_p_factor", f2_p_factor_main, f2_p_factor_usage},
    {"f2_p_divisors", f2_p_divisors_main, f2_p_divisors_usage},
    {"f2_p_eval", f2_p_eval_main, f2_p_eval_usage},
    {"f2_p_random", f2_p_random_main, f2_p_random_usage},
    {"f2_p_qp", f2_p_qp_main, f2_p_qp_usage},
    {"f2_p_mat_op", f2_p_mat_op_main, 0 /*f2pmatop_usage*/},
    {"f2_p_comp_mx", f2_p_comp_mx_main, f2_p_comp_mx_usage},

    {"f2_pm_list", f2_pm_list_main, f2_pm_list_usage},
    {"f2_pm_op", f2_pm_op_main, f2_pm_op_usage},
    {"f2_pm_tbl", f2_pm_tbl_main, f2_pm_tbl_usage},
    {"f2_pm_ord", f2_pm_ord_main, f2_pm_ord_usage},
    {"f2_pm_find_gen", f2_pm_find_gen_main, f2_pm_find_gen_usage},
    {"f2_pm_log", f2_pm_log_main, f2_pm_log_usage},
    {"f2_pm_ch_pol", f2_pm_ch_pol_main, f2_pm_ch_pol_usage},
    {"f2_pm_min_pol", f2_pm_min_pol_main, f2_pm_min_pol_usage},
    {"f2_pm_convert", f2_pm_convert_main, f2_pm_convert_usage},
    {"f2_pm_random", f2_pm_random_main, f2_pm_random_usage},

    {"f2_pm_mat_op", f2_pm_mat_op_main, f2_pm_mat_op_usage},
    {"f2_pm_vec_op", f2_pm_vec_op_main, f2_pm_vec_op_usage},
    {"f2_pm_mat_solve", f2_pm_mat_solve_main, f2_pm_mat_solve_usage},
    {"f2_pm_mat_ch_pol", f2_pm_mat_ch_pol_main, f2_pm_mat_ch_pol_usage},
    {"f2_pm_mat_dable", f2_pm_mat_dable_main, f2_pm_mat_dable_usage},
    {"f2_pm_mat_ord", f2_pm_mat_ord_main, f2_pm_mat_ord_usage},
    {"f2_pm_mat_random", f2_pm_mat_random_main, f2_pm_mat_random_usage},

    {"f2_pr_op", f2_pr_op_main, 0 /*f2prop_usage*/},
    {"f2_pr_random", f2_pr_random_main, f2_pr_random_usage},
    {"f2_pr_mat_op", f2_pr_mat_op_main, 0 /*f2prmatop_usage*/},
    {"f2_pr_mat_random", f2_pr_mat_random_main, f2_pr_mat_random_usage},

    {"f2n_p_list", f2n_p_list_main, f2n_p_list_usage},
    {"f2n_p_op", f2n_p_op_main, f2n_p_op_usage},
    {"f2n_p_mat_op", f2n_p_mat_op_main, f2n_p_mat_op_usage},
    {"f2n_p_deg", f2n_p_deg_main, f2n_p_deg_usage},
    {"f2n_p_gcd", f2n_p_gcd_main, f2n_p_gcd_usage},
    {"f2n_p_lcm", f2n_p_lcm_main, f2n_p_lcm_usage},
    {"f2n_p_totient", f2n_p_totient_main, f2n_p_totient_usage},
    {"f2n_p_test", f2n_p_test_main, f2n_p_test_usage},
    {"f2n_p_find", f2n_p_find_main, f2n_p_find_usage},
    {"f2n_p_factor", f2n_p_factor_main, f2n_p_factor_usage},
    {"f2n_p_divisors", f2n_p_divisors_main, f2n_p_divisors_usage},
    {"f2n_p_eval", f2n_p_eval_main, f2n_p_eval_usage},
    {"f2n_p_random", f2n_p_random_main, f2n_p_random_usage},
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
    {"f2n_p_qp", f2n_p_qp_main, f2n_p_qp_usage},

    {"f2n_pm_mat_op", f2n_pm_mat_op_main, f2n_pm_mat_op_usage},
    {"f2n_pm_vec_op", f2n_pm_vec_op_main, f2n_pm_vec_op_usage},
    {"f2n_pm_mat_random", f2n_pm_mat_random_main, f2n_pm_mat_random_usage},

    {"f2n_pr_op", f2n_pr_op_main, f2n_pr_op_usage},
    {"f2n_pr_mat_op", f2n_pr_mat_op_main, f2n_pr_mat_op_usage},

    {"fp_list", fp_list_main, fp_list_usage},
    {"fpop", fpop_main, fpop_usage},
    {"fptbl", fptbl_main, fptbl_usage},
    {"fpord", fpord_main, fpord_usage},
    {"fp_max_ord", fp_max_ord_main, fp_max_ord_usage},
    {"fporbit", fporbit_main, fporbit_usage},
    {"fp_find_gen", fp_find_gen_main, fp_find_gen_usage},
    {"fp_log", fp_log_main, fp_log_usage},
    {"fprandom", fprandom_main, fprandom_usage},

    {"fp_mat_op", fp_mat_op_main, fp_mat_op_usage},
    {"fpvecop", fpvecop_main, fpvecop_usage},
    {"fp_mat_ch_pol", fp_mat_ch_pol_main, fp_mat_ch_pol_usage},
    {"fp_mat_ord", fp_mat_ord_main, fp_mat_ord_usage},
    {"fp_mat_random", fp_mat_random_main, fp_mat_random_usage},

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
    {"fpn_p_mat_op", fpn_p_mat_op_main, fpn_p_mat_op_usage},
    {"fpn_p_gcd", fpn_p_gcd_main, fpn_p_gcd_usage},
    {"fpnpqp", fpnpqp_main, fpnpqp_usage},

    // To do:
    //{"fpn_p_list",        fpn_p_list_main,        fpn_p_list_usage},
    //{"fpn_p_comp_mx",      fpn_p_comp_mx_main,      fpn_p_comp_mx_usage},
    //{"fpn_p_deg",         fpn_p_deg_main,         fpn_p_deg_usage},
    //{"fpn_p_lcm",         fpn_p_lcm_main,         fpn_p_lcm_usage},
    //{"fpnptotient",     fpnptotient_main,     fpnptotient_usage},
    //{"fpnptest",        fpnptest_main,        fpnptest_usage},
    //{"fpn_p_find",        fpn_p_find_main,        fpn_p_find_usage},
    //{"fpn_p_factor",      fpn_p_factor_main,      fpn_p_factor_usage},
    //{"fpn_p_divisors",    fpn_p_divisors_main,    fpn_p_divisors_usage},
    //{"fpn_p_eval",        fpn_p_eval_main,        fpn_p_eval_usage},
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
  //   spiff f2_p_deg { f2_p_factor { f2_p_op 2 ^ 127 - 1 } }
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
