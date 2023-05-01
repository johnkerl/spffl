// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef INT_RANDOM_H
#define INT_RANDOM_H

#include <cstdint>

namespace spffl::random {

unsigned get_random_uint32(void);
uint64_t get_random_uint64(void);
int get_random_int(void);

} // namespace spffl::random

#endif // INT_RANDOM_H
