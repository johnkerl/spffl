#include "f2_polyrat_handlers.h"
#include "cmd_line_matrix_ops.h"
#include "cmd_line_ops.h"
#include "cmd_line_vector_ops.h"
#include "f2_poly_random.h"
#include "f2_polyrat_t.h"

int f2_pr_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cliparser::cmd_line_parse<spffl::rationals::f2_polyrat_t>(
      argc - 1, argv + 1, spffl::rationals::f2_polyrat_t(0),
      spffl::rationals::f2_polyrat_t(1));
  return 0;
}

void f2_pr_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {deg} [count]\n";
  exit(1);
}

int f2_pr_random_main(int argc, char **argv, usage_t *pusage) {
  int deg, count = 1;

  if ((argc != 2) && (argc != 3)) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &deg) != 1) {
    pusage(argv[0]);
  }
  if (argc == 3) {
    if (sscanf(argv[2], "%d", &count) != 1) {
      pusage(argv[0]);
    }
  }

  spffl::polynomials::f2_poly_t zero(0);
  spffl::polynomials::f2_poly_t one(1);
  for (int i = 0; i < count; i++) {
    spffl::polynomials::f2_poly_t numer = spffl::random::f2_poly_random(deg);
    spffl::polynomials::f2_poly_t denom = spffl::random::f2_poly_random(deg);
    if (denom == zero) {
      denom = one;
    }
    spffl::rationals::f2_polyrat_t q(numer, denom);
    std::cout << q << std::endl;
  }

  return 0;
}

int f2_pr_mat_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cliparser::cmd_line_mat_parse<spffl::rationals::f2_polyrat_t>(
      argc - 1, argv + 1,
      spffl::rationals::f2_polyrat_t(spffl::polynomials::f2_poly_t(0)),
      spffl::rationals::f2_polyrat_t(spffl::polynomials::f2_poly_t(1)));
  return 0;
}

void f2_pr_mat_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {deg} {num_rows} {num_cols}\n";
  exit(1);
}

int f2_pr_mat_random_main(int argc, char **argv, usage_t *pusage) {
  int deg, nr, nc;

  if (argc != 4) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &deg) != 1) {
    pusage(argv[0]);
  }
  if (sscanf(argv[2], "%d", &nr) != 1) {
    pusage(argv[0]);
  }
  if (sscanf(argv[3], "%d", &nc) != 1) {
    pusage(argv[0]);
  }

  tmatrix<spffl::rationals::f2_polyrat_t> A(nr, nc);

  spffl::polynomials::f2_poly_t zero(0);
  spffl::polynomials::f2_poly_t one(1);
  for (int i = 0; i < nr; i++) {
    for (int j = 0; j < nc; j++) {
      spffl::polynomials::f2_poly_t numer = spffl::random::f2_poly_random(deg);
      spffl::polynomials::f2_poly_t denom = spffl::random::f2_poly_random(deg);
      if (denom == zero) {
        denom = one;
      }
      A[i][j] = spffl::rationals::f2_polyrat_t(numer, denom);
    }
  }
  std::cout << A << std::endl;

  return 0;
}
