#include "f2n_poly_handlers.h"
#include "cmd_line_matrix_ops.h"
#include "cmd_line_ops.h"
#include "cmd_line_vector_ops.h"
#include "f2n_poly_factor.h"
#include "f2n_poly_random.h"
#include "f2n_poly_t.h"
#include "f2n_poly_totient.h"
#include "f2_polymod_linear_algebra.h"
#include "qff.h"
#include "qpoly_t.h"
#include "list_elements.h"
#include "tbl_types.h"
#include <string.h>

void f2nplist_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {deglo[-deghi]}\n";
  exit(1);
}

int f2nplist_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  int deglo, deghi;
  if (argc != 3)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);

  if (sscanf(argv[2], "%d-%d", &deglo, &deghi) == 2)
    ;
  else if (sscanf(argv[2], "%d", &deglo) == 1)
    deghi = deglo;
  else
    pusage(argv[0]);
  for (int deg = deglo; deg <= deghi; deg++) {
    tvector<spffl::polynomials::f2n_poly_t> elts = spffl::list::f2npoly_list(m, deg);
    elts.crout(std::cout);
  }
  return 0;
}

void f2npop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {...}\n";
  exit(1);
}

int f2npop_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  if (argc < 2)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  spffl::polynomials::f2n_poly_t zero = spffl::polynomials::f2n_poly_t::prime_sfld_elt(0, m);
  spffl::polynomials::f2n_poly_t one = spffl::polynomials::f2n_poly_t::prime_sfld_elt(1, m);
  cmd_line_parse<spffl::polynomials::f2n_poly_t>(argc - 2, argv + 2, zero, one);
  return 0;
}

void f2npdeg_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
  exit(1);
}

int f2npdeg_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  if (argc < 2)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);

  for (int argi = 2; argi < argc; argi++) {
    spffl::polynomials::f2n_poly_t a;
    if (!a.from_string(argv[argi], m))
      pusage(argv[0]);
    if (argc > 3)
      std::cout << a << ": ";
    std::cout << a.find_degree() << std::endl;
  }
  return 0;
}

void f2npgcd_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-e] {m} {a} {b}\n";
  exit(1);
}

int f2npgcd_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2n_poly_t a, b, g, r, s;

  if (argc == 4) {
    if (!m.from_string(argv[1]))
      pusage(argv[0]);
    if (!a.from_string(argv[2], m))
      pusage(argv[0]);
    if (!b.from_string(argv[3], m))
      pusage(argv[0]);
    g = a.gcd(b);
    std::cout << g << std::endl;

  } else if (argc == 5) {
    if (strcmp(argv[1], "-e") != 0)
      pusage(argv[0]);
    if (!m.from_string(argv[2]))
      pusage(argv[0]);
    if (!a.from_string(argv[3], m))
      pusage(argv[0]);
    if (!b.from_string(argv[4], m))
      pusage(argv[0]);

    g = a.ext_gcd(b, r, s);
    std::cout << g << " = " << r << " * " << a << " + " << s << " * " << b
              << std::endl;

    spffl::polynomials::f2n_poly_t check = a * r + b * s;
    if (g != check) {
      std::cerr << "Coding error in extended GCD.\n";
      exit(1);
    }
  } else {
    pusage(argv[0]);
  }

  return 0;
}

void f2nplcm_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
  exit(1);
}

int f2nplcm_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2n_poly_t a, l;

  if (argc < 3)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  if (!a.from_string(argv[2], m))
    pusage(argv[0]);
  l = a;
  for (int argi = 3; argi < argc; argi++) {
    if (!a.from_string(argv[argi], m))
      pusage(argv[0]);
    l = (l * a) / l.gcd(a);
  }
  std::cout << l << std::endl;
  return 0;
}

void f2nptotient_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
  exit(1);
}

int f2nptotient_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2n_poly_t a;
  int phi;
  if (argc < 3)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  for (int argi = 2; argi < argc; argi++) {
    if (!a.from_string(argv[argi], m))
      pusage(argv[0]);
    phi = spffl::factorization::f2n_poly_totient(a);
    if (argc > 3)
      std::cout << a << ": ";
    std::cout << phi << std::endl;
  }
  return 0;
}

void f2nptest_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
  exit(1);
}

int f2nptest_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  if (argc < 2)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);

  for (int argi = 2; argi < argc; argi++) {
    spffl::polynomials::f2n_poly_t a;
    if (!a.from_string(argv[argi], m))
      pusage(argv[0]);
    if (argc > 3)
      std::cout << a << ": ";
    if (spffl::factorization::f2npoly_is_irreducible(a))
      std::cout << "IRREDUCIBLE\n";
    else
      std::cout << "reducible\n";
  }
  return 0;
}

void f2npfind_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-1|-r] {m} {deglo[-deghi]}\n";
  exit(1);
}

