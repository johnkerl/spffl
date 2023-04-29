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

    v.set(43, 1);
    v.set(44, 0);
    v.set(97, 1);
    v.toggle_element(55);

    printf("%016llx %016llx\n", (unsigned long long)v.expose()[0], (unsigned long long)v.expose()[1]);
    for (int i = 0; i < 100; i++) {
        printf("%d %d\n", i, v.get_int(i));
    }
    return 0;
}
