#include <polynomials/f2_poly_t.h>
#include <iostream>

int main(int argc, char** argv) {
  spffl::polynomials::f2_poly_t a(1);
  for (int argi = 1; argi < argc; argi++) {
    spffl::polynomials::f2_poly_t b(argv[argi]);
    a *= b;
  }
  std::cout << a << std::endl;

  return 0;
}
