#include "fp_polymod_handlers.h"
#include "tbl_types.h"

#include "spffl/cli_parser/cmd_line_matrix_ops.h"
#include "spffl/cli_parser/cmd_line_ops.h"
#include "spffl/cli_parser/cmd_line_vector_ops.h"
#include "spffl/linalg/min_char_polys.h"
#include "spffl/list/list_elements.h"
#include "spffl/polynomials/fp_polymod_t.h"
#include "spffl/polynomials/fp_poly_io.h"
#include "spffl/random/fp_polymod_random.h"

#include <string.h>

void fp_pm_list_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-a|-u] {p} {m}\n";
  exit(1);
}

int fp_pm_list_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;
  spffl::list::sp_list_type_t type = spffl::list::SP_LIST_ALL;
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
  if (sscanf(argv[2], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[3], p, m)) {
    pusage(argv[0]);
  }
  spffl::containers::vector_over<spffl::polynomials::fp_polymod_t> elts = fp_polymod_list(m, type);
  elts.crout(std::cout);
  return 0;
}

void fp_pm_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} {...}\n";
  exit(1);
}

int fp_pm_op_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;

  if (argc < 3) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
  }
  spffl::cli_parser::cmd_line_parse<spffl::polynomials::fp_polymod_t>(argc - 3,
      argv + 3, spffl::polynomials::fp_polymod_t::prime_subfield_element(0, m),
      spffl::polynomials::fp_polymod_t::prime_subfield_element(1, m));
  return 0;
}

void fp_pm_tbl_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} {+|-|*|u*|/}\n";
  exit(1);
}

int fp_pm_tbl_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;
  spffl::polynomials::fp_polymod_t g;

  int tbl_type = TBL_TYPE_PLUS;
  if (argc != 4) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
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

#if 0
	else if (strncmp(argv[3], "log:", 4) == 0) {
		if (!spffl::polynomials::fp_polymod_from_string_into(&argv[3][4], m, g))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strcmp(argv[3], "log") == 0) {
		if (!fp_polymod_find_generator(m, g)) {
			std::cerr << "Couldn't find generator mod "
				<< m << "\n";
			exit(1);
		}
		tbl_type = TBL_TYPE_LOG;
	}
	else if (strncmp(argv[3], "alog:", 5) == 0) {
		if (!spffl::polynomials::fp_polymod_from_string_into(&argv[3][5], m, g))
			pusage(argv[0]);
		tbl_type = TBL_TYPE_ALOG;
	}
	else if (strcmp(argv[3], "alog") == 0) {
		if (!fp_polymod_find_generator(m, g)) {
			std::cerr << "Couldn't find generator mod "
				<< m << "\n";
			exit(1);
		}
		tbl_type = TBL_TYPE_ALOG;
	}
#endif
  else {
    pusage(argv[0]);
  }

  spffl::containers::vector_over<spffl::polynomials::fp_polymod_t> elts;
  if ((tbl_type == TBL_TYPE_UNIT_MUL) || (tbl_type == TBL_TYPE_UNIT_DIV) ||
      (tbl_type == TBL_TYPE_LOG) || (tbl_type == TBL_TYPE_ALOG)) {
    elts = fp_polymod_list(m, spffl::list::SP_LIST_UNITS);
  } else {
    elts = fp_polymod_list(m, spffl::list::SP_LIST_ALL);
  }
  int n = elts.get_num_elements();

#if 0
	if (tbl_type == TBL_TYPE_LOG) {
		std::cout << "element power\n";
		std::cout << "------- -----\n";
		for (int i = 0; i < n; i++) {
			int e = fp_polymod_log(g, elts[i]);
			std::cout << elts[i] << " " << e << "\n";
		}
		return 0;
	}
	if (tbl_type == TBL_TYPE_ALOG) {
		std::cout << "power element\n";
		std::cout << "----- -------\n";
		spffl::polynomials::fp_polymod_t gp = g / g;
		for (int i = 0; i < n; i++) {
			std::cout << i << " " << gp << "\n";
			gp *= g;
		}
		return 0;
	}
#endif

  spffl::polynomials::fp_polymod_t a, b, c;

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

int fp_pm_mat_op_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;

  if (argc < 3) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
  }
  spffl::cli_parser::cmd_line_mat_parse<spffl::polynomials::fp_polymod_t>(
      argc - 3, argv + 3,
      spffl::polynomials::fp_polymod_t::prime_subfield_element(0, m),
      spffl::polynomials::fp_polymod_t::prime_subfield_element(1, m));
  return 0;
}

int fp_pm_vecop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;

  if (argc < 3) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
  }
  spffl::cli_parser::cmd_line_vec_parse<spffl::polynomials::fp_polymod_t>(
      argc - 3, argv + 3,
      spffl::polynomials::fp_polymod_t::prime_subfield_element(0, m),
      spffl::polynomials::fp_polymod_t::prime_subfield_element(1, m));
  return 0;
}

