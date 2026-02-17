// ================================================================
// I/O and from_string for fp_poly_t and fp_polymod_t.
// Format: comma-separated coefficients, leading (highest degree) first.
// e.g. "1,0,1" = x^2 + 1.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_FP_POLY_IO_HPP
#define SPFFL_POLYNOMIALS_FP_POLY_IO_HPP

#include "spffl/polynomials/aliases.hpp"
#include "spffl/polynomials/fp_polymod_t.hpp"
#include "spffl/intmath/intmod_t.h"
#include <string>
#include <sstream>
#include <optional>
#include <cctype>

namespace spffl::polynomials {

/// Parses comma-separated coefficients (leading first), each reduced mod p.
/// Returns nullopt on parse error or empty input.
inline std::optional<fp_poly_t> fp_poly_from_string(const std::string& s, int p) {
  if (p <= 0) {
    return std::nullopt;
  }
  std::vector<spffl::intmath::intmod_t> coeffs;
  std::istringstream iss(s);
  std::string token;
  while (std::getline(iss, token, ',')) {
    // trim whitespace
    while (!token.empty() && std::isspace(static_cast<unsigned char>(token.front()))) {
      token.erase(0, 1);
    }
    while (!token.empty() && std::isspace(static_cast<unsigned char>(token.back()))) {
      token.pop_back();
    }
    if (token.empty()) {
      return std::nullopt;
    }
    int r;
    std::istringstream tok(token);
    if (!(tok >> r) || tok.peek() != std::char_traits<char>::eof()) {
      return std::nullopt;
    }
    coeffs.push_back(spffl::intmath::intmod_t(r, p));
  }
  if (coeffs.empty()) {
    return std::nullopt;
  }
  // coeffs[0] = leading, coeffs.back() = constant. polynomial_of stores [c0, c1, ...].
  std::vector<spffl::intmath::intmod_t> storage(coeffs.rbegin(), coeffs.rend());
  return fp_poly_t(std::move(storage));
}

/// Legacy compat: fill poly from string; return true on success.
inline bool fp_poly_from_string_into(const std::string& s, int p, fp_poly_t& poly) {
  auto opt = fp_poly_from_string(s, p);
  if (!opt) return false;
  poly = std::move(*opt);
  return true;
}

/// Legacy compat: polynomial from base-m expansion of integer b (lowest digit = constant coeff).
inline fp_poly_t fp_poly_from_base_rep(int b, int m) {
  if (m <= 0) return fp_poly_t();
  std::vector<spffl::intmath::intmod_t> coeffs;
  if (b == 0) {
    coeffs.push_back(spffl::intmath::intmod_t(0, m));
    return fp_poly_t(std::move(coeffs));
  }
  while (b) {
    coeffs.push_back(spffl::intmath::intmod_t(b % m, m));
    b /= m;
  }
  return fp_poly_t(std::move(coeffs));
}

/// Reads from stream: first the modulus (int), then comma-separated coefficients.
/// Format: "p c0,c1,...,cn" e.g. "7 1,0,1".
inline std::istream& operator>>(std::istream& is, fp_poly_t& poly) {
  int p;
  if (!(is >> p)) {
    return is;
  }
  std::string rest;
  if (!std::getline(is, rest)) {
    return is;
  }
  auto opt = fp_poly_from_string(rest, p);
  if (!opt) {
    is.setstate(std::ios::failbit);
    return is;
  }
  poly = std::move(*opt);
  return is;
}

// ---------------------------------------------------------------------------
// fp_polymod_t: from_string and operator>>
// ---------------------------------------------------------------------------

/// Parses residue polynomial with comma-separated coefficients (leading first).
/// Uses the same prime as the modulus; returns nullopt on parse error.
inline std::optional<fp_polymod_t> fp_polymod_from_string(
    const std::string& s, const fp_poly_t& modulus) {
  if (modulus.is_zero()) {
    return std::nullopt;
  }
  int p = modulus.get_coeff(0).get_modulus();
  auto opt = fp_poly_from_string(s, p);
  if (!opt) {
    return std::nullopt;
  }
  return fp_polymod_t(std::move(*opt), modulus);
}

/// Reads from stream: prime p, then modulus coeffs, then residue coeffs.
/// Format: "p  modulus_coeffs  residue_coeffs" on one line, e.g. "7 1,0,1 0,1" for F7[x]/(x^2+1), residue x.
inline std::istream& operator>>(std::istream& is, fp_polymod_t& out) {
  int p;
  if (!(is >> p)) {
    return is;
  }
  std::string rest;
  if (!std::getline(is, rest)) {
    return is;
  }
  // Trim leading space from rest, then split on first space into modulus and residue parts
  auto start = rest.find_first_not_of(" \t");
  if (start == std::string::npos) {
    is.setstate(std::ios::failbit);
    return is;
  }
  rest = rest.substr(start);
  auto mid = rest.find(' ');
  if (mid == std::string::npos) {
    is.setstate(std::ios::failbit);
    return is;
  }
  std::string line_mod = rest.substr(0, mid);
  std::string line_res = rest.substr(mid + 1);
  auto res_start = line_res.find_first_not_of(" \t");
  if (res_start != std::string::npos) {
    line_res = line_res.substr(res_start);
  }
  auto opt_mod = fp_poly_from_string(line_mod, p);
  auto opt_res = fp_poly_from_string(line_res, p);
  if (!opt_mod || !opt_res) {
    is.setstate(std::ios::failbit);
    return is;
  }
  out = fp_polymod_t(std::move(*opt_res), *opt_mod);
  return is;
}

/// Legacy compat: fill out from string with given modulus; return true on success.
inline bool fp_polymod_from_string_into(
    const std::string& s, const fp_poly_t& modulus, fp_polymod_t& out) {
  auto opt = fp_polymod_from_string(s, modulus);
  if (!opt) return false;
  out = std::move(*opt);
  return true;
}

}  // namespace spffl::polynomials

#endif  // SPFFL_POLYNOMIALS_FP_POLY_IO_HPP
