// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "polynomials/f2_poly_t.h"

#include <iostream>

using namespace std;
using namespace spffl::polynomials;

static void show_promote_1() {
  cout << "PROMOTE_1" << endl;
  f2_poly_t a = 1;
  for (int i = 0; i < 128; i++) {
    std::cout << a << " " << i << " " << a.find_degree() << endl;
    a._promote_1();
  }
  cout << endl;
}

static void show_promote_4() {
  cout << "PROMOTE_4" << endl;
  f2_poly_t a = 1;
  for (int i = 0; i < 32; i++) {
    std::cout << a << " " << i * 4 << endl;
    a._promote_4();
  }
  cout << endl;
}

static void show_promote_n() {
  cout << "PROMOTE_N" << endl;
  f2_poly_t a = 1;
  for (int i = 0; i < 128; i++) {
    f2_poly_t b = a;
    b._promote_n(i);
    std::cout << b << " " << i << endl;
  }
  cout << endl;
}

static void show_demote_1() {
  cout << "DEMOTE_1" << endl;
  f2_poly_t a("100000000000000000000000000000000");
  for (int i = 0; i <= 128; i++) {
    std::cout << a << " " << i << endl;
    a._demote_1();
  }
  cout << endl;
}

static void debug() {
  // f2_poly_t a("12293e1d44694da98f2c9c6de5b51e8");
  // f2_poly_t a("11111111111111111111111111111111");
  // f2_poly_t a("ffffffffffffffff");
  // f2_poly_t a("5555555555555555");
  // f2_poly_t a("aaaaaaaaaaaaaaaa");
  // f2_poly_t a("aaaaaaaa");
  f2_poly_t a("aaaaaaaa");
  f2_poly_t a2 = a * a;

  cout << "A   " << a << endl;
  cout << "A^2 " << a2 << endl;

  f2_poly_t root;
  bool ok = a2.square_root(root);
  cout << "OK " << ok << endl;
  cout << "ROOT " << root << endl;
}

int main() {
  // show_promote_1();
  // show_promote_4();
  // show_promote_n();
  // show_demote_1();
  debug();

  return 0;
}
