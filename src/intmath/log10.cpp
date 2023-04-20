#include "log10.h"

// ----------------------------------------------------------------
unsigned calc_log10_unsigned(unsigned n, int want_ceil) {
  unsigned rv = 0;

  n /= 10;
  while (n > 0) {
    n /= 10;
    rv++;
  }

  // xxx always returns floor.  fix me.
  return rv;
}
