#include "spffl/libspffl.h"

// ----------------------------------------------------------------
static void usage(char *argv0) {
  std::cout << "Usage: " << argv0 << " {m} {a1,a2,a3,a4,a6} {x1,y1,z1} {x2,y2,z2}\n";
  std::cout << "Where y^2 + a1 x y + a3 y = x^3 + a2 x^2 + a4 x + a6\n";
  exit(1);
}

// ----------------------------------------------------------------
static void check_point(const char *desc, f2_polymod_t a1, f2_polymod_t a2, f2_polymod_t a3,
  f2_polymod_t a4, f2_polymod_t a6, f2_polymod_t x, f2_polymod_t y, f2_polymod_t z) {
  f2_polymod_t f = (y * y + a1 * x * y + a3 * y * z) * z + x * (x * (x + a2 * z) + a4 * z) + a6 * z;
  f2_polymod_t zero = y - y;
  if (f != zero) {
#if 1
    std::cerr << "The " << desc << " point [" << x << "," << y << "," << z
              << "] is not on the curve y^2 + " << a1 << " x y + " << a3 << " y = x^3 + " << a2
              << " x^2 + " << a4 << " x + " << a6 << "\n";

    std::cerr << y * y * z << "\n";
    std::cerr << a1 * x * y * z << "\n";
    std::cerr << a3 * y * z * z << "\n";
    std::cerr << x * x * x << "\n";
    std::cerr << a2 * x * x * z << "\n";
    std::cerr << a4 * x * z * z << "\n";
    std::cerr << a6 * z * z * z << "\n";

    exit(1);
#else
    std::cout << "#";
#endif
  } else {
#if 1
#else
    std::cout << " ";
#endif
  }
}

// ----------------------------------------------------------------
int main(int argc, char **argv) {
  f2_poly_t m;
  f2_polymod_t a1, a2, a3, a4, a6;
  f2_polymod_t x1, y1, z1;
  f2_polymod_t x2, y2, z2;
  f2_polymod_t x3, y3, z3;
  f2_polymod_t lambda, nu;

  if (argc != 5)
    usage(argv[0]);
  if (!m.from_string(argv[1]))
    usage(argv[0]);
  if (!ft_scan_quintuple(argv[2], m, a1, a2, a3, a4, a6))
    usage(argv[0]);
  if (!ft_scan_triple(argv[3], m, x1, y1, z1))
    usage(argv[0]);
  if (!ft_scan_triple(argv[4], m, x2, y2, z2))
    usage(argv[0]);

  f2_polymod_t zero = f2_polymod_t::prime_subfield_element(0, m);
  f2_polymod_t one = f2_polymod_t::prime_subfield_element(1, m);
  check_point("input", a1, a2, a3, a4, a6, x1, y1, z1);
  check_point("input", a1, a2, a3, a4, a6, x2, y2, z2);

  if (x1 == zero && y1 == one && z1 == zero) {
    // P1 is O
    x3 = x2;
    y3 = y2;
    z3 = z2;
  } else if (x2 == zero && y2 == one && z2 == zero) {
    // P2 is O
    x3 = x1;
    y3 = y1;
    z3 = z1;
  } else if (x1 == x2 && y1 == y2 && z1 == z2) {
    // Duplication formula:  Silverman pp. 58-59.
    lambda = (x1 * x1 + a4 + a1 * y1) / (a1 * x1 + a3);
    nu = (x1 * x1 * x1 + a4 * x1 + a3 * y1) / (a1 * x1 + a3);

    x3 = lambda * lambda + a1 * lambda + a2 + x1 + x2;
    y3 = (lambda + a1) * x3 + nu + a3;
    z3 = one;
  } else if (x1 == x2) {
    // Vertical line
    x3 = zero;
    y3 = one;
    z3 = zero;
  } else {
    // Product formula:  Silverman pp. 58-59.
    lambda = (y2 + y1) / (x2 + x1);
    nu = (y1 * x2 + y2 * x1) / (x2 + x1);

    x3 = lambda * lambda + a1 * lambda + a2 + x1 + x2;
    y3 = (lambda + a1) * x3 + nu + a3;
    z3 = one;
  }

  check_point("computed", a1, a2, a3, a4, a6, x3, y3, z3);

  std::cout << x3 << "," << y3 << "," << z3 << "\n";

  return 0;
}
