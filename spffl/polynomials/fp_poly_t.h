// ================================================================
// fp_poly_t: Fp[x] as polynomial_of<intmod_t> (Phase 1.3 migration).
// Include this for fp_poly_t and legacy I/O helpers.
// ================================================================

#ifndef FPPOLY_T_H
#define FPPOLY_T_H

#include "spffl/polynomials/aliases.hpp"
#include "spffl/polynomials/fp_poly_io.hpp"

// Legacy: free function gcd (also available as member and friend in polynomial_of).
namespace spffl::polynomials {
inline fp_poly_t gcd(const fp_poly_t& a, const fp_poly_t& b) { return a.gcd(b); }
}

#endif  // FPPOLY_T_H
