// ================================================================
// fp_poly_t: Fp[x] as polynomial_of<intmod_t> (Phase 1.3 migration).
// Include this for fp_poly_t and legacy I/O helpers.
// ================================================================
// Note: gcd(fp_poly_t, fp_poly_t) is provided by polynomial_of<> friend in
// polynomial_of.hpp. Do not add a separate overload here or GCC will see
// ambiguity with that friend when resolving gcd in vector_over::vgcd().

#ifndef FPPOLY_T_H
#define FPPOLY_T_H

#include "spffl/polynomials/aliases.hpp"
#include "spffl/polynomials/fp_poly_io.hpp"

#endif  // FPPOLY_T_H
