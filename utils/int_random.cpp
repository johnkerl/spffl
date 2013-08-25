// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <iostream>

#include "int_random.h"
#include "psdes.h"

#ifdef USE_DEV_URANDOM // Linux only
#define BUFSZ 10000
#endif

// ----------------------------------------------------------------
unsigned get_random_unsigned(void)
{
	return (unsigned)get_random_int();
}

// ----------------------------------------------------------------
unsigned long long get_random_ull(void)
{
	unsigned lo = get_random_unsigned();
	unsigned hi = get_random_unsigned();
	return ((unsigned long long)hi << 32) | (unsigned long long)lo;
}

// ----------------------------------------------------------------
#ifdef USE_DEV_URANDOM // Linux only
int get_random_int(void)
{
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
int get_random_int(void)
{
	return iran32();
}
#endif // USE_DEV_URANDOM
