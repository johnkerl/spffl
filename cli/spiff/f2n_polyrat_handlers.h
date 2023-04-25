#ifndef F2NPOLYRAT_HANDLERS_H
#define F2NPOLYRAT_HANDLERS_H

#include "handlers.h"

void f2n_pr_op_usage(char *argv0);
int f2n_pr_op_main(int argc, char **argv, usage_t *pusage);

void f2n_pr_mat_op_usage(char *argv0);
int f2n_pr_mat_op_main(int argc, char **argv, usage_t *pusage);

#endif // F2NPOLYRAT_HANDLERS_H
