// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fppolymod_random.h"
#include "fppoly_random.h"

// ----------------------------------------------------------------
fppolymod_t fppolymod_random(fppoly_t m) {
  int deg = m.find_degree();
  if (deg < 1) {
    std::cerr << "fppolymod_random:  degree (" << deg << ") of " << m
              << " should be >= 1.\n";
    exit(1);
  }
  int p = m.get_char();
  return fppolymod_t(fppoly_random(p, deg), m);
}
