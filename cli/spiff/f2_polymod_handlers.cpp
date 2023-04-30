#include "f2_polymod_handlers.h"
#include "tbl_types.h"

#include "random/f2_polymod_random.h"
#include "units/f2_polymod_units.h"
#include "list/list_elements.h"
#include "linalg/min_char_polys.h"
#include "linalg/f2_polymod_convert.h"
#include "linalg/f2_polymod_linear_algebra.h"
#include "cliparser/cmd_line_matrix_ops.h"
#include "cliparser/cmd_line_ops.h"
#include "cliparser/cmd_line_vector_ops.h"
#include <string.h>

void f2_pm_list_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-a|-u] {m}\n";
  exit(1);
}

int f2_pm_list_main(int argc, char **argv, usage_t *pusage) {
  spffl::list::sp_list_type_t type = spffl::list::SP_LIST_ALL;
  spffl::polynomials::f2_poly_t m;
  if (argc == 3) {
    if (strcmp(argv[1], "-a") == 0) {
      type = spffl::list::SP_LIST_ALL;
    } else if (strcmp(argv[1], "-u") == 0) {
      type = spffl::list::SP_LIST_UNITS;
    } else if (strcmp(argv[1], "-nu") == 0) {
      type = spffl::list::SP_LIST_NON_UNITS;
    } else {
      pusage(argv[0]);
    }
    if (!m.from_string(argv[2])) {
      pusage(argv[0]);
    }
    tvector<spffl::polynomials::f2_polymod_t> elts = f2_polymod_list(m, type);
    elts.crout(std::cout);
  } else if (argc == 4) {
    spffl::polynomials::f2_polymod_t g;
    if (strcmp(argv[1], "-m") == 0) {
      type = spffl::list::SP_LIST_MULTIPLES;
    } else if (strcmp(argv[1], "-rp") == 0) {
      type = spffl::list::SP_LIST_REL_PRIME;
    } else {
      pusage(argv[0]);
    }
    if (!m.from_string(argv[3])) {
      pusage(argv[0]);
    }
    if (!g.from_string(argv[2], m)) {
      pusage(argv[0]);
    }
    tvector<spffl::polynomials::f2_polymod_t> elts = f2_polymod_glist(g, type);
    elts.crout(std::cout);
  } else {
    pusage(argv[0]);
  }
  return 0;
}

void f2_pm_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {a} {b}\n";
  exit(1);
}

int f2_pm_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  if (argc < 2) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  spffl::cliparser::cmd_line_parse<spffl::polynomials::f2_polymod_t>(argc - 2,
      argv + 2,
      spffl::polynomials::f2_polymod_t(spffl::polynomials::f2_poly_t(0), m),
      spffl::polynomials::f2_polymod_t(spffl::polynomials::f2_poly_t(1), m));
  return 0;
}

void f2_pm_tbl_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {+|-|*|u*|/|log[:g]|alog[:g]}\n";
  exit(1);
}

