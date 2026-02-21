// ================================================================
// Generic residue-ring algorithms using concepts.
// Example: optional inverse and solve a*x = b over any Residue_ring_with_recip.
// ================================================================

#ifndef SPFFL_ALGORITHMS_OPTIONAL_INVERSE_H
#define SPFFL_ALGORITHMS_OPTIONAL_INVERSE_H

#include "spffl/concepts.h"
#include <optional>

namespace spffl::algorithms {

/// Returns a^{-1} if a is a unit, otherwise nullopt.
template <typename R>
  requires spffl::concepts::Residue_ring_with_recip<R>
std::optional<R> optional_inverse(R const& a) {
  R inv;
  if (!a.recip(inv)) return std::nullopt;
  return inv;
}

/// Returns x such that a*x == b if a is a unit, otherwise nullopt.
template <typename R>
  requires spffl::concepts::Residue_ring_with_recip<R>
std::optional<R> optional_solve_ax_eq_b(R const& a, R const& b) {
  auto inv = optional_inverse(a);
  if (!inv) return std::nullopt;
  return b * *inv;
}

}  // namespace spffl::algorithms

#endif  // SPFFL_ALGORITHMS_OPTIONAL_INVERSE_H
