// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

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

#include "spffl/base/spffl_exception.h"
#include "spffl/cli_parser/cmd_interp.h"

#include <iostream>
#include <string>
#include <vector>

// ----------------------------------------------------------------
typedef struct _lookup_t {
  std::string name;
  main_t *pmain;
  usage_t *pusage;
} lookup_t;

// clang-format off
std::vector<lookup_t> z_lookups {
  {"z_op",                      z_op_main,         nullptr},
  {"z_gcd",                     z_gcd_main,        z_gcd_usage},
  {"z_lcm",                     z_lcm_main,        z_lcm_usage},
  {"z_totient",                 z_totient_main,    z_totient_usage},
  {"z_test_prime",              z_test_prime_main, z_test_prime_usage},
  {"spffl::intmath::nth_prime", nth_prime_main,    nth_prime_usage},
  {"z_list",                    z_list_main,       z_list_usage},
  {"z_factor",                  z_factor_main,     z_factor_usage},
  {"z_divisors",                z_divisors_main,   z_divisors_usage},
  {"z_mat_op",                  z_mat_op_main,     nullptr},
};

std::vector<lookup_t> q_lookups {
  {"q_op",         q_op_main,     nullptr/*q_op_usage*/},
  {"q_vec_op",     q_vec_op_main, nullptr/*q_vec_op_usage*/},
  {"q_mat_op",     q_mat_op_main, nullptr/*q_mat_op_usage*/},
  {"q_cyclotomic", q_cyclo_main,  q_cyclo_usage},
  {"q_p_op",       q_p_op_main,   nullptr/*q_p_op_usage*/},
};

std::vector<lookup_t> f2_lookups {
  {"f2_op",         f2_op_main,         nullptr/*f2op_usage*/},
  {"f2_random",     f2_random_main,     f2_random_usage},
  {"f2_vec_op",     f2_vec_op_main,     nullptr/*f2vecop_usage*/},
  {"f2_mat_op",     f2_mat_op_main,     nullptr/*f2matop_usage*/},
  {"f2_mat_ch_pol", f2_mat_ch_pol_main, f2_mat_ch_pol_usage},
  {"f2_mat_ord",    f2_mat_ord_main,    f2_mat_ord_usage},
  {"f2_mat_random", f2_mat_random_main, f2_mat_random_usage},
};

std::vector<lookup_t> f2_p_lookups        {
  {"f2_p_list",         f2_p_list_main,     f2_p_list_usage},
  {"f2_p_op",           f2_p_op_main,       nullptr/*f2pop_usage*/},
  {"f2_p_deg",          f2_p_deg_main,      f2_p_deg_usage},
  {"f2_p_gcd",          f2_p_gcd_main,      f2_p_gcd_usage},
  {"f2_p_lcm",          f2_p_lcm_main,      f2_p_lcm_usage},
  {"f2_p_totient",      f2_p_totient_main,  f2_p_totient_usage},
  {"f2_p_test",         f2_p_test_main,     f2_p_test_usage},
  {"f2_p_find",         f2_p_find_main,     f2_p_find_usage},
  {"f2_p_period",       f2_p_period_main,   f2_p_period_usage},
  {"f2_p_factor",       f2_p_factor_main,   f2_p_factor_usage},
  {"f2_p_divisors",     f2_p_divisors_main, f2_p_divisors_usage},
  {"f2_p_eval",         f2_p_eval_main,     f2_p_eval_usage},
  {"f2_p_random",       f2_p_random_main,   f2_p_random_usage},
  {"f2_p_qp",           f2_p_qp_main,       f2_p_qp_usage},
  {"f2_p_mat_op",       f2_p_mat_op_main,   nullptr/*f2pmatop_usage*/},
  {"f2_p_comp_mx",      f2_p_comp_mx_main,  f2_p_comp_mx_usage},
};

