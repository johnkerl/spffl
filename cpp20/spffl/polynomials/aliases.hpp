// ================================================================
// Type aliases: polynomial_of<Coeff> for concrete coefficient types.
// Include this when you need fp_poly_t, etc., in the cpp20 port.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_ALIASES_HPP
#define SPFFL_POLYNOMIALS_ALIASES_HPP

#include "spffl/polynomials/polynomial_of.hpp"
#include "spffl/intmath/intmod_t.hpp"

namespace spffl::polynomials {

/// Polynomials over Z/pZ (Fp[x]). Coefficient type: intmod_t.
using fp_poly_t = polynomial_of<spffl::intmath::intmod_t>;

}  // namespace spffl::polynomials

#endif  // SPFFL_POLYNOMIALS_ALIASES_HPP
