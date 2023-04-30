#include "q_handlers.h"
#include "cli_parser/cmd_line_matrix_ops.h"
#include "cli_parser/cmd_line_vector_ops.h"
#include "intmath/intrat_t.h"
#include "polynomials/q_poly_t.h"
#include "q_cyclotomic/cyclo_poly.h"

int q_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cli_parser::cmd_line_parse<spffl::intmath::intrat_t>(argc - 1,
      argv + 1, spffl::intmath::intrat_t(0), spffl::intmath::intrat_t(1));
  return 0;
}

int q_mat_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cli_parser::cmd_line_mat_parse<spffl::intmath::intrat_t>(argc - 1,
      argv + 1, spffl::intmath::intrat_t(0), spffl::intmath::intrat_t(1));
  return 0;
}

int q_vec_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cli_parser::cmd_line_vec_parse<spffl::intmath::intrat_t>(argc - 1,
      argv + 1, spffl::intmath::intrat_t(0), spffl::intmath::intrat_t(1));
  return 0;
}

void q_cyclo_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {n}\n";
  exit(1);
}

int q_p_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cli_parser::cmd_line_parse<spffl::polynomials::q_poly_t>(argc - 1,
      argv + 1, spffl::polynomials::q_poly_t(spffl::intmath::intrat_t(0)),
      spffl::polynomials::q_poly_t(spffl::intmath::intrat_t(1)));
  return 0;
}

int q_cyclo_main(int argc, char **argv, usage_t *pusage) {
  int n;
  if (argc < 2) {
    pusage(argv[0]);
  }
  for (int argi = 1; argi < argc; argi++) {
    if (sscanf(argv[argi], "%d", &n) != 1) {
      pusage(argv[0]);
    }
    std::cout << spffl::q_cyclotomic::get_cyclo_qpoly(n) << std::endl;
  }
  return 0;
}
