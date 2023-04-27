// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "f2_poly_factor.h"
#include "f2_poly_random.h"
#include "tfacinfo.h"

//#define F2POLY_FACTOR_DEBUG
#define USE_BIT_MATRIX

#ifdef USE_BIT_MATRIX
#include "bit_matrix_t.h"
#else
#include "bit_t.h"
#include "tmatrix.h"
#endif

namespace spffl::factorization {

static void
f2_poly_pre_berlekamp(spffl::polynomials::f2_poly_t f,
                      tfacinfo<spffl::polynomials::f2_poly_t> &rfinfo,
                      bool recurse);

static void f2_poly_berlekamp(spffl::polynomials::f2_poly_t f,
                              tfacinfo<spffl::polynomials::f2_poly_t> &rfinfo,
                              bool recurse);

spffl::polynomials::f2_poly_t f2_poly_from_vector(
#ifdef USE_BIT_MATRIX
    spffl::bits::bit_vector_t &v,
#else
    tvector<spffl::bits::bit_t> &v,
#endif
    int n);

// ----------------------------------------------------------------
tfacinfo<spffl::polynomials::f2_poly_t>
f2_poly_factor(spffl::polynomials::f2_poly_t f) {
  tfacinfo<spffl::polynomials::f2_poly_t> finfo;
  if (f.find_degree() == 0) {
    finfo.insert_unit(f);
    return finfo;
  }
  f2_poly_pre_berlekamp(f, finfo, true);
  return finfo;
}

// ----------------------------------------------------------------
static void
f2_poly_pre_berlekamp(spffl::polynomials::f2_poly_t f,
                      tfacinfo<spffl::polynomials::f2_poly_t> &rfinfo,
                      bool recurse) {
  spffl::polynomials::f2_poly_t d = f.deriv();
  spffl::polynomials::f2_poly_t g = f.gcd(d);

#ifdef F2POLY_FACTOR_DEBUG
  std::cout << "\n";
  std::cout << "f2_poly_pre_berlekamp input = " << f << "  f' = " << d
            << "  (f,f') = " << g << "\n";
#endif

  if (g == 0) {
    if (f != 0) {
      std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
                << "\n";
      exit(1);
    }
#ifdef F2POLY_FACTOR_DEBUG
    std::cout << "g=0 f=0 insert " << f << "\n";
#endif
    rfinfo.insert_factor(f);
    return;
  } else if (g == 1) {
    // Input is squarefree.
    f2_poly_berlekamp(f, rfinfo, recurse);
  } else if (d == 0) {
    // Input is a perfect square
    spffl::polynomials::f2_poly_t s;
    tfacinfo<spffl::polynomials::f2_poly_t> sfinfo;
    if (!f.square_root(s)) {
      std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
                << "\n";
      exit(1);
    }

    // Multiplicity is p only if degree is > 0.
    f2_poly_pre_berlekamp(s, sfinfo, recurse);
    if (f.find_degree() > 0)
      sfinfo.exp_all(2);
    rfinfo.merge(sfinfo);
#ifdef F2POLY_FACTOR_DEBUG
    std::cout << "square insert " << sfinfo << "\n";
#endif
  } else {
    spffl::polynomials::f2_poly_t q = f / g;
    f2_poly_pre_berlekamp(g, rfinfo, recurse);
    f2_poly_pre_berlekamp(q, rfinfo, recurse);
  }
}

// ----------------------------------------------------------------
// See my "Computation in finite fields" (ffcomp.pdf) for a full description
// of this algorithm.
//
// Given squarefree f(x), we want to find polynomials h(x) such that
// h^q equiv h (mod f).  (Example: f = 31 = 7 * b.  Deg(f) = 5.)
// By explicit search, we can find the following polynomials h of degree
// < 5 such that h**2 = h mod f (Lidl and Niederreiter call these "f-reducing
// polynomials"): 00 01 1c 1d.
//
// To avoid having to do a search, we use linear algebra instead.
//
// f = x^5+x^4+1 = 110001
//   x^0 = 00001
//   x^2 = 00100
//   x^4 = 10000
//   x^6 = 10011
//   x^8 = 11101
//
// h   = a_4 x^4 + a_3 x^3 + a_2 x^2 + a_1 x + a_0
// h^2 = a_4(x^4+x^3+x^2+1) + a_3(x^4+x+1) + a_2(x^4) + a_1(x^2) + a_0(1)
//
// [ a_4 ]     [ 1 1 1 0 0 ]     [ a_4 ]
// [ a_3 ]     [ 1 0 0 0 0 ]     [ a_3 ]
// [ a_2 ]  =  [ 1 0 0 1 0 ]  *  [ a_2 ]
// [ a_1 ]     [ 1 1 0 0 0 ]     [ a_1 ]
// [ a_0 ]     [ 1 1 0 0 1 ]     [ a_0 ]
//
// [ 0 ]  .  [ 0 1 1 0 0 ]  .  [ a_4 ]
// [ 0 ]  .  [ 1 1 0 0 0 ]  .  [ a_3 ]
// [ 0 ]  =  [ 1 0 1 1 0 ]  *  [ a_2 ]
// [ 0 ]  .  [ 1 1 0 1 0 ]  .  [ a_1 ]
// [ 0 ]  .  [ 1 1 0 0 0 ]  .  [ a_0 ]
//
// Call the matrix B.  Its (n-1-j)th column is x^{jq} mod f.  Put it in
// row-echelon form to obtain
//
// [ 1 0 1 0 0 ]
// [ 0 1 1 0 0 ]
// [ 0 0 0 1 0 ]
// [ 0 0 0 0 0 ]
// [ 0 0 0 0 0 ]
//
// with kernel basis
//
// [ 1 1 1 0 0 ]
// [ 0 0 0 0 1 ]
//
// These are h1 = 1c and h2 = 1, respectively.  Compute gcd(f, h1) = 7 and
// gcd(f, h1+1) = b to obtain non-trivial factors of f.

static void f2_poly_berlekamp(spffl::polynomials::f2_poly_t f,
                              tfacinfo<spffl::polynomials::f2_poly_t> &rfinfo,
                              bool recurse) {
  int n = f.find_degree();
  spffl::polynomials::f2_poly_t x(1, 0);
  spffl::polynomials::f2_poly_t x2 = (x * x) % f;
  spffl::polynomials::f2_poly_t x2i(1);
  int i, j, row, rank, dimker;
  // spffl::bits::bit_t zero(0);
  // spffl::bits::bit_t one(1);

#ifdef F2POLY_FACTOR_DEBUG
  std::cout << "\n";
  std::cout << "f2_poly_berlekamp input = " << f << "\n";
#endif
#ifdef USE_BIT_MATRIX
  spffl::bits::bit_matrix_t BI(n, n);
#else
  tmatrix<spffl::bits::bit_t> BI(n, n);
#endif

  if (n < 2) {
    rfinfo.insert_factor(f);
#ifdef F2POLY_FACTOR_DEBUG
    std::cout << "n<2 insert " << f << "\n";
#endif
    return;
  }

  // Populate the B matrix.
  for (j = 0; j < n; j++) {
    for (i = 0; i < n; i++) {
#ifdef USE_BIT_MATRIX
      BI[n - 1 - i].set(n - 1 - j, spffl::bits::bit_t(x2i.bit_at(i)));
#else
      BI[n - 1 - i][n - 1 - j] = spffl::bits::bit_t(x2i.bit_at(i));
#endif
    }
    x2i = (x2i * x2) % f;
  }

#ifdef F2POLY_FACTOR_DEBUG
  std::cout << "B =\n" << BI << "\n";
#endif

  // Form B - I.
  for (i = 0; i < n; i++) {
#ifdef USE_BIT_MATRIX
    BI[i].toggle_element(i);
#else
    BI[i][i] = BI[i][i] - one;
#endif
  }

#ifdef F2POLY_FACTOR_DEBUG
  std::cout << "B-I =\n" << BI << "\n";
#endif

  BI.row_echelon_form();

#ifdef F2POLY_FACTOR_DEBUG
  std::cout << "B-I, rr =\n" << BI << "\n";
#endif

  rank = BI.get_rank_rr();
  dimker = n - rank;

  if (dimker == 1) {
#ifdef F2POLY_FACTOR_DEBUG
    std::cout << "dimker=1 insert " << f << "\n";
#endif
    rfinfo.insert_factor(f);
    return;
  }

  // Find a basis for the nullspace of B - I.
#ifdef USE_BIT_MATRIX
  spffl::bits::bit_matrix_t nullspace_basis;
#else
  tmatrix<spffl::bits::bit_t> nullspace_basis;
#endif

#ifdef USE_BIT_MATRIX
  bool got = BI.get_kernel_basis(nullspace_basis);
#else
  bool got = BI.get_kernel_basis(nullspace_basis, zero, one);
#endif

  if (!got) {
    std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
              << "\n";
    exit(1);
  }
  if (nullspace_basis.get_num_rows() != dimker) {
    std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
              << "\n";
    exit(1);
  }
#ifdef F2POLY_FACTOR_DEBUG
  std::cout << "nullity = " << dimker << "\n";
  std::cout << "nullspace basis =\n" << nullspace_basis << "\n";
#endif // F2POLY_FACTOR_DEBUG

  // For each h in the nullspace basis, form
  //   f1 = gcd(f, h)
  //   f2 = gcd(f, h-1)
  // Now, the polynomial h=1 is always in the nullspace, in which case
  // f1 = 1 and f2 = f, which results in a trivial factorization.  Any
  // of the other h's will work fine, producing a non-trivial
  // factorization of f into two factors.  (Note that either or both
  // of them may be reducible, in which we'll need to apply this
  // algorithm recursively until we're down to irreducible factors.)
  // Here, for the sake of illustration, is what happens with all the
  // h's, even though we need only one of them (with f = 703):

  // h=001
  //   f1: 001
  //   f2: 70e = 2 3 7 b d
  // h=102     = 2 3 b d
  //   f1: 102 = 2 3 b d
  //   f2: 007 = 7
  // h=284     = 2 2 7 3b
  //   f1: 00e = 2 7
  //   f2: 081 = 3 b d
  // h=0e8     = 2 2 2 3 b
  //   f1: 03a = 2 3 b
  //   f2: 023 = 7 d
  // h=310     = 2 2 2 2 7 b
  //   f1: 062 = 2 7 b
  //   f2: 017 = 3 d

  for (row = 0; row < dimker; row++) {
    spffl::polynomials::f2_poly_t h, hc;
    h = f2_poly_from_vector(nullspace_basis[row], n);
    hc = h + spffl::polynomials::f2_poly_t(1);

    spffl::polynomials::f2_poly_t check1 = (h * h) % f;
    spffl::polynomials::f2_poly_t check2 = (hc * hc) % f;
    if ((h != check1) || (hc != check2)) {
      std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
                << "\n";
      std::cerr << "  h  = " << h << "  h^2  = " << check1 << "\n";
      std::cerr << "  hc = " << hc << "  hc^2 = " << check2 << "\n";
      exit(1);
    }

    spffl::polynomials::f2_poly_t f1 = f.gcd(h);
    spffl::polynomials::f2_poly_t f2 = f.gcd(hc);

#ifdef F2POLY_FACTOR_DEBUG
    std::cout << "h  = " << h << "  hc = " << hc << "\n";
    std::cout << "f1 = " << f1 << "  f2 = " << f2 << "\n";
#endif // F2POLY_FACTOR_DEBUG

    if ((f1 == 1) || (f2 == 1))
      continue;

    // The nullity of B-I is the number of irreducible
    // factors of f.  If the nullity is 2, we have a
    // pair of factors which are both irreducible and
    // so we don't need to recurse.
    if (dimker == 2) {
#ifdef F2POLY_FACTOR_DEBUG
      std::cout << "dimker=2 insert " << f1 << ", " << f2 << "\n";
#endif
      rfinfo.insert_factor(f1);
      rfinfo.insert_factor(f2);
    } else if (!recurse) {
#ifdef F2POLY_FACTOR_DEBUG
      std::cout << "dimker=2 insert " << f1 << ", " << f2 << "\n";
#endif
      rfinfo.insert_factor(f1);
      rfinfo.insert_factor(f2);
    } else {
      f2_poly_pre_berlekamp(f1, rfinfo, recurse);
      f2_poly_pre_berlekamp(f2, rfinfo, recurse);
    }
    return;
  }
  std::cerr << "Coding error: file " << __FILE__ << " line " << __LINE__
            << "\n";
  exit(1);
}

// ----------------------------------------------------------------
spffl::polynomials::f2_poly_t f2_poly_from_vector(
#ifdef USE_BIT_MATRIX
    spffl::bits::bit_vector_t &v,
#else
    tvector<spffl::bits::bit_t> &v,
#endif
    int n) {
  spffl::polynomials::f2_poly_t f(0);
  for (int i = 0; i < n; i++)
    if (v.get(n - 1 - i) == 1)
      f.set_bit(i);
  return f;
}

//// ----------------------------------------------------------------
//// Given the prime factorization p1^m1 ... pk^mk of n, how to enumerate all
//// factors of n?
////
//// Example 72 = 2^3 * 3^2.  Exponent on 2 is one of 0, 1, 2, 3.  Exponent on
//// 3 is one of 0, 1, 2.  Number of possibilities:  product over i of (mi + 1).
//// Factors are:
////
////	2^0 3^0    1
////	2^0 3^1    3
////	2^0 3^2    9
////	2^1 3^0    2
////	2^1 3^1    6
////	2^1 3^2   18
////	2^2 3^0    4
////	2^2 3^1   12
////	2^2 3^2   36
////	2^3 3^0    8
////	2^3 3^1   24
////	2^3 3^2   72
//
// unsigned f2_poly_num_divisors(
//	f2_poly_factor_info_t * pfinfo)
//{
//	unsigned rv;
//	int i;
//
//	if ((pfinfo->num_distinct < 0)
//		|| (pfinfo->num_distinct > F2POLY_MAX_NUM_FACTORS))
//	{
//		fprintf(stderr, "f2_poly_num_divisors:  num distinct (%d) "
//			"out of bounds 0-%d\n",
//			pfinfo->num_distinct, F2POLY_MAX_NUM_FACTORS);
//		exit(1);
//	}
//
//	rv = 1;
//	for (i = 0; i < pfinfo->num_distinct; i++)
//		rv *= pfinfo->factor_counts[i].count + 1;
//	return rv;
//}

//// ----------------------------------------------------------------
//// See comments to the above.  k is treated as a multibase representation
//// over the bases mi+1.
//
// spffl::polynomials::f2_poly_t f2_poly_kth_divisor(
//	f2_poly_factor_info_t * pfinfo,
//	unsigned k)
//{
//	spffl::polynomials::f2_poly_t rv;
//	spffl::polynomials::f2_poly_t fp;
//	int i;
//	unsigned base;
//	unsigned power;
//
//	rv = f2_poly_from_base_rep(1);
//	for (i = 0; i < pfinfo->num_distinct; i++) {
//		base = pfinfo->factor_counts[i].count + 1;
//		power = k % base;
//		k = k / base;
//
//		fp = f2_poly_power(&pfinfo->factor_counts[i].f, power);
//		rv = f2_poly_mul(&rv, &fp);
//	}
//	return rv;
//}

//// ----------------------------------------------------------------
//// The caller must free the return value.
//
// spffl::polynomials::f2_poly_t * f2_poly_get_all_divisors(
//	spffl::polynomials::f2_poly_t * pr,
//	unsigned * pnum_divisors)
//{
//	f2_poly_factor_info_t finfo;
//	unsigned nf, k;
//	spffl::polynomials::f2_poly_t * all_divisors;
//
//	f2_poly_factor(pr, &finfo);
//	nf = f2_poly_num_divisors(&finfo);
//	*pnum_divisors = nf;
//
//	all_divisors = (spffl::polynomials::f2_poly_t *)malloc_check(nf *
// sizeof(spffl::polynomials::f2_poly_t)); 	for (k = 0; k < nf; k++) {
//		all_divisors[k] = f2_poly_kth_divisor(&finfo, k);
//	}
//	qsort(all_divisors, nf, sizeof(spffl::polynomials::f2_poly_t),
// f2_poly_qcmp);
//
//	return all_divisors;
//}

// ----------------------------------------------------------------
bool f2_poly_is_irreducible(spffl::polynomials::f2_poly_t f) {
  tfacinfo<spffl::polynomials::f2_poly_t> finfo;

  int d = f.find_degree();
  if (d == 0)
    return false;
  if (d == 1)
    return true;

  f2_poly_pre_berlekamp(f, finfo, false);

#ifdef FPPOLY_FACTOR_DEBUG
  std::cout << "f2pirr: input = " << f << "\n";
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
spffl::polynomials::f2_poly_t f2_poly_find_irreducible(int degree) {
  spffl::polynomials::f2_poly_t rv(0);
  rv.set_bit(degree);
  rv.set_bit(0);

  if (degree < 1) {
    std::cout << "f2_poly_find_irreducible:  degree must be positive; got "
              << degree << ".\n";
    exit(1);
  }

  while (rv.find_degree() == degree) {
    if (f2_poly_is_irreducible(rv))
      return rv;
    rv.increment();
    rv.increment();
  }

  // There are irreducibles of all positive degrees, so it is
  // an error if we failed to find one.
  std::cout << "f2_poly_find_irreducible:  coding error.\n";
  exit(1);

  return rv;
}

// ----------------------------------------------------------------
spffl::polynomials::f2_poly_t f2_poly_random_irreducible(int degree) {
  spffl::polynomials::f2_poly_t rv;

  if (degree < 1) {
    std::cout << "f2_poly_random_irreducible:  degree must be positive; got "
              << degree << ".\n";
    exit(1);
  }

  for (;;) {
    rv = spffl::random::f2_poly_random(degree);
    rv.set_bit(0);
    if (f2_poly_is_irreducible(rv))
      return rv;
  }
}

} // namespace spffl::factorization
