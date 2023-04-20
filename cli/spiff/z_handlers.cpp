// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <string.h>

#include "z_handlers.h"

#include "cmdlinematops.h"
#include "int_factor.h"
#include "int_gcd.h"
#include "int_totient.h"
#include "isprime.h"
#include "tfacinfo.h"

int zop_main(int argc, char **argv, usage_t *pusage) {
  cmd_line_parse<int>(argc - 1, argv + 1, 0, 1);
  return 0;
}

void zgcd_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-e] {a} {b}\n";
  exit(1);
}

int zgcd_main(int argc, char **argv, usage_t *pusage) {
  if ((argc >= 2) && (strcmp(argv[1], "-e") == 0)) {
    int a, b, g, r, s;
    if (argc != 4)
      pusage(argv[0]);
    if (sscanf(argv[2], "%d", &a) != 1)
      pusage(argv[0]);
    if (sscanf(argv[3], "%d", &b) != 1)
      pusage(argv[0]);

    g = int_ext_gcd(a, b, r, s);
    std::cout << g << " = " << r << " * " << a << " + " << s << " * " << b
              << std::endl;

    int check = a * r + b * s;
    if (g != check) {
      std::cerr << "Coding error in extended GCD.\n";
      exit(1);
    }
  } else {
    int a, g;
    if (argc < 2)
      pusage(argv[0]);
    if (sscanf(argv[1], "%d", &a) != 1)
      pusage(argv[0]);
    g = a;
    for (int argi = 2; argi < argc; argi++) {
      if (sscanf(argv[argi], "%d", &a) != 1)
        pusage(argv[0]);
      g = int_gcd(g, a);
    }
    std::cout << g << std::endl;
  }
  return 0;
}

void zlcm_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {integers ...}\n";
  exit(1);
}

int zlcm_main(int argc, char **argv, usage_t *pusage) {
  int a, l;
  if (argc < 2)
    pusage(argv[0]);
  if (sscanf(argv[1], "%d", &a) != 1)
    pusage(argv[0]);
  l = a;
  for (int argi = 2; argi < argc; argi++) {
    if (sscanf(argv[argi], "%d", &a) != 1)
      pusage(argv[0]);
    l = int_lcm(l, a);
  }
  std::cout << l << std::endl;
  return 0;
}

void ztotient_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {integers ...}\n";
  exit(1);
}

int ztotient_main(int argc, char **argv, usage_t *pusage) {
  int a, phi;
  if (argc < 2)
    pusage(argv[0]);
  for (int argi = 1; argi < argc; argi++) {
    if (sscanf(argv[argi], "%d", &a) != 1)
      pusage(argv[0]);
    phi = int_totient(a);
    if (argc > 2)
      std::cout << a << ": ";
    std::cout << phi << std::endl;
  }
  return 0;
}

void ztestprime_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {integers ...}\n";
  exit(1);
}

int ztestprime_main(int argc, char **argv, usage_t *pusage) {
  int a;
  for (int argi = 1; argi < argc; argi++) {
    if (sscanf(argv[argi], "%d", &a) != 1)
      pusage(argv[0]);
    if (argc > 2)
      std::cout << a << ": ";
    if (isprime(a))
      std::cout << "PRIME\n";
    else
      std::cout << "not prime\n";
  }
  return 0;
}

void nthprime_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {n[-m]}\n";
  exit(1);
}

int nthprime_main(int argc, char **argv, usage_t *pusage) {
  if (argc < 2)
    pusage(argv[0]);
  for (int argi = 1; argi < argc; argi++) {
    int lo, hi;
    if (sscanf(argv[argi], "%d-%d", &lo, &hi) == 2)
      ;
    else if (sscanf(argv[argi], "%d", &lo) == 1)
      hi = lo;
    else
      pusage(argv[0]);
    for (int n = lo; n <= hi; n++) {
      std::cout << nthprime(n) << std::endl;
    }
  }
  return 0;
}

void zlist_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {start [reps [stride]]}\n";
  exit(1);
}

int zlist_main(int argc, char **argv, usage_t *pusage) {
  int walker = 1;
  int reps = 1;
  int stride = 1;

  if (argc < 2 || argc > 4)
    pusage(argv[0]);
  if (argc >= 2) {
    if (sscanf(argv[1], "%d", &walker) != 1)
      pusage(argv[0]);
  }
  if (argc >= 3) {
    if (sscanf(argv[2], "%d", &reps) != 1)
      pusage(argv[0]);
  }
  if (argc >= 4) {
    if (sscanf(argv[3], "%d", &stride) != 1)
      pusage(argv[0]);
  }

  while (reps > 0) {
    printf("%d\n", walker);
    walker += stride;
    reps--;
  }

  return 0;
}

void zfactor_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " {integers ...}\n";
  exit(1);
}

int zfactor_main(int argc, char **argv, usage_t *pusage) {
  int a;
  for (int argi = 1; argi < argc; argi++) {
    if (sscanf(argv[argi], "%d", &a) != 1)
      pusage(argv[0]);
    if (argc > 2)
      std::cout << a << " = ";
    tfacinfo<int> finfo = int_factor(a);
    std::cout << finfo << std::endl;

    int check = finfo.unfactor(1);
    if (check != a) {
      std::cerr << "Coding error in zfactor.\n";
      std::cerr << "  Input: " << a << std::endl;
      std::cerr << "  Check: " << check << std::endl;
      std::cerr << "  Factors: " << finfo << std::endl;
      exit(1);
    }
  }
  return 0;
}

void zdivisors_usage(char *argv0) {
  std::cerr << "Usage: " << argv0 << " [-mp] {integers ...}\n";
  exit(1);
}

int zdivisors_main(int argc, char **argv, usage_t *pusage) {
  int a;
  int argb = 1;
  int maximal_proper_only = 0;
  if ((argc >= 2) && (strcmp(argv[1], "-mp") == 0)) {
    argb++;
    maximal_proper_only = 1;
  }
  if ((argc - argb) < 1)
    pusage(argv[0]);
  for (int argi = argb; argi < argc; argi++) {
    if (sscanf(argv[argi], "%d", &a) != 1)
      pusage(argv[0]);
    if ((argc - argb) > 1)
      std::cout << a << ": ";
    tfacinfo<int> finfo = int_factor(a);
    tvector<int> divisors;
    if (maximal_proper_only) {
      if (!finfo.get_maximal_proper_divisors(divisors, 1)) {
        std::cout << "(none)\n";
        continue;
      }
    } else {
      divisors = finfo.get_all_divisors(1);
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

int zmatop_main(int argc, char **argv, usage_t *pusage) {
  cmd_line_mat_parse<int>(argc - 1, argv + 1, 0, 1);
  return 0;
}
