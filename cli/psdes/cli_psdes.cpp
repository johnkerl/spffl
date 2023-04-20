#include <stdio.h>
#include <stdlib.h>

#include "psdes.h"

int main(int argc, char **argv) {

  // Non-reentrant version with default seeds:
  printf("iran32: 0x%08x\n", iran32());
  printf("iran32: 0x%08x\n", iran32());
  printf("iran32: 0x%08x\n", iran32());

  // Non-reentrant version with default seeds:
  printf("\n");
  printf("fran32: %.8f\n", fran32());
  printf("fran32: %.8f\n", fran32());
  printf("fran32: %.8f\n", fran32());

  // Non-reentrant version with specified seeds:
  printf("\n");
  printf("sran32(1)\n");
  sran32(1);
  printf("iran32: 0x%08x\n", iran32());
  printf("iran32: 0x%08x\n", iran32());
  printf("iran32: 0x%08x\n", iran32());

  printf("\n");
  printf("fran32: %.8f\n", fran32());
  printf("fran32: %.8f\n", fran32());
  printf("fran32: %.8f\n", fran32());

  return 0;
}
