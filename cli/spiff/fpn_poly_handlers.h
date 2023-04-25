#ifndef FPNPOLY_HANDLERS_H
#define FPNPOLY_HANDLERS_H

#include "handlers.h"

void fpn_p_op_usage(char *argv0);
int fpn_p_op_main(int argc, char **argv, usage_t *pusage);

void fpn_p_mat_op_usage(char *argv0);
int fpn_p_mat_op_main(int argc, char **argv, usage_t *pusage);

void fpn_p_gcd_usage(char *argv0);
int fpn_p_gcd_main(int argc, char **argv, usage_t *pusage);

void fpn_p_qp_usage(char *argv0);
int fpn_p_qp_main(int argc, char **argv, usage_t *pusage);

#endif // FPNPOLY_HANDLERS_H