int f2npfind_main(int argc, char **argv, usage_t *pusage) {
  bool do_random = false;
  int deglo, deghi;
  spffl::polynomials::f2_poly_t m;

  if (argc != 4)
    pusage(argv[0]);
  if (strcmp(argv[1], "-1") == 0)
    do_random = false;
  else if (strcmp(argv[1], "-r") == 0)
    do_random = true;
  else
    pusage(argv[0]);
  if (!m.from_string(argv[2]))
    pusage(argv[0]);

  if (sscanf(argv[3], "%d-%d", &deglo, &deghi) == 2)
    ;
  else if (sscanf(argv[3], "%d", &deglo) == 1)
    deghi = deglo;
  else
    pusage(argv[0]);

  for (int deg = deglo; deg <= deghi; deg++) {
    spffl::polynomials::f2n_poly_t a;
    if (do_random)
      a = spffl::factorization::f2npoly_random_irr(m, deg);
    else
      a = spffl::factorization::f2npoly_find_irr(m, deg);
    std::cout << a << std::endl;
  }
  return 0;
}

void f2npfactor_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {polys ...}\n";
  exit(1);
}

int f2npfactor_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  if (argc < 2)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);

  for (int argi = 2; argi < argc; argi++) {
    spffl::polynomials::f2n_poly_t a;
    if (!a.from_string(argv[argi], m))
      pusage(argv[0]);
    if (argc > 3)
      std::cout << a << " = ";
    tfacinfo<spffl::polynomials::f2n_poly_t> finfo = spffl::factorization::f2n_poly_factor(a);
    std::cout << finfo << std::endl;

    spffl::polynomials::f2_poly_t z(1);
    spffl::polynomials::f2n_poly_t one(spffl::polynomials::f2_polymod_t(z, m));
    spffl::polynomials::f2n_poly_t check = finfo.unfactor(one);
    if (check != a) {
      std::cerr << "Coding error in spffl::factorization::f2n_poly_factor.\n";
      std::cerr << "  Input: " << a << std::endl;
      std::cerr << "  Check: " << check << std::endl;
      std::cerr << "  Factors: " << finfo << std::endl;
      exit(1);
    }
  }
  return 0;
}

void f2npdivisors_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-mp] {m} {polys ...}\n";
  exit(1);
}

int f2npdivisors_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2n_poly_t a;
  int argb = 1;
  int maximal_proper_only = 0;
  if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
    maximal_proper_only = 1;
    argb++;
  }
  if ((argc - argb) < 2)
    pusage(argv[0]);
  if (!m.from_string(argv[argb]))
    pusage(argv[0]);
  argb++;
  spffl::polynomials::f2_polymod_t c1(spffl::polynomials::f2_poly_t(1), m);
  spffl::polynomials::f2n_poly_t one(c1);
  for (int argi = argb; argi < argc; argi++) {
    if (!a.from_string(argv[argi], m))
      pusage(argv[0]);
    if ((argc - argb) > 1)
      std::cout << a << ": ";
    tfacinfo<spffl::polynomials::f2n_poly_t> finfo = spffl::factorization::f2n_poly_factor(a);
    tvector<spffl::polynomials::f2n_poly_t> divisors;
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
    std::cout << std::endl;
  }
  return 0;
}

void f2npeval_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {f} {elements of Fq ...}\n";
  exit(1);
}

int f2npeval_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2n_poly_t f;
  spffl::polynomials::f2_polymod_t a, b;

  if (argc < 4)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  if (!f.from_string(argv[2], m))
    pusage(argv[0]);
  for (int argi = 3; argi < argc; argi++) {
    if (!a.from_string(argv[argi], m))
      pusage(argv[0]);
    b = f.eval(a);
    std::cout << b << std::endl;
  }

  return 0;
}

void f2nprandom_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {deg} [count]\n";
  exit(1);
}

int f2nprandom_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  int deg, count = 1;

  if ((argc != 3) && (argc != 4))
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  if (sscanf(argv[2], "%d", &deg) != 1)
    pusage(argv[0]);
  if (argc == 4) {
    if (sscanf(argv[3], "%d", &count) != 1)
      pusage(argv[0]);
  }

  for (int i = 0; i < count; i++)
    std::cout << spffl::random::f2n_poly_random(m, deg) << std::endl;

  return 0;
}

void f2npcompmx_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {poly}\n";
  exit(1);
}

int f2npcompmx_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::polynomials::f2n_poly_t chpol;

  if (argc != 3)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  if (!chpol.from_string(argv[2], m))
    pusage(argv[0]);

  tmatrix<spffl::polynomials::f2_polymod_t> A = spffl::linalg::f2np_companion_matrix(chpol);
  std::cout << A << std::endl;

  return 0;
}

void f2npqp_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {qpolys ...}\n";
  exit(1);
}

int f2npqp_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  spffl::rationals::qpoly_t qp;
  spffl::polynomials::f2n_poly_t f2np;
  if (argc < 3)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  for (int argi = 2; argi < argc; argi++) {
    if (!qp.from_string(argv[argi]))
      pusage(argv[0]);
    f2np = spffl::qcyclo::f2npoly_from_qpoly(qp, m);
    std::cout << f2np << std::endl;
  }
  return 0;
}

void f2npmatop_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {m} {...}\n";
  exit(1);
}

int f2npmatop_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t m;
  if (argc < 2)
    pusage(argv[0]);
  if (!m.from_string(argv[1]))
    pusage(argv[0]);
  spffl::polynomials::f2n_poly_t zero = spffl::polynomials::f2n_poly_t::prime_sfld_elt(0, m);
  spffl::polynomials::f2n_poly_t one = spffl::polynomials::f2n_poly_t::prime_sfld_elt(1, m);
  cmd_line_mat_parse<spffl::polynomials::f2n_poly_t>(argc - 2, argv + 2, zero, one);
  return 0;
}
