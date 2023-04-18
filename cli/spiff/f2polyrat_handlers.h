#ifndef F2POLYRAT_HANDLERS_H
#define F2POLYRAT_HANDLERS_H

#include "handlers.h"

int f2prop_main(int argc, char ** argv, usage_t * pusage);
void f2prrandom_usage(char * argv0);

int f2prrandom_main(int argc, char ** argv, usage_t * pusage);
int f2prmatop_main(int argc, char ** argv, usage_t * pusage);

void f2prmatrandom_usage(char * argv0);
int f2prmatrandom_main(int argc, char ** argv, usage_t * pusage);

#endif // F2POLYRAT_HANDLERS_H
