#include "f2n_polymod_handlers.h"
#include "tbl_types.h"

#include "spffl/cli_parser/cmd_line_matrix_ops.h"
#include "spffl/cli_parser/cmd_line_ops.h"
#include "spffl/cli_parser/cmd_line_vector_ops.h"
#include "spffl/linalg/min_char_polys.h"
#include "spffl/list/list_elements.h"
#include "spffl/polynomials/f2n_polymod_t.h"
#include "spffl/polynomials/fpn_f2n_io.h"
#include "spffl/random/f2n_polymod_random.h"
#include "spffl/units/f2n_polymod_units.h"

#include <string.h>

void f2n_pm_list_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-a|-u] {im} {om}\n";
  exit(1);
}

int f2n_pm_list_main(int argc, char **argv, usage_t *pusage) {
  spffl::list::sp_list_type_t type = spffl::list::SP_LIST_ALL;
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  if (argc != 4) {
    pusage(argv[0]);
  }
  if (strcmp(argv[1], "-a") == 0) {
    type = spffl::list::SP_LIST_ALL;
  } else if (strcmp(argv[1], "-u") == 0) {
    type = spffl::list::SP_LIST_UNITS;
  } else if (strcmp(argv[1], "-nu") == 0) {
    type = spffl::list::SP_LIST_NON_UNITS;
  } else {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[2])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[3], im);
    if (!opt) pusage(argv[0]);
    om = std::move(*opt);
  }
  spffl::containers::vector_over<spffl::polynomials::f2n_polymod_t> elts = f2n_polymod_list(om, type);
  elts.crout(std::cout);
  return 0;
}

void f2n_pm_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
  exit(1);
}

int f2n_pm_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  if (argc < 3) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt) pusage(argv[0]);
    om = std::move(*opt);
  }
  spffl::polynomials::f2n_polymod_t zero(
      spffl::polynomials::prime_subfield_element(0, im), om);
  spffl::polynomials::f2n_polymod_t one(
      spffl::polynomials::prime_subfield_element(1, im), om);
  spffl::cli_parser::cmd_line_parse<spffl::polynomials::f2n_polymod_t>(
      argc - 3, argv + 3, zero, one);
  return 0;
}

void f2n_pm_tbl_usage(char *argv0) {
  std::cerr << "Usage: " << argv0
            << " {im} {om} {+|-|*|u*|/|log[:g]|alog[:g]}\n";
  exit(1);
}