void fp_pm_mat_ord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} {goes here}\n";
  exit(1);
}

int fp_pm_mat_ord_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;

  if ((argc != 3) && (argc != 4)) {
    pusage(argv[0]);
  }

  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
  }

  spffl::polynomials::fp_polymod_t zero =
      spffl::polynomials::fp_polymod_t::prime_subfield_element(0, m);
  spffl::polynomials::fp_polymod_t one =
      spffl::polynomials::fp_polymod_t::prime_subfield_element(1, m);

  tmatrix<spffl::polynomials::fp_polymod_t> A;
  A = zero;
  std::cin >> A;
  spffl::polynomials::fp_polymod_t d = A.det();

  if (d == zero) {
    std::cout << 0 << std::endl;
  } else {
    tmatrix<spffl::polynomials::fp_polymod_t> I = A.make_I(zero, one);
    int order;
    tmatrix<spffl::polynomials::fp_polymod_t> Apower = A;

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

void fp_pm_mat_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} {# rows} {# cols}\n";
  exit(1);
}

int fp_pm_mat_random_main(int argc, char **argv, usage_t *pusage) {
  int p, nr, nc;
  spffl::polynomials::fp_poly_t m;

  if (argc != 5) {
    pusage(argv[0]);
  }

  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
  }
  if (sscanf(argv[3], "%d", &nr) != 1) {
    pusage(argv[0]);
  }
  if (sscanf(argv[4], "%d", &nc) != 1) {
    pusage(argv[0]);
  }

  tmatrix<spffl::polynomials::fp_polymod_t> A(nr, nc);
  for (int i = 0; i < nr; i++) {
    for (int j = 0; j < nc; j++) {
      A[i][j] = spffl::random::fp_polymod_random(m);
    }
  }
  std::cout << A;
  return 0;
}

void fp_pm_ord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} {a}\n";
  exit(1);
}

int fp_pm_ord_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;
  spffl::polynomials::fp_polymod_t a;

  if (argc != 4) {
    pusage(argv[0]);
  }

  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_polymod_from_string_into(argv[3], m, a)) {
    pusage(argv[0]);
  }

  spffl::polynomials::fp_polymod_t ai;
  if (!a.recip(ai)) {
    std::cout << 0 << std::endl;
    return 0;
  }

  spffl::polynomials::fp_polymod_t zero(spffl::intmath::intmod_t(0, p), m);
  spffl::polynomials::fp_polymod_t one(spffl::intmath::intmod_t(1, p), m);
  int order;
  spffl::polynomials::fp_polymod_t apower = a;

  for (order = 1;; order++) {
    if (apower == one) {
      std::cout << order << std::endl;
      return 0;
    }
    apower *= a;
  }

  std::cout << order << std::endl;

  return 0;
}

void fp_pm_ch_pol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} {residues ...}\n";
  exit(1);
}

int fp_pm_ch_pol_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;
  spffl::polynomials::fp_polymod_t a;

  if (argc < 4) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
  }
  for (int argi = 3; argi < argc; argi++) {
    if (!spffl::polynomials::fp_polymod_from_string_into(argv[argi], m, a)) {
      pusage(argv[0]);
    }
    spffl::polynomials::fp_poly_t cp =
        spffl::linalg::fp_polymod_characteristic_polynomial(a);
    if (argc > 4) {
      std::cout << a << ": ";
    }
    std::cout << cp << "\n";
  }

  return 0;
}

void fp_pm_min_pol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} {residues ...}\n";
  exit(1);
}

int fp_pm_min_pol_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;
  spffl::polynomials::fp_polymod_t a;

  if (argc < 4) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
  }
  for (int argi = 3; argi < argc; argi++) {
    if (!spffl::polynomials::fp_polymod_from_string_into(argv[argi], m, a)) {
      pusage(argv[0]);
    }
    spffl::polynomials::fp_poly_t cp =
        spffl::linalg::fp_polymod_minimal_polynomial(a);
    if (argc > 4) {
      std::cout << a << ": ";
    }
    std::cout << cp << "\n";
  }

  return 0;
}

void fp_pm_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} [count]\n";
  exit(1);
}

int fp_pm_random_main(int argc, char **argv, usage_t *pusage) {
  int p, count = 1;
  spffl::polynomials::fp_poly_t m;

  if ((argc != 3) && (argc != 4)) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, m)) {
    pusage(argv[0]);
  }
  if (argc == 4) {
    if (sscanf(argv[3], "%d", &count) != 1) {
      pusage(argv[0]);
    }
  }

  for (int i = 0; i < count; i++) {
    std::cout << spffl::random::fp_polymod_random(m) << std::endl;
  }

  return 0;
}
