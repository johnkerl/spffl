// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef INT_GCD_H
#define INT_GCD_H

// Same as int_gcd, but overloaded.  This is important for template use.
int gcd(int a, int b);

int int_gcd(int a, int b);

// a * m + b * n = gcd(a, b)
// TODO: switch from pointer to reference
int int_ext_gcd(int a, int b, int *pm, int *pn);

int int_lcm(int a, int b);

#endif // INT_GCD_H
