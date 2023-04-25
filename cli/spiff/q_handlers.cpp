#include "q_handlers.h"
#include "cmd_line_matrix_ops.h"
#include "cmd_line_vector_ops.h"
#include "cyclo_poly.h"
#include "intrat_t.h"
#include "qpoly_t.h"

int q_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cliparser::cmd_line_parse<spffl::rationals::intrat_t>(
      argc - 1, argv + 1, spffl::rationals::intrat_t(0),
      spffl::rationals::intrat_t(1));
  return 0;
}

int q_mat_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cliparser::cmd_line_mat_parse<spffl::rationals::intrat_t>(
      argc - 1, argv + 1, spffl::rationals::intrat_t(0),
      spffl::rationals::intrat_t(1));
  return 0;
}

int q_vec_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cliparser::cmd_line_vec_parse<spffl::rationals::intrat_t>(
      argc - 1, argv + 1, spffl::rationals::intrat_t(0),
      spffl::rationals::intrat_t(1));
  return 0;
}

void q_cyclo_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {n}\n";
  exit(1);
}

int q_p_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cliparser::cmd_line_parse<spffl::rationals::qpoly_t>(
      argc - 1, argv + 1,
      spffl::rationals::qpoly_t(spffl::rationals::intrat_t(0)),
      spffl::rationals::qpoly_t(spffl::rationals::intrat_t(1)));
  return 0;
}

int q_cyclo_main(int argc, char **argv, usage_t *pusage) {
  int n;
  if (argc < 2)
    pusage(argv[0]);
  for (int argi = 1; argi < argc; argi++) {
    if (sscanf(argv[argi], "%d", &n) != 1)
      pusage(argv[0]);
    std::cout << spffl::q_cyclo::get_cyclo_qpoly(n) << std::endl;
  }
  return 0;
}
