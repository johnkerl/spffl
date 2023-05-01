// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2_poly_handlers.h"

#include "cli_parser/cmd_line_matrix_ops.h"
#include "factorization/f2_poly_factor.h"
#include "factorization/f2_poly_totient.h"
#include "linalg/f2_linear_algebra.h"
#include "list/list_elements.h"
#include "polynomials/f2_poly_t.h"
#include "q_cyclotomic/qff.h"
#include "random/f2_poly_random.h"
#include "units/f2_polymod_units.h"
#include <string.h>

void f2_p_list_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {deglo[-deghi]}\n";
  exit(1);
}

int f2_p_list_main(int argc, char **argv, usage_t *pusage) {
  int deglo, deghi;
  if (argc != 2) {
    pusage(argv[0]);
  }

  if (sscanf(argv[1], "%d-%d", &deglo, &deghi) == 2)
    ;
  else if (sscanf(argv[1], "%d", &deglo) == 1) {
    deghi = deglo;
  } else {
    pusage(argv[0]);
  }

  for (int deg = deglo; deg <= deghi; deg++) {
    tvector<spffl::polynomials::f2_poly_t> elts =
        spffl::list::f2_poly_list(deg);
    elts.crout(std::cout);
  }
  return 0;
}

int f2_p_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cli_parser::cmd_line_parse<spffl::polynomials::f2_poly_t>(argc - 1,
      argv + 1, spffl::polynomials::f2_poly_t(0),
      spffl::polynomials::f2_poly_t(1));
  return 0;
}

void f2_p_deg_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {polys ...}\n";
  exit(1);
}

int f2_p_deg_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t a;
  for (int argi = 1; argi < argc; argi++) {
    if (!a.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    if (argc > 2) {
      std::cout << a << ": ";
    }
    std::cout << a.find_degree() << std::endl;
  }
  return 0;
}

void f2_p_gcd_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-e] {poly1} {poly2}\n";
  exit(1);
}

int f2_p_gcd_main(int argc, char **argv, usage_t *pusage) {
  if ((argc >= 2) && (strcmp(argv[1], "-e") == 0)) {
    spffl::polynomials::f2_poly_t a, b, g, r, s;
    if (argc != 4) {
      pusage(argv[0]);
    }
    if (!a.from_string(argv[2])) {
      pusage(argv[0]);
    }
    if (!b.from_string(argv[3])) {
      pusage(argv[0]);
    }

    g = a.ext_gcd(b, r, s);
    std::cout << g << " = " << r << " * " << a << " + " << s << " * " << b
              << std::endl;

    spffl::polynomials::f2_poly_t check = a * r + b * s;
    if (g != check) {
      std::cerr << "Coding error in extended GCD.\n";
      exit(1);
    }
  } else {
    spffl::polynomials::f2_poly_t a, g;
    if (argc < 2) {
      pusage(argv[0]);
    }
    if (!a.from_string(argv[1])) {
      pusage(argv[0]);
    }
    g = a;
    for (int argi = 2; argi < argc; argi++) {
      if (!a.from_string(argv[argi])) {
        pusage(argv[0]);
      }
      g = g.gcd(a);
    }
    std::cout << g << std::endl;
  }
  return 0;
}

void f2_p_lcm_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {polys ...}\n";
  exit(1);
}

int f2_p_lcm_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t a, l;

  if (argc < 2) {
    pusage(argv[0]);
  }
  if (!a.from_string(argv[1])) {
    pusage(argv[0]);
  }
  l = a;
  for (int argi = 2; argi < argc; argi++) {
    if (!a.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    l = (l * a) / l.gcd(a);
  }
  std::cout << l << std::endl;
  return 0;
}

void f2_p_totient_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {polys ...}\n";
  exit(1);
}

int f2_p_totient_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t a;
  int phi;
  if (argc < 2) {
    pusage(argv[0]);
  }
  for (int argi = 1; argi < argc; argi++) {
    if (!a.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    phi = spffl::factorization::f2_poly_totient(a);
    if (argc > 2) {
      std::cout << a << ": ";
    }
    std::cout << phi << std::endl;
  }
  return 0;
}

