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

// ---------------------------------------------------------------------------
// Simple finite-field-like type modulo 7 to exercise quot_and_rem and gcd.
// ---------------------------------------------------------------------------

struct mod7_t {
  int v{};

  mod7_t() = default;
  explicit mod7_t(int x) { v = norm(x); }

  static int norm(int x) {
    int m = x % 7;
    if (m < 0) {
      m += 7;
    }
    return m;
  }

  mod7_t operator+(mod7_t that) const { return mod7_t(v + that.v); }
  mod7_t operator-(mod7_t that) const { return mod7_t(v - that.v); }
  mod7_t operator-() const { return mod7_t(-v); }
  mod7_t operator*(mod7_t that) const { return mod7_t(v * that.v); }

  mod7_t &operator+=(mod7_t that) { v = norm(v + that.v); return *this; }
  mod7_t &operator-=(mod7_t that) { v = norm(v - that.v); return *this; }
  mod7_t &operator*=(mod7_t that) { v = norm(v * that.v); return *this; }

  bool operator==(mod7_t that) const { return v == that.v; }
  bool operator!=(mod7_t that) const { return v != that.v; }
  bool operator<(mod7_t that) const { return v < that.v; }

  // Multiplicative inverse via brute force (fine for tests).
  bool recip(mod7_t &rinv) const {
    if (v == 0) {
      return false;
    }
    for (int x = 1; x < 7; ++x) {
      if (norm(v * x) == 1) {
        rinv = mod7_t(x);
        return true;
      }
    }
    return false;
  }

  mod7_t operator/(mod7_t that) const {
    mod7_t inv;
    if (!that.recip(inv)) {
      throw std::runtime_error("mod7_t: division by non-invertible element");
    }
    return (*this) * inv;
  }
};

TEST_CASE("polynomial_of<mod7_t>: quot_and_rem and gcd") {
  using P = polynomial_of<mod7_t>;

  mod7_t z(0), o(1), two(2);

  // p(x) = x^2 + 1 over F_7
  P p(o, z, o);       // coeffs: 1 (x^0), 0 (x^1), 1 (x^2)
  // q(x) = x + 1
  P q(o, o);          // coeffs: 1 (x^0), 1 (x^1)

  // Expect p = (x - 1)*q + 2 over F_7.
  P quot, rem;
  p.quot_and_rem(q, quot, rem);

  CHECK(quot.find_degree() == 1);
  // Check by recomposition: p == quot*q + rem.
  P recomposed = (quot * q) + rem;
  CHECK(recomposed.find_degree() == p.find_degree());
  // Evaluate at a few points to ensure equality.
  for (int x = 0; x < 7; ++x) {
    mod7_t xx(x);
    CHECK(p.eval(xx).v == recomposed.eval(xx).v);
  }

  // GCD of p and q is 1 in F_7[x] (they are coprime).
  P g = p.gcd(q);
  CHECK(g.find_degree() == 0);
  // g(1) should be non-zero mod 7 if it's a unit (not strictly necessary).
  CHECK(g.eval(mod7_t(1)).v != 0);
}

