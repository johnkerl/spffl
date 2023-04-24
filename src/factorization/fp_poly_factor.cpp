// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "fp_poly_factor.h"
#include "fp_poly_random.h"
#include "intmod_t.h"
#include "tfacinfo.h"
#include "tmatrix.h"

//#define FPPOLY_FACTOR_DEBUG

static void fppoly_pre_berlekamp(spffl::polynomials::fp_poly_t f, tfacinfo<spffl::polynomials::fp_poly_t> &rfinfo,
                                 int recurse);

static void fppoly_berlekamp(spffl::polynomials::fp_poly_t f, tfacinfo<spffl::polynomials::fp_poly_t> &rfinfo,
                             int recurse);

spffl::polynomials::fp_poly_t fppoly_from_vector(tvector<spffl::intmath::intmod_t> v, int n);

// ----------------------------------------------------------------
tfacinfo<spffl::polynomials::fp_poly_t> fp_poly_factor(spffl::polynomials::fp_poly_t f) {
  tfacinfo<spffl::polynomials::fp_poly_t> finfo;
  int d = f.find_degree();
  int p = f.get_char();
  spffl::intmath::intmod_t zero(0, p);
  spffl::intmath::intmod_t one(1, p);

  if (d == 0) {
    finfo.insert_unit(f);
    return finfo;
  }

  spffl::intmath::intmod_t leader = f.get_coeff(d);
  if ((leader != zero) && (leader != one)) {
    finfo.insert_unit(leader);
    f /= leader;
  }

  fppoly_pre_berlekamp(f, finfo, 1);
  return finfo;
}

// ----------------------------------------------------------------
static void fppoly_pre_berlekamp(spffl::polynomials::fp_poly_t f, tfacinfo<spffl::polynomials::fp_poly_t> &rfinfo,
                                 int recurse) {
  spffl::polynomials::fp_poly_t d = f.deriv();
  spffl::polynomials::fp_poly_t g = f.gcd(d);

#ifdef FPPOLY_FACTOR_DEBUG
  std::cout << "\n";
  std::cout << "fppoly_pre_berlekamp input = " << f << "  f' = " << d
            << "  (f,f') = " << g << "\n";
#endif

  if (g == 0) {
    if (f != 0) {
      std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
                << "\n";
      exit(1);
    }
    rfinfo.insert_factor(f);
    return;
  } else if (g.find_degree() == 0) {
    // Input is squarefree.
    fppoly_berlekamp(f, rfinfo, recurse);
  } else if (d == 0) {
    // Input is a perfect pth power
    spffl::polynomials::fp_poly_t s;
    tfacinfo<spffl::polynomials::fp_poly_t> sfinfo;
    int p = f.get_char();
    if (!f.pth_root(s)) {
      std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
                << "\n";
      exit(1);
    }

    // Multiplicity is p only if degree is > 0.
    fppoly_pre_berlekamp(s, sfinfo, recurse);
    if (f.find_degree() > 0)
      sfinfo.exp_all(p);
    rfinfo.merge(sfinfo);
  } else {
    spffl::polynomials::fp_poly_t q = f / g;

    // Input was already made monic, so these factors should
    // be as well.
    g /= g.get_coeff(g.find_degree());
    q /= q.get_coeff(q.find_degree());

    fppoly_pre_berlekamp(g, rfinfo, recurse);
    fppoly_pre_berlekamp(q, rfinfo, recurse);
  }
}

// ----------------------------------------------------------------
// See my "Computation in finite fields" (ffcomp.pdf) for a full description
// of this algorithm.  See f2_poly_factor.cpp for some sample data.