void f2_p_test_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {-i|-p|-ip} {polys ...}\n";
  std::cerr << "-i: irreducible; -p: primitive.\n";
  exit(1);
}

int f2_p_test_main(int argc, char **argv, usage_t *pusage) {
  bool do_irr = false, do_prim = false;
  if (argc < 3) {
    pusage(argv[0]);
  }

  if (strcmp(argv[1], "-i") == 0) {
    do_irr  = true;
    do_prim = false;
  } else if (strcmp(argv[1], "-p") == 0) {
    do_irr  = false;
    do_prim = true;
  } else if (strcmp(argv[1], "-ip") == 0) {
    do_irr  = true;
    do_prim = true;
  } else {
    pusage(argv[0]);
  }

  for (int argi = 2; argi < argc; argi++) {
    spffl::polynomials::f2_poly_t a;
    if (!a.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    if (argc > 2) {
      std::cout << a << ": ";
    }
    if (do_irr) {
      if (spffl::factorization::f2_poly_is_irreducible(a)) {
        std::cout << "IRREDUCIBLE";
      } else {
        std::cout << "reducible";
      }
    }
    if (do_irr && do_prim) {
      std::cout << " ";
    }
    if (do_prim) {
      if (spffl::units::f2_poly_is_primitive(a)) {
        std::cout << "PRIMITIVE";
      } else {
        std::cout << "imprimitive";
      }
    }
    std::cout << std::endl;
  }
  return 0;
}

void f2_p_find_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {-1|-r} {-i|-p|-ip} {deglo[-deghi]}\n";
  std::cerr << "-1: lowest degree; -r: random\n";
  std::cerr << "-i: irreducible; -p: primitive\n";
  exit(1);
}

int f2_p_find_main(int argc, char **argv, usage_t *pusage) {
  bool do_random = false;
  int deglo, deghi;
  bool do_irr = false, do_prim = false;

  if (argc != 4) {
    pusage(argv[0]);
  }
  if (strcmp(argv[1], "-1") == 0) {
    do_random = false;
  } else if (strcmp(argv[1], "-r") == 0) {
    do_random = true;
  } else {
    pusage(argv[0]);
  }

  if (strcmp(argv[2], "-i") == 0) {
    do_irr  = true;
    do_prim = false;
  } else if (strcmp(argv[2], "-p") == 0) {
    do_irr  = false;
    do_prim = true;
  } else if (strcmp(argv[2], "-ip") == 0) {
    do_irr  = true;
    do_prim = true;
  } else {
    pusage(argv[0]);
  }

  if (sscanf(argv[3], "%d-%d", &deglo, &deghi) == 2)
    ;
  else if (sscanf(argv[3], "%d", &deglo) == 1) {
    deghi = deglo;
  } else {
    pusage(argv[0]);
  }

  for (int deg = deglo; deg <= deghi; deg++) {
    spffl::polynomials::f2_poly_t a;
    if (do_prim) {
      a = do_random ? spffl::units::f2_poly_random_prim(deg, do_irr)
                    : spffl::units::f2_poly_find_prim(deg, do_irr);
    } else {
      a = do_random ? spffl::factorization::f2_poly_random_irreducible(deg)
                    : spffl::factorization::f2_poly_find_irreducible(deg);
    }
    std::cout << a << std::endl;
  }
  return 0;
}

void f2_p_period_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {polys ...}\n";
  exit(1);
}

int f2_p_period_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t a;
  for (int argi = 1; argi < argc; argi++) {
    if (!a.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    if (argc > 2) {
      std::cout << a << ": ";
    }
    std::cout << spffl::units::f2_poly_period(a) << std::endl;
  }
  return 0;
}

void f2_p_factor_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {polys ...}\n";
  exit(1);
}

