#include "spffl/tmvpoly.h"
#include "spffl/tmvpolyscan.h"
#include "spffl/tmvrat.h"
#include "spffl/tmvratscan.h"

// ----------------------------------------------------------------
static void usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {rat func} {args}\n";
  exit(1);
}

// ----------------------------------------------------------------
int main(int argc, char **argv) {
  f2_poly_t m;
  tmvrat<f2_polymod_t> r;

  if (argc < 3)
    usage(argv[0]);
  if (!m.from_string(argv[1]))
    usage(argv[0]);
  if (!tmvrat_f2_polymod_from_string(r, argv[2], m))
    usage(argv[0]);
  // if (xxx) r = r.homogenize();
  int nvars = r.get_nvars();

  if ((argc - 3) != nvars)
    usage(argv[0]);
  tvector<f2_polymod_t> X(nvars);
  int argi, vi;
  for (argi = 3, vi = 0; argi < argc; argi++, vi++) {
    f2_polymod_t c;
    if (!c.from_string(argv[argi], m))
      usage(argv[0]);
    X[vi] = c;
  }
  f2_polymod_t Y = r.eval(X);
  std::cout << Y << "\n";

  return 0;
}
