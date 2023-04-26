#ifndef F2POLYMOD_HANDLERS_H
#define F2POLYMOD_HANDLERS_H

#include "handlers.h"

void f2_pm_list_usage(char *argv0);
int f2_pm_list_main(int argc, char **argv, usage_t *pusage);

void f2_pm_op_usage(char *argv0);
int f2_pm_op_main(int argc, char **argv, usage_t *pusage);

void f2_pm_tbl_usage(char *argv0);
int f2_pm_tbl_main(int argc, char **argv, usage_t *pusage);

void f2_pm_ord_usage(char *argv0);
int f2_pm_ord_main(int argc, char **argv, usage_t *pusage);

void f2_pm_find_gen_usage(char *argv0);
int f2_pm_find_gen_main(int argc, char **argv, usage_t *pusage);

void f2_pm_log_usage(char *argv0);
int f2_pm_log_main(int argc, char **argv, usage_t *pusage);

void f2_pm_ch_pol_usage(char *argv0);
int f2_pm_ch_pol_main(int argc, char **argv, usage_t *pusage);

void f2_pm_min_pol_usage(char *argv0);
int f2_pm_min_pol_main(int argc, char **argv, usage_t *pusage);

void f2_pm_convert_usage(char *argv0);
int f2_pm_convert_main(int argc, char **argv, usage_t *pusage);

void f2_pm_random_usage(char *argv0);
int f2_pm_random_main(int argc, char **argv, usage_t *pusage);

void f2_pm_mat_op_usage(char *argv0);
int f2_pm_mat_op_main(int argc, char **argv, usage_t *pusage);

void f2_pm_vec_op_usage(char *argv0);
int f2_pm_vec_op_main(int argc, char **argv, usage_t *pusage);

void f2_pm_mat_solve_usage(char *argv0);
int f2_pm_mat_solve_main(int argc, char **argv, usage_t *pusage);

void f2_pm_mat_ch_pol_usage(char *argv0);
int f2_pm_mat_ch_pol_main(int argc, char **argv, usage_t *pusage);

void f2_pm_mat_diagonalizable_usage(char *argv0);
int f2_pm_mat_diagonalizable_main(int argc, char **argv, usage_t *pusage);

void f2_pm_mat_ord_usage(char *argv0);
int f2_pm_mat_ord_main(int argc, char **argv, usage_t *pusage);

void f2_pm_mat_random_usage(char *argv0);
int f2_pm_mat_random_main(int argc, char **argv, usage_t *pusage);

#endif // F2POLYMOD_HANDLERS_H
