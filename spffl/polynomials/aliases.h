// ================================================================
// Type aliases: polynomial_of<Coeff> for concrete coefficient types.
// Include this when you need fp_poly_t, etc.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_ALIASES_H
#define SPFFL_POLYNOMIALS_ALIASES_H

#include "spffl/polynomials/polynomial_of.h"
#include "spffl/intmath/intmod_t.h"

namespace spffl::polynomials {

/// Polynomials over Z/pZ (Fp[x]). Coefficient type: intmod_t.
using fp_poly_t = polynomial_of<spffl::intmath::intmod_t>;

}  // namespace spffl::polynomials

#endif  // SPFFL_POLYNOMIALS_ALIASES_H