int f2_p_factor_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t a;
  for (int argi = 1; argi < argc; argi++) {
    if (!a.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    if (argc > 2) {
      std::cout << a << " = ";
    }
    tfacinfo<spffl::polynomials::f2_poly_t> finfo =
        spffl::factorization::f2_poly_factor(a);
    std::cout << finfo << std::endl;

    spffl::polynomials::f2_poly_t check =
        finfo.unfactor(spffl::polynomials::f2_poly_t(1));
    if (check != a) {
      std::cerr << "Coding error in spffl::factorization::f2_poly_factor.\n";
      std::cerr << "  Input: " << a << std::endl;
      std::cerr << "  Check: " << check << std::endl;
      std::cerr << "  Factors: " << finfo << std::endl;
      exit(1);
    }
  }
  return 0;
}

void f2_p_divisors_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-mp] {polys ...}\n";
  exit(1);
}

int f2_p_divisors_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t a;
  int argb                = 1;
  int maximal_proper_only = 0;
  if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
    maximal_proper_only = 1;
    argb++;
  }
  for (int argi = argb; argi < argc; argi++) {
    if (!a.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    if ((argc - argb) > 1) {
      std::cout << a << ": ";
    }
    tfacinfo<spffl::polynomials::f2_poly_t> finfo =
        spffl::factorization::f2_poly_factor(a);
    tvector<spffl::polynomials::f2_poly_t> divisors;
    if (maximal_proper_only) {
      if (!finfo.get_maximal_proper_divisors(
              divisors, spffl::polynomials::f2_poly_t(1))) {
        std::cout << "(none)\n";
        continue;
      }
    } else {
      divisors = finfo.get_all_divisors(spffl::polynomials::f2_poly_t(1));
    }
    int nd = divisors.get_num_elements();
    for (int k = 0; k < nd; k++) {
      if (k > 0) {
        std::cout << " ";
      }
      std::cout << divisors[k];
    }
    std::cout << std::endl;
  }
  return 0;
}

void f2_p_eval_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {f} {elements of F2 ...}\n";
  exit(1);
}

int f2_p_eval_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t f;
  spffl::bits::bit_t a, b;

  if (argc < 3) {
    pusage(argv[0]);
  }
  if (!f.from_string(argv[1])) {
    pusage(argv[0]);
  }
  for (int argi = 2; argi < argc; argi++) {
    if (!a.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    b = f.eval(a);
    std::cout << b << std::endl;
  }

  return 0;
}

void f2_p_random_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {deg} [count]\n";
  exit(1);
}

int f2_p_random_main(int argc, char **argv, usage_t *pusage) {
  int deg, count = 1;

  if ((argc != 2) && (argc != 3)) {
    pusage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &deg) != 1) {
    pusage(argv[0]);
  }
  if (argc == 3) {
    if (sscanf(argv[2], "%d", &count) != 1) {
      pusage(argv[0]);
    }
  }

  for (int i = 0; i < count; i++) {
    std::cout << spffl::random::f2_poly_random(deg) << std::endl;
  }

  return 0;
}

void f2_p_comp_mx_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {f2 chpoly}\n";
  exit(1);
}

int f2_p_comp_mx_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::f2_poly_t chpol;

  if (argc != 2) {
    pusage(argv[0]);
  }
  if (!chpol.from_string(argv[1])) {
    pusage(argv[0]);
  }

  tmatrix<spffl::bits::bit_t> A = spffl::linalg::f2_companion_matrix(chpol);
  std::cout << A << std::endl;

  return 0;
}

int f2_p_mat_op_main(int argc, char **argv, usage_t *pusage) {
  spffl::cli_parser::cmd_line_mat_parse<spffl::polynomials::f2_poly_t>(argc - 1,
      argv + 1, spffl::polynomials::f2_poly_t(0),
      spffl::polynomials::f2_poly_t(1));
  return 0;
}

void f2_p_qp_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {qpolys ...}\n";
  exit(1);
}

int f2_p_qp_main(int argc, char **argv, usage_t *pusage) {
  spffl::polynomials::q_poly_t qp;
  spffl::polynomials::f2_poly_t f2p;
  if (argc < 2) {
    pusage(argv[0]);
  }
  for (int argi = 1; argi < argc; argi++) {
    if (!qp.from_string(argv[argi])) {
      pusage(argv[0]);
    }
    f2p = spffl::q_cyclotomic::f2_poly_from_q_poly(qp);
    std::cout << f2p << std::endl;
  }
  return 0;
}
