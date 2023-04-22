#include "fp_handlers.h"
#include "cmd_line_matrix_ops.h"
#include "cmd_line_ops.h"
#include "cmd_line_vector_ops.h"
#include "fp_units.h"
#include "fp_linear_algebra.h"
#include "intmod_random.h"
#include "intmod_t.h"
#include "list_elements.h"
#include "tbl_types.h"
#include "tmatrix.h"
#include <string.h>

void fplist_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-a|-u] {p}\n";
  exit(1);
}

int fplist_main(int argc, char **argv, usage_t *pusage) {
  sp_list_type_t type = SP_LIST_ALL;
  int m;
  // -g
  // -o {spec}
  if (argc == 3) {
    if (strcmp(argv[1], "-a") == 0)
      type = SP_LIST_ALL;
    else if (strcmp(argv[1], "-u") == 0)
      type = SP_LIST_UNITS;
    else if (strcmp(argv[1], "-nu") == 0)
      type = SP_LIST_NON_UNITS;
    else
      pusage(argv[0]);
    if (sscanf(argv[2], "%d", &m) != 1)
      pusage(argv[0]);
    tvector<spffl::intmath::intmod_t> elts = intmod_list(m, type);
    elts.crout(std::cout);
  } else if (argc == 4) {
    spffl::intmath::intmod_t g;
    if (strcmp(argv[1], "-m") == 0)
      type = SP_LIST_MULTIPLES;
    else if (strcmp(argv[1], "-rp") == 0)
      type = SP_LIST_REL_PRIME;
    else
      pusage(argv[0]);
    if (sscanf(argv[3], "%d", &m) != 1)
      pusage(argv[0]);
    if (!g.from_string(argv[2], m))
      pusage(argv[0]);
    tvector<spffl::intmath::intmod_t> elts = intmod_glist(g, type);
    elts.crout(std::cout);
  } else {
    pusage(argv[0]);
  }
  return 0;
}
void fpop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {...}\n";
  exit(1);
}

int fpop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  if (argc < 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  cmd_line_parse<spffl::intmath::intmod_t>(argc - 2, argv + 2, spffl::intmath::intmod_t(0, p), spffl::intmath::intmod_t(1, p));
  return 0;
}

void fptbl_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {+|-|*|u*|/|log[:g]|alog[:g]}\n";
  exit(1);
}

