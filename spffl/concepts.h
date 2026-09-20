// ================================================================
// C++20 concept sketch for spffl refactoring.
// See REFACTORING_PROPOSAL.md. No dependency on spffl types.
// ================================================================

#ifndef SPFFL_CONCEPTS_H
#define SPFFL_CONCEPTS_H

#include <concepts>
#include <iostream>
#include <vector>

namespace spffl::concepts {

// ---------------------------------------------------------------------------
// Ring element (coefficient type for polynomials, element type for vectors)
// ---------------------------------------------------------------------------

template <typename T>
concept Copyable = std::copy_constructible<T> && std::copyable<T>;

template <typename T>
concept Ring_element = Copyable<T> && requires(T const &a, T const &b, T &mut_a) {
  { a + b } -> std::convertible_to<T>;
  { a - b } -> std::convertible_to<T>;
  { a * b } -> std::convertible_to<T>;
  { -a } -> std::convertible_to<T>;
  mut_a += b;
  mut_a -= b;
  mut_a *= b;
  { a == b } -> std::convertible_to<bool>;
  { a != b } -> std::convertible_to<bool>;
  { a - a } -> std::convertible_to<T>; // zero
};

template <typename T>
concept Ring_element_with_io =
  Ring_element<T> && requires(T const &a, std::ostream &os, std::istream &is) {
    { os << a } -> std::same_as<std::ostream &>;
    { is >> std::declval<T &>() } -> std::same_as<std::istream &>;
  };

// Optional: coefficient type that supports multiplicative inverse (for division)
template <typename T>
concept Field_element = Ring_element<T> && requires(T const &a, T const &b, T &rinv) {
  { a / b } -> std::convertible_to<T>;
  { a.recip(rinv) } -> std::convertible_to<bool>; // true if invertible
};

// ---------------------------------------------------------------------------
// Euclidean domain (integers or polynomials: quot/rem + gcd)
// ---------------------------------------------------------------------------

template <typename E>
concept Euclidean_domain = Ring_element<E> && requires(E const &a, E const &b, E &q, E &r) {
  { a.quot_and_rem(b, q, r) } -> std::same_as<void>;
  { a.gcd(b) } -> std::convertible_to<E>;
};

// Extended GCD (for inverses in residue rings)
template <typename E>
concept Euclidean_domain_with_ext_gcd =
  Euclidean_domain<E> && requires(E const &a, E const &b, E &m, E &n) {
    { a.ext_gcd(b, m, n) } -> std::convertible_to<E>;
  };

// Free-function form (for ADL / overload use with built-in int, etc.)
template <typename E>
concept Has_gcd_free = Ring_element<E> && requires(E const &a, E const &b) {
  { gcd(a, b) } -> std::convertible_to<E>;
};

// ---------------------------------------------------------------------------
// Polynomial ring element (unified interface for polynomial_of<C> and f2_poly_t)
// ---------------------------------------------------------------------------

template <typename P>
concept Polynomial_ring_element =
  Euclidean_domain<P> && requires(P const &p, P const &q, P &qout, P &rout, int n) {
    { p.find_degree() } -> std::convertible_to<int>;
    { p.exp(n) } -> std::convertible_to<P>;
    { p.deriv() } -> std::convertible_to<P>;
    p.quot_and_rem(q, qout, rout);
    { p.gcd(q) } -> std::convertible_to<P>;
  };

template <typename P>
concept Polynomial_with_ext_gcd =
  Polynomial_ring_element<P> && requires(P const &a, P const &b, P &m, P &n) {
    { a.ext_gcd(b, m, n) } -> std::convertible_to<P>;
  };

// ---------------------------------------------------------------------------
// Residue / quotient ring (Z/mZ, F2[x]/(m), Fp[x]/(m), ...)
// ---------------------------------------------------------------------------

template <typename R>
concept Residue_ring = Ring_element<R> && requires(R const &a) {
  { a.get_residue() };
  { a.get_modulus() };
};

template <typename R>
concept Residue_ring_with_recip = Residue_ring<R> && requires(R const &a, R &rinv) {
  { a.recip(rinv) } -> std::convertible_to<bool>;
  { a.exp(std::declval<int>()) } -> std::convertible_to<R>;
};

// ---------------------------------------------------------------------------
// Vector over ring element (STL-based or tvector-like)
// ---------------------------------------------------------------------------

template <typename V, typename T>
concept Vector_over = Ring_element<T> && requires(V const &v, V &mut_v, int i, T const &s) {
  { v[i] } -> std::convertible_to<T const &>;
  { mut_v[i] } -> std::convertible_to<T &>;
  { v.get_num_elements() } -> std::convertible_to<int>;
  { v + v } -> std::convertible_to<V>;
  { v - v } -> std::convertible_to<V>;
  { v * s } -> std::convertible_to<V>;
  { -v } -> std::convertible_to<V>;
};

// Optional: dot product for inner product spaces
template <typename V, typename T>
concept Vector_with_dot = Vector_over<V, T> && requires(V const &u, V const &v) {
  { u.dot(v) } -> std::convertible_to<T>;
};

// ---------------------------------------------------------------------------
// Matrix over ring element (STL-based or tmatrix-like)
// ---------------------------------------------------------------------------

template <typename M, typename T>
concept Matrix_over = Ring_element<T> && requires(M const &A, M const &B, std::size_t i) {
  { A[i] }; // row: indexable (vector-like)
  { A.get_num_rows() } -> std::convertible_to<int>;
  { A.get_num_cols() } -> std::convertible_to<int>;
  { A + B } -> std::convertible_to<M>;
  { A - B } -> std::convertible_to<M>;
  { A * B } -> std::convertible_to<M>;
  { -A } -> std::convertible_to<M>;
};

// Matrix-vector product
template <typename M, typename V, typename T>
concept Matrix_vector_product =
  Matrix_over<M, T> && Vector_over<V, T> && requires(M const &A, V const &x) {
    { A * x } -> std::convertible_to<V>;
  };

// ---------------------------------------------------------------------------
// Bit vector / matrix (bit-packed; not matrix-of-byte)
// ---------------------------------------------------------------------------

template <typename V>
concept Bit_vector_like = requires(V const &v, V &mut_v, std::size_t i, int b) {
  { v.get(i) };
  mut_v.set(i, b);
  { v.get_num_elements() } -> std::convertible_to<int>;
  { v + v } -> std::convertible_to<V>;
  { v - v } -> std::convertible_to<V>;
};

template <typename M>
concept Bit_matrix_like = requires(M const &A, std::size_t i) {
  A[i]; // row access (Bit_vector_like)
  { A.get_num_rows() } -> std::convertible_to<int>;
  { A.get_num_cols() } -> std::convertible_to<int>;
  { A + A } -> std::convertible_to<M>;
  { A * A } -> std::convertible_to<M>;
};

// ---------------------------------------------------------------------------
// Helpers: detect optional operations (e.g. characteristic for polynomials)
// ---------------------------------------------------------------------------

template <typename T, typename = void> struct has_get_characteristic : std::false_type {};

template <typename T>
struct has_get_characteristic<T,
  std::void_t<decltype(std::declval<T const &>().get_characteristic())>> : std::true_type {};

template <typename T>
inline constexpr bool has_get_characteristic_v = has_get_characteristic<T>::value;

template <typename T, typename = void> struct has_get_modulus : std::false_type {};

template <typename T>
struct has_get_modulus<T, std::void_t<decltype(std::declval<T const &>().get_modulus())>>
    : std::true_type {};

template <typename T> inline constexpr bool has_get_modulus_v = has_get_modulus<T>::value;

} // namespace spffl::concepts

#endif // SPFFL_CONCEPTS_H
