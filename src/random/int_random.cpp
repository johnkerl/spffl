// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <fcntl.h>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "int_random.h"
#include "psdes.h"

#ifdef USE_DEV_URANDOM // Linux only
#define BUFSZ 10000
#endif

namespace spffl::random {

// ----------------------------------------------------------------
uint32_t get_random_unsigned(void) { return (uint32_t)get_random_int(); }

// ----------------------------------------------------------------
uint64_t get_random_ull(void) {
  uint32_t lo = get_random_unsigned();
  uint32_t hi = get_random_unsigned();
  return ((uint64_t)hi << 32) | (uint64_t)lo;
}

// ----------------------------------------------------------------
#ifdef USE_DEV_URANDOM // Linux only
int get_random_int(void) {
  static int fd = -1;
  static int buf[BUFSZ];
  static int bufpos = 0;
  int rv;
  if (fd == -1) {
    fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
      std::cerr << "Couldn't open /dev/urandom.\n";
      perror("Reason");
      exit(1);
    }
  }

  if (bufpos == 0) {
    if (read(fd, buf, BUFSZ * sizeof(int)) < 0) {
      std::cerr << "Couldn't read /dev/urandom.\n";
      perror("Reason");
      exit(1);
    }
  }
  rv = buf[bufpos];
  bufpos++;
  if (bufpos >= BUFSZ)
    bufpos = 0;
  return rv;
}
#else
int get_random_int(void) { return spffl::bitrand::iran32(); }
#endif // USE_DEV_URANDOM

} // namespace spffl::random
