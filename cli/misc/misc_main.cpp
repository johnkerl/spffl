// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include <stdio.h>

#include "bit_vector_t.h"

using namespace spffl::bits;

int main() {
    bit_vector_t v(100);
    v.set(0, bit_t(1));
    printf("%016llx %016llx\n", (unsigned long long)v.expose()[0], (unsigned long long)v.expose()[1]);
    return 0;
}
