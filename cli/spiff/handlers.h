#ifndef HANDLERS_H
#define HANDLERS_H

#include "cmdlineops.h"

typedef void usage_t(char *argv0);
typedef int main_t(int argc, char **argv, usage_t *pusage);

#endif // HANDLERS_H
