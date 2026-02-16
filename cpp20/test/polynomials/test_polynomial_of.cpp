// Basic sanity tests for spffl::polynomials::polynomial_of<Coeff>.

#include <catch2/catch_test_macros.hpp>

#include "spffl/concepts.hpp"
#include "spffl/polynomials/polynomial_of.hpp"
#include "spffl/polynomials/aliases.hpp"
#include "spffl/polynomials/fp_polymod_t.hpp"
#include "spffl/polynomials/fp_poly_io.hpp"

using spffl::polynomials::polynomial_of;

// Concept satisfaction: polynomial_of and fp_polymod_t model the proposal concepts.
TEST_CASE("polynomial_of<intmod_t> models polynomial concepts") {
  using spffl::polynomials::fp_poly_t;
  static_assert(spffl::concepts::Ring_element<spffl::intmath::intmod_t>);
  static_assert(spffl::concepts::Field_element<spffl::intmath::intmod_t>);
  static_assert(spffl::concepts::Euclidean_domain<fp_poly_t>);
  static_assert(spffl::concepts::Polynomial_ring_element<fp_poly_t>);
  static_assert(spffl::concepts::Polynomial_with_ext_gcd<fp_poly_t>);
}

TEST_CASE("fp_polymod_t models Residue_ring") {
  using spffl::polynomials::fp_polymod_t;
  static_assert(spffl::concepts::Residue_ring<fp_polymod_t>);
  static_assert(spffl::concepts::Residue_ring_with_recip<fp_polymod_t>);
}

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

// ---------------------------------------------------------------------------
// fp_poly_t = polynomial_of<intmod_t> (Fp[x] via cpp20 aliases).
// ---------------------------------------------------------------------------

#include "spffl/polynomials/aliases.hpp"

TEST_CASE("fp_poly_t (polynomial_of<intmod_t>): F7[x] arithmetic and division") {
  using spffl::polynomials::fp_poly_t;
  using spffl::intmath::intmod_t;

  const int p = 7;
  intmod_t zero(0, p), one(1, p);

  // a(x) = x^2 + 1,  b(x) = x + 1  in F_7[x]
  fp_poly_t a(one, zero, one);   // coeffs x^0, x^1, x^2
  fp_poly_t b(one, one);

  fp_poly_t sum = a + b;         // x^2 + x + 2
  CHECK(sum.find_degree() == 2);
  CHECK(sum.eval(intmod_t(0, p)).get_residue() == 2);
  CHECK(sum.eval(intmod_t(1, p)).get_residue() == 4);

  fp_poly_t quot, rem;
  a.quot_and_rem(b, quot, rem);
  // a = quot * b + rem
  fp_poly_t recomposed = (quot * b) + rem;
  for (int x = 0; x < p; ++x) {
    intmod_t xx(x, p);
    CHECK(a.eval(xx).get_residue() == recomposed.eval(xx).get_residue());
  }

  fp_poly_t g = a.gcd(b);
  CHECK(g.find_degree() == 0);
  CHECK(!g.is_zero());

  // ext_gcd: a*rm + b*rn = g (here g is constant unit)
  fp_poly_t rm, rn;
  fp_poly_t g2 = a.ext_gcd(b, rm, rn);
  fp_poly_t lhs = (a * rm) + (b * rn);
  CHECK(g2.find_degree() == g.find_degree());
  for (int x = 0; x < p; ++x) {
    intmod_t xx(x, p);
    CHECK(lhs.eval(xx).get_residue() == g2.eval(xx).get_residue());
  }

  // exp: (1+x)^2 = 1 + 2x + x^2 in F_7
  fp_poly_t b_sq = b.exp(2);
  CHECK(b_sq.find_degree() == 2);
  CHECK(b_sq.get_coeff(0).get_residue() == 1);
  CHECK(b_sq.get_coeff(1).get_residue() == 2);
  CHECK(b_sq.get_coeff(2).get_residue() == 1);

  // Direct quot_and_rem: x^2 / (x^2+1) => quot=1, rem=-1 (constant 6 mod 7)
  // (c2,c1,c0) -> coeffs_[0]=c0, coeffs_[2]=c2; x^2 has coeffs [0,0,1] so (one, zero, zero)
  fp_poly_t x_sq_poly(one, zero, zero);
  fp_poly_t m_poly(one, zero, one);  // x^2+1
  fp_poly_t qq, rr;
  x_sq_poly.quot_and_rem(m_poly, qq, rr);
  CHECK(rr.find_degree() == 0);
  CHECK(rr.get_coeff(0).get_residue() == 6);  // -1 mod 7

  // operator/ and operator%
  fp_poly_t q_div = x_sq_poly / m_poly;
  fp_poly_t r_mod = x_sq_poly % m_poly;
  CHECK(q_div.find_degree() == 0);
  CHECK(q_div.get_coeff(0).get_residue() == 1);
  CHECK(r_mod.find_degree() == 0);
  CHECK(r_mod.get_coeff(0).get_residue() == 6);

  // deriv: d/dx(1 + 2x + x^2) = 2 + 2x in F_7
  fp_poly_t b_deriv = b_sq.deriv();
  CHECK(b_deriv.find_degree() == 1);
  CHECK(b_deriv.get_coeff(0).get_residue() == 2);
  CHECK(b_deriv.get_coeff(1).get_residue() == 2);
}

