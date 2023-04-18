#ifndef F2_HANDLERS_H
#define F2_HANDLERS_H

#include "handlers.h"

int f2op_main(int argc, char ** argv, usage_t * pusage);

void f2random_usage(char * argv0);
int f2random_main(int argc, char ** argv, usage_t * pusage);

int f2matop_main(int argc, char ** argv, usage_t * pusage);

int f2vecop_main(int argc, char ** argv, usage_t * pusage);

void f2matchpol_usage(char * argv0);
int f2matchpol_main(int argc, char ** argv, usage_t * pusage);

void f2matord_usage(char * argv0);
int f2matord_main(int argc, char ** argv, usage_t * pusage);

void f2matrandom_usage(char * argv0);
int f2matrandom_main(int argc, char ** argv, usage_t * pusage);

#endif // F2_HANDLERS_H
