#include "f2n_polyrat_handlers.h"
#include "cmd_line_matrix_ops.h"
#include "cmd_line_ops.h"
#include "cmd_line_vector_ops.h"
#include "f2n_polyrat_t.h"

void f2nprop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {...}\n";
  exit(1);
}
int f2nprop_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  if (argc < 2)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  spffl::rationals::f2n_polyrat_t zero =
      spffl::rationals::f2n_polyrat_t::prime_sfld_elt(0, m);
  spffl::rationals::f2n_polyrat_t one =
      spffl::rationals::f2n_polyrat_t::prime_sfld_elt(1, m);
  spffl::cliparser::cmd_line_parse<spffl::rationals::f2n_polyrat_t>(
      argc - 2, argv + 2, zero, one);
  return 0;
}

void f2nprmatop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {inner m} {...}\n";
  exit(1);
}

int f2nprmatop_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  if (argc < 2)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  spffl::rationals::f2n_polyrat_t zero =
      spffl::rationals::f2n_polyrat_t::prime_sfld_elt(0, m);
  spffl::rationals::f2n_polyrat_t one =
      spffl::rationals::f2n_polyrat_t::prime_sfld_elt(1, m);
  spffl::cliparser::cmd_line_mat_parse<spffl::rationals::f2n_polyrat_t>(
      argc - 2, argv + 2, zero, one);
  return 0;
}