int f2_pm_tbl_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2_polymod_t g;
  int tbl_type = TBL_TYPE_PLUS;
  if (argc != 3) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }

  if (strcmp(argv[2], "+") == 0) {
    tbl_type = TBL_TYPE_PLUS;
  } else if (strcmp(argv[2], "-") == 0) {
    tbl_type = TBL_TYPE_MINUS;
  } else if (strcmp(argv[2], "*") == 0) {
    tbl_type = TBL_TYPE_MUL;
  } else if (strcmp(argv[2], ".") == 0) {
    tbl_type = TBL_TYPE_MUL;
  } else if (strcmp(argv[2], "u*") == 0) {
    tbl_type = TBL_TYPE_UNIT_MUL;
  } else if (strcmp(argv[2], "u.") == 0) {
    tbl_type = TBL_TYPE_UNIT_MUL;
  } else if (strcmp(argv[2], "/") == 0) {
    tbl_type = TBL_TYPE_UNIT_DIV;
  }

  else if (strncmp(argv[2], "log:", 4) == 0) {
    if (!g.from_string(&argv[2][4], m)) {
      pusage(argv[0]);
    }
    tbl_type = TBL_TYPE_LOG;
  } else if (strcmp(argv[2], "log") == 0) {
    if (!spffl::units::f2_polymod_find_generator(m, g)) {
      std::cerr << "Couldn't find generator mod " << m << std::endl;
      exit(1);
    }
    tbl_type = TBL_TYPE_LOG;
  } else if (strncmp(argv[2], "alog:", 5) == 0) {
    if (!g.from_string(&argv[2][5], m)) {
      pusage(argv[0]);
    }
    tbl_type = TBL_TYPE_ALOG;
  } else if (strcmp(argv[2], "alog") == 0) {
    if (!spffl::units::f2_polymod_find_generator(m, g)) {
      std::cerr << "Couldn't find generator mod " << m << std::endl;
      exit(1);
    }
    tbl_type = TBL_TYPE_ALOG;
  } else {
    pusage(argv[0]);
  }

  tvector<spffl::polynomials::f2_polymod_t> elts;
  if ((tbl_type == TBL_TYPE_UNIT_MUL) || (tbl_type == TBL_TYPE_UNIT_DIV) ||
      (tbl_type == TBL_TYPE_LOG) || (tbl_type == TBL_TYPE_ALOG)) {
    elts = f2_polymod_list(m, spffl::list::SP_LIST_UNITS);
  } else {
    elts = f2_polymod_list(m, spffl::list::SP_LIST_ALL);
  }
  int n = elts.get_num_elements();

  if (tbl_type == TBL_TYPE_LOG) {
    std::cout << "element power\n";
    std::cout << "------- -----\n";
    for (int i = 0; i < n; i++) {
      int e = spffl::units::f2_polymod_log(g, elts[i]);
      std::cout << elts[i] << " " << e << std::endl;
    }
    return 0;
  }
  if (tbl_type == TBL_TYPE_ALOG) {
    std::cout << "power element\n";
    std::cout << "----- -------\n";
    spffl::polynomials::f2_polymod_t gp = g / g;
    for (int i = 0; i < n; i++) {
      std::cout << i << " " << gp << std::endl;
      gp *= g;
    }
    return 0;
  }

  spffl::polynomials::f2_polymod_t a, b, c;

  for (int i = 0; i < n; i++) {
    a = elts[i];
    for (int j = 0; j < n; j++) {
      b = elts[j];
      switch (tbl_type) {
      case TBL_TYPE_PLUS:
        c = a + b;
        break;
      case TBL_TYPE_MINUS:
        c = a - b;
        break;
      case TBL_TYPE_MUL:
        c = a * b;
        break;
      case TBL_TYPE_UNIT_MUL:
        c = a * b;
        break;
      case TBL_TYPE_UNIT_DIV:
        c = a / b;
        break;
      }
      if (j > 0) {
        std::cout << " ";
      }
      std::cout << c;
    }
    std::cout << std::endl;
  }

  return 0;
}

void f2_pm_ord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {a}\n";
  exit(1);
}

int f2_pm_ord_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2_polymod_t a;
  if (argc < 3) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  for (int argi = 2; argi < argc; argi++) {
    if (!a.from_string(argv[argi], m)) {
      pusage(argv[0]);
    }
    if (argc > 3) {
      std::cout << a << ": ";
    }
    std::cout << spffl::units::f2_polymod_order(a) << std::endl;
  }
  return 0;
}

void f2_pm_find_gen_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m}\n";
  exit(1);
}

int f2_pm_find_gen_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2_polymod_t g;
  int rv = 0;
  if (argc < 2) {
    pusage(argv[0]);
  }
  for (int argi = 1; argi < argc; argi++) {
    if (!m.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    if (argc > 2) {
      std::cout << m << ": ";
    }
    if (spffl::units::f2_polymod_find_generator(m, g)) {
      std::cout << g << std::endl;
    } else {
      std::cout << "Generator not found.\n";
      rv = 1;
    }
  }
  return rv;
}

void f2_pm_log_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {g} {a}\n";
  exit(1);
}

int f2_pm_log_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2_polymod_t g, a;
  if (argc < 4) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  if (!g.from_string(argv[2], m)) {
    pusage(argv[0]);
  }
  for (int argi = 3; argi < argc; argi++) {
    if (!a.from_string(argv[argi], m)) {
      pusage(argv[0]);
    }
    if (argc > 4) {
      std::cout << a << ": ";
    }
    std::cout << spffl::units::f2_polymod_log(g, a) << std::endl;
  }
  return 0;
}

