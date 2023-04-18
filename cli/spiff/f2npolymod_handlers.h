#ifndef F2NPOLYMOD_HANDLERS_H
#define F2NPOLYMOD_HANDLERS_H
#include "handlers.h"

void f2npmlist_usage(char * argv0);
int f2npmlist_main(int argc, char ** argv, usage_t * pusage);

void f2npmop_usage(char * argv0);
int f2npmop_main(int argc, char ** argv, usage_t * pusage);

void f2npmtbl_usage(char * argv0);
int f2npmtbl_main(int argc, char ** argv, usage_t * pusage);

void f2npmord_usage(char * argv0);
int f2npmord_main(int argc, char ** argv, usage_t * pusage);

void f2npmfindgen_usage(char * argv0);
int f2npmfindgen_main(int argc, char ** argv, usage_t * pusage);

void f2npmlog_usage(char * argv0);
int f2npmlog_main(int argc, char ** argv, usage_t * pusage);

void f2npmchpol_usage(char * argv0);
int f2npmchpol_main(int argc, char ** argv, usage_t * pusage);

void f2npmminpol_usage(char * argv0);
int f2npmminpol_main(int argc, char ** argv, usage_t * pusage);

void f2npmrandom_usage(char * argv0);
int f2npmrandom_main(int argc, char ** argv, usage_t * pusage);

void f2npmmatop_usage(char * argv0);
int f2npmmatop_main(int argc, char ** argv, usage_t * pusage);

void f2npmvecop_usage(char * argv0);
int f2npmvecop_main(int argc, char ** argv, usage_t * pusage);

void f2npmmatrandom_usage(char * argv0);
int f2npmmatrandom_main(int argc, char ** argv, usage_t * pusage);

#endif // F2NPOLYMOD_HANDLERS_H
