#include "fp_poly_handlers.h"
#include "cmd_line_matrix_ops.h"
#include "cmd_line_ops.h"
#include "cmd_line_vector_ops.h"
#include "fp_linear_algebra.h"
#include "fp_poly_factor.h"
#include "fp_poly_random.h"
#include "fp_poly_t.h"
#include "fp_poly_totient.h"
#include "qff.h"
#include "list_elements.h"
#include <string.h>

void fpplist_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {deglo[-deghi]}\n";
  exit(1);
}

int fpplist_main(int argc, char **argv, usage_t *pusage) {
  int p, deglo, deghi;
  if (argc != 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (sscanf(argv[2], "%d-%d", &deglo, &deghi) == 2)
    ;
  else if (sscanf(argv[2], "%d", &deglo) == 1)
    deghi = deglo;
  else
    pusage(argv[0]);
  for (int deg = deglo; deg <= deghi; deg++) {
    tvector<spffl::polynomials::fp_poly_t> elts = fppoly_list(p, deg);
    elts.crout(std::cout);
  }
  return 0;
}

void fppop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
  exit(1);
}

int fppop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  if (argc < 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  cmd_line_parse<spffl::polynomials::fp_poly_t>(argc - 2, argv + 2, spffl::polynomials::fp_poly_t(0, p), spffl::polynomials::fp_poly_t(1, p));
  return 0;
}

void fppmatop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
  exit(1);
}

int fppmatop_main(int argc, char **argv, usage_t *pusage) {
  int p;
  if (argc < 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  cmd_line_mat_parse<spffl::polynomials::fp_poly_t>(argc - 2, argv + 2, spffl::polynomials::fp_poly_t(0, p),
                                  spffl::polynomials::fp_poly_t(1, p));
  return 0;
}

void fppcompmx_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {poly}\n";
  exit(1);
}

int fppcompmx_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t chpol;

  if (argc != 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!chpol.from_string(argv[2], p))
    pusage(argv[0]);

  tmatrix<spffl::intmath::intmod_t> A = fp_companion_matrix(chpol);
  std::cout << A << "\n";

  return 0;
}

void fppdeg_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
  exit(1);
}

int fppdeg_main(int argc, char **argv, usage_t *pusage) {
  int p;
  if (argc < 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);

  for (int argi = 2; argi < argc; argi++) {
    spffl::polynomials::fp_poly_t a;
    if (!a.from_string(argv[argi], p))
      pusage(argv[0]);
    if (argc > 3)
      std::cout << a << ": ";
    std::cout << a.find_degree() << "\n";
  }
  return 0;
}

void fppgcd_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} [-e] {a} {b}\n";
  exit(1);
}

int fppgcd_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t a, b, g, r, s;

  if (argc == 4) {
    if (sscanf(argv[1], "%d", &p) != 1)
      pusage(argv[0]);
    if (!a.from_string(argv[2], p))
      pusage(argv[0]);
    if (!b.from_string(argv[3], p))
      pusage(argv[0]);
    g = a.gcd(b);
    std::cout << g << std::endl;
  } else if (argc == 5) {
    if (strcmp(argv[1], "-e") != 0)
      pusage(argv[0]);
    if (sscanf(argv[2], "%d", &p) != 1)
      pusage(argv[0]);
    if (!a.from_string(argv[3], p))
      pusage(argv[0]);
    if (!b.from_string(argv[4], p))
      pusage(argv[0]);
    g = a.ext_gcd(b, r, s);
    std::cout << g << " = " << r << " * " << a << " + " << s << " * " << b
              << std::endl;
  } else {
    pusage(argv[0]);
  }

  return 0;
}

void fpplcm_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
  exit(1);
}

int fpplcm_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t a, l;

  if (argc < 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!a.from_string(argv[2], p))
    pusage(argv[0]);
  l = a;
  for (int argi = 3; argi < argc; argi++) {
    if (!a.from_string(argv[argi], p))
      pusage(argv[0]);
    l = (l * a) / l.gcd(a);
  }
  std::cout << l << std::endl;
  return 0;
}

void fpptotient_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
  exit(1);
}

int fpptotient_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t a;
  int phi;
  if (argc < 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  for (int argi = 2; argi < argc; argi++) {
    if (!a.from_string(argv[argi], p))
      pusage(argv[0]);
    phi = fp_poly_totient(a);
    if (argc > 3)
      std::cout << a << ": ";
    std::cout << phi << std::endl;
  }
  return 0;
}

void fpptest_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
  exit(1);
}

int fpptest_main(int argc, char **argv, usage_t *pusage) {
  int p;
  if (argc < 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);

  for (int argi = 2; argi < argc; argi++) {
    spffl::polynomials::fp_poly_t a;
    if (!a.from_string(argv[argi], p))
      pusage(argv[0]);
    if (argc > 3)
      std::cout << a << ": ";
    if (fppoly_is_irreducible(a))
      std::cout << "IRREDUCIBLE\n";
    else
      std::cout << "reducible\n";
  }
  return 0;
}

