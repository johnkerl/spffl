// Tests for spffl::containers::vector_over<T>.

#include <catch2/catch_test_macros.hpp>

#include "spffl/concepts.hpp"
#include "spffl/containers/vector_over.hpp"
#include "spffl/intmath/intmod_t.hpp"

using spffl::containers::vector_over;
using spffl::intmath::intmod_t;

TEST_CASE("vector_over<int> satisfies Vector_over and basic arithmetic") {
  static_assert(spffl::concepts::Vector_over<vector_over<int>, int>);
  static_assert(spffl::concepts::Vector_with_dot<vector_over<int>, int>);

  vector_over<int> u(3);
  u[0] = 1;
  u[1] = 2;
  u[2] = 3;

  vector_over<int> v(3);
  v[0] = 4;
  v[1] = 5;
  v[2] = 6;

  vector_over<int> sum = u + v;
  CHECK(sum[0] == 5);
  CHECK(sum[1] == 7);
  CHECK(sum[2] == 9);

  int d = u.dot(v);
  CHECK(d == 1*4 + 2*5 + 3*6);  // 32
}

TEST_CASE("vector_over<intmod_t>: ring ops and dot") {
  using V = vector_over<intmod_t>;
  static_assert(spffl::concepts::Vector_over<V, intmod_t>);
  static_assert(spffl::concepts::Vector_with_dot<V, intmod_t>);

  const int p = 7;
  V a(2);
  a[0] = intmod_t(3, p);
  a[1] = intmod_t(5, p);

  V b(2);
  b[0] = intmod_t(1, p);
  b[1] = intmod_t(2, p);

  V sum = a + b;
  CHECK(sum[0].get_residue() == 4);
  CHECK(sum[1].get_residue() == 0);  // 7 mod 7

  intmod_t dot_ab = a.dot(b);
  CHECK(dot_ab.get_residue() == (3*1 + 5*2) % p);  // 13 ≡ 6 mod 7
}
