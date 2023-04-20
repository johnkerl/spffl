#include "qff.h"

// ----------------------------------------------------------------
bit_t bit_from_rat(intrat_t r) {
  bit_t numer(r.get_numerator());
  bit_t denom(r.get_denominator());
  return numer / denom;
}

// ----------------------------------------------------------------
intmod_t intmod_from_rat(intrat_t r, int p) {
  intmod_t numer(r.get_numerator(), p);
  intmod_t denom(r.get_denominator(), p);

  return numer / denom;
}

// ----------------------------------------------------------------
f2poly_t f2poly_from_qpoly(qpoly_t q) {
  f2poly_t rv;
  int d = q.find_degree();
  for (int i = d; i >= 0; i--)
    rv.set_coeff(i, bit_from_rat(q.get_coeff(i)));
  return rv;
}

// ----------------------------------------------------------------
fppoly_t fppoly_from_qpoly(qpoly_t q, int p) {
  fppoly_t rv;
  int d = q.find_degree();
  for (int i = d; i >= 0; i--)
    rv.set_coeff(i, intmod_from_rat(q.get_coeff(i), p));
  return rv;
}

// ----------------------------------------------------------------
f2npoly_t f2npoly_from_qpoly(qpoly_t q, f2poly_t im) {
  f2npoly_t rv;
  int d = q.find_degree();
  for (int i = d; i >= 0; i--) {
    // xxx unimpl
    intmod_t m = intmod_from_rat(q.get_coeff(i), 2);
    f2polymod_t c = f2polymod_t::prime_sfld_elt(m.get_residue(), im);
    rv.set_coeff(i, c);
  }
  return rv;
}

// ----------------------------------------------------------------
fpnpoly_t fpnpoly_from_qpoly(qpoly_t q, fppoly_t im) {
  int d = q.find_degree();
  int p = im.get_char();
  intmod_t z0(0, p);
  fppoly_t z1(z0);
  fppolymod_t z2(z0, im);
  fpnpoly_t rv(z2);
  for (int i = d; i >= 0; i--) {
    intmod_t m = intmod_from_rat(q.get_coeff(i), p);
    fppolymod_t c = fppolymod_t::prime_sfld_elt(m.get_residue(), im);
    rv.set_coeff(i, c);
  }
  return rv;
}