void fppfind_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-1|-r] {p} {deglo[-deghi]}\n";
  exit(1);
}

int fppfind_main(int argc, char **argv, usage_t *pusage) {
  bool do_random = false;
  int deglo, deghi;
  int p;

  if (argc != 4)
    pusage(argv[0]);
  if (strcmp(argv[1], "-1") == 0)
    do_random = false;
  else if (strcmp(argv[1], "-r") == 0)
    do_random = true;
  else
    pusage(argv[0]);
  if (sscanf(argv[2], "%d", &p) != 1)
    pusage(argv[0]);

  if (sscanf(argv[3], "%d-%d", &deglo, &deghi) == 2)
    ;
  else if (sscanf(argv[3], "%d", &deglo) == 1)
    deghi = deglo;
  else
    pusage(argv[0]);

  for (int deg = deglo; deg <= deghi; deg++) {
    spffl::polynomials::fp_poly_t a;
    if (do_random)
      a = fppoly_random_irr(p, deg);
    else
      a = fppoly_find_irr(p, deg);
    std::cout << a << "\n";
  }
  return 0;
}

void fppfactor_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {polys ...}\n";
  exit(1);
}

int fppfactor_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t a;

  if (argc < 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);

  for (int argi = 2; argi < argc; argi++) {
    if (!a.from_string(argv[argi], p))
      pusage(argv[0]);
    if (argc > 3)
      std::cout << a << " = ";
    tfacinfo<spffl::polynomials::fp_poly_t> finfo = fp_poly_factor(a);
    std::cout << finfo << "\n";

    spffl::polynomials::fp_poly_t check = finfo.unfactor(spffl::polynomials::fp_poly_t(spffl::intmath::intmod_t(1, p)));
    if (check != a) {
      std::cerr << "Coding error in fp_poly_factor.\n";
      std::cerr << "  Input: " << a << "\n";
      std::cerr << "  Check: " << check << "\n";
      std::cerr << "  Factors: " << finfo << "\n";
      exit(1);
    }
  }
  return 0;
}

void fppdivisors_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-mp] {p} {polys ...}\n";
  exit(1);
}

int fppdivisors_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t a;
  int argb = 1;
  int maximal_proper_only = 0;
  if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
    maximal_proper_only = 1;
    argb++;
  }
  if ((argc - argb) < 2)
    pusage(argv[0]);
  if (sscanf(argv[argb], "%d", &p) != 1)
    pusage(argv[0]);
  argb++;
  spffl::polynomials::fp_poly_t one(spffl::intmath::intmod_t(1, p));
  for (int argi = argb; argi < argc; argi++) {
    if (!a.from_string(argv[argi], p))
      pusage(argv[0]);
    if ((argc - argb) > 1)
      std::cout << a << ": ";
    tfacinfo<spffl::polynomials::fp_poly_t> finfo = fp_poly_factor(a);
    tvector<spffl::polynomials::fp_poly_t> divisors;
    if (maximal_proper_only) {
      if (!finfo.get_maximal_proper_divisors(divisors, one)) {
        std::cout << "(none)\n";
        continue;
      }
    } else {
      divisors = finfo.get_all_divisors(one);
    }
    int nd = divisors.get_num_elements();
    for (int k = 0; k < nd; k++) {
      if (k > 0)
        std::cout << " ";
      std::cout << divisors[k];
    }
    std::cout << "\n";
  }
  return 0;
}

void fppeval_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {f} {elements of Fp ...}\n";
  exit(1);
}

int fppeval_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::polynomials::fp_poly_t f;
  spffl::intmath::intmod_t a, b;

  if (argc < 4)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (!f.from_string(argv[2], p))
    pusage(argv[0]);
  for (int argi = 3; argi < argc; argi++) {
    if (!a.from_string(argv[argi], p))
      pusage(argv[0]);
    b = f.eval(a);
    std::cout << b << "\n";
  }

  return 0;
}

void fpprandom_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {deg} [count]\n";
  exit(1);
}

int fpprandom_main(int argc, char **argv, usage_t *pusage) {
  int p, deg, count = 1;

  if ((argc != 3) && (argc != 4))
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  if (sscanf(argv[2], "%d", &deg) != 1)
    pusage(argv[0]);
  if (argc == 4) {
    if (sscanf(argv[3], "%d", &count) != 1)
      pusage(argv[0]);
  }

  for (int i = 0; i < count; i++)
    std::cout << fp_poly_random(p, deg) << std::endl;

  return 0;
}

void fppqp_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {p} {qpolys ...}\n";
  exit(1);
}

int fppqp_main(int argc, char **argv, usage_t *pusage) {
  int p;
  spffl::rationals::qpoly_t qp;
  spffl::polynomials::fp_poly_t fpp;
  if (argc < 3)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &p) != 1)
    pusage(argv[0]);
  for (int argi = 2; argi < argc; argi++) {
    if (!qp.from_string(argv[argi]))
      pusage(argv[0]);
    fpp = fppoly_from_qpoly(qp, p);
    std::cout << fpp << "\n";
  }
  return 0;
}
