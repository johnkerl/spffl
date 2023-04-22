#include "qff.h"

// ----------------------------------------------------------------
spffl::bits::bit_t bit_from_rat(intrat_t r) {
  spffl::bits::bit_t numer(r.get_numerator());
  spffl::bits::bit_t denom(r.get_denominator());
  return numer / denom;
}

// ----------------------------------------------------------------
spffl::intmath::intmod_t intmod_from_rat(intrat_t r, int p) {
  spffl::intmath::intmod_t numer(r.get_numerator(), p);
  spffl::intmath::intmod_t denom(r.get_denominator(), p);

  return numer / denom;
}

// ----------------------------------------------------------------
f2_poly_t f2poly_from_qpoly(qpoly_t q) {
  f2_poly_t rv;
  int d = q.find_degree();
  for (int i = d; i >= 0; i--)
    rv.set_coeff(i, bit_from_rat(q.get_coeff(i)));
  return rv;
}

// ----------------------------------------------------------------
fp_poly_t fppoly_from_qpoly(qpoly_t q, int p) {
  fp_poly_t rv;
  int d = q.find_degree();
  for (int i = d; i >= 0; i--)
    rv.set_coeff(i, intmod_from_rat(q.get_coeff(i), p));
  return rv;
}

// ----------------------------------------------------------------
f2n_poly_t f2npoly_from_qpoly(qpoly_t q, f2_poly_t im) {
  f2n_poly_t rv;
  int d = q.find_degree();
  for (int i = d; i >= 0; i--) {
    // xxx unimpl
    spffl::intmath::intmod_t m = intmod_from_rat(q.get_coeff(i), 2);
    f2_polymod_t c = f2_polymod_t::prime_sfld_elt(m.get_residue(), im);
    rv.set_coeff(i, c);
  }
  return rv;
}

// ----------------------------------------------------------------
fpn_poly_t fpnpoly_from_qpoly(qpoly_t q, fp_poly_t im) {
  int d = q.find_degree();
  int p = im.get_char();
  spffl::intmath::intmod_t z0(0, p);
  fp_poly_t z1(z0);
  fp_polymod_t z2(z0, im);
  fpn_poly_t rv(z2);
  for (int i = d; i >= 0; i--) {
    spffl::intmath::intmod_t m = intmod_from_rat(q.get_coeff(i), p);
    fp_polymod_t c = fp_polymod_t::prime_sfld_elt(m.get_residue(), im);
    rv.set_coeff(i, c);
  }
  return rv;
}
