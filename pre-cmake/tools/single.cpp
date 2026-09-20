// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <iostream>
#include <stdio.h>

#include "spffl/libspffl.h"
#include "spffl/cmd_line_ops.h"

typedef void usage_t(char *argv0);
typedef int main_t(int argc, char **argv, usage_t *pusage);

static void f2_pm_mat_solve_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {A} {b}\n";
  std::cerr << "Solves A x = b for x, only when a unique solution exists.\n";
  exit(1);
}

// ----------------------------------------------------------------
tmatrix<f2_polymod_t> f2np_poly_of_matrix(
  f2n_poly_t f, tmatrix<f2_polymod_t> A, f2_polymod_t zero, f2_polymod_t one) {
  tmatrix<f2_polymod_t> fA(zero, A.get_num_rows(), A.get_num_cols());
  tmatrix<f2_polymod_t> Ap = A.make_I(zero, one);
  int deg = f.find_degree();

  for (int i = 0; i <= deg; i++) {
    f2_polymod_t c = f.get_coeff(i);
    tmatrix<f2_polymod_t> foo = Ap * c;
    fA += foo;
    Ap *= A;
  }

  return fA;
}

// ----------------------------------------------------------------
static int f2_pm_mat_solve_main(int argc, char **argv, usage_t *pusage) {
  f2_poly_t m = 0;
  f2_polymod_t zero, one;
  f2n_poly_t f;
  tmatrix<f2_polymod_t> A;

  if (argc != 4)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  zero = f2_polymod_t(m.prime_subfield_element(0), m);
  one = f2_polymod_t(m.prime_subfield_element(1), m);
  if (!f.from_string(argv[2], m))
    pusage(argv[0]);
  A = f2_polymod_t(zero);
  if (!A.load_from_file(argv[3]))
    pusage(argv[0]);

  tmatrix<f2_polymod_t> fA = f2np_poly_of_matrix(f, A, zero, one);
  if (fA.is_zero())
    std::cout << f << "\n";
  return 0;
}

int main(int argc, char **argv) { return f2_pm_mat_solve_main(argc, argv, f2_pm_mat_solve_usage); }