int fptbl_main(int argc, char **argv, usage_t *pusage) {
  int p;
  int tbl_type = TBL_TYPE_PLUS;
  spffl::intmath::intmod_t g;

  if (argc != 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);

  if (strcmp(argv[2], "+") == 0)
    tbl_type = TBL_TYPE_PLUS;
  else if (strcmp(argv[2], "-") == 0)
    tbl_type = TBL_TYPE_MINUS;
  else if (strcmp(argv[2], "*") == 0)
    tbl_type = TBL_TYPE_MUL;
  else if (strcmp(argv[2], ".") == 0)
    tbl_type = TBL_TYPE_MUL;
  else if (strcmp(argv[2], "u*") == 0)
    tbl_type = TBL_TYPE_UNIT_MUL;
  else if (strcmp(argv[2], "u.") == 0)
    tbl_type = TBL_TYPE_UNIT_MUL;
  else if (strcmp(argv[2], "/") == 0)
    tbl_type = TBL_TYPE_UNIT_DIV;

  else if (strncmp(argv[2], "log:", 4) == 0) {
    if (!g.from_string(&argv[2][4], p))
      pusage(argv[0]);
    tbl_type = TBL_TYPE_LOG;
  } else if (strcmp(argv[2], "log") == 0) {
    if (!fp_find_generator(p, g)) {
      std::cerr << "Couldn't find generator mod " << p << "\n";
      exit(1);
    }
    tbl_type = TBL_TYPE_LOG;
  } else if (strncmp(argv[2], "alog:", 5) == 0) {
    if (!g.from_string(&argv[2][5], p))
      pusage(argv[0]);
    tbl_type = TBL_TYPE_ALOG;
  } else if (strcmp(argv[2], "alog") == 0) {
    if (!fp_find_generator(p, g)) {
      std::cerr << "Couldn't find generator mod " << p << "\n";
      exit(1);
    }
    tbl_type = TBL_TYPE_ALOG;
  } else
    pusage(argv[0]);

  tvector<spffl::intmath::intmod_t> elts;
  if ((tbl_type == TBL_TYPE_UNIT_MUL) || (tbl_type == TBL_TYPE_UNIT_DIV) ||
      (tbl_type == TBL_TYPE_LOG) || (tbl_type == TBL_TYPE_ALOG))
    elts = intmod_list(p, SP_LIST_UNITS);
  else
    elts = intmod_list(p, SP_LIST_ALL);
  int n = elts.get_num_elements();

  if (tbl_type == TBL_TYPE_LOG) {
    std::cout << "element power\n";
    std::cout << "------- -----\n";
    for (int i = 0; i < n; i++) {
      int e = fp_log(g, elts[i]);
      std::cout << elts[i] << " " << e << "\n";
    }
    return 0;
  }
  if (tbl_type == TBL_TYPE_ALOG) {
    std::cout << "power element\n";
    std::cout << "----- -------\n";
    spffl::intmath::intmod_t gp = g / g;
    for (int i = 0; i < n; i++) {
      std::cout << i << " " << gp << "\n";
      gp *= g;
    }
    return 0;
  }

  spffl::intmath::intmod_t a, b, c;

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
      if (j > 0)
        std::cout << " ";
      std::cout << c;
    }
    std::cout << "\n";
  }

  return 0;
}

void fpord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {a}\n";
  exit(1);
}

int fpord_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::intmath::intmod_t a;
  if (argc < 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  for (int argi = 2; argi < argc; argi++) {
    if (!a.from_string(argv[argi], p))
      pusage(argv[0]);
    if (argc > 3)
      std::cout << a << ": ";
    std::cout << fp_order(a) << "\n";
  }
  return 0;
}

void fpmaxord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p}\n";
  exit(1);
}

int fpmaxord_main(int argc, char **argv, usage_t *pusage) {
  int p;
  if (argc != 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  tvector<spffl::intmath::intmod_t> elts = intmod_list(p, SP_LIST_UNITS);
  int n = elts.get_num_elements();
  int max = 0;
  for (int i = 0; i < n; i++) {
    int cur = fp_order(elts[i]);
    if (cur > max)
      max = cur;
  }
  std::cout << max << "\n";
  return 0;
}

void fporbit_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {a} [a0]\n";
  exit(1);
}

int fporbit_main(int argc, char **argv, usage_t *pusage) {
  int p, a, apower;
  int a0 = 1;
  if ((argc != 3) && (argc != 4))
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (sscanf(argv[2], "%d", &a) != 1)
    pusage(argv[0]);
  if (argc == 4) {
    if (sscanf(argv[3], "%d", &a0) != 1)
      pusage(argv[0]);
  }
  if (gcd(a, p) != 1) {
    std::cerr << "fporbit_main: a must be coprime to p.\n";
    exit(1);
  }

  a %= p;
  a0 %= p;
  apower = a;

  int counter = 0;
  while (1) {
    std::cout << ((apower * a0) % p) << "\n";

    if (apower == 1)
      break;

    counter++;
    if (counter > p) {
      std::cerr << "Internal error finding orbit of " << a0 << " mod " << p
                << "\n";
      exit(1);
    }

    apower = (apower * a) % p;
  }

  return 0;
}

void fpfindgen_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p}\n";
  exit(1);
}

