// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// Template class for multivariate rational functions.

#ifndef TMVRAT_H
#define TMVRAT_H

#include "spffl/tmvpoly.h"

template <class ktype> class tmvrat;
template <class ktype> static std::ostream &operator<<(std::ostream &os, const tmvrat<ktype> &rat);

// ================================================================
template <class ktype> class tmvrat {
  private:
  tmvpoly<ktype> numer;
  tmvpoly<ktype> denom;

  // ----------------------------------------------------------------
  public:
  tmvrat(void) {}

  // ----------------------------------------------------------------
  tmvrat(tmvpoly<ktype> n, tmvpoly<ktype> d) {
    this->numer = n;
    this->denom = d;
    this->check_equal_nvars();
  }

  // ----------------------------------------------------------------
  tmvrat(const tmvrat &that) {
    this->numer = that.numer;
    this->denom = that.denom;
  }

  // ----------------------------------------------------------------
  tmvrat &operator=(const tmvrat &that) {
    this->numer = that.numer;
    this->denom = that.denom;
    return *this;
  }

  // ----------------------------------------------------------------
  ~tmvrat(void) {}

  // ----------------------------------------------------------------
  // tmvrat operator+(tmvrat that)
  //{
  //}

  // ----------------------------------------------------------------
  // Unary negation
  // tmvrat operator-(void)
  //{
  //}

  // ----------------------------------------------------------------
  // tmvrat operator-(tmvrat that)
  //{
  //}

  // ----------------------------------------------------------------
  // tmvrat operator*(tmvrat that)
  //{
  //}

  // tmvrat operator+=(tmvrat that)
  //{
  //	*this = *this + that;
  //	return *this;
  // }
  // tmvrat operator-=(tmvrat that)
  //{
  //	*this = *this - that;
  //	return *this;
  // }
  // tmvrat operator*=(tmvrat that)
  //{
  //	*this = *this * that;
  //	return *this;
  // }

  // ----------------------------------------------------------------
  // For input, please use tmvratscan.h.

  friend std::ostream &operator<< <>(std::ostream &os, const tmvrat &rat);

  // ----------------------------------------------------------------
  void tex_or_pretty_print(std::ostream &os, bool do_tex) {
    this->numer.tex_or_pretty_print(os, do_tex);
    os << "/";
    this->denom.tex_or_pretty_print(os, do_tex);
  }

  void tex_print(std::ostream &os) {
    this->numer.tex_print(os);
    os << "/";
    this->denom.tex_print(os);
  }
  void pretty_print(std::ostream &os) {
    this->numer.pretty_print(os);
    os << "/";
    this->denom.pretty_print(os);
  }

  // ----------------------------------------------------------------
  int get_nvars(void) {
    int nnv = this->numer.get_nvars();
    int dnv = this->denom.get_nvars();
    if (nnv != dnv) {
      exit(1);
    }
    return nnv;
  }

  // ----------------------------------------------------------------
  ktype eval(ktype c0) { return this->numer.eval(c0) / this->denom.eval(c0); }

  // ----------------------------------------------------------------
  ktype eval(ktype c0, ktype c1) { return this->numer.eval(c0, c1) / this->denom.eval(c0, c1); }

  // ----------------------------------------------------------------
  ktype eval(ktype c0, ktype c1, ktype c2) {
    return this->numer.eval(c0, c1, c2) / this->denom.eval(c0, c1, c2);
  }

  // ----------------------------------------------------------------
  ktype eval(tvector<ktype> c) { return this->numer.eval(c) / this->denom.eval(c); }

  // ----------------------------------------------------------------
  // The matrix argument is to be thought of as an array of vectors.
  tvector<ktype> eval(tmatrix<ktype> &m) {
    int n = m.get_num_rows();
    tvector<ktype> rv(n);
    for (int i = 0; i < n; i++)
      rv[i] = this->eval(m[i]);
    return rv;
  }

  // ----------------------------------------------------------------
  tmvrat homogenize(void) {
    tmvpoly<ktype> hnumer = this->numer.homogenize();
    tmvpoly<ktype> hdenom = this->denom.homogenize();
    tmvrat rv(hnumer, hdenom);
    return rv;
  }

  // ----------------------------------------------------------------
  private:
  void check_equal_nvars(void) {
    int nnv = this->numer.get_nvars();
    int dnv = this->denom.get_nvars();
    if (nnv != dnv) {
      std::cerr << "tmvrat:  numerator #vars (" << nnv << ") != denominator #vars (" << dnv
                << ").\n";
      exit(1);
    }
  }
};

// ----------------------------------------------------------------
template <class element_type>
static std::ostream &operator<<(std::ostream &os, const tmvrat<element_type> &rat) {
  os << rat.numer << "/" << rat.denom;
  return os;
}

#endif // TMVRAT_H