static void fppoly_berlekamp(spffl::polynomials::fp_poly_t f, tfacinfo<spffl::polynomials::fp_poly_t> &rfinfo,
                             int recurse) {
  int n = f.find_degree();
  int p = f.get_char();
  spffl::intmath::intmod_t zero(0, p);
  spffl::intmath::intmod_t one(1, p);
  spffl::polynomials::fp_poly_t x(one, zero);
  spffl::polynomials::fp_poly_t xp;
  spffl::polynomials::fp_poly_t xpi = one;
  spffl::polynomials::fp_poly_t f1, f2;
  int i, j, row, rank, dimker;

  xp = x;
  for (int i = 1; i < p; i++)
    xp = (xp * x) % f;

#ifdef FPPOLY_FACTOR_DEBUG
  std::cout << "\n";
  std::cout << "fppoly_berlekamp input = " << f << "\n";
  std::cout << "x"
            << " = " << x << "\n";
#endif
  tmatrix<spffl::intmath::intmod_t> BI(n, n);

  if (n < 2) {
    rfinfo.insert_factor(f);
    return;
  }

  // Populate the B matrix.
  for (j = 0; j < n; j++) {
    for (i = 0; i < n; i++) {
      BI[n - 1 - i][n - 1 - j] = xpi.get_coeff(i);
    }
#ifdef FPPOLY_FACTOR_DEBUG
    std::cout << "x^" << p << "*" << j << " = " << xpi << "\n";
#endif
    xpi = (xpi * xp) % f;
  }

#ifdef FPPOLY_FACTOR_DEBUG
  std::cout << "B =\n" << BI << "\n";
#endif

  // Form B - I.
  for (i = 0; i < n; i++)
    BI[i][i] -= one;

#ifdef FPPOLY_FACTOR_DEBUG
  std::cout << "B-I =\n" << BI << "\n";
#endif

  BI.row_echelon_form();

#ifdef FPPOLY_FACTOR_DEBUG
  std::cout << "B-I, rr =\n" << BI << "\n";
#endif

  rank = BI.get_rank_rr();
  dimker = n - rank;

  if (dimker == 1) {
    rfinfo.insert_factor(f);
    return;
  }

  // Find a basis for the nullspace of B - I.
  tmatrix<spffl::intmath::intmod_t> nullspace_basis;
  if (!BI.get_kernel_basis(nullspace_basis, zero, one)) {
    std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
              << "\n";
    exit(1);
  }
  if (nullspace_basis.get_num_rows() != dimker) {
    std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
              << "\n";
    exit(1);
  }
#ifdef FPPOLY_FACTOR_DEBUG
  std::cout << "nullity = " << dimker << "\n";
  std::cout << "nullspace basis =\n" << nullspace_basis << "\n";
#endif // FPPOLY_FACTOR_DEBUG

  int got_it = 0;
  for (row = 0; row < dimker && !got_it; row++) {
    spffl::polynomials::fp_poly_t h = fppoly_from_vector(nullspace_basis[row], n);
#ifdef FPPOLY_FACTOR_DEBUG
    std::cout << "h  = " << h << "\n";
#endif // FPPOLY_FACTOR_DEBUG
    if (h == 1)
      continue;

    for (int c = 0; c < p; c++) {
      spffl::polynomials::fp_poly_t hc = h - f.prime_sfld_elt(c);
      f1 = f.gcd(hc);
#ifdef FPPOLY_FACTOR_DEBUG
      std::cout << "hc  = " << hc << "  f1 = " << f1 << "\n";
#endif // FPPOLY_FACTOR_DEBUG
      int f1d = f1.find_degree();
      int fd = f.find_degree();
      if ((0 < f1d) && (f1d < fd)) {
        got_it = 1;
        break;
      }
    }
  }

  if (!got_it) {
    // No non-trivial factors found.
    std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
              << "\n";
    exit(1);
  }

  f2 = f / f1;

#ifdef FPPOLY_FACTOR_DEBUG
  std::cout << "f1 = " << f1 << "  f2 = " << f2 << "\n";
#endif // FPPOLY_FACTOR_DEBUG

  // Input was already made monic, so these factors should
  // be as well.
  f1 /= f1.get_coeff(f1.find_degree());
  f2 /= f2.get_coeff(f2.find_degree());

  // The nullity of B-I is the number of irreducible
  // factors of r.  If the nullity is 2, we have a
  // pair of factors which are both irreducible and
  // so we don't need to recurse.
  if (dimker == 2) {
    rfinfo.insert_factor(f1);
    rfinfo.insert_factor(f2);
  } else if (!recurse) {
    rfinfo.insert_factor(f1);
    rfinfo.insert_factor(f2);
  } else {
    fppoly_pre_berlekamp(f1, rfinfo, recurse);
    fppoly_pre_berlekamp(f2, rfinfo, recurse);
  }
}

// ----------------------------------------------------------------
spffl::polynomials::fp_poly_t fppoly_from_vector(tvector<spffl::intmath::intmod_t> v, int n) {
  spffl::polynomials::fp_poly_t f;
  f.set_coeff(0, v[0] - v[0]);
  for (int i = 0; i < n; i++)
    f.set_coeff(n - 1 - i, v[i]);
  return f;
}

// ----------------------------------------------------------------
int fppoly_is_irreducible(spffl::polynomials::fp_poly_t f) {
  tfacinfo<spffl::polynomials::fp_poly_t> finfo;

  int d = f.find_degree();
  if (d == 0)
    return 0;
  if (d == 1)
    return 1;

  f /= f.get_coeff(d);
  fppoly_pre_berlekamp(f, finfo, 0);

#ifdef FPPOLY_FACTOR_DEBUG
  std::cout << "fppirr: input = " << f << "\n";
  std::cout << "factors = " << finfo << "\n";
  std::cout << "# factors = " << finfo.get_num_factors() << "\n";
#endif // FPPOLY_FACTOR_DEBUG

  if (finfo.get_num_factors() == 1)
    return 1;
  else
    return 0;
}

// ----------------------------------------------------------------
// Lexically lowest
spffl::polynomials::fp_poly_t fppoly_find_irr(int p, int degree) {
  spffl::intmath::intmod_t zero(0, p), one(1, p);
  spffl::polynomials::fp_poly_t rv = zero;
  rv.set_coeff(degree, one);

  if (degree < 1) {
    std::cout << "fppoly_find_irr:  degree must be positive; got " << degree
              << ".\n";
    exit(1);
  }

  while (rv.find_degree() == degree) {
    if (rv.get_coeff(0) != zero) {
      if (fppoly_is_irreducible(rv))
        return rv;
    }
    rv.increment();
    // xxx smarter
  }

  // There are irreducibles of all positive degrees, so it is
  // an error if we failed to find one.
  std::cout << "fppoly_find_irr:  coding error.\n";
  exit(1);

  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::fp_poly_t fppoly_random_irr(int p, int degree) {
  spffl::intmath::intmod_t zero(0, p);
  spffl::polynomials::fp_poly_t rv;

  if (degree < 1) {
    std::cout << "fppoly_random_irr:  degree must be positive; got " << degree
              << ".\n";
    exit(1);
  }

  for (;;) {
    rv = fp_poly_random(p, degree);
    if (rv.get_coeff(0) == zero)
      continue;
    if (fppoly_is_irreducible(rv)) {
      rv /= rv.get_coeff(degree); // make monic
      return rv;
    }
  }
}