int f2n_pm_tbl_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  spffl::polynomials::f2n_polymod_t g;
  int tbl_type = TBL_TYPE_PLUS;
  if (argc != 4) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt) pusage(argv[0]);
    om = std::move(*opt);
  }

  if (strcmp(argv[3], "+") == 0) {
    tbl_type = TBL_TYPE_PLUS;
  } else if (strcmp(argv[3], "-") == 0) {
    tbl_type = TBL_TYPE_MINUS;
  } else if (strcmp(argv[3], "*") == 0) {
    tbl_type = TBL_TYPE_MUL;
  } else if (strcmp(argv[3], ".") == 0) {
    tbl_type = TBL_TYPE_MUL;
  } else if (strcmp(argv[3], "u*") == 0) {
    tbl_type = TBL_TYPE_UNIT_MUL;
  } else if (strcmp(argv[3], "u.") == 0) {
    tbl_type = TBL_TYPE_UNIT_MUL;
  } else if (strcmp(argv[3], "/") == 0) {
    tbl_type = TBL_TYPE_UNIT_DIV;
  }

  else if (strncmp(argv[3], "log:", 4) == 0) {
    auto opt = spffl::polynomials::f2n_polymod_from_string(&argv[3][4], om);
    if (!opt) pusage(argv[0]);
    g = std::move(*opt);
    tbl_type = TBL_TYPE_LOG;
  } else if (strcmp(argv[3], "log") == 0) {
    if (!spffl::units::f2n_polymod_find_generator(om, g)) {
      std::cerr << "Couldn't find generator mod " << om << "\n";
      exit(1);
    }
    tbl_type = TBL_TYPE_LOG;
  } else if (strncmp(argv[3], "alog:", 5) == 0) {
    auto opt = spffl::polynomials::f2n_polymod_from_string(&argv[3][5], om);
    if (!opt) pusage(argv[0]);
    g = std::move(*opt);
    tbl_type = TBL_TYPE_ALOG;
  } else if (strcmp(argv[3], "alog") == 0) {
    if (!spffl::units::f2n_polymod_find_generator(om, g)) {
      std::cerr << "Couldn't find generator mod " << om << "\n";
      exit(1);
    }
    tbl_type = TBL_TYPE_ALOG;
  } else {
    pusage(argv[0]);
  }

  spffl::containers::vector_over<spffl::polynomials::f2n_polymod_t> elts;
  if ((tbl_type == TBL_TYPE_UNIT_MUL) || (tbl_type == TBL_TYPE_UNIT_DIV) ||
      (tbl_type == TBL_TYPE_LOG) || (tbl_type == TBL_TYPE_ALOG)) {
    elts = f2n_polymod_list(om, spffl::list::SP_LIST_UNITS);
  } else {
    elts = f2n_polymod_list(om, spffl::list::SP_LIST_ALL);
  }
  int n = elts.get_num_elements();

  if (tbl_type == TBL_TYPE_LOG) {
    std::cout << "element power\n";
    std::cout << "------- -----\n";
    for (int i = 0; i < n; i++) {
      int e = spffl::units::f2n_polymod_log(g, elts[i]);
      std::cout << elts[i] << " " << e << "\n";
    }
    return 0;
  }
  if (tbl_type == TBL_TYPE_ALOG) {
    std::cout << "power element\n";
    std::cout << "----- -------\n";
    spffl::polynomials::f2n_polymod_t gp = g / g;
    for (int i = 0; i < n; i++) {
      std::cout << i << " " << gp << "\n";
      gp *= g;
    }
    return 0;
  }

  spffl::polynomials::f2n_polymod_t a, b, c;

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
    std::cout << "\n";
  }

  return 0;
}

void f2n_pm_ord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {im} {om} {a}\n";
  exit(1);
}

int f2n_pm_ord_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  spffl::polynomials::f2n_polymod_t a;
  if (argc < 4) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt) pusage(argv[0]);
    om = std::move(*opt);
  }
  for (int argi = 3; argi < argc; argi++) {
    auto opt_a = spffl::polynomials::f2n_polymod_from_string(argv[argi], om);
    if (!opt_a) pusage(argv[0]);
    a = std::move(*opt_a);
    if (argc > 4) {
      std::cout << a << ": ";
    }
    std::cout << spffl::units::f2n_polymod_order(a) << "\n";
  }
  return 0;
}

void f2n_pm_find_gen_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {im} {om}\n";
  exit(1);
}

int f2n_pm_find_gen_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  spffl::polynomials::f2n_polymod_t g;
  int rv = 0;
  if (argc < 3) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  for (int argi = 2; argi < argc; argi++) {
    {
      auto opt = spffl::polynomials::f2n_poly_from_string(argv[argi], im);
      if (!opt) pusage(argv[0]);
      om = std::move(*opt);
    }
    if (argc > 3) {
      std::cout << om << ": ";
    }
    if (spffl::units::f2n_polymod_find_generator(om, g)) {
      std::cout << g << "\n";
    } else {
      std::cout << "Generator not found.\n";
      rv = 1;
    }
  }
  return rv;
}

void f2n_pm_log_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {im} {om} {g} {a}\n";
  exit(1);
}

int f2n_pm_log_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  spffl::polynomials::f2n_polymod_t g, a;
  if (argc < 5) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt_om = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt_om) pusage(argv[0]);
    om = std::move(*opt_om);
  }
  {
    auto opt_g = spffl::polynomials::f2n_polymod_from_string(argv[3], om);
    if (!opt_g) pusage(argv[0]);
    g = std::move(*opt_g);
  }
  for (int argi = 4; argi < argc; argi++) {
    auto opt_a = spffl::polynomials::f2n_polymod_from_string(argv[argi], om);
    if (!opt_a) pusage(argv[0]);
    a = std::move(*opt_a);
    if (argc > 5) {
      std::cout << a << ": ";
    }
    std::cout << spffl::units::f2n_polymod_log(g, a) << "\n";
  }
  return 0;
}

void f2n_pm_ch_pol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {im} {m} {residues ...}\n";
  exit(1);
}

