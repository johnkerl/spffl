#include "fpn_poly_handlers.h"

#include "spffl/cli_parser/cmd_line_matrix_ops.h"
#include "spffl/polynomials/fpn_f2n_io.hpp"
#include "spffl/polynomials/fpn_poly_t.h"
#include "spffl/q_cyclotomic/qff.h"

#include <string.h>

// ----------------------------------------------------------------
void fpn_p_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {...}\n";
  exit(1);
}

int fpn_p_op_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t im;
  if (argc < 3) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, im)) {
    pusage(argv[0]);
  }
  spffl::polynomials::fpn_poly_t zero =
      spffl::polynomials::prime_subfield_element(0, im);
  spffl::polynomials::fpn_poly_t one =
      spffl::polynomials::prime_subfield_element(1, im);
  spffl::cli_parser::cmd_line_parse<spffl::polynomials::fpn_poly_t>(
      argc - 3, argv + 3, zero, one);
  return 0;
}

// ----------------------------------------------------------------
void fpn_p_mat_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {...}\n";
  exit(1);
}

int fpn_p_mat_op_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t im;
  if (argc < 3) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, im)) {
    pusage(argv[0]);
  }
  spffl::polynomials::fpn_poly_t zero =
      spffl::polynomials::prime_subfield_element(0, im);
  spffl::polynomials::fpn_poly_t one =
      spffl::polynomials::prime_subfield_element(1, im);
  spffl::cli_parser::cmd_line_mat_parse<spffl::polynomials::fpn_poly_t>(
      argc - 3, argv + 3, zero, one);
  return 0;
}

void fpn_p_gcd_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-e] {p} {im} {a} {b}\n";
  exit(1);
}

int fpn_p_gcd_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t im;
  spffl::polynomials::fpn_poly_t a, b, g, r, s;

  if (argc == 5) {
    if (sscanf(argv[1], "%d", &p) != 1) {
      pusage(argv[0]);
    }
    if (!spffl::polynomials::fp_poly_from_string_into(argv[2], p, im)) {
      pusage(argv[0]);
    }
    auto opt_a = spffl::polynomials::fpn_poly_from_string(argv[3], im);
    auto opt_b = spffl::polynomials::fpn_poly_from_string(argv[4], im);
    if (!opt_a || !opt_b) pusage(argv[0]);
    a = std::move(*opt_a);
    b = std::move(*opt_b);
    g = a.gcd(b);
    std::cout << g << std::endl;
  } else if (argc == 6) {
    if (strcmp(argv[1], "-e") != 0) {
      pusage(argv[0]);
    }
    if (sscanf(argv[2], "%d", &p) != 1) {
      pusage(argv[0]);
    }
    if (!spffl::polynomials::fp_poly_from_string_into(argv[3], p, im)) {
      pusage(argv[0]);
    }
    auto opt_a = spffl::polynomials::fpn_poly_from_string(argv[4], im);
    auto opt_b = spffl::polynomials::fpn_poly_from_string(argv[5], im);
    if (!opt_a || !opt_b) pusage(argv[0]);
    a = std::move(*opt_a);
    b = std::move(*opt_b);
    g = a.ext_gcd(b, r, s);
    std::cout << g << " = " << r << " * " << a << " + " << s << " * " << b
              << std::endl;
  } else {
    pusage(argv[0]);
  }

  return 0;
}

void fpn_p_qp_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {m} {qpolys ...}\n";
  exit(1);
}

int fpn_p_qp_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t m;
  spffl::polynomials::q_poly_t qp;
  spffl::polynomials::fpn_poly_t fpnp;
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
    if (!qp.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    fpnp = spffl::q_cyclotomic::fpn_poly_from_qpoly(qp, m);
    std::cout << fpnp << "\n";
  }
  return 0;
}
