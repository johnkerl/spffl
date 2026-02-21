// Tests for spffl::containers::matrix_over<T>.

#include <catch2/catch_test_macros.hpp>

#include "spffl/concepts.h"
#include "spffl/containers/matrix_over.h"
#include "spffl/containers/vector_over.h"
#include "spffl/intmath/intmod_t.h"

using spffl::containers::matrix_over;
using spffl::containers::vector_over;
using spffl::intmath::intmod_t;

TEST_CASE("matrix_over<int> satisfies Matrix_over and basic arithmetic") {
  static_assert(spffl::concepts::Matrix_over<matrix_over<int>, int>);

  matrix_over<int> A(2, 3);
  A[0][0] = 1; A[0][1] = 2; A[0][2] = 3;
  A[1][0] = 4; A[1][1] = 5; A[1][2] = 6;

  matrix_over<int> B(2, 3);
  B[0][0] = 1; B[0][1] = 0; B[0][2] = 0;
  B[1][0] = 0; B[1][1] = 1; B[1][2] = 0;

  matrix_over<int> S = A + B;
  CHECK(S[0][0] == 2);
  CHECK(S[1][1] == 6);

  matrix_over<int> C(3, 2);
  C[0][0] = 1; C[0][1] = 0;
  C[1][0] = 0; C[1][1] = 1;
  C[2][0] = 0; C[2][1] = 0;

  matrix_over<int> P = A * C;  // 2x3 * 3x2 -> 2x2
  CHECK(P.get_num_rows() == 2);
  CHECK(P.get_num_cols() == 2);
  CHECK(P[0][0] == 1);
  CHECK(P[0][1] == 2);
  CHECK(P[1][0] == 4);
  CHECK(P[1][1] == 5);
}

TEST_CASE("matrix_over * vector_over (Matrix_vector_product)") {
  static_assert(spffl::concepts::Matrix_vector_product<
      matrix_over<int>, vector_over<int>, int>);

  matrix_over<int> A(2, 3);
  A[0][0] = 1; A[0][1] = 0; A[0][2] = 1;
  A[1][0] = 0; A[1][1] = 1; A[1][2] = 1;

  vector_over<int> x(3);
  x[0] = 1; x[1] = 2; x[2] = 3;

  vector_over<int> y = A * x;
  CHECK(y.get_num_elements() == 2);
  CHECK(y[0] == 1*1 + 0*2 + 1*3);  // 4
  CHECK(y[1] == 0*1 + 1*2 + 1*3);  // 5
}

TEST_CASE("matrix_over<intmod_t>: ring ops and multiply") {
  using M = matrix_over<intmod_t>;
  static_assert(spffl::concepts::Matrix_over<M, intmod_t>);

  const int p = 7;
  M A(2, 2);
  A[0][0] = intmod_t(1, p); A[0][1] = intmod_t(2, p);
  A[1][0] = intmod_t(3, p); A[1][1] = intmod_t(4, p);

  M B(2, 2);
  B[0][0] = intmod_t(1, p); B[0][1] = intmod_t(0, p);
  B[1][0] = intmod_t(0, p); B[1][1] = intmod_t(1, p);

  M I = A * B;
  CHECK(I[0][0].get_residue() == 1);
  CHECK(I[0][1].get_residue() == 2);
  CHECK(I[1][0].get_residue() == 3);
  CHECK(I[1][1].get_residue() == 4);
}
