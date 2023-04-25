#ifndef Q_HANDLERS_H
#define Q_HANDLERS_H

#include "handlers.h"

int q_op_main(int argc, char **argv, usage_t *pusage);

int q_mat_op_main(int argc, char **argv, usage_t *pusage);

int q_vec_op_main(int argc, char **argv, usage_t *pusage);

int q_p_op_main(int argc, char **argv, usage_t *pusage);

void q_cyclo_usage(char *argv0);
int q_cyclo_main(int argc, char **argv, usage_t *pusage);

#endif // Q_HANDLERS_H
