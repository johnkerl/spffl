#include <stdio.h>
#include <stdlib.h>

#include "spffl/intmath/int_gcd.h"

static void usage(char *argv0) {
  fprintf(
      stderr, "Usage: %s {a} {b} where a and b are decimal integers.\n", argv0);
  exit(1);
}

int main(int argc, char **argv) {
  int a, b, g;

  if (argc != 3) {
    usage(argv[0]);
  }
  if (sscanf(argv[1], "%d", &a) != 1) {
    usage(argv[0]);
  }
  if (sscanf(argv[2], "%d", &b) != 1) {
    usage(argv[0]);
  }

  g = spffl::intmath::int_gcd(a, b);

  printf("%d\n", g);

  return 0;
}
