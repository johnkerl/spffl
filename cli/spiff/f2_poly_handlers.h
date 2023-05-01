// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLY_HANDLERS_H
#define F2POLY_HANDLERS_H

#include "handlers.h"

void f2_p_list_usage(char *argv0);
int f2_p_list_main(int argc, char **argv, usage_t *pusage);

int f2_p_op_main(int argc, char **argv, usage_t *pusage);

void f2_p_deg_usage(char *argv0);
int f2_p_deg_main(int argc, char **argv, usage_t *pusage);

void f2_p_gcd_usage(char *argv0);
int f2_p_gcd_main(int argc, char **argv, usage_t *pusage);

void f2_p_lcm_usage(char *argv0);
int f2_p_lcm_main(int argc, char **argv, usage_t *pusage);

void f2_p_totient_usage(char *argv0);
int f2_p_totient_main(int argc, char **argv, usage_t *pusage);

void f2_p_test_usage(char *argv0);
int f2_p_test_main(int argc, char **argv, usage_t *pusage);

void f2_p_find_usage(char *argv0);
int f2_p_find_main(int argc, char **argv, usage_t *pusage);

void f2_p_period_usage(char *argv0);
int f2_p_period_main(int argc, char **argv, usage_t *pusage);

void f2_p_factor_usage(char *argv0);
int f2_p_factor_main(int argc, char **argv, usage_t *pusage);

void f2_p_divisors_usage(char *argv0);
int f2_p_divisors_main(int argc, char **argv, usage_t *pusage);

void f2_p_eval_usage(char *argv0);
int f2_p_eval_main(int argc, char **argv, usage_t *pusage);

void f2_p_random_usage(char *argv0);
int f2_p_random_main(int argc, char **argv, usage_t *pusage);

void f2_p_comp_mx_usage(char *argv0);
int f2_p_comp_mx_main(int argc, char **argv, usage_t *pusage);

int f2_p_mat_op_main(int argc, char **argv, usage_t *pusage);

void f2_p_qp_usage(char *argv0);
int f2_p_qp_main(int argc, char **argv, usage_t *pusage);

#endif // F2POLY_HANDLERS_H