std::vector<lookup_t> f2_pm_lookups {
  {"f2_pm_list",               f2_pm_list_main,               f2_pm_list_usage},
  {"f2_pm_op",                 f2_pm_op_main,                 f2_pm_op_usage},
  {"f2_pm_tbl",                f2_pm_tbl_main,                f2_pm_tbl_usage},
  {"f2_pm_ord",                f2_pm_ord_main,                f2_pm_ord_usage},
  {"f2_pm_find_gen",           f2_pm_find_gen_main,           f2_pm_find_gen_usage},
  {"f2_pm_log",                f2_pm_log_main,                f2_pm_log_usage},
  {"f2_pm_ch_pol",             f2_pm_ch_pol_main,             f2_pm_ch_pol_usage},
  {"f2_pm_min_pol",            f2_pm_min_pol_main,            f2_pm_min_pol_usage},
  {"f2_pm_convert",            f2_pm_convert_main,            f2_pm_convert_usage},
  {"f2_pm_random",             f2_pm_random_main,             f2_pm_random_usage},
  {"f2_pm_mat_op",             f2_pm_mat_op_main,             f2_pm_mat_op_usage},
  {"f2_pm_vec_op",             f2_pm_vec_op_main,             f2_pm_vec_op_usage},
  {"f2_pm_mat_solve",          f2_pm_mat_solve_main,          f2_pm_mat_solve_usage},
  {"f2_pm_mat_ch_pol",         f2_pm_mat_ch_pol_main,         f2_pm_mat_ch_pol_usage},
  {"f2_pm_mat_diagonalizable", f2_pm_mat_diagonalizable_main, f2_pm_mat_diagonalizable_usage},
  {"f2_pm_mat_ord",            f2_pm_mat_ord_main,            f2_pm_mat_ord_usage},
  {"f2_pm_mat_random",         f2_pm_mat_random_main,         f2_pm_mat_random_usage},
};

std::vector<lookup_t> f2_pr_lookups {
  {"f2_pr_op",         f2_pr_op_main,         nullptr/*f2prop_usage*/},
  {"f2_pr_random",     f2_pr_random_main,     f2_pr_random_usage},
  {"f2_pr_mat_op",     f2_pr_mat_op_main,     nullptr/*f2prmatop_usage*/},
  {"f2_pr_mat_random", f2_pr_mat_random_main, f2_pr_mat_random_usage},
};

std::vector<lookup_t> f2n_p_lookups {
  {"f2n_p_list",     f2n_p_list_main,     f2n_p_list_usage},
  {"f2n_p_op",       f2n_p_op_main,       f2n_p_op_usage},
  {"f2n_p_mat_op",   f2n_p_mat_op_main,   f2n_p_mat_op_usage},
  {"f2n_p_deg",      f2n_p_deg_main,      f2n_p_deg_usage},
  {"f2n_p_gcd",      f2n_p_gcd_main,      f2n_p_gcd_usage},
  {"f2n_p_lcm",      f2n_p_lcm_main,      f2n_p_lcm_usage},
  {"f2n_p_totient",  f2n_p_totient_main,  f2n_p_totient_usage},
  {"f2n_p_test",     f2n_p_test_main,     f2n_p_test_usage},
  {"f2n_p_find",     f2n_p_find_main,     f2n_p_find_usage},
  {"f2n_p_factor",   f2n_p_factor_main,   f2n_p_factor_usage},
  {"f2n_p_divisors", f2n_p_divisors_main, f2n_p_divisors_usage},
  {"f2n_p_eval",     f2n_p_eval_main,     f2n_p_eval_usage},
  {"f2n_p_random",   f2n_p_random_main,   f2n_p_random_usage},
  {"f2n_p_comp_mx",  f2n_p_comp_mx_main,  f2n_p_comp_mx_usage},
};

std::vector<lookup_t> f2n_pm_lookups {
  {"f2n_pm_list",       f2n_pm_list_main,       f2n_pm_list_usage},
  {"f2n_pm_op",         f2n_pm_op_main,         f2n_pm_op_usage},
  {"f2n_pm_tbl",        f2n_pm_tbl_main,        f2n_pm_tbl_usage},
  {"f2n_pm_ord",        f2n_pm_ord_main,        f2n_pm_ord_usage},
  {"f2n_pm_find_gen",   f2n_pm_find_gen_main,   f2n_pm_find_gen_usage},
  {"f2n_pm_log",        f2n_pm_log_main,        f2n_pm_log_usage},
  {"f2n_pm_ch_pol",     f2n_pm_ch_pol_main,     f2n_pm_ch_pol_usage},
  {"f2n_pm_min_pol",    f2n_pm_min_pol_main,    f2n_pm_min_pol_usage},
  {"f2n_pm_random",     f2n_pm_random_main,     f2n_pm_random_usage},
  {"f2n_p_qp",          f2n_p_qp_main,          f2n_p_qp_usage},
  {"f2n_pm_mat_op",     f2n_pm_mat_op_main,     f2n_pm_mat_op_usage},
  {"f2n_pm_vec_op",     f2n_pm_vec_op_main,     f2n_pm_vec_op_usage},
  {"f2n_pm_mat_random", f2n_pm_mat_random_main, f2n_pm_mat_random_usage},
};

std::vector<lookup_t> f2n_pr_lookups {
  {"f2n_pr_op",     f2n_pr_op_main,     f2n_pr_op_usage},
  {"f2n_pr_mat_op", f2n_pr_mat_op_main, f2n_pr_mat_op_usage},
};

