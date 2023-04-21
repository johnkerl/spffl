#include "f2_handlers.h"
#include "bit_t.h"
#include "cmd_line_matrix_ops.h"
#include "cmd_line_vector_ops.h"
#include "f2_linear_algebra.h"
#include "f2_poly_t.h"
#include "int_random.h"
#include "tmatrix.h"

int f2op_main(int argc, char **argv, usage_t *pusage) {
  cmd_line_parse<bit_t>(argc - 1, argv + 1, bit_t(0), bit_t(1));
  return 0;
}

void f2random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [count]\n";
  exit(1);
}

int f2random_main(int argc, char **argv, usage_t *pusage) {
  int count = 1;

  if ((argc != 1) && (argc != 2))
    pusage(argv[0]);
  if (argc == 2) {
    if (sscanf(argv[1], "%d", &count) != 1)
      pusage(argv[0]);
  }

  for (int i = 0; i < count; i++)
    std::cout << (get_random_int() & 1) << std::endl;

  return 0;
}

int f2matop_main(int argc, char **argv, usage_t *pusage) {
  cmd_line_mat_parse<bit_t>(argc - 1, argv + 1, bit_t(0), bit_t(1));
  return 0;
}

int f2vecop_main(int argc, char **argv, usage_t *pusage) {
  cmd_line_vec_parse<bit_t>(argc - 1, argv + 1, bit_t(0), bit_t(1));
  return 0;
}

void f2matchpol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {goes here}\n";
  exit(1);
}

int f2matchpol_main(int argc, char **argv, usage_t *pusage) {
  tmatrix<bit_t> A;

  if (argc != 2)
    pusage(argv[0]);
  A = bit_t(0);
  if (!A.load_from_file(argv[1]))
    pusage(argv[0]);
  f2_poly_t chpol = f2_char_poly(A);
  std::cout << chpol << std::endl;

  return 0;
}

void f2matord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {goes here}\n";
  exit(1);
}

int f2matord_main(int argc, char **argv, usage_t *pusage) {
  tmatrix<bit_t> A;

  if (argc != 1)
    pusage(argv[0]);

  bit_t zero(0);
  bit_t one(1);

  A = zero;
  std::cin >> A;
  bit_t d = A.det();

  if (d == zero) {
    std::cout << 0 << std::endl;
  } else {
    tmatrix<bit_t> I = A.make_I(zero, one);
    int order;
    tmatrix<bit_t> Apower = A;

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

void f2matrandom_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {# rows} {# cols}\n";
  exit(1);
}

int f2matrandom_main(int argc, char **argv, usage_t *pusage) {
  int nr, nc;

  if (argc != 3)
    pusage(argv[0]);

  if (sscanf(argv[1], "%d", &nr) != 1)
    pusage(argv[0]);
  if (sscanf(argv[2], "%d", &nc) != 1)
    pusage(argv[0]);
  tmatrix<bit_t> A(nr, nc);
  for (int i = 0; i < nr; i++)
    for (int j = 0; j < nc; j++)
      A[i][j] = bit_t(get_random_unsigned() & 1);
  std::cout << A;
  return 0;
}
