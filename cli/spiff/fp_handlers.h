#ifndef FP_HANDLERS_H
#define FP_HANDLERS_H

#include "handlers.h"

void fp_list_usage(char *argv0);
int fp_list_main(int argc, char **argv, usage_t *pusage);

void fpop_usage(char *argv0);
int fpop_main(int argc, char **argv, usage_t *pusage);

void fptbl_usage(char *argv0);
int fptbl_main(int argc, char **argv, usage_t *pusage);

void fpord_usage(char *argv0);
int fpord_main(int argc, char **argv, usage_t *pusage);

void fp_max_ord_usage(char *argv0);
int fp_max_ord_main(int argc, char **argv, usage_t *pusage);

void fporbit_usage(char *argv0);
int fporbit_main(int argc, char **argv, usage_t *pusage);

void fp_find_gen_usage(char *argv0);
int fp_find_gen_main(int argc, char **argv, usage_t *pusage);

void fp_log_usage(char *argv0);
int fp_log_main(int argc, char **argv, usage_t *pusage);

void fprandom_usage(char *argv0);
int fprandom_main(int argc, char **argv, usage_t *pusage);

void fp_mat_op_usage(char *argv0);
int fp_mat_op_main(int argc, char **argv, usage_t *pusage);

void fpvecop_usage(char *argv0);
int fpvecop_main(int argc, char **argv, usage_t *pusage);

void fp_mat_ch_pol_usage(char *argv0);
int fp_mat_ch_pol_main(int argc, char **argv, usage_t *pusage);

void fp_mat_ord_usage(char *argv0);
int fp_mat_ord_main(int argc, char **argv, usage_t *pusage);

void fp_mat_random_usage(char *argv0);
int fp_mat_random_main(int argc, char **argv, usage_t *pusage);

#endif // FP_HANDLERS_H
