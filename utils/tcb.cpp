#include <stdio.h>
#include "count_bits.h"

#define BITCOUNT(x) (((BCAUX(x)+(BCAUX(x)>>4)) & 0x0f0f0f0f)%255)
#define BCAUX(x) ((x) \
  - (((x)>>1) & 0x77777777) \
  - (((x)>>2) & 0x33333333) \
  - (((x)>>3) & 0x11111111))

// ----------------------------------------------------------------
int main(int argc, char ** argv)
{
	unsigned max = 65536;
	unsigned i;
	unsigned mxor = 0;

	if (argc > 1)
		(void)sscanf(argv[1], "%u", &max);

	//unsigned fbc;
	//unsigned sbc;
	//unsigned diff;
	//for (i = 0; i < max; i++) {
	//	fbc = BITCOUNT(i);
	//	sbc = count_one_bits((unsigned char *)&i, sizeof(i));
	//	diff = fbc - sbc;
	//	printf("%08x %9u  %3u %3d   %3u\n", i, i, fbc, sbc, diff);
	//}

	if (argc == 2) {
		for (i = 0; i < max; i++) {
			mxor ^= BITCOUNT(i);
		}
		printf("s %08x\n", mxor);
	}
	else {
		for (i = 0; i < max; i++) {
			mxor ^= count_one_bits((unsigned char *)&i, sizeof(i));
		}
		printf("f %08x\n", mxor);
	}

	return 0;
}
