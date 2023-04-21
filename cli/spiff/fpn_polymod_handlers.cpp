#include "fpn_polymod_handlers.h"
#include "cmd_line_matrix_ops.h"
#include "cmd_line_ops.h"
#include "cmd_line_vector_ops.h"
#include "fpn_polymod_t.h"

// ----------------------------------------------------------------
void fpnpmop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
  exit(1);
}

int fpnpmop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  fp_poly_t im;
  fpn_poly_t om;
  if (argc < 4)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!im.from_string(argv[2], p))
    pusage(argv[0]);
  if (!om.from_string(argv[3], im))
    pusage(argv[0]);
  fpn_polymod_t zero = fpn_polymod_t::prime_sfld_elt(0, om);
  fpn_polymod_t one = fpn_polymod_t::prime_sfld_elt(1, om);
  cmd_line_parse<fpn_polymod_t>(argc - 4, argv + 4, zero, one);
  return 0;
}

// ----------------------------------------------------------------
void fpnpmmatop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
  exit(1);
}

int fpnpmmatop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  fp_poly_t im;
  fpn_poly_t om;
  if (argc < 4)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!im.from_string(argv[2], p))
    pusage(argv[0]);
  if (!om.from_string(argv[3], im))
    pusage(argv[0]);
  fpn_polymod_t zero = fpn_polymod_t::prime_sfld_elt(0, om);
  fpn_polymod_t one = fpn_polymod_t::prime_sfld_elt(1, om);
  cmd_line_mat_parse<fpn_polymod_t>(argc - 4, argv + 4, zero, one);
  return 0;
}
