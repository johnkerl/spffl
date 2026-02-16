// ================================================================
// Generic 2x2 linear solve A*x = b over a ring with reciprocal.
// Uses Matrix_over and Vector_over; demonstrates generic linear algebra.
// ================================================================

#ifndef SPFFL_ALGORITHMS_OPTIONAL_SOLVE_2X2_HPP
#define SPFFL_ALGORITHMS_OPTIONAL_SOLVE_2X2_HPP

#include "spffl/concepts.hpp"
#include "spffl/containers/matrix_over.hpp"
#include "spffl/containers/vector_over.hpp"
#include <optional>

namespace spffl::algorithms {

/// Solves A*x = b for 2x2 A and length-2 b when det(A) is a unit.
/// Returns nullopt if A is not 2x2, b is not length 2, or det(A) is not invertible.
template <typename R>
  requires spffl::concepts::Residue_ring_with_recip<R>
std::optional<spffl::containers::vector_over<R>> optional_solve_2x2(
    spffl::containers::matrix_over<R> const& A,
    spffl::containers::vector_over<R> const& b) {
  if (A.get_num_rows() != 2 || A.get_num_cols() != 2 || b.get_num_elements() != 2) {
    return std::nullopt;
  }
  R const& a = A[0][0];
  R const& b00 = A[0][1];
  R const& c = A[1][0];
  R const& d = A[1][1];
  R det = a * d - b00 * c;
  R det_inv;
  if (!det.recip(det_inv)) return std::nullopt;
  R x0 = (d * b[0] - b00 * b[1]) * det_inv;
  R x1 = (-c * b[0] + a * b[1]) * det_inv;
  spffl::containers::vector_over<R> x(2);
  x[0] = x0;
  x[1] = x1;
  return x;
}

}  // namespace spffl::algorithms

#endif  // SPFFL_ALGORITHMS_OPTIONAL_SOLVE_2X2_HPP
