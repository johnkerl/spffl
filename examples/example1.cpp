#include <spffl/polynomials/f2_poly_t.h>
#include <iostream>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " {one or more F2 polynomials in hex, e.g. \"abc def\"\n";
    exit(1);
  }

  spffl::polynomials::f2_poly_t a(1);

  for (int argi = 1; argi < argc; argi++) {
    spffl::polynomials::f2_poly_t b(argv[argi]);
    a *= b;
  }
  std::cout << a << std::endl;

  return 0;
}
