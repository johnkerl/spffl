// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef F2POLY_HANDLERS_H
#define F2POLY_HANDLERS_H

#include "handlers.h"

void f2plist_usage(char * argv0);
int f2plist_main(int argc, char ** argv, usage_t * pusage);

int f2pop_main(int argc, char ** argv, usage_t * pusage);

void f2pdeg_usage(char * argv0);
int f2pdeg_main(int argc, char ** argv, usage_t * pusage);

void f2pgcd_usage(char * argv0);
int f2pgcd_main(int argc, char ** argv, usage_t * pusage);

void f2plcm_usage(char * argv0);
int f2plcm_main(int argc, char ** argv, usage_t * pusage);

void f2ptotient_usage(char * argv0);
int f2ptotient_main(int argc, char ** argv, usage_t * pusage);

void f2ptest_usage(char * argv0);
int f2ptest_main(int argc, char ** argv, usage_t * pusage);

void f2pfind_usage(char * argv0);
int f2pfind_main(int argc, char ** argv, usage_t * pusage);

void f2pperiod_usage(char * argv0);
int f2pperiod_main(int argc, char ** argv, usage_t * pusage);

void f2pfactor_usage(char * argv0);
int f2pfactor_main(int argc, char ** argv, usage_t * pusage);

void f2pdivisors_usage(char * argv0);
int f2pdivisors_main(int argc, char ** argv, usage_t * pusage);

void f2peval_usage(char * argv0);
int f2peval_main(int argc, char ** argv, usage_t * pusage);

void f2prandom_usage(char * argv0);
int f2prandom_main(int argc, char ** argv, usage_t * pusage);

void f2pcompmx_usage(char * argv0);
int f2pcompmx_main(int argc, char ** argv, usage_t * pusage);

int f2pmatop_main(int argc, char ** argv, usage_t * pusage);

#endif // F2POLY_HANDLERS_H
