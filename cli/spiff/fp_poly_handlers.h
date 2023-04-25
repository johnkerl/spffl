#ifndef FPPOLY_HANDLERS_H
#define FPPOLY_HANDLERS_H

#include "handlers.h"

void fp_p_list_usage(char *argv0);
int fp_p_list_main(int argc, char **argv, usage_t *pusage);

void fp_p_op_usage(char *argv0);
int fp_p_op_main(int argc, char **argv, usage_t *pusage);

void fp_p_mat_op_usage(char *argv0);
int fp_p_mat_op_main(int argc, char **argv, usage_t *pusage);

void fp_p_comp_mx_usage(char *argv0);
int fp_p_comp_mx_main(int argc, char **argv, usage_t *pusage);

void fp_p_deg_usage(char *argv0);
int fp_p_deg_main(int argc, char **argv, usage_t *pusage);

void fp_p_gcd_usage(char *argv0);
int fp_p_gcd_main(int argc, char **argv, usage_t *pusage);

void fp_p_lcm_usage(char *argv0);
int fp_p_lcm_main(int argc, char **argv, usage_t *pusage);

void fp_p_totient_usage(char *argv0);
int fp_p_totient_main(int argc, char **argv, usage_t *pusage);

void fp_p_test_usage(char *argv0);
int fp_p_test_main(int argc, char **argv, usage_t *pusage);

void fp_p_find_usage(char *argv0);
int fp_p_find_main(int argc, char **argv, usage_t *pusage);

void fp_p_factor_usage(char *argv0);
int fp_p_factor_main(int argc, char **argv, usage_t *pusage);

void fp_p_divisors_usage(char *argv0);
int fp_p_divisors_main(int argc, char **argv, usage_t *pusage);

void fp_p_eval_usage(char *argv0);
int fp_p_eval_main(int argc, char **argv, usage_t *pusage);

void fp_p_random_usage(char *argv0);
int fp_p_random_main(int argc, char **argv, usage_t *pusage);

void fp_p_qp_usage(char *argv0);
int fp_p_qp_main(int argc, char **argv, usage_t *pusage);

#endif // FPPOLY_HANDLERS_H
