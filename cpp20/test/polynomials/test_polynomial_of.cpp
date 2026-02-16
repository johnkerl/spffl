// Basic sanity tests for spffl::polynomials::polynomial_of<Coeff>.

#include <catch2/catch_test_macros.hpp>

#include "spffl/polynomials/polynomial_of.hpp"

using spffl::polynomials::polynomial_of;

TEST_CASE("polynomial_of<int>: basic arithmetic") {
  polynomial_of<int> p1(1, 2);     // 2x + 1
  polynomial_of<int> p2(3, -1);    // -1 + 3x

  auto sum = p1 + p2;              // (2x+1)+(-1+3x) = 5x
  CHECK(sum.find_degree() == 1);
  CHECK(sum.eval(1) == 5);

  auto prod = p1 * p2;             // (2x+1)*(-1+3x) = -1 + x + 6x^2
  CHECK(prod.find_degree() == 2);
  CHECK(prod.eval(1) == (-1 + 1 + 6)); // = 6
}

