#ifndef F2NPOLYMOD_HANDLERS_H
#define F2NPOLYMOD_HANDLERS_H

#include "handlers.h"

void f2n_pm_list_usage(char *argv0);
int f2n_pm_list_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_op_usage(char *argv0);
int f2n_pm_op_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_tbl_usage(char *argv0);
int f2n_pm_tbl_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_ord_usage(char *argv0);
int f2n_pm_ord_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_find_gen_usage(char *argv0);
int f2n_pm_find_gen_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_log_usage(char *argv0);
int f2n_pm_log_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_ch_pol_usage(char *argv0);
int f2n_pm_ch_pol_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_min_pol_usage(char *argv0);
int f2n_pm_min_pol_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_random_usage(char *argv0);
int f2n_pm_random_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_mat_op_usage(char *argv0);
int f2n_pm_mat_op_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_vec_op_usage(char *argv0);
int f2n_pm_vec_op_main(int argc, char **argv, usage_t *pusage);

void f2n_pm_mat_random_usage(char *argv0);
int f2n_pm_mat_random_main(int argc, char **argv, usage_t *pusage);

#endif // F2NPOLYMOD_HANDLERS_H