std::vector<lookup_t> fp_lookups {
  {"fp_list",       fp_list_main,       fp_list_usage},
  {"fp_op",         fp_op_main,         fp_op_usage},
  {"fp_tbl",        fp_tbl_main,        fp_tbl_usage},
  {"fp_ord",        fp_ord_main,        fp_ord_usage},
  {"fp_max_ord",    fp_max_ord_main,    fp_max_ord_usage},
  {"fp_orbit",      fp_orbit_main,      fp_orbit_usage},
  {"fp_find_gen",   fp_find_gen_main,   fp_find_gen_usage},
  {"fp_log",        fp_log_main,        fp_log_usage},
  {"fp_random",     fp_random_main,     fp_random_usage},
  {"fp_mat_op",     fp_mat_op_main,     fp_mat_op_usage},
  {"fp_vec_op",     fp_vec_op_main,     fp_vec_op_usage},
  {"fp_mat_ch_pol", fp_mat_ch_pol_main, fp_mat_ch_pol_usage},
  {"fp_mat_ord",    fp_mat_ord_main,    fp_mat_ord_usage},
  {"fp_mat_random", fp_mat_random_main, fp_mat_random_usage},
};

std::vector<lookup_t> fp_p_lookups {
  {"fp_p_list",     fp_p_list_main,     fp_p_list_usage},
  {"fp_p_op",       fp_p_op_main,       fp_p_op_usage},
  {"fp_p_mat_op",   fp_p_mat_op_main,   fp_p_mat_op_usage},
  {"fp_p_comp_mx",  fp_p_comp_mx_main,  fp_p_comp_mx_usage},
  {"fp_p_deg",      fp_p_deg_main,      fp_p_deg_usage},
  {"fp_p_gcd",      fp_p_gcd_main,      fp_p_gcd_usage},
  {"fp_p_lcm",      fp_p_lcm_main,      fp_p_lcm_usage},
  {"fp_p_totient",  fp_p_totient_main,  fp_p_totient_usage},
  {"fp_p_test",     fp_p_test_main,     fp_p_test_usage},
  {"fp_p_find",     fp_p_find_main,     fp_p_find_usage},
  {"fp_p_factor",   fp_p_factor_main,   fp_p_factor_usage},
  {"fp_p_divisors", fp_p_divisors_main, fp_p_divisors_usage},
  {"fp_p_eval",     fp_p_eval_main,     fp_p_eval_usage},
  {"fp_p_random",   fp_p_random_main,   fp_p_random_usage},
  {"fp_p_qp",       fp_p_qp_main,       fp_p_qp_usage},
};

std::vector<lookup_t> fp_pm_lookups {
  {"fp_pm_list",       fp_pm_list_main,       fp_pm_list_usage},
  {"fp_pm_op",         fp_pm_op_main,         fp_pm_op_usage},
  {"fp_pm_tbl",        fp_pm_tbl_main,        fp_pm_tbl_usage},
  {"fp_pm_ord",        fp_pm_ord_main,        fp_pm_ord_usage},
  {"fp_pm_ch_pol",     fp_pm_ch_pol_main,     fp_pm_ch_pol_usage},
  {"fp_pm_min_pol",    fp_pm_min_pol_main,    fp_pm_min_pol_usage},
  {"fp_pm_random",     fp_pm_random_main,     fp_pm_random_usage},
  {"fp_pm_mat_op",     fp_pm_mat_op_main,     nullptr/*fppmmatop_usage*/},
  {"fp_pm_vecop",      fp_pm_vecop_main,      nullptr/*fppmvecop_usage*/},
  {"fp_pm_mat_ord",    fp_pm_mat_ord_main,    fp_pm_mat_ord_usage},
  {"fp_pm_mat_random", fp_pm_mat_random_main, fp_pm_mat_random_usage},
};

std::vector<lookup_t> fp_pr_lookups {
  {"fp_pr_op",     fp_pr_op_main,     fp_pr_op_usage},
  {"fp_pr_mat_op", fp_pr_mat_op_main, fp_pr_mat_op_usage},
};

std::vector<lookup_t> fpn_p_lookups {
  {"fpn_p_op",     fpn_p_op_main,     fpn_p_op_usage},
  {"fpn_p_mat_op", fpn_p_mat_op_main, fpn_p_mat_op_usage},
  {"fpn_p_gcd",    fpn_p_gcd_main,    fpn_p_gcd_usage},
  {"fpn_p_qp",     fpn_p_qp_main,     fpn_p_qp_usage},
  // To do:
  //{"fpn_p_list",        fpn_p_list_main,        fpn_p_list_usage},
  //{"fpn_p_comp_mx",     fpn_p_comp_mx_main,     fpn_p_comp_mx_usage},
  //{"fpn_p_deg",         fpn_p_deg_main,         fpn_p_deg_usage},
  //{"fpn_p_lcm",         fpn_p_lcm_main,         fpn_p_lcm_usage},
  //{"fpn_p_totient",     fpn_p_totient_main,     fpn_p_totient_usage},
  //{"fpn_p_test",        fpn_p_test_main,        fpn_p_test_usage},
  //{"fpn_p_find",        fpn_p_find_main,        fpn_p_find_usage},
  //{"fpn_p_factor",      fpn_p_factor_main,      fpn_p_factor_usage},
  //{"fpn_p_divisors",    fpn_p_divisors_main,    fpn_p_divisors_usage},
  //{"fpn_p_eval",        fpn_p_eval_main,        fpn_p_eval_usage},
  //{"fpn_p_random",      fpn_p_random_main,      fpn_p_random_usage},
};

