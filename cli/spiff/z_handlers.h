// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef Z_HANDLERS_H
#define Z_HANDLERS_H

#include "handlers.h"

int z_op_main(int argc, char **argv, usage_t *pusage);

void z_gcd_usage(char *argv0);
int z_gcd_main(int argc, char **argv, usage_t *pusage);

void z_lcm_usage(char *argv0);
int z_lcm_main(int argc, char **argv, usage_t *pusage);

void z_totient_usage(char *argv0);
int z_totient_main(int argc, char **argv, usage_t *pusage);

void z_test_prime_usage(char *argv0);
int z_test_prime_main(int argc, char **argv, usage_t *pusage);

void nthprime_usage(char *argv0);
int nthprime_main(int argc, char **argv, usage_t *pusage);

void z_list_usage(char *argv0);
int z_list_main(int argc, char **argv, usage_t *pusage);

void z_factor_usage(char *argv0);
int z_factor_main(int argc, char **argv, usage_t *pusage);

void z_divisors_usage(char *argv0);
int z_divisors_main(int argc, char **argv, usage_t *pusage);

int z_mat_op_main(int argc, char **argv, usage_t *pusage);

#endif // Z_HANDLERS_H