void f2_pm_ch_pol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {residues ...}\n";
  exit(1);
}

int f2_pm_ch_pol_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2_polymod_t a;

  if (argc < 3) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  for (int argi = 2; argi < argc; argi++) {
    if (!a.from_string(argv[argi], m)) {
      pusage(argv[0]);
    }
    spffl::polynomials::f2_poly_t cp =
        spffl::linalg::f2_polymod_characteristic_polynomial(a);
    if (argc > 3) {
      std::cout << a << ": ";
    }
    std::cout << cp << std::endl;
  }

  return 0;
}

void f2_pm_min_pol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {residues ...}\n";
  exit(1);
}

int f2_pm_min_pol_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2_polymod_t a;

  if (argc < 3) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  for (int argi = 2; argi < argc; argi++) {
    if (!a.from_string(argv[argi], m)) {
      pusage(argv[0]);
    }
    spffl::polynomials::f2_poly_t mp =
        spffl::linalg::f2_polymod_minimal_polynomial(a);
    if (argc > 3) {
      std::cout << a << ": ";
    }
    std::cout << mp << std::endl;
  }

  return 0;
}

void f2_pm_convert_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m1} {m2} {residues ...}\n";
  exit(1);
}

int f2_pm_convert_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m1, m2;
  spffl::polynomials::f2_polymod_t a1, a2, g1, g2;

  if (argc < 4) {
    pusage(argv[0]);
  }
  if (!m1.from_string(argv[1])) {
    pusage(argv[0]);
  }
  if (!m2.from_string(argv[2])) {
    pusage(argv[0]);
  }
  if (!spffl::units::f2_polymod_find_generator(m1, g1)) {
    std::cerr << "Can't find generator mod " << m1 << ".\n";
    exit(1);
  }
  if (!spffl::linalg::f2_polymod_convert_prep(g1, m2, g2)) {
    std::cerr << "Can't find generator mod " << m2 << ".\n";
    exit(1);
  }
  for (int argi = 3; argi < argc; argi++) {
    if (!a1.from_string(argv[argi], m1)) {
      pusage(argv[0]);
    }
    a2 = spffl::linalg::f2_polymod_convert_scalar(g1, g2, a1);
    if (argc > 4) {
      std::cout << a1 << ": ";
    }
    std::cout << a2 << std::endl;
  }

  return 0;
}

void f2_pm_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} [count]\n";
  exit(1);
}

int f2_pm_random_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  int count = 1;

  if ((argc != 2) && (argc != 3)) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  if (argc == 3) {
    if (sscanf(argv[2], "%d", &count) != 1) {
      pusage(argv[0]);
    }
  }

  for (int i = 0; i < count; i++) {
    std::cout << spffl::random::f2_polymod_random(m) << std::endl;
  }

  return 0;
}

void f2_pm_mat_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
  exit(1);
}

int f2_pm_mat_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m = 0;
  spffl::polynomials::f2_polymod_t zero, one;

  if (argc < 2) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  zero = spffl::polynomials::f2_polymod_t(m.prime_subfield_element(0), m);
  one  = spffl::polynomials::f2_polymod_t(m.prime_subfield_element(1), m);
  spffl::cliparser::cmd_line_mat_parse<spffl::polynomials::f2_polymod_t>(
      argc - 2, argv + 2, zero, one);
  return 0;
}

void f2_pm_vec_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
  exit(1);
}

int f2_pm_vec_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m = 0;
  spffl::polynomials::f2_polymod_t zero, one;

  if (argc < 2) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  zero = spffl::polynomials::f2_polymod_t(m.prime_subfield_element(0), m);
  one  = spffl::polynomials::f2_polymod_t(m.prime_subfield_element(1), m);
  spffl::cliparser::cmd_line_vec_parse<spffl::polynomials::f2_polymod_t>(
      argc - 2, argv + 2, zero, one);
  return 0;
}

void f2_pm_mat_solve_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {A} {b}\n";
  std::cerr << "Solves A x = b for x, only when a unique solution exists.\n";
  exit(1);
}

