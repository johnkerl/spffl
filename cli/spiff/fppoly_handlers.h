#ifndef FPPOLY_HANDLERS_H
#define FPPOLY_HANDLERS_H

#include "handlers.h"

void fpplist_usage(char *argv0);
int fpplist_main(int argc, char **argv, usage_t *pusage);

void fppop_usage(char *argv0);
int fppop_main(int argc, char **argv, usage_t *pusage);

void fppmatop_usage(char *argv0);
int fppmatop_main(int argc, char **argv, usage_t *pusage);

void fppcompmx_usage(char *argv0);
int fppcompmx_main(int argc, char **argv, usage_t *pusage);

void fppdeg_usage(char *argv0);
int fppdeg_main(int argc, char **argv, usage_t *pusage);

void fppgcd_usage(char *argv0);
int fppgcd_main(int argc, char **argv, usage_t *pusage);

void fpplcm_usage(char *argv0);
int fpplcm_main(int argc, char **argv, usage_t *pusage);

void fpptotient_usage(char *argv0);
int fpptotient_main(int argc, char **argv, usage_t *pusage);

void fpptest_usage(char *argv0);
int fpptest_main(int argc, char **argv, usage_t *pusage);

void fppfind_usage(char *argv0);
int fppfind_main(int argc, char **argv, usage_t *pusage);

void fppfactor_usage(char *argv0);
int fppfactor_main(int argc, char **argv, usage_t *pusage);

void fppdivisors_usage(char *argv0);
int fppdivisors_main(int argc, char **argv, usage_t *pusage);

void fppeval_usage(char *argv0);
int fppeval_main(int argc, char **argv, usage_t *pusage);

void fpprandom_usage(char *argv0);
int fpprandom_main(int argc, char **argv, usage_t *pusage);

void fppqp_usage(char *argv0);
int fppqp_main(int argc, char **argv, usage_t *pusage);

#endif // FPPOLY_HANDLERS_H
