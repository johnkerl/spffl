#include "qff.h"

namespace spffl::qcyclo {

// ----------------------------------------------------------------
spffl::bits::bit_t bit_from_rat(spffl::rationals::intrat_t r) {
  spffl::bits::bit_t numer(r.get_numerator());
  spffl::bits::bit_t denom(r.get_denominator());
  return numer / denom;
}

// ----------------------------------------------------------------
spffl::intmath::intmod_t intmod_from_rat(spffl::rationals::intrat_t r, int p) {
  spffl::intmath::intmod_t numer(r.get_numerator(), p);
  spffl::intmath::intmod_t denom(r.get_denominator(), p);

  return numer / denom;
}

// ----------------------------------------------------------------
spffl::polynomials::f2_poly_t f2poly_from_qpoly(spffl::rationals::qpoly_t q) {
  spffl::polynomials::f2_poly_t rv;
  int d = q.find_degree();
  for (int i = d; i >= 0; i--)
    rv.set_coeff(i, bit_from_rat(q.get_coeff(i)));
  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::fp_poly_t fppoly_from_qpoly(spffl::rationals::qpoly_t q, int p) {
  spffl::polynomials::fp_poly_t rv;
  int d = q.find_degree();
  for (int i = d; i >= 0; i--)
    rv.set_coeff(i, intmod_from_rat(q.get_coeff(i), p));
  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::f2n_poly_t f2npoly_from_qpoly(spffl::rationals::qpoly_t q, spffl::polynomials::f2_poly_t im) {
  spffl::polynomials::f2n_poly_t rv;
  int d = q.find_degree();
  for (int i = d; i >= 0; i--) {
    // xxx unimpl
    spffl::intmath::intmod_t m = intmod_from_rat(q.get_coeff(i), 2);
    spffl::polynomials::f2_polymod_t c = spffl::polynomials::f2_polymod_t::prime_sfld_elt(m.get_residue(), im);
    rv.set_coeff(i, c);
  }
  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::fpn_poly_t fpnpoly_from_qpoly(spffl::rationals::qpoly_t q, spffl::polynomials::fp_poly_t im) {
  int d = q.find_degree();
  int p = im.get_char();
  spffl::intmath::intmod_t z0(0, p);
  spffl::polynomials::fp_poly_t z1(z0);
  spffl::polynomials::fp_polymod_t z2(z0, im);
  spffl::polynomials::fpn_poly_t rv(z2);
  for (int i = d; i >= 0; i--) {
    spffl::intmath::intmod_t m = intmod_from_rat(q.get_coeff(i), p);
    spffl::polynomials::fp_polymod_t c = spffl::polynomials::fp_polymod_t::prime_sfld_elt(m.get_residue(), im);
    rv.set_coeff(i, c);
  }
  return rv;
}

} // namespace