int f2_pm_mat_solve_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m = 0;
  spffl::polynomials::f2_polymod_t zero, one;

  if (argc != 4) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }

  zero = spffl::polynomials::f2_polymod_t(m.prime_subfield_element(0), m);
  one  = spffl::polynomials::f2_polymod_t(m.prime_subfield_element(1), m);

  tmatrix<spffl::polynomials::f2_polymod_t> A;
  tvector<spffl::polynomials::f2_polymod_t> x;
  tvector<spffl::polynomials::f2_polymod_t> b;

  A = spffl::polynomials::f2_polymod_t(zero);
  b = spffl::polynomials::f2_polymod_t(zero);
  if (!A.load_from_file(argv[2])) {
    pusage(argv[0]);
  }
  if (!b.load_from_file(argv[3])) {
    pusage(argv[0]);
  }

  if (!A.solve_unique(x, b, zero, one)) {
    std::cerr << "No unique solution.\n";
    return 1;
  }
  std::cout << x << std::endl;
  return 0;
}

void f2_pm_mat_ch_pol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
  exit(1);
}

int f2_pm_mat_ch_pol_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  tmatrix<spffl::polynomials::f2_polymod_t> A;

  if (argc != 3) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  A = spffl::polynomials::f2_polymod_t(spffl::polynomials::f2_poly_t(0), m);
  if (!A.load_from_file(argv[2])) {
    pusage(argv[0]);
  }

  spffl::polynomials::f2n_poly_t chpol =
      spffl::linalg::f2_polymod_characteristic_polynomial(A);
  std::cout << chpol << std::endl;

  return 0;
}

void f2_pm_mat_diagonalizable_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
  exit(1);
}

int f2_pm_mat_diagonalizable_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  tmatrix<spffl::polynomials::f2_polymod_t> A;

  if (argc != 3) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  A = spffl::polynomials::f2_polymod_t(spffl::polynomials::f2_poly_t(0), m);
  if (!A.load_from_file(argv[2])) {
    pusage(argv[0]);
  }

  spffl::polynomials::f2_poly_t splitter_modulus;
  tvector<spffl::polynomials::f2_polymod_t> eigenvalues;
  if (spffl::linalg::f2_polymod_matrix_is_diagonalizable(
          A, splitter_modulus, eigenvalues)) {
    std::cout << "Diagonalizable.\n";
  } else {
    std::cout << "Non-diagonalizable.\n";
  }
  std::cout << std::endl;
  std::cout << "Splitter modulus: " << splitter_modulus << std::endl;
  std::cout << "Eigenvalues:\n";
  int nei = eigenvalues.get_num_elements();
  for (int i = 0; i < nei; i++) {
    std::cout << "  " << eigenvalues[i] << std::endl;
  }

  return 0;
}

void f2_pm_mat_ord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {goes here}\n";
  exit(1);
}

int f2_pm_mat_ord_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  tmatrix<spffl::polynomials::f2_polymod_t> A;

  if (argc != 2) {
    pusage(argv[0]);
  }

  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }

  spffl::polynomials::f2_polymod_t zero(spffl::polynomials::f2_poly_t(0), m);
  spffl::polynomials::f2_polymod_t one(spffl::polynomials::f2_poly_t(1), m);

  A = zero;
  std::cin >> A;
  spffl::polynomials::f2_polymod_t d = A.det();

  if (d == zero) {
    std::cout << 0 << std::endl;
  } else {
    tmatrix<spffl::polynomials::f2_polymod_t> I = A.make_I(zero, one);
    int order;
    tmatrix<spffl::polynomials::f2_polymod_t> Apower = A;

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

void f2_pm_mat_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {# rows} {# cols}\n";
  exit(1);
}

int f2_pm_mat_random_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  int nr, nc;

  if (argc != 4) {
    pusage(argv[0]);
  }

  if (!m.from_string(argv[1])) {
    pusage(argv[0]);
  }
  if (sscanf(argv[2], "%d", &nr) != 1) {
    pusage(argv[0]);
  }
  if (sscanf(argv[3], "%d", &nc) != 1) {
    pusage(argv[0]);
  }
  tmatrix<spffl::polynomials::f2_polymod_t> A(nr, nc);
  for (int i = 0; i < nr; i++) {
    for (int j = 0; j < nc; j++) {
      A[i][j] = spffl::random::f2_polymod_random(m);
    }
  }
  std::cout << A;
  return 0;
}