int f2n_pm_ch_pol_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t m;
  spffl::polynomials::f2n_polymod_t a;

  if (argc < 4) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt) pusage(argv[0]);
    m = std::move(*opt);
  }
  for (int argi = 3; argi < argc; argi++) {
    auto opt_a = spffl::polynomials::f2n_polymod_from_string(argv[argi], m);
    if (!opt_a) pusage(argv[0]);
    a = std::move(*opt_a);
    spffl::polynomials::f2n_poly_t cp = spffl::linalg::f2npm_char_poly(a);
    if (argc > 4) {
      std::cout << a << ": ";
    }
    std::cout << cp << "\n";
  }

  return 0;
}

void f2n_pm_min_pol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {im} {m} {residues ...}\n";
  exit(1);
}

int f2n_pm_min_pol_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t m;
  spffl::polynomials::f2n_polymod_t a;

  if (argc < 4) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt) pusage(argv[0]);
    m = std::move(*opt);
  }
  for (int argi = 3; argi < argc; argi++) {
    auto opt_a = spffl::polynomials::f2n_polymod_from_string(argv[argi], m);
    if (!opt_a) pusage(argv[0]);
    a = std::move(*opt_a);
    spffl::polynomials::f2n_poly_t mp = spffl::linalg::f2npm_min_poly(a);
    if (argc > 4) {
      std::cout << a << ": ";
    }
    std::cout << mp << "\n";
  }

  return 0;
}

void f2n_pm_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {inner m} {outer m} [count]\n";
  exit(1);
}

int f2n_pm_random_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  int count = 1;

  if ((argc != 3) && (argc != 4)) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt) pusage(argv[0]);
    om = std::move(*opt);
  }
  if (argc == 4) {
    if (sscanf(argv[3], "%d", &count) != 1) {
      pusage(argv[0]);
    }
  }

  for (int i = 0; i < count; i++) {
    std::cout << spffl::random::f2n_polymod_random(im, om) << std::endl;
  }

  return 0;
}

void f2n_pm_mat_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
  exit(1);
}

int f2n_pm_mat_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  if (argc < 3) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt) pusage(argv[0]);
    om = std::move(*opt);
  }
  spffl::polynomials::f2n_polymod_t zero(
      spffl::polynomials::prime_subfield_element(0, im), om);
  spffl::polynomials::f2n_polymod_t one(
      spffl::polynomials::prime_subfield_element(1, im), om);
  spffl::cli_parser::cmd_line_mat_parse<spffl::polynomials::f2n_polymod_t>(
      argc - 3, argv + 3, zero, one);
  return 0;
}

void f2n_pm_vec_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {...}\n";
  exit(1);
}

int f2n_pm_vec_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  if (argc < 3) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt) pusage(argv[0]);
    om = std::move(*opt);
  }
  spffl::polynomials::f2n_polymod_t zero(
      spffl::polynomials::prime_subfield_element(0, im), om);
  spffl::polynomials::f2n_polymod_t one(
      spffl::polynomials::prime_subfield_element(1, im), om);
  spffl::cli_parser::cmd_line_vec_parse<spffl::polynomials::f2n_polymod_t>(
      argc - 3, argv + 3, zero, one);
  return 0;
}

void f2n_pm_mat_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {inner m} {outer m} {# rows} {# cols}\n";
  exit(1);
}

int f2n_pm_mat_random_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t im;
  spffl::polynomials::f2n_poly_t om;
  int nr, nc;

  if (argc != 5) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[1])) {
    pusage(argv[0]);
  }
  {
    auto opt = spffl::polynomials::f2n_poly_from_string(argv[2], im);
    if (!opt) pusage(argv[0]);
    om = std::move(*opt);
  }
  if (sscanf(argv[3], "%d", &nr) != 1) {
    pusage(argv[0]);
  }
  if (sscanf(argv[4], "%d", &nc) != 1) {
    pusage(argv[0]);
  }

  spffl::containers::matrix_over<spffl::polynomials::f2n_polymod_t> A(nr, nc);
  for (int i = 0; i < nr; i++) {
    for (int j = 0; j < nc; j++) {
      A[i][j] = spffl::random::f2n_polymod_random(im, om);
    }
  }
  std::cout << A << "\n";

  return 0;
}
