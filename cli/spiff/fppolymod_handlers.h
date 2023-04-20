#ifndef FPPOLYMOD_HANDLERS_H
#define FPPOLYMOD_HANDLERS_H

#include "handlers.h"

void fppmlist_usage(char *argv0);
int fppmlist_main(int argc, char **argv, usage_t *pusage);

void fppmop_usage(char *argv0);
int fppmop_main(int argc, char **argv, usage_t *pusage);

void fppmtbl_usage(char *argv0);
int fppmtbl_main(int argc, char **argv, usage_t *pusage);

int fppmmatop_main(int argc, char **argv, usage_t *pusage);

int fppmvecop_main(int argc, char **argv, usage_t *pusage);

void fppmmatord_usage(char *argv0);
int fppmmatord_main(int argc, char **argv, usage_t *pusage);

void fppmmatrandom_usage(char *argv0);
int fppmmatrandom_main(int argc, char **argv, usage_t *pusage);

void fppmord_usage(char *argv0);
int fppmord_main(int argc, char **argv, usage_t *pusage);

void fppmchpol_usage(char *argv0);
int fppmchpol_main(int argc, char **argv, usage_t *pusage);

void fppmminpol_usage(char *argv0);
int fppmminpol_main(int argc, char **argv, usage_t *pusage);

void fppmrandom_usage(char *argv0);
int fppmrandom_main(int argc, char **argv, usage_t *pusage);

#endif // FPPOLYMOD_HANDLERS_H
