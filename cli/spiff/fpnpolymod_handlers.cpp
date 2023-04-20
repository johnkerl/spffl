#include "fpnpolymod_handlers.h"
#include "cmdlinematops.h"
#include "cmdlineops.h"
#include "cmdlinevecops.h"
#include "fpnpolymod_t.h"

// ----------------------------------------------------------------
void fpnpmop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
  exit(1);
}

int fpnpmop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  fppoly_t im;
  fpnpoly_t om;
  if (argc < 4)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!im.from_string(argv[2], p))
    pusage(argv[0]);
  if (!om.from_string(argv[3], im))
    pusage(argv[0]);
  fpnpolymod_t zero = fpnpolymod_t::prime_sfld_elt(0, om);
  fpnpolymod_t one = fpnpolymod_t::prime_sfld_elt(1, om);
  cmd_line_parse<fpnpolymod_t>(argc - 4, argv + 4, zero, one);
  return 0;
}

// ----------------------------------------------------------------
void fpnpmmatop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {im} {om} {...}\n";
  exit(1);
}

int fpnpmmatop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  fppoly_t im;
  fpnpoly_t om;
  if (argc < 4)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!im.from_string(argv[2], p))
    pusage(argv[0]);
  if (!om.from_string(argv[3], im))
    pusage(argv[0]);
  fpnpolymod_t zero = fpnpolymod_t::prime_sfld_elt(0, om);
  fpnpolymod_t one = fpnpolymod_t::prime_sfld_elt(1, om);
  cmd_line_mat_parse<fpnpolymod_t>(argc - 4, argv + 4, zero, one);
  return 0;
}
