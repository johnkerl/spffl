#include <catch2/catch_test_macros.hpp>

#include "f2_poly_t.h"

using namespace spffl::polynomials;

TEST_CASE("spffl::polynomials::f2_poly_t_ctors") {
  f2_poly_t f0;
  CHECK(f0.find_degree() == 0);

  f2_poly_t f1_0(0);
  CHECK(f1_0.find_degree() == 0);
  f2_poly_t f1_1(1);
  CHECK(f1_1.find_degree() == 0);

  f2_poly_t f2(1, 1, 1);
  CHECK(f2.find_degree() == 2);

  CHECK(f0.get_characteristic() == 2);
}

TEST_CASE("spffl::polynomials::f2_poly_t_degrees") {
  CHECK(f2_poly_t::from_base_rep(0x0).find_degree() == 0);
  CHECK(f2_poly_t::from_base_rep(0x1).find_degree() == 0);

  CHECK(f2_poly_t::from_base_rep(0x2).find_degree() == 1);
  CHECK(f2_poly_t::from_base_rep(0x3).find_degree() == 1);

  CHECK(f2_poly_t::from_base_rep(0x4).find_degree() == 2);
  CHECK(f2_poly_t::from_base_rep(0x5).find_degree() == 2);
  CHECK(f2_poly_t::from_base_rep(0x6).find_degree() == 2);
  CHECK(f2_poly_t::from_base_rep(0x7).find_degree() == 2);
}

TEST_CASE("spffl::polynomials::f2_poly_t_prime_sfld_elt") {
  f2_poly_t f;
  CHECK(f.prime_subfield_element(0) == f2_poly_t(0));
  CHECK(f.prime_subfield_element(1) == f2_poly_t(1));
  CHECK(f.prime_subfield_element(2) == f2_poly_t(0));
  CHECK(f.prime_subfield_element(3) == f2_poly_t(1));
}

TEST_CASE("spffl::polynomials::f2_poly_t_from_string") {
  f2_poly_t f;

  CHECK(f.from_string((char *)"0") == true);
  CHECK(f == f2_poly_t::from_base_rep(0));

  CHECK(f.from_string((char *)"1") == true);
  CHECK(f == f2_poly_t::from_base_rep(1));

  CHECK(f.from_string((char *)"ab") == true);
  CHECK(f == f2_poly_t::from_base_rep(0xab));
  CHECK(f.find_degree() == 7);

  CHECK(f.from_string((char *)"deadbeefcafefeedc0dec0debaddf00d") == true);
  CHECK(f.find_degree() == 127);

  CHECK(f.bit_at(127) == 1);
  CHECK(f.bit_at(126) == 1);
  CHECK(f.bit_at(125) == 0);
  CHECK(f.bit_at(124) == 1);

  CHECK(f.bit_at(123) == 1);
  CHECK(f.bit_at(122) == 1);
  CHECK(f.bit_at(121) == 1);
  CHECK(f.bit_at(120) == 0);

  f2_poly_t g;
  CHECK(g.from_string((char *)"deadbeefcafefeedc0dec0debaddf00e") == true);
  CHECK(f != g);
  f.increment();
  CHECK(f == g);
}

// TODO:
//  f2_poly_t &operator = (f2_poly_t that);
//  f2_poly_t &operator = (int bit); // 0 or 1; other bits ignored.

TEST_CASE("spffl::polynomials::f2_poly_t_arithmetic_small") {
  f2_poly_t a("a");
  f2_poly_t b("b");

  CHECK(a + a == f2_poly_t("0"));
  CHECK(a - a == f2_poly_t("0"));
  CHECK(a + b == f2_poly_t("1"));
  CHECK(a - b == f2_poly_t("1"));
  CHECK(a * b == f2_poly_t("4e"));
  CHECK(a * 0 == f2_poly_t("0"));
  CHECK(a * 1 == a);
  CHECK(a.exp(17) == f2_poly_t("a0000000a0000"));
  CHECK(a / b == f2_poly_t("1"));
  CHECK(a % b == f2_poly_t("1"));
  CHECK(b % a == f2_poly_t("1"));

  f2_poly_t q, r;
  a.quot_and_rem(b, q, r);
  CHECK(q == a / b);
  CHECK(r == a % b);

  f2_poly_t m, n;
  f2_poly_t g = a.ext_gcd(b, m, n);
  CHECK(m == f2_poly_t("1"));
  CHECK(n == f2_poly_t("1"));
  CHECK(a * m + b * n == g);

  CHECK(a.deriv() == f2_poly_t("5"));

  f2_poly_t root;
  bool ok = a.square_root(root);
  CHECK(!ok);

  ok = (a * a).square_root(root);
  CHECK(ok);
  CHECK(root == a);

  CHECK(a.eval(0) == 0);
  CHECK(a.eval(1) == 0);
  CHECK(b.eval(0) == 1);
  CHECK(b.eval(1) == 1);

  CHECK(f2_poly_t("0") == 0);
  CHECK(f2_poly_t("1") == 1);
  CHECK(a == a);
  CHECK(a != b);
  CHECK(a != 1);
  CHECK(b != 1);
  CHECK(a < b);
  CHECK(b > a);
  CHECK(a <= a);
  CHECK(b <= b);
  CHECK(a >= a);
  CHECK(b >= b);
  CHECK(a <= b);
  CHECK(b >= a);

  a.set_coeff(18, spffl::bits::bit_t(1));
  CHECK(a == f2_poly_t("4000a"));

  a.set_coeff(19, spffl::bits::bit_t(1));
  CHECK(a == f2_poly_t("c000a"));

  a.set_coeff(18, spffl::bits::bit_t(0));
  CHECK(a == f2_poly_t("8000a"));

  a.set_bit(21);
  CHECK(a == f2_poly_t("28000a"));

  a.set_bit(129);
  CHECK(a == f2_poly_t("20000000000000000000000000028000a"));
}

