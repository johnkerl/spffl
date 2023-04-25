#ifndef FPPOLYRAT_HANDLERS_H
#define FPPOLYRAT_HANDLERS_H

#include "handlers.h"

void fp_pr_op_usage(char *argv0);
int fp_pr_op_main(int argc, char **argv, usage_t *pusage);

void fp_pr_mat_op_usage(char *argv0);
int fp_pr_mat_op_main(int argc, char **argv, usage_t *pusage);

#endif // FPPOLYRAT_HANDLERS_H
