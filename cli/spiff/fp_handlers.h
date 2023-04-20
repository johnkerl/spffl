#ifndef FP_HANDLERS_H
#define FP_HANDLERS_H

#include "handlers.h"

void fplist_usage(char *argv0);
int fplist_main(int argc, char **argv, usage_t *pusage);

void fpop_usage(char *argv0);
int fpop_main(int argc, char **argv, usage_t *pusage);

void fptbl_usage(char *argv0);
int fptbl_main(int argc, char **argv, usage_t *pusage);

void fpord_usage(char *argv0);
int fpord_main(int argc, char **argv, usage_t *pusage);

void fpmaxord_usage(char *argv0);
int fpmaxord_main(int argc, char **argv, usage_t *pusage);

void fporbit_usage(char *argv0);
int fporbit_main(int argc, char **argv, usage_t *pusage);

void fpfindgen_usage(char *argv0);
int fpfindgen_main(int argc, char **argv, usage_t *pusage);

void fplog_usage(char *argv0);
int fplog_main(int argc, char **argv, usage_t *pusage);

void fprandom_usage(char *argv0);
int fprandom_main(int argc, char **argv, usage_t *pusage);

void fpmatop_usage(char *argv0);
int fpmatop_main(int argc, char **argv, usage_t *pusage);

void fpvecop_usage(char *argv0);
int fpvecop_main(int argc, char **argv, usage_t *pusage);

void fpmatchpol_usage(char *argv0);
int fpmatchpol_main(int argc, char **argv, usage_t *pusage);

void fpmatord_usage(char *argv0);
int fpmatord_main(int argc, char **argv, usage_t *pusage);

void fpmatrandom_usage(char *argv0);
int fpmatrandom_main(int argc, char **argv, usage_t *pusage);

#endif // FP_HANDLERS_H
