#ifndef F2POLYMOD_HANDLERS_H
#define F2POLYMOD_HANDLERS_H

#include "handlers.h"

void f2pmlist_usage(char *argv0);
int f2pmlist_main(int argc, char **argv, usage_t *pusage);

void f2pmop_usage(char *argv0);
int f2pmop_main(int argc, char **argv, usage_t *pusage);

void f2pmtbl_usage(char *argv0);
int f2pmtbl_main(int argc, char **argv, usage_t *pusage);

void f2pmord_usage(char *argv0);
int f2pmord_main(int argc, char **argv, usage_t *pusage);

void f2pmfindgen_usage(char *argv0);
int f2pmfindgen_main(int argc, char **argv, usage_t *pusage);

void f2pmlog_usage(char *argv0);
int f2pmlog_main(int argc, char **argv, usage_t *pusage);

void f2pmchpol_usage(char *argv0);
int f2pmchpol_main(int argc, char **argv, usage_t *pusage);

void f2pmminpol_usage(char *argv0);
int f2pmminpol_main(int argc, char **argv, usage_t *pusage);

void f2pmconvert_usage(char *argv0);
int f2pmconvert_main(int argc, char **argv, usage_t *pusage);

void f2pmrandom_usage(char *argv0);
int f2pmrandom_main(int argc, char **argv, usage_t *pusage);

void f2pmmatop_usage(char *argv0);
int f2pmmatop_main(int argc, char **argv, usage_t *pusage);

void f2pmvecop_usage(char *argv0);
int f2pmvecop_main(int argc, char **argv, usage_t *pusage);

void f2pmmatsolve_usage(char *argv0);
int f2pmmatsolve_main(int argc, char **argv, usage_t *pusage);

void f2pmmatchpol_usage(char *argv0);
int f2pmmatchpol_main(int argc, char **argv, usage_t *pusage);

void f2pmmatdable_usage(char *argv0);
int f2pmmatdable_main(int argc, char **argv, usage_t *pusage);

void f2pmmatord_usage(char *argv0);
int f2pmmatord_main(int argc, char **argv, usage_t *pusage);

void f2pmmatrandom_usage(char *argv0);
int f2pmmatrandom_main(int argc, char **argv, usage_t *pusage);

#endif // F2POLYMOD_HANDLERS_H
