// ================================================================
// Phase 1.4: fpn and f2n as polynomial_of<...> and residue_of<...>.
// Include after aliases.hpp and fp_polymod_t.hpp. Do not include from aliases.hpp.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_FPN_F2N_ALIASES_HPP
#define SPFFL_POLYNOMIALS_FPN_F2N_ALIASES_HPP

#include "spffl/polynomials/aliases.hpp"
#include "spffl/polynomials/fp_polymod_t.hpp"
#include "spffl/residue_of.hpp"
#include "spffl/polynomials/f2_polymod_t.h"
#include "spffl/euclidean.hpp"
#include "spffl/intmath/intmod_t.h"
#include <vector>

namespace spffl::polynomials {

/// Polynomials over Fp^n = Fp[x]/(m). Coefficient type: fp_polymod_t.
using fpn_poly_t = polynomial_of<fp_polymod_t>;

/// Residue ring Fpn[x]/(modulus). Element of Fpn[x]/(m).
using fpn_polymod_t = spffl::residue_of<fpn_poly_t>;

/// Polynomials over F2^n = F2[x]/(m). Coefficient type: f2_polymod_t (legacy).
using f2n_poly_t = polynomial_of<f2_polymod_t>;

/// Residue ring F2n[x]/(modulus). Element of F2n[x]/(m).
using f2n_polymod_t = spffl::residue_of<f2n_poly_t>;

/// Free-function gcd for template/ADL use (same as the gcd method).
inline fpn_poly_t gcd(const fpn_poly_t& a, const fpn_poly_t& b) {
  return spffl::euclidean::gcd(a, b);
}

inline f2n_poly_t gcd(const f2n_poly_t& a, const f2n_poly_t& b) {
  return spffl::euclidean::gcd(a, b);
}

// ---------------------------------------------------------------------------
// Prime subfield elements (explicit modulus; no static method on type alias).
// ---------------------------------------------------------------------------

inline f2n_poly_t prime_subfield_element(int v, const f2_poly_t& m) {
  return f2n_poly_t(f2_polymod_t::prime_subfield_element(v, m));
}

inline fpn_poly_t prime_subfield_element(int v, const fp_poly_t& m) {
  int p = m.get_coeff(0).get_modulus();
  return fpn_poly_t(fp_polymod_t(fp_poly_t(spffl::intmath::intmod_t(v, p)), m));
}

// ---------------------------------------------------------------------------
// F2^n polynomial square root (char 2: sqrt exists iff odd-degree coeffs are 0).
// ---------------------------------------------------------------------------
inline bool square_root(const f2n_poly_t& f, f2n_poly_t& rroot) {
  int d = f.find_degree();
  if (d < 0) {
    rroot = f;
    return true;
  }
  f2_poly_t m = f.get_coeff(0).get_modulus();
  f2_polymod_t zero(0, m);
  int n = m.find_degree();
  int pow = 1 << (n - 1);
  std::vector<f2_polymod_t> out(static_cast<std::size_t>(d) + 1, zero);
  for (int si = 0, di = 0; si <= d; si += 2, ++di) {
    out[static_cast<std::size_t>(di)] = f.get_coeff(si).exp(pow);
    if (si + 1 <= d && f.get_coeff(si + 1) != zero) {
      return false;
    }
  }
  rroot = f2n_poly_t(std::move(out));
  return true;
}

}  // namespace spffl::polynomials

#endif  // SPFFL_POLYNOMIALS_FPN_F2N_ALIASES_HPP
