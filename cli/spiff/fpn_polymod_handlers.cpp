#include "fpn_polymod_handlers.h"

#include "spffl/cli_parser/cmd_line_matrix_ops.h"
#include "spffl/cli_parser/cmd_line_ops.h"
#include "spffl/cli_parser/cmd_line_vector_ops.h"
#include "spffl/polynomials/fpn_polymod_t.h"

// ----------------------------------------------------------------
void fpn_pm_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
  exit(1);
}

int fpn_pm_op_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t im;
  spffl::polynomials::fpn_poly_t om;
  if (argc < 4) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[2], p)) {
    pusage(argv[0]);
  }
  if (!om.from_string(argv[3], im)) {
    pusage(argv[0]);
  }
  spffl::polynomials::fpn_polymod_t zero =
      spffl::polynomials::fpn_polymod_t::prime_subfield_element(0, om);
  spffl::polynomials::fpn_polymod_t one =
      spffl::polynomials::fpn_polymod_t::prime_subfield_element(1, om);
  spffl::cli_parser::cmd_line_parse<spffl::polynomials::fpn_polymod_t>(
      argc - 4, argv + 4, zero, one);
  return 0;
}

// ----------------------------------------------------------------
void fpn_pm_mat_op_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
  exit(1);
}

int fpn_pm_mat_op_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t im;
  spffl::polynomials::fpn_poly_t om;
  if (argc < 4) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &p) != 1) {
    pusage(argv[0]);
  }
  if (!im.from_string(argv[2], p)) {
    pusage(argv[0]);
  }
  if (!om.from_string(argv[3], im)) {
    pusage(argv[0]);
  }
  spffl::polynomials::fpn_polymod_t zero =
      spffl::polynomials::fpn_polymod_t::prime_subfield_element(0, om);
  spffl::polynomials::fpn_polymod_t one =
      spffl::polynomials::fpn_polymod_t::prime_subfield_element(1, om);
  spffl::cli_parser::cmd_line_mat_parse<spffl::polynomials::fpn_polymod_t>(
      argc - 4, argv + 4, zero, one);
  return 0;
}
