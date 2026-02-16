// ================================================================
// I/O and from_string for fp_poly_t (polynomial_of<intmod_t>).
// Format: comma-separated coefficients, leading (highest degree) first.
// e.g. "1,0,1" = x^2 + 1.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_FP_POLY_IO_HPP
#define SPFFL_POLYNOMIALS_FP_POLY_IO_HPP

#include "spffl/polynomials/aliases.hpp"
#include "spffl/intmath/intmod_t.hpp"
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

}  // namespace spffl::polynomials

#endif  // SPFFL_POLYNOMIALS_FP_POLY_IO_HPP
