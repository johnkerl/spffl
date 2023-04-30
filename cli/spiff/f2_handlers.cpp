#include "f2_handlers.h"
#include "bits/bit_t.h"
#include "cli_parser/cmd_line_matrix_ops.h"
#include "cli_parser/cmd_line_vector_ops.h"
#include "containers/tmatrix.h"
#include "linalg/f2_linear_algebra.h"
#include "polynomials/f2_poly_t.h"
#include "random/int_random.h"

int f2_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cli_parser::cmd_line_parse<spffl::bits::bit_t>(
      argc - 1, argv + 1, spffl::bits::bit_t(0), spffl::bits::bit_t(1));
  return 0;
}

void f2_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [count]\n";
  exit(1);
}

int f2_random_main(int argc, char **argv, usage_t *pusage) {
  int count = 1;

  if ((argc != 1) && (argc != 2)) {
    pusage(argv[0]);
  }
  if (argc == 2) {
    if (sscanf(argv[1], "%d", &count) != 1) {
      pusage(argv[0]);
    }
  }

  for (int i = 0; i < count; i++) {
    std::cout << (spffl::random::get_random_int() & 1) << std::endl;
  }

  return 0;
}

int f2_mat_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cli_parser::cmd_line_mat_parse<spffl::bits::bit_t>(
      argc - 1, argv + 1, spffl::bits::bit_t(0), spffl::bits::bit_t(1));
  return 0;
}

int f2_vec_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cli_parser::cmd_line_vec_parse<spffl::bits::bit_t>(
      argc - 1, argv + 1, spffl::bits::bit_t(0), spffl::bits::bit_t(1));
  return 0;
}

void f2_mat_ch_pol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {goes here}\n";
  exit(1);
}

int f2_mat_ch_pol_main(int argc, char **argv, usage_t *pusage) {
  tmatrix<spffl::bits::bit_t> A;

  if (argc != 2) {
    pusage(argv[0]);
  }
  A = spffl::bits::bit_t(0);
  if (!A.load_from_file(argv[1])) {
    pusage(argv[0]);
  }
  spffl::polynomials::f2_poly_t chpol = spffl::linalg::f2_char_poly(A);
  std::cout << chpol << std::endl;

  return 0;
}

void f2_mat_ord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {goes here}\n";
  exit(1);
}

int f2_mat_ord_main(int argc, char **argv, usage_t *pusage) {
  tmatrix<spffl::bits::bit_t> A;

  if (argc != 1) {
    pusage(argv[0]);
  }

  spffl::bits::bit_t zero(0);
  spffl::bits::bit_t one(1);

  A = zero;
  std::cin >> A;
  spffl::bits::bit_t d = A.det();

  if (d == zero) {
    std::cout << 0 << std::endl;
  } else {
    tmatrix<spffl::bits::bit_t> I = A.make_I(zero, one);
    int order;
    tmatrix<spffl::bits::bit_t> Apower = A;

    for (order = 1;; order++) {
      if (Apower == I) {
        std::cout << order << std::endl;
        return 0;
      }
      Apower *= A;
    }

    std::cout << order << std::endl;
  }

  return 0;
}

void f2_mat_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {# rows} {# cols}\n";
  exit(1);
}

int f2_mat_random_main(int argc, char **argv, usage_t *pusage) {
  int nr, nc;

  if (argc != 3) {
    pusage(argv[0]);
  }

  if (sscanf(argv[1], "%d", &nr) != 1) {
    pusage(argv[0]);
  }
  if (sscanf(argv[2], "%d", &nc) != 1) {
    pusage(argv[0]);
  }
  tmatrix<spffl::bits::bit_t> A(nr, nc);
  for (int i = 0; i < nr; i++) {
    for (int j = 0; j < nc; j++) {
      A[i][j] = spffl::bits::bit_t(spffl::random::get_random_uint32() & 1);
    }
  }
  std::cout << A;
  return 0;
}
