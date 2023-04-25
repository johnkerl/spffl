#ifndef F2_HANDLERS_H
#define F2_HANDLERS_H

#include "handlers.h"

int f2_op_main(int argc, char **argv, usage_t *pusage);

void f2_random_usage(char *argv0);
int f2_random_main(int argc, char **argv, usage_t *pusage);

int f2_mat_op_main(int argc, char **argv, usage_t *pusage);

int f2_vec_op_main(int argc, char **argv, usage_t *pusage);

void f2_mat_ch_pol_usage(char *argv0);
int f2_mat_ch_pol_main(int argc, char **argv, usage_t *pusage);

void f2_mat_ord_usage(char *argv0);
int f2_mat_ord_main(int argc, char **argv, usage_t *pusage);

void f2_mat_random_usage(char *argv0);
int f2_mat_random_main(int argc, char **argv, usage_t *pusage);

#endif // F2_HANDLERS_H
