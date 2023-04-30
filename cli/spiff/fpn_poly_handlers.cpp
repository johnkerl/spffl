#include "fpn_poly_handlers.h"

#include "polynomials/fpn_poly_t.h"
#include "q_cyclo/qff.h"
#include "cliparser/cmd_line_matrix_ops.h"
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
  if (!im.from_string(argv[2], p)) {
    pusage(argv[0]);
  }
  spffl::polynomials::fpn_poly_t zero =
      spffl::polynomials::fpn_poly_t::prime_subfield_element(0, im);
  spffl::polynomials::fpn_poly_t one =
      spffl::polynomials::fpn_poly_t::prime_subfield_element(1, im);
  spffl::cliparser::cmd_line_parse<spffl::polynomials::fpn_poly_t>(
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
  if (!im.from_string(argv[2], p)) {
    pusage(argv[0]);
  }
  spffl::polynomials::fpn_poly_t zero =
      spffl::polynomials::fpn_poly_t::prime_subfield_element(0, im);
  spffl::polynomials::fpn_poly_t one =
      spffl::polynomials::fpn_poly_t::prime_subfield_element(1, im);
  spffl::cliparser::cmd_line_mat_parse<spffl::polynomials::fpn_poly_t>(
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
    if (!im.from_string(argv[2], p)) {
      pusage(argv[0]);
    }
    if (!a.from_string(argv[3], im)) {
      pusage(argv[0]);
    }
    if (!b.from_string(argv[4], im)) {
      pusage(argv[0]);
    }
    g = a.gcd(b);
    std::cout << g << std::endl;
  } else if (argc == 6) {
    if (strcmp(argv[1], "-e") != 0) {
      pusage(argv[0]);
    }
    if (sscanf(argv[2], "%d", &p) != 1) {
      pusage(argv[0]);
    }
    if (!im.from_string(argv[3], p)) {
      pusage(argv[0]);
    }
    if (!a.from_string(argv[4], im)) {
      pusage(argv[0]);
    }
    if (!b.from_string(argv[5], im)) {
      pusage(argv[0]);
    }
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
  spffl::rationals::qpoly_t qp;
  spffl::polynomials::fpn_poly_t fpnp;
  if (argc < 4) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!m.from_string(argv[2], p)) {
    pusage(argv[0]);
  }
  for (int argi = 3; argi < argc; argi++) {
    if (!qp.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    fpnp = spffl::q_cyclo::fpn_poly_from_qpoly(qp, m);
    std::cout << fpnp << "\n";
  }
  return 0;
}
