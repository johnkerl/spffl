#ifndef FP_HANDLERS_H
#define FP_HANDLERS_H

#include "handlers.h"

void fp_list_usage(char *argv0);
int fp_list_main(int argc, char **argv, usage_t *pusage);

void fp_op_usage(char *argv0);
int fp_op_main(int argc, char **argv, usage_t *pusage);

void fp_tbl_usage(char *argv0);
int fp_tbl_main(int argc, char **argv, usage_t *pusage);

void fp_ord_usage(char *argv0);
int fp_ord_main(int argc, char **argv, usage_t *pusage);

void fp_max_ord_usage(char *argv0);
int fp_max_ord_main(int argc, char **argv, usage_t *pusage);

void fp_orbit_usage(char *argv0);
int fp_orbit_main(int argc, char **argv, usage_t *pusage);

void fp_find_gen_usage(char *argv0);
int fp_find_gen_main(int argc, char **argv, usage_t *pusage);

void fp_log_usage(char *argv0);
int fp_log_main(int argc, char **argv, usage_t *pusage);

void fp_random_usage(char *argv0);
int fp_random_main(int argc, char **argv, usage_t *pusage);

void fp_mat_op_usage(char *argv0);
int fp_mat_op_main(int argc, char **argv, usage_t *pusage);

void fp_vec_op_usage(char *argv0);
int fp_vec_op_main(int argc, char **argv, usage_t *pusage);

void fp_mat_ch_pol_usage(char *argv0);
int fp_mat_ch_pol_main(int argc, char **argv, usage_t *pusage);

void fp_mat_ord_usage(char *argv0);
int fp_mat_ord_main(int argc, char **argv, usage_t *pusage);

void fp_mat_random_usage(char *argv0);
int fp_mat_random_main(int argc, char **argv, usage_t *pusage);

#endif // FP_HANDLERS_H
