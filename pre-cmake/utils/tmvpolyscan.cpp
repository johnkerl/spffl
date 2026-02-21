#include "spffl/tmvpolyscan.h"

// ----------------------------------------------------------------
// Expected format matches that from tmvpoly's ostream operator.
// E.g. 2 x^3 y + 4 y z is:
//
//   "2.3.1.0+4.0.1.1"

int tmvpoly_f2_polymod_from_string(tmvpoly<f2_polymod_t> &f, const char *string, f2_poly_t m) {
  f = tmvpoly<f2_polymod_t>(); // Initialize to the zero polynomial.

  char *cpstring = strdup(string);
  int nmonoms = count_tokens((char *)string, "+");
  char **monomv = new char *[nmonoms];
  (void)tokenize(cpstring, "+", monomv, nmonoms);
  int nvars0 = 0;

  for (int i = 0; i < nmonoms; i++) {

    int cnvars = count_tokens(monomv[i], ".");
    int nvars = cnvars - 1;
    if (i == 0) {
      nvars0 = nvars;
    } else {
      if (nvars != nvars0) {
        std::cerr << "tmvpoly_f2_polymod_from_string: all "
                     "monomials must have same # variables.\n";
        free(cpstring);
        delete[] monomv;
        return 0;
      }
    }

    if (nvars < 1) {
      std::cerr << "tmvpoly_f2_polymod_from_string: need >= 1 variable in \"" << monomv[i]
                << "\".\n";
      free(cpstring);
      delete[] monomv;
      return 0;
    }

    char **cvarv = new char *[cnvars];
    int *expts = new int[nvars];
    (void)tokenize(monomv[i], ".", cvarv, cnvars);

    f2_polymod_t coeff;
    if (!coeff.from_string(cvarv[0], m)) {
      std::cerr << "tmvpoly_f2_polymod_from_string: couldn't parse \"" << cvarv[0]
                << "\" as coefficient.\n";
      free(cpstring);
      delete[] monomv;
      delete[] cvarv;
      delete[] expts;
      return 0;
    }

    for (int j = 0; j < nvars; j++) {
      if (sscanf(cvarv[j + 1], "%d", &expts[j]) != 1) {
        std::cerr << "tmvpoly_f2_polymod_from_string: couldn't parse \"" << cvarv[j + 1]
                  << "\" as exponent.\n";
        free(cpstring);
        delete[] monomv;
        delete[] cvarv;
        delete[] expts;
        return 0;
      }
    }
    tmvpoly<f2_polymod_t> monom(coeff, expts, nvars);
    f += monom;
    delete[] cvarv;
    delete[] expts;
  }

  free(cpstring);
  delete[] monomv;
  return 1;
}

// ----------------------------------------------------------------
// Expected format matches that from tmvpoly's ostream operator.
// E.g. 2 x^3 y + 4 y z is:
//
//   "2.3.1.0+4.0.1.1"

int tmvpoly_fp_polymod_from_string(tmvpoly<fp_polymod_t> &f, const char *string, fp_poly_t m) {
  f = tmvpoly<fp_polymod_t>(); // Initialize to the zero polynomial.

  char *cpstring = strdup(string);
  int nmonoms = count_tokens((char *)string, "+");
  char **monomv = new char *[nmonoms];
  (void)tokenize(cpstring, "+", monomv, nmonoms);
  int nvars0 = 0;

  for (int i = 0; i < nmonoms; i++) {

    int cnvars = count_tokens(monomv[i], ".");
    int nvars = cnvars - 1;
    if (i == 0) {
      nvars0 = nvars;
    } else {
      if (nvars != nvars0) {
        std::cerr << "tmvpoly_fp_polymod_from_string: all "
                     "monomials must have same # variables.\n";
        free(cpstring);
        delete[] monomv;
        return 0;
      }
    }

    if (nvars < 1) {
      std::cerr << "tmvpoly_fp_polymod_from_string: need >= 1 variable in \"" << monomv[i]
                << "\".\n";
      free(cpstring);
      delete[] monomv;
      return 0;
    }

    char **cvarv = new char *[cnvars];
    int *expts = new int[nvars];
    (void)tokenize(monomv[i], ".", cvarv, cnvars);

    fp_polymod_t coeff;
    if (!coeff.from_string(cvarv[0], m)) {
      std::cerr << "tmvpoly_fp_polymod_from_string: couldn't parse \"" << cvarv[0]
                << "\" as coefficient.\n";
      free(cpstring);
      delete[] monomv;
      delete[] cvarv;
      delete[] expts;
      return 0;
    }

    for (int j = 0; j < nvars; j++) {
      if (sscanf(cvarv[j + 1], "%d", &expts[j]) != 1) {
        std::cerr << "tmvpoly_fp_polymod_from_string: couldn't parse \"" << cvarv[j + 1]
                  << "\" as exponent.\n";
        free(cpstring);
        delete[] monomv;
        delete[] cvarv;
        delete[] expts;
        return 0;
      }
    }
    tmvpoly<fp_polymod_t> monom(coeff, expts, nvars);
    f += monom;
    delete[] cvarv;
    delete[] expts;
  }

  free(cpstring);
  delete[] monomv;
  return 1;
}
