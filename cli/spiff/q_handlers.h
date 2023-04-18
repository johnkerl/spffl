#ifndef Q_HANDLERS_H
#define Q_HANDLERS_H

#include "handlers.h"

int qop_main(int argc, char ** argv, usage_t * pusage);

int qmatop_main(int argc, char ** argv, usage_t * pusage);

int qvecop_main(int argc, char ** argv, usage_t * pusage);

int qpop_main(int argc, char ** argv, usage_t * pusage);

void qcyclo_usage(char * argv0);
int qcyclo_main(int argc, char ** argv, usage_t * pusage);

#endif // Q_HANDLERS_H