std::vector<lookup_t> fpn_pm_lookups {
  {"fpn_pm_op",     fpn_pm_op_main,     fpn_pm_op_usage},
  {"fpn_pm_mat_op", fpn_pm_mat_op_main, fpn_pm_mat_op_usage},
  // To do:
  //{"fpn_pm_list",       fpn_pm_list_main,       fpn_pm_list_usage},
  //{"fpn_pm_tbl",        fpn_pm_tbl_main,        fpn_pm_tbl_usage},
  //{"fpn_pm_ord",        fpn_pm_ord_main,        fpn_pm_ord_usage},
  //{"fpn_pm_ch_pol",     fpn_pm_ch_pol_main,     fpn_pm_ch_pol_usage},
  //{"fpn_pm_min_pol",    fpn_pm_min_pol_main,    fpn_pm_min_pol_usage},
  //{"fpn_pm_random",     fpn_pm_random_main,     fpn_pm_random_usage},
  //{"fpn_pm_mat_random", fpn_pm_mat_random_main, fpn_pm_mat_random_usage},
};
// clang-format off

// ----------------------------------------------------------------
typedef struct _lookup_group_t {
  std::string name;
  std::vector<lookup_t> lookups;
} lookup_group_t;

// clang-format off
std::vector<lookup_group_t> lookup_groups {
  {"Integers",                               z_lookups},
  {"Quotient field of integers",             q_lookups},
  {"F2 (bits)",                              f2_lookups},
  {"Polynomials over F2",                    f2_p_lookups},
  {"Residue field of F2 polynomials (F2^n)", f2_pm_lookups},
  {"Quotient field of F2 polynomials",       f2_pr_lookups},
  {"Polynomials of F2^n",                    f2n_p_lookups},
  {"Residue field of F2^n polynomials",      f2n_pm_lookups},
  {"Quotient field of F2^n polynomials",     f2n_pr_lookups},
  {"Fp (modular arithmetic)",                fp_lookups},
  {"Polynomials over Fp",                    fp_p_lookups},
  {"Residue field of Fp polynomials",        fp_pm_lookups},
  {"Quotient field of Fp polynomials",       fp_pr_lookups},
  {"Polynomials over Fp^n",                  fpn_p_lookups},
  {"Residue field of Fp^n polynomials",      fpn_pm_lookups},
};
// clang-format on

// ----------------------------------------------------------------
void main_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {command} {command-specific arguments ...}\n";
  std::cerr << "Use " << argv0 << " -l to list available commands.\n";
  exit(1);
}

static int try_main(int argc, char **argv) {
  char *exename = argv[0];
  argc--, argv++;

  // Recursively invokes this program to handle {} pairs, e.g.
  //   spiff f2_p_deg { f2_p_factor { f2_p_op 2 ^ 127 - 1 } }
  spffl::cli_parser::cmd_interpolate(exename, argc, argv);

  if (argc < 1) {
    main_usage(exename);
  }

  if (strcmp(argv[0], "-l") == 0) {
    for (auto it = lookup_groups.begin(); it != lookup_groups.end(); it++) {
      std::cout << it->name << ":\n";
      auto lookups = it->lookups;
      for (auto it2 = lookups.begin(); it2 != lookups.end(); it2++) {
        std::cout << "  " << it2->name << "\n";
      }
    }
    exit(0);
  }

  for (auto it = lookup_groups.begin(); it != lookup_groups.end(); it++) {
    auto lookups = it->lookups;
    for (auto it2 = lookups.begin(); it2 != lookups.end(); it2++) {
      if (std::string(argv[0]) == it2->name) {
        return it2->pmain(argc, argv, it2->pusage);
      }
    }
  }

  std::cerr << exename << ": subcommand \"" << argv[0] << "\" not found.\n";
  return 1;
}

int main(int argc, char **argv) {
  try {
    try_main(argc, argv);
  } catch (spffl::exception_t e) {
    std::cerr << e.what() << "\n";
  }
  return 0;
}
