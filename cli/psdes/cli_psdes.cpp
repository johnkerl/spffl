#include <stdio.h>
#include <stdlib.h>

#include "bitrand/psdes.h"

int main(int argc, char **argv) {

  // Non-reentrant version with default seeds:
  printf("iran32: 0x%08x\n", spffl::bitrand::iran32());
  printf("iran32: 0x%08x\n", spffl::bitrand::iran32());
  printf("iran32: 0x%08x\n", spffl::bitrand::iran32());

  // Non-reentrant version with default seeds:
  printf("\n");
  printf("fran32: %.8f\n", spffl::bitrand::fran32());
  printf("fran32: %.8f\n", spffl::bitrand::fran32());
  printf("fran32: %.8f\n", spffl::bitrand::fran32());

  // Non-reentrant version with specified seeds:
  printf("\n");
  printf("sran32(1)\n");
  spffl::bitrand::sran32(1);
  printf("iran32: 0x%08x\n", spffl::bitrand::iran32());
  printf("iran32: 0x%08x\n", spffl::bitrand::iran32());
  printf("iran32: 0x%08x\n", spffl::bitrand::iran32());

  printf("\n");
  printf("fran32: %.8f\n", spffl::bitrand::fran32());
  printf("fran32: %.8f\n", spffl::bitrand::fran32());
  printf("fran32: %.8f\n", spffl::bitrand::fran32());

  return 0;
}
