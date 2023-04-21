#include "fpn_poly_handlers.h"
#include "fpn_poly_t.h"
#include "cmd_line_matrix_ops.h"
#include "qff.h"
#include <string.h>

// ----------------------------------------------------------------
void fpnpop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {...}\n";
  exit(1);
}

int fpnpop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  fp_poly_t im;
  if (argc < 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!im.from_string(argv[2], p))
    pusage(argv[0]);
  fpn_poly_t zero = fpn_poly_t::prime_sfld_elt(0, im);
  fpn_poly_t one = fpn_poly_t::prime_sfld_elt(1, im);
  cmd_line_parse<fpn_poly_t>(argc - 3, argv + 3, zero, one);
  return 0;
}

// ----------------------------------------------------------------
void fpnpmatop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {...}\n";
  exit(1);
}

int fpnpmatop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  fp_poly_t im;
  if (argc < 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!im.from_string(argv[2], p))
    pusage(argv[0]);
<<<<<<< HEAD:cli/spiff/fpnpoly_handlers.cpp
  fpnpoly_t zero = fpnpoly_t::prime_sfld_elt(0, im);
  fpnpoly_t one = fpnpoly_t::prime_sfld_elt(1, im);
  cmd_line_mat_parse<fpnpoly_t>(argc - 3, argv + 3, zero, one);
||||||| parent of bfba4fd (More underscores in names):cli/spiff/fpnpoly_handlers.cpp
  fpnpoly_t zero = fpnpoly_t::prime_sfld_elt(0, im);
  fpnpoly_t one = fpnpoly_t::prime_sfld_elt(1, im);
  ed_cmd_line_mat_parse<fpnpoly_t>(argc - 3, argv + 3, zero, one);
=======
  fpn_poly_t zero = fpn_poly_t::prime_sfld_elt(0, im);
  fpn_poly_t one = fpn_poly_t::prime_sfld_elt(1, im);
  ed_cmd_line_mat_parse<fpn_poly_t>(argc - 3, argv + 3, zero, one);
>>>>>>> bfba4fd (More underscores in names):cli/spiff/fpn_poly_handlers.cpp
  return 0;
}

void fpnpgcd_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-e] {p} {im} {a} {b}\n";
  exit(1);
}

int fpnpgcd_main(int argc, char **argv, usage_t *pusage) {
  int p;
  fp_poly_t im;
  fpn_poly_t a, b, g, r, s;

  if (argc == 5) {
    if (sscanf(argv[1], "%d", &p) != 1)
      pusage(argv[0]);
    if (!im.from_string(argv[2], p))
      pusage(argv[0]);
    if (!a.from_string(argv[3], im))
      pusage(argv[0]);
    if (!b.from_string(argv[4], im))
      pusage(argv[0]);
    g = a.gcd(b);
    std::cout << g << std::endl;
  } else if (argc == 6) {
    if (strcmp(argv[1], "-e") != 0)
      pusage(argv[0]);
    if (sscanf(argv[2], "%d", &p) != 1)
      pusage(argv[0]);
    if (!im.from_string(argv[3], p))
      pusage(argv[0]);
    if (!a.from_string(argv[4], im))
      pusage(argv[0]);
    if (!b.from_string(argv[5], im))
      pusage(argv[0]);
    g = a.ext_gcd(b, r, s);
    std::cout << g << " = " << r << " * " << a << " + " << s << " * " << b
              << std::endl;
  } else {
    pusage(argv[0]);
  }

  return 0;
}

void fpnpqp_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} {qpolys ...}\n";
  exit(1);
}

int fpnpqp_main(int argc, char **argv, usage_t *pusage) {
  int p;
  fp_poly_t m;
  qpoly_t qp;
  fpn_poly_t fpnp;
  if (argc < 4)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!m.from_string(argv[2], p))
    pusage(argv[0]);
  for (int argi = 3; argi < argc; argi++) {
    if (!qp.from_string(argv[argi]))
      pusage(argv[0]);
    fpnp = fpnpoly_from_qpoly(qp, m);
    std::cout << fpnp << "\n";
  }
  return 0;
}
