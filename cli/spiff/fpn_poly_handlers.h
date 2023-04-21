#ifndef FPNPOLY_HANDLERS_H
#define FPNPOLY_HANDLERS_H

#include "handlers.h"

void fpnpop_usage(char *argv0);
int fpnpop_main(int argc, char **argv, usage_t *pusage);

void fpnpmatop_usage(char *argv0);
int fpnpmatop_main(int argc, char **argv, usage_t *pusage);

void fpnpgcd_usage(char *argv0);
int fpnpgcd_main(int argc, char **argv, usage_t *pusage);

void fpnpqp_usage(char *argv0);
int fpnpqp_main(int argc, char **argv, usage_t *pusage);

#endif // FPNPOLY_HANDLERS_H
