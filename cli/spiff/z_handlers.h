// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef Z_HANDLERS_H
#define Z_HANDLERS_H

#include "handlers.h"

int zop_main(int argc, char ** argv, usage_t * pusage);

void zgcd_usage(char * argv0);
int zgcd_main(int argc, char ** argv, usage_t * pusage);

void zlcm_usage(char * argv0);
int zlcm_main(int argc, char ** argv, usage_t * pusage);

void ztotient_usage(char * argv0);
int ztotient_main(int argc, char ** argv, usage_t * pusage);

void ztestprime_usage(char * argv0);
int ztestprime_main(int argc, char ** argv, usage_t * pusage);

void nthprime_usage(char * argv0);
int nthprime_main(int argc, char ** argv, usage_t * pusage);

void zlist_usage(char * argv0);
int zlist_main(int argc, char ** argv, usage_t * pusage);

void zfactor_usage(char * argv0);
int zfactor_main(int argc, char ** argv, usage_t * pusage);

void zdivisors_usage(char * argv0);
int zdivisors_main(int argc, char ** argv, usage_t * pusage);

int zmatop_main(int argc, char ** argv, usage_t * pusage);

#endif // Z_HANDLERS_H
