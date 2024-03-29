#include "fp_polyrat_handlers.h"

#include "spffl/cli_parser/cmd_line_matrix_ops.h"
#include "spffl/cli_parser/cmd_line_ops.h"
#include "spffl/cli_parser/cmd_line_vector_ops.h"
#include "spffl/rationals/fp_polyrat_t.h"

void fp_pr_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {...}\n";
  exit(1);
}

int fp_pr_op_main(int argc, char **argv, usage_t *pusage) {
  int p;
  if (argc < 2) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  spffl::cli_parser::cmd_line_parse<spffl::rationals::fp_polyrat_t>(argc - 2,
      argv + 2, spffl::rationals::fp_polyrat_t::prime_subfield_element(0, p),
      spffl::rationals::fp_polyrat_t::prime_subfield_element(1, p));
  return 0;
}

void fp_pr_mat_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {...}\n";
  exit(1);
}

int fp_pr_mat_op_main(int argc, char **argv, usage_t *pusage) {
  int p;
  if (argc < 2) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  spffl::cli_parser::cmd_line_mat_parse<spffl::rationals::fp_polyrat_t>(
      argc - 2, argv + 2,
      spffl::rationals::fp_polyrat_t::prime_subfield_element(0, p),
      spffl::rationals::fp_polyrat_t::prime_subfield_element(1, p));
  return 0;
}
