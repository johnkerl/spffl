// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2polymod_random.h"
#include "f2poly_random.h"
#include "int_random.h"

// ----------------------------------------------------------------
f2polymod_t f2polymod_random(f2poly_t m) {
  int deg = m.find_degree();
  if (deg < 1) {
    std::cerr << "f2polymod_random:  degree (" << deg << ") of " << m
              << " should be >= 1.\n";
    exit(1);
  }

  return f2polymod_t(f2poly_random(deg), m);
}
