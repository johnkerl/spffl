#include "q_handlers.h"
#include "cmd_line_matrix_ops.h"
#include "cmd_line_vector_ops.h"
#include "cyclo_poly.h"
#include "intrat_t.h"
#include "qpoly_t.h"

int qop_main(int argc, char **argv, usage_t *pusage) {
  cmd_line_parse<intrat_t>(argc - 1, argv + 1, intrat_t(0), intrat_t(1));
  return 0;
}

int qmatop_main(int argc, char **argv, usage_t *pusage) {
  cmd_line_mat_parse<intrat_t>(argc - 1, argv + 1, intrat_t(0), intrat_t(1));
  return 0;
}

int qvecop_main(int argc, char **argv, usage_t *pusage) {
  cmd_line_vec_parse<intrat_t>(argc - 1, argv + 1, intrat_t(0), intrat_t(1));
  return 0;
}

void qcyclo_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {n}\n";
  exit(1);
}

int qpop_main(int argc, char **argv, usage_t *pusage) {
  cmd_line_parse<qpoly_t>(argc - 1, argv + 1, qpoly_t(intrat_t(0)),
                          qpoly_t(intrat_t(1)));
  return 0;
}

int qcyclo_main(int argc, char **argv, usage_t *pusage) {
  int n;
  if (argc < 2)
    pusage(argv[0]);
  for (int argi = 1; argi < argc; argi++) {
    if (sscanf(argv[argi], "%d", &n) != 1)
      pusage(argv[0]);
    std::cout << get_cyclo_qpoly(n) << std::endl;
  }
  return 0;
}
