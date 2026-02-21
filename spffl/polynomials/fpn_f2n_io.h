// ================================================================
// I/O for f2n_poly_t and fpn_poly_t: explicit modulus, no hidden state.
// Use from_string(s, m) or read_f2n_poly(is, m) instead of operator>>.
// ================================================================

#ifndef SPFFL_POLYNOMIALS_FPN_F2N_IO_H
#define SPFFL_POLYNOMIALS_FPN_F2N_IO_H

#include "spffl/polynomials/fpn_f2n_aliases.h"
#include "spffl/polynomials/fp_poly_io.h"
#include "spffl/base/tokenize.h"
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace spffl::polynomials {

// ---------------------------------------------------------------------------
// f2n_poly_t: from_string and read (coefficients in "high:...:low" format).
// ---------------------------------------------------------------------------

inline std::optional<f2n_poly_t> f2n_poly_from_string(
    const std::string& s, const f2_poly_t& m) {
  int num_colons = 0;
  for (char c : s) {
    if (c == ':') ++num_colons;
  }
  std::vector<char> buf(s.begin(), s.end());
  buf.push_back('\0');
  std::vector<char*> argv(static_cast<std::size_t>(num_colons + 1));
  int argc = spffl::base::tokenize(buf.data(), ":", argv.data(),
                                   static_cast<int>(argv.size()));
  if (argc < 1) return std::nullopt;

  std::vector<f2_polymod_t> coeffs(static_cast<std::size_t>(argc));
  for (int i = 0; i < argc; ++i) {
    f2_poly_t r;
    std::istringstream iss(argv[static_cast<std::size_t>(i)]);
    iss >> r;
    if (iss.fail()) return std::nullopt;
    // argv[0] = high degree, so coefficient of x^i is argv[argc-1-i]
    coeffs[static_cast<std::size_t>(i)] =
        f2_polymod_t(r, m);  // i runs 0..argc-1, we want coeff[i] = argv[argc-1-i]
  }
  // coeffs[i] currently holds argv[i]. We need poly coeff j = argv[argc-1-j], so swap.
  std::vector<f2_polymod_t> out_coeffs(static_cast<std::size_t>(argc));
  for (int i = 0; i < argc; ++i)
    out_coeffs[static_cast<std::size_t>(argc - 1 - i)] = coeffs[static_cast<std::size_t>(i)];
  return f2n_poly_t(std::move(out_coeffs));
}

inline std::optional<f2n_poly_t> read_f2n_poly(std::istream& is, const f2_poly_t& m) {
  std::string line;
  if (!std::getline(is, line)) return std::nullopt;
  return f2n_poly_from_string(line, m);
}

inline std::optional<f2n_poly_t> read_f2n_poly(std::istringstream& iss, const f2_poly_t& m) {
  std::string line;
  if (!std::getline(iss, line)) return std::nullopt;
  return f2n_poly_from_string(line, m);
}

/// CLI/stream read using context (zero) for modulus. Used by cmd_line_parse/tvector.
inline void read_element(std::istringstream& iss, const f2n_poly_t& zero, f2n_poly_t& out) {
  f2_poly_t m = (zero.find_degree() >= 0 && zero.get_coeff(0).get_modulus().find_degree() >= 0)
                    ? zero.get_coeff(0).get_modulus()
                    : f2_poly_t(1);  // fallback for default-constructed zero
  auto opt = read_f2n_poly(iss, m);
  if (!opt) {
    iss.setstate(std::ios::failbit);
    return;
  }
  out = std::move(*opt);
}

// ---------------------------------------------------------------------------
// f2n_polymod_t: parse polynomial then reduce mod modulus.
// ---------------------------------------------------------------------------
inline std::optional<f2n_polymod_t> f2n_polymod_from_string(
    const std::string& s, const f2n_poly_t& modulus) {
  f2_poly_t im = modulus.find_degree() >= 0 ? modulus.get_coeff(0).get_modulus() : f2_poly_t(1);
  auto opt = f2n_poly_from_string(s, im);
  if (!opt) return std::nullopt;
  return f2n_polymod_t(std::move(*opt), modulus);
}

/// CLI/stream read for f2n_polymod_t (context = zero, get modulus from zero.get_modulus()).
inline void read_element(std::istringstream& iss, const f2n_polymod_t& zero, f2n_polymod_t& out) {
  f2n_poly_t om = zero.get_modulus();
  std::string line;
  if (!std::getline(iss, line)) {
    iss.setstate(std::ios::failbit);
    return;
  }
  auto opt = f2n_polymod_from_string(line, om);
  if (!opt) {
    iss.setstate(std::ios::failbit);
    return;
  }
  out = std::move(*opt);
}

// ---------------------------------------------------------------------------
// fpn_poly_t: from_string and read (same "high:...:low" format).
// ---------------------------------------------------------------------------

inline std::optional<fpn_poly_t> fpn_poly_from_string(
    const std::string& s, const fp_poly_t& m) {
  int num_colons = 0;
  for (char c : s) {
    if (c == ':') ++num_colons;
  }
  std::vector<char> buf(s.begin(), s.end());
  buf.push_back('\0');
  std::vector<char*> argv(static_cast<std::size_t>(num_colons + 1));
  int argc = spffl::base::tokenize(buf.data(), ":", argv.data(),
                                   static_cast<int>(argv.size()));
  if (argc < 1) return std::nullopt;

  int p = m.get_coeff(0).get_modulus();
  std::vector<fp_polymod_t> coeffs(static_cast<std::size_t>(argc));
  for (int i = 0; i < argc; ++i) {
    fp_poly_t r(spffl::intmath::intmod_t(0, p));
    std::istringstream iss(argv[static_cast<std::size_t>(i)]);
    iss >> r;
    if (iss.fail()) return std::nullopt;
    coeffs[static_cast<std::size_t>(i)] = fp_polymod_t(r, m);
  }
  std::vector<fp_polymod_t> out_coeffs(static_cast<std::size_t>(argc));
  for (int i = 0; i < argc; ++i)
    out_coeffs[static_cast<std::size_t>(argc - 1 - i)] = coeffs[static_cast<std::size_t>(i)];
  return fpn_poly_t(std::move(out_coeffs));
}

inline std::optional<fpn_poly_t> read_fpn_poly(std::istream& is, const fp_poly_t& m) {
  std::string line;
  if (!std::getline(is, line)) return std::nullopt;
  return fpn_poly_from_string(line, m);
}

inline std::optional<fpn_poly_t> read_fpn_poly(std::istringstream& iss, const fp_poly_t& m) {
  std::string line;
  if (!std::getline(iss, line)) return std::nullopt;
  return fpn_poly_from_string(line, m);
}

/// CLI/stream read for fpn_poly_t (context = zero for modulus).
inline void read_element(std::istringstream& iss, const fpn_poly_t& zero, fpn_poly_t& out) {
  fp_poly_t m = (zero.find_degree() >= 0) ? zero.get_coeff(0).get_modulus() : fp_poly_t();
  auto opt = read_fpn_poly(iss, m);
  if (!opt) {
    iss.setstate(std::ios::failbit);
    return;
  }
  out = std::move(*opt);
}

// ---------------------------------------------------------------------------
// fpn_polymod_t: parse polynomial then reduce mod modulus.
// ---------------------------------------------------------------------------
inline std::optional<fpn_polymod_t> fpn_polymod_from_string(
    const std::string& s, const fpn_poly_t& modulus) {
  fp_poly_t im = modulus.find_degree() >= 0 ? modulus.get_coeff(0).get_modulus() : fp_poly_t();
  auto opt = fpn_poly_from_string(s, im);
  if (!opt) return std::nullopt;
  return fpn_polymod_t(std::move(*opt), modulus);
}

/// CLI/stream read for fpn_polymod_t.
inline void read_element(std::istringstream& iss, const fpn_polymod_t& zero, fpn_polymod_t& out) {
  fpn_poly_t om = zero.get_modulus();
  std::string line;
  if (!std::getline(iss, line)) {
    iss.setstate(std::ios::failbit);
    return;
  }
  auto opt = fpn_polymod_from_string(line, om);
  if (!opt) {
    iss.setstate(std::ios::failbit);
    return;
  }
  out = std::move(*opt);
}

}  // namespace spffl::polynomials

#endif  // SPFFL_POLYNOMIALS_FPN_F2N_IO_H