// ---------------------------------------------------------------------------
// fp_polymod_t: Fp[x]/(m) residue ring.
// ---------------------------------------------------------------------------

#include "spffl/polynomials/fp_polymod_t.hpp"

TEST_CASE("fp_polymod_t: F7[x]/(x^2+1) ring and inverse") {
  using spffl::polynomials::fp_poly_t;
  using spffl::polynomials::fp_polymod_t;
  using spffl::intmath::intmod_t;

  const int p = 7;
  intmod_t zero(0, p), one(1, p);

  // m(x) = x^2 + 1 (irreducible in F_7)
  fp_poly_t m(one, zero, one);
  // x: coeffs [0,1] so (c1,c0)=(one, zero)
  fp_poly_t x_poly(one, zero);
  fp_polymod_t x_mod(x_poly, m);

  fp_polymod_t one_mod(fp_poly_t::one(x_poly), m);
  fp_polymod_t zero_mod(fp_poly_t(zero), m);
  fp_polymod_t x_sq = x_mod * x_mod;  // x^2 ≡ -1 (mod x^2+1)
  CHECK(x_sq.get_residue().find_degree() == 0);
  // x^2 = -1 so x_sq + 1 = 0 in the ring
  CHECK((x_sq + one_mod).get_residue().get_coeff(0).get_residue() == 0);
  // (-1)^2 = 1
  fp_polymod_t x_4 = x_sq * x_sq;
  CHECK(x_4 == one_mod);

  // x should be a unit; 1/x exists
  fp_polymod_t x_inv;
  REQUIRE(x_mod.recip(x_inv));
  fp_polymod_t prod = x_mod * x_inv;
  CHECK(prod == one_mod);
}

// ---------------------------------------------------------------------------
// fp_poly_t from_string and operator>>
// ---------------------------------------------------------------------------

TEST_CASE("fp_poly_from_string: comma-separated coefficients, leading first") {
  using spffl::polynomials::fp_poly_from_string;
  using spffl::polynomials::fp_poly_t;

  auto opt = fp_poly_from_string("1,0,1", 7);
  REQUIRE(opt.has_value());
  fp_poly_t p = *opt;
  CHECK(p.find_degree() == 2);
  CHECK(p.get_coeff(0).get_residue() == 1);
  CHECK(p.get_coeff(1).get_residue() == 0);
  CHECK(p.get_coeff(2).get_residue() == 1);

  opt = fp_poly_from_string("1,2", 7);  // 2 + x
  REQUIRE(opt.has_value());
  p = *opt;
  CHECK(p.find_degree() == 1);
  CHECK(p.get_coeff(0).get_residue() == 2);
  CHECK(p.get_coeff(1).get_residue() == 1);

  CHECK(!fp_poly_from_string("", 7).has_value());
  CHECK(!fp_poly_from_string("1,foo,2", 7).has_value());
}

TEST_CASE("fp_poly_t operator>>: modulus then coefficients") {
  using spffl::polynomials::fp_poly_t;

  std::istringstream iss("7 1,0,1");
  fp_poly_t p;
  iss >> p;
  REQUIRE(iss);
  CHECK(p.find_degree() == 2);
  CHECK(p.get_coeff(0).get_residue() == 1);
  CHECK(p.get_coeff(2).get_residue() == 1);
}

// ---------------------------------------------------------------------------
// fp_polymod_t from_string and operator>>
// ---------------------------------------------------------------------------

TEST_CASE("fp_polymod_from_string: residue with given modulus") {
  using spffl::polynomials::fp_poly_from_string;
  using spffl::polynomials::fp_polymod_from_string;
  using spffl::polynomials::fp_poly_t;
  using spffl::polynomials::fp_polymod_t;

  auto mod_opt = fp_poly_from_string("1,0,1", 7);  // x^2 + 1
  REQUIRE(mod_opt.has_value());
  fp_poly_t m = *mod_opt;

  auto res_opt = fp_polymod_from_string("1,0", m);  // residue x (leading 1, constant 0)
  REQUIRE(res_opt.has_value());
  fp_polymod_t a = *res_opt;
  CHECK(a.get_residue().find_degree() == 1);
  CHECK(a.get_residue().get_coeff(1).get_residue() == 1);

  res_opt = fp_polymod_from_string("1", m);  // residue 1
  REQUIRE(res_opt.has_value());
  a = *res_opt;
  CHECK(a.get_residue().find_degree() == 0);
  CHECK(a.get_residue().get_coeff(0).get_residue() == 1);
}

TEST_CASE("fp_polymod_t operator>>: p, modulus coeffs, residue coeffs on one line") {
  using spffl::polynomials::fp_polymod_t;

  std::istringstream iss("7 1,0,1 1,0");  // F7[x]/(x^2+1), element x (residue coeffs leading first)
  fp_polymod_t a;
  iss >> a;
  REQUIRE(iss);
  CHECK(a.get_residue().find_degree() == 1);
  CHECK(a.get_modulus().find_degree() == 2);
}

