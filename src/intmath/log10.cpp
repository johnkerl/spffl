#include "log10.h"

namespace spffl::intmath {

unsigned calc_log10_unsigned_floor(unsigned n) {
  unsigned rv = 0;

  n /= 10;
  while (n > 0) {
    n /= 10;
    rv++;
  }
  return rv;
}

} // namespace spffl::intmath
