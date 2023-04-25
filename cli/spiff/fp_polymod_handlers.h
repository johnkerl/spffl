#ifndef FPPOLYMOD_HANDLERS_H
#define FPPOLYMOD_HANDLERS_H

#include "handlers.h"

void fp_pm_list_usage(char *argv0);
int fp_pm_list_main(int argc, char **argv, usage_t *pusage);

void fp_pm_op_usage(char *argv0);
int fp_pm_op_main(int argc, char **argv, usage_t *pusage);

void fp_pm_tbl_usage(char *argv0);
int fp_pm_tbl_main(int argc, char **argv, usage_t *pusage);

int fp_pm_mat_op_main(int argc, char **argv, usage_t *pusage);

int fp_pm_vecop_main(int argc, char **argv, usage_t *pusage);

void fp_pm_mat_ord_usage(char *argv0);
int fp_pm_mat_ord_main(int argc, char **argv, usage_t *pusage);

void fp_pm_mat_random_usage(char *argv0);
int fp_pm_mat_random_main(int argc, char **argv, usage_t *pusage);

void fp_pm_ord_usage(char *argv0);
int fp_pm_ord_main(int argc, char **argv, usage_t *pusage);

void fp_pm_ch_pol_usage(char *argv0);
int fp_pm_ch_pol_main(int argc, char **argv, usage_t *pusage);

void fp_pm_min_pol_usage(char *argv0);
int fp_pm_min_pol_main(int argc, char **argv, usage_t *pusage);

void fp_pm_random_usage(char *argv0);
int fp_pm_random_main(int argc, char **argv, usage_t *pusage);

#endif // FPPOLYMOD_HANDLERS_H