TEST_CASE("spffl::polynomials::f2_poly_t_arithmetic_big") {
  f2_poly_t a("12293e1d44694da98f2c9c6de5b51e8");
  f2_poly_t b("3b2a5e669f064560558942f80709bb82979af");

  CHECK(a + a == f2_poly_t("0"));
  CHECK(a - a == f2_poly_t("0"));
  CHECK(a + b == f2_poly_t("3b2a5e74b63858243cc4eb772b95d66722847"));
  CHECK(a - b == f2_poly_t("3b2a5e74b63858243cc4eb772b95d66722847"));
  CHECK(a * b == f2_poly_t("3c273ff360978b0eabdb9da321425d879f9f8324a7f6e5f3040"
                           "e68c440da6b7dbd8"));
  CHECK(a * 0 == f2_poly_t("0"));
  CHECK(a * 1 == a);
  CHECK(a.exp(2) ==
        f2_poly_t(
            "1040441055401511010144110514441405504504150145154114511015440"));
  CHECK(a / b == f2_poly_t("0"));
  CHECK(b / a == f2_poly_t("3cd491e"));
  CHECK(a % a == f2_poly_t("0"));
  CHECK(a % b == f2_poly_t("12293e1d44694da98f2c9c6de5b51e8"));
  CHECK(b % a == f2_poly_t("e47d6ecbec0f769ab3528e1031a41f"));

  f2_poly_t q, r;
  a.quot_and_rem(b, q, r);
  CHECK(q == a / b);
  CHECK(r == a % b);

  CHECK(a.gcd(b) == f2_poly_t("3"));
  CHECK(b.gcd(a) == f2_poly_t("3"));

  f2_poly_t m, n;
  f2_poly_t g = a.ext_gcd(b, m, n);
  CHECK(m == f2_poly_t("f7368ac33cd3c9bce8e73eb39baedb7c6690"));
  CHECK(n == f2_poly_t("4314434929d6692b3807c175ed57b5"));
  CHECK(a * m + b * n == g);
  CHECK(a.deriv() == f2_poly_t("114150400140454451444145050054"));

  f2_poly_t root;
  bool ok = a.square_root(root);
  CHECK(!ok);

  ok = (a * a).square_root(root);
  CHECK(ok);
  CHECK(root == a);

  CHECK(a.eval(0) == 0);
  CHECK(a.eval(1) == 0);
  CHECK(b.eval(0) == 1);
  CHECK(b.eval(1) == 0);

  CHECK(f2_poly_t("0") == 0);
  CHECK(f2_poly_t("1") == 1);
  CHECK(a == a);
  CHECK(a != b);
  CHECK(a != 1);
  CHECK(b != 1);
  CHECK(a < b);
  CHECK(b > a);
  CHECK(a <= a);
  CHECK(b <= b);
  CHECK(a >= a);
  CHECK(b >= b);
  CHECK(a <= b);
  CHECK(b >= a);

  a.set_coeff(18, spffl::bits::bit_t(1));
  CHECK(a == f2_poly_t("12293e1d44694da98f2c9c6de5f51e8"));

  a.set_coeff(19, spffl::bits::bit_t(1));
  CHECK(a == f2_poly_t("12293e1d44694da98f2c9c6de5f51e8"));

  a.set_coeff(18, spffl::bits::bit_t(0));
  CHECK(a == f2_poly_t("12293e1d44694da98f2c9c6de5b51e8"));

  a.set_bit(21);
  CHECK(a == f2_poly_t("12293e1d44694da98f2c9c6de7b51e8"));

  a.set_bit(129);
  CHECK(a == f2_poly_t("2012293e1d44694da98f2c9c6de7b51e8"));
}

// TODO:
// f2_poly_t &operator += (f2_poly_t that);
// f2_poly_t &operator -= (f2_poly_t that);
// f2_poly_t &operator *= (f2_poly_t that);
// f2_poly_t &operator *= (int bit); // 0 or 1; other bits ignored.
// f2_poly_t &operator /= (f2_poly_t &that);
// f2_poly_t &operator %= (f2_poly_t &that);