int fpfindgen_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::intmath::intmod_t g;
  int rv = 0;
  if (argc < 2)
    pusage(argv[0]);
  for (int argi = 1; argi < argc; argi++) {
    if (sscanf(argv[argi], "%d", &p) != 1)
      pusage(argv[0]);
    if (argc > 2)
      std::cout << p << ": ";
    if (fp_find_generator(p, g)) {
      std::cout << g << "\n";
    } else {
      std::cout << "Generator not found.\n";
      rv = 1;
    }
  }
  return rv;
}

void fplog_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {g} {a}\n";
  exit(1);
}

int fplog_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::intmath::intmod_t g, a;
  if (argc < 4)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!g.from_string(argv[2], p))
    pusage(argv[0]);
  for (int argi = 3; argi < argc; argi++) {
    if (!a.from_string(argv[argi], p))
      pusage(argv[0]);
    if (argc > 4)
      std::cout << a << ": ";
    std::cout << fp_log(g, a) << "\n";
  }
  return 0;
}

void fprandom_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} [count]\n";
  exit(1);
}

int fprandom_main(int argc, char **argv, usage_t *pusage) {
  int m, count = 1;

  if ((argc != 2) && (argc != 3))
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &m) != 1)
    pusage(argv[0]);
  if (argc == 3) {
    if (sscanf(argv[2], "%d", &count) != 1)
      pusage(argv[0]);
  }

  for (int i = 0; i < count; i++)
    std::cout << intmod_random(m) << std::endl;

  return 0;
}

void fpmatop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
  exit(1);
}

int fpmatop_main(int argc, char **argv, usage_t *pusage) {
  int p = 0;
  if (argc < 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  cmd_line_mat_parse<spffl::intmath::intmod_t>(argc - 2, argv + 2, spffl::intmath::intmod_t(0, p),
                               spffl::intmath::intmod_t(1, p));
  return 0;
}

void fpvecop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
  exit(1);
}

int fpvecop_main(int argc, char **argv, usage_t *pusage) {
  int p = 0;
  if (argc < 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  cmd_line_vec_parse<spffl::intmath::intmod_t>(argc - 2, argv + 2, spffl::intmath::intmod_t(0, p),
                               spffl::intmath::intmod_t(1, p));
  return 0;
}

void fpmatchpol_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
  exit(1);
}

int fpmatchpol_main(int argc, char **argv, usage_t *pusage) {
  int p;
  tmatrix<spffl::intmath::intmod_t> A;

  if (argc != 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  A = spffl::intmath::intmod_t(0, p);
  if (!A.load_from_file(argv[2]))
    pusage(argv[0]);

  fp_poly_t chpol = fp_char_poly(A);
  std::cout << chpol << std::endl;

  return 0;
}

void fpmatord_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {goes here}\n";
  exit(1);
}

int fpmatord_main(int argc, char **argv, usage_t *pusage) {
  int p;
  tmatrix<spffl::intmath::intmod_t> A;

  if (argc != 2)
    pusage(argv[0]);

  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  spffl::intmath::intmod_t zero(0, p);
  spffl::intmath::intmod_t one(1, p);

  A = zero;
  std::cin >> A;
  spffl::intmath::intmod_t d = A.det();

  if (d == zero) {
    std::cout << 0 << std::endl;
  } else {
    tmatrix<spffl::intmath::intmod_t> I = A.make_I(zero, one);
    int order;
    tmatrix<spffl::intmath::intmod_t> Apower = A;

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

void fpmatrandom_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {# rows} {# cols}\n";
  exit(1);
}

int fpmatrandom_main(int argc, char **argv, usage_t *pusage) {
  int p, nr, nc;

  if (argc != 4)
    pusage(argv[0]);

  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (sscanf(argv[2], "%d", &nr) != 1)
    pusage(argv[0]);
  if (sscanf(argv[3], "%d", &nc) != 1)
    pusage(argv[0]);
  tmatrix<spffl::intmath::intmod_t> A(nr, nc);
  for (int i = 0; i < nr; i++)
    for (int j = 0; j < nc; j++)
      A[i][j] = intmod_random(p);
  std::cout << A;
  return 0;
}
