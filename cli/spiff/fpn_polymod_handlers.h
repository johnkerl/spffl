#ifndef FPNPOLYMOD_HANDLERS_H
#define FPNPOLYMOD_HANDLERS_H

#include "handlers.h"

void fpn_pm_op_usage(char *argv0);
int fpn_pm_op_main(int argc, char **argv, usage_t *pusage);

void fpn_pm_mat_op_usage(char *argv0);
int fpn_pm_mat_op_main(int argc, char **argv, usage_t *pusage);

#endif // FPNPOLYMOD_HANDLERS_H
