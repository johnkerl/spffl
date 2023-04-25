#ifndef F2POLYRAT_HANDLERS_H
#define F2POLYRAT_HANDLERS_H

#include "handlers.h"

int f2_pr_op_main(int argc, char **argv, usage_t *pusage);
void f2_pr_random_usage(char *argv0);

int f2_pr_random_main(int argc, char **argv, usage_t *pusage);
int f2_pr_mat_op_main(int argc, char **argv, usage_t *pusage);

void f2_pr_mat_random_usage(char *argv0);
int f2_pr_mat_random_main(int argc, char **argv, usage_t *pusage);

#endif // F2POLYRAT_HANDLERS_H
