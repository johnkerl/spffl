// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef INT_GCD_H
#define INT_GCD_H
namespace spffl::intmath {

// Same as int_gcd, but overloaded.  This is important for template use.
int gcd(const int a, const int b);

int int_gcd(int a, int b);

// a * m + b * n = gcd(a, b)
int int_ext_gcd(int a, int b, int &m, int &n);

int int_lcm(int a, int b);

} // namespace spffl::intmath
#endif // INT_GCD_H
