# Refactoring Proposal: Concepts and Unified Types

This document proposes a C++20 refactor of spffl to reduce duplication using concepts, a single “polynomial-of” template, Euclidean-domain abstraction, concept-based residue/quotient rings, and STL-based matrix/vector with a dedicated bit-packed matrix/vector.

---

## 1. Ring element concept (polynomial coefficients)

**Goal:** One concept that describes “usable as a polynomial coefficient” so a single polynomial implementation can be instantiated for different coefficient types.

**Concept: `Ring_element<C>`** (or `Coefficient_ring<C>`)

Requirements on `C`:

- **Ring ops:** `a + b`, `a - b`, `a * b`, `-a`, `a += b`, `a -= b`, `a *= b`
- **Zero/one:** Expressible via `a - a` (zero) and `a / a` for non-zero `a` (one), or optional: `C::zero(modulus_context?)`, `C::one(modulus_context?)` for stateful rings
- **Comparison:** `a == b`, `a != b`
- **Scalar scaling (optional):** For F2, `* int` (0/1); for Fp, `* intmod_t`; for Fq, `* f2_polymod_t` / `fp_polymod_t` — can be a separate concept or optional ops
- **I/O:** `ostream << c`, `istream >> c` (with modulus/context set elsewhere for mod types)
- **Division (for fields):** `a / b`, `recip(rinv)` for inversion where applicable

**Concrete models:**

- `spffl::bits::bit_t` (F2)
- `spffl::intmath::intmod_t` (Fp)
- `spffl::polynomials::f2_polymod_t` (F2^n)
- `spffl::polynomials::fp_polymod_t` (Fp^n)
- `spffl::intmath::intrat_t` (Q) — for q_poly_t

**Note:** No need to require “polynomial coefficient” to be a field; only coefficient ring. Division in the *polynomial* ring is implemented via `quot_and_rem` and leading-coefficient inverse when the coefficient ring is a field.

---

## 2. Polynomial-of\<Coeff\> class

**Goal:** Replace the duplicated logic in `fp_poly_t`, `f2n_poly_t`, `fpn_poly_t` (and optionally `q_poly_t`) with one template class.

**Design:**

- **Class:** `polynomial_of<Coeff>` in namespace `spffl::polynomials`, with `Coeff` constrained by the ring-element concept.
- **Storage:** `std::vector<Coeff> coeffs_` (or equivalent), degree = `coeffs_.size() - 1` with implicit leading zeros trimmed. This matches the current “array of coefficients” representation used by fp/f2n/fpn.
- **API:** Same as current polynomial types:
  - Constructors: default, from one/two/three coeffs, from string (with context for modulus), `from_base_rep` where meaningful
  - Arithmetic: `+`, `-`, `*`, `/`, `%`, `+=`, `-=`, `*=`, `/=`, `%=`
  - `quot_and_rem`, `gcd`, `ext_gcd`, `exp`, `deriv`
  - `find_degree`, `get_coeff`, `set_coeff`
  - Comparison and ordering (for sorting/loops)
  - I/O and `from_string` (with context passed in for mod types)
- **Free function:** `gcd(const polynomial_of<C>&, const polynomial_of<C>&)` for template use (as today).

**Type aliases (for compatibility):**

```cpp
using fp_poly_t   = polynomial_of<spffl::intmath::intmod_t>;
using f2n_poly_t  = polynomial_of<spffl::polynomials::f2_polymod_t>;
using fpn_poly_t  = polynomial_of<spffl::polynomials::fp_polymod_t>;
using q_poly_t    = polynomial_of<spffl::intmath::intrat_t>;  // if desired
```

**Characteristic / modulus:** For prime subfield and printing, the coefficient type carries context (e.g. `intmod_t::get_modulus()`, `f2_polymod_t::get_modulus()`). The polynomial can expose `get_characteristic()` by delegating to `Coeff` when that’s defined (e.g. via a trait or optional concept).

---

## 3. Euclidean domain concept (for GCD / residue rings)

**Goal:** Unify “things that support quotient/remainder and GCD” so one set of algorithms and residue-ring templates works for integers and for polynomials.

**Concept: `Euclidean_domain<E>`**

Requirements:

- **Ring:** `E` models the ring concept (add, subtract, multiply, zero, one, equality).
- **Division with remainder:**  
  `quot_and_rem(a, b, q, r)` or member `a.quot_and_rem(b, q, r)` such that `a = q*b + r` with “remainder smaller than divisor” (norm or degree).
- **GCD:**  
  Either free function `gcd(a, b)` or member `a.gcd(b)` returning an element of `E`.
- **Extended GCD (for residue rings):**  
  `ext_gcd(a, b, m, n)` with `a*m + b*n = gcd(a,b)` (optional but needed for inverses in quotient rings).

**Models:**

- **Integral types (e.g. `int`, `long`):**  
  Use `std::is_integral` (or a small wrapper) and provide:
  - `quot_and_rem` → `q = a/b`, `r = a%b`
  - `gcd` → existing `int_gcd` / overloaded `gcd(int,int)`
  - `ext_gcd` → `int_ext_gcd`
- **Polynomial types:**  
  - `polynomial_of<C>` when `Coeff` is a field (so leading-coeff inverse exists).
  - **Exception:** `f2_poly_t` (see below) — same interface, different storage.

**Usage:** Residue/quotient ring templates (below) and any generic code that does GCD or division (e.g. factorization, rational reconstruction) constrain their element type by `Euclidean_domain`.

---

## 4. Exception: f2_poly_t (bit-packed F2[x])

**Constraint:** F2[x] uses bit-packing (e.g. `std::vector<uint64_t> parts`), not “polynomial-of\<byte\>” or “polynomial-of\<bit_t\>”. So it cannot be implemented as `polynomial_of<bit_t>` with the same storage layout.

**Proposed approach:**

- **Keep `f2_poly_t` as a dedicated class** with its current bit-packed representation and optimizations (XOR for add, bit masks, etc.).
- **Make `f2_poly_t` model the same interface as “polynomial over a ring”:**
  - Same operations: `+`, `-`, `*`, `/`, `%`, `quot_and_rem`, `gcd`, `ext_gcd`, `find_degree`, etc.
  - Same free function `gcd(const f2_poly_t&, const f2_poly_t&)`.
- **Concept:** Introduce a concept that captures “polynomial ring element” (e.g. `Polynomial_ring_element<P>` or reuse `Euclidean_domain<P>` for P = polynomial types). Then:
  - `polynomial_of<C>` models it when `C` is a field coefficient.
  - `f2_poly_t` also models it.
- **Generic code** that only needs ring + division + GCD can be written in terms of this concept and will work for both `polynomial_of<...>` and `f2_poly_t` without requiring the same storage.

**No “polynomial-of-byte”:** Do not try to express F2[x] as `polynomial_of<std::byte>` or `polynomial_of<uint8_t>`; that would lose the bit-packing and the current performance. The proposal is “one generic polynomial class for coefficient-array types + one special case (f2_poly_t) that satisfies the same concept.”

---

## 5. Concept templates for residue rings and quotient rings

**Goal:** Single implementation for Z/mZ, F2[x]/(m), Fp[x]/(m), etc., all requiring Euclidean GCD for inversion.

**Concept: `Residue_ring<R>` or `Quotient_ring<R>`**

- Type `R` represents an element of a quotient of an Euclidean domain (e.g. Z/mZ, F2[x]/(m), Fp[x]/(m)).
- **Ring ops:** `+`, `-`, `*`, `+=`, `-=`, `*=`, `==`, `!=`, zero, one.
- **Quotient structure:**  
  `get_residue()`, `get_modulus()` (or equivalent) so the underlying Euclidean domain and ideal are known.
- **Division / inverse:**  
  `recip(rinv)` or `operator/` using extended GCD in the underlying domain (so the concept requires that the underlying domain has `ext_gcd`).

**Template design:**

- **Option A – single template:**  
  `residue_ring<E, Modulus>` where `E` is the Euclidean domain element type and `Modulus` is the ideal (e.g. `int` for Z/mZ, `f2_poly_t` for F2[x]/(m), `fp_poly_t` for Fp[x]/(m)).  
  Constraint: `E` is `Euclidean_domain<E>`; operations on residues are defined in terms of operations on `E` and reduction mod the modulus.
- **Option B – type-erased modulus:**  
  The residue type holds both the residue and the modulus (as today’s `intmod_t`, `f2_polymod_t`, `fp_polymod_t`). Then the *concept* `Residue_ring<R>` describes the interface; existing classes can be refactored to implement it, and new ones can be added (e.g. a generic `residue_of<E>` that stores `E residue, E modulus` and uses `gcd`/`ext_gcd` on `E`).

**Concrete types (concept models):**

- `intmod_t` (Z/mZ, E = int)
- `f2_polymod_t` (F2[x]/(m), E = f2_poly_t)
- `fp_polymod_t` (Fp[x]/(m), E = fp_poly_t)
- `fpn_polymod_t` (Fq[x]/(m), E = fpn_poly_t) — same idea

**Euclidean requirement:** Any template that implements “residue ring” or “quotient ring” and needs multiplicative inverse should require `Euclidean_domain<E>` and use `ext_gcd(residue, modulus, ...)` for inversion.

---

## 6. Matrix and vector: concepts and STL

**Goal:** Use STL containers and concepts so that one set of algorithms works over “vector of T” and “matrix of T”, while keeping a specialized path for bits.

**Concepts:**

- **`Ring_element<T>`** (or reuse the coefficient concept): so `T` supports `+`, `-`, `*`, zero, one, `==`.
- **`Vector_over<V, T>`:**  
  `V` is a vector with element type `T` (e.g. `std::vector<T>` or `tvector<T>`).  
  Requirements: indexing `v[i]`, size, construction from size, element-wise `+`, `-`, scalar `*`, dot product (optional), and that `T` models `Ring_element<T>`.
- **`Matrix_over<M, T>`:**  
  `M` is a matrix with element type `T`.  
  Requirements: row access (e.g. `m[i]` → row vector), dimensions, matrix-vector product, matrix-matrix product, construction from dimensions. Element type `T` models `Ring_element<T>`.

**Implementation:**

- **Default:** Use STL:
  - Vector: `std::vector<T>` with a thin wrapper or free functions for `operator+`, `operator*`, dot, etc., so they satisfy the concept.
  - Matrix: `std::vector<std::vector<T>>` (or a single `std::vector<T>` with row-major indexing) and the same algebraic interface as current `tmatrix`.
- **Compatibility:** Either:
  - Replace `tvector<T>` / `tmatrix<T>` by aliases to STL-based types, or
  - Keep `tvector`/`tmatrix` but implement them in terms of `std::vector` internally and make them model the new concepts.

**Algorithms:** Row reduction, determinant, inverse, kernel basis, solve, etc. can be written once as templates constrained by `Matrix_over<M, T>` and `Ring_element<T>`, and optionally `Euclidean_domain<T>` or “field” when division is needed.

---

## 7. Specialized matrix/vector of bits (bit-packing)

**Goal:** Keep a dedicated, bit-packed implementation for F2 linear algebra; do *not* use “matrix of byte” or “matrix of bit_t”.

**Design:**

- **Keep `bit_vector_t` and `bit_matrix_t`** as they are (or refactor internally without changing the idea): storage is bits in `uint64_t` words, not one byte or one `bit_t` per entry.
- **Concept (optional):** Define a concept such as `Bit_vector<V>` / `Bit_matrix<M>` that captures the *interface* (e.g. `get(i)`, `set(i, b)`, `operator+`, row operations, row_reduce, etc.). Then:
  - `bit_vector_t` and `bit_matrix_t` model this concept.
  - Generic F2-only algorithms can be written against this concept if desired.
- **Interop:** Where higher-level code wants “a matrix over F2”, it can use either:
  - `tmatrix<bit_t>` (or STL-based matrix of `bit_t`) for small/dense or when a uniform “matrix over ring element” is desired, or
  - `bit_matrix_t` for performance-critical or large F2 linear algebra.

So: “matrix/vector concepts + STL” for general T, and “specialized bit_matrix_t / bit_vector_t with bit-packing” as a separate, first-class implementation, not as `matrix_of<byte>`.

---

## 8. Implementation order (suggested)

1. **Concepts (headers only):**  
   Define `Ring_element`, `Euclidean_domain`, `Residue_ring`, `Vector_over`, `Matrix_over` (and optionally `Polynomial_ring_element`, `Bit_vector`/`Bit_matrix`) in a single `concepts.hpp` or split by domain.
2. **Polynomial-of:**  
   Implement `polynomial_of<Coeff>` with `Coeff` constrained by the ring concept; add type aliases; migrate `fp_poly_t`, `f2n_poly_t`, `fpn_poly_t` (and optionally `q_poly_t`) to use it; delete duplicated .cpp code.
3. **Euclidean domain:**  
   Ensure integers and all polynomial types (including `f2_poly_t`) model `Euclidean_domain`; add free-function or trait-based dispatch for `gcd`/`ext_gcd` where needed.
4. **Residue/quotient:**  
   Introduce `residue_of<E>` or refactor existing polymod types to satisfy `Residue_ring`; use Euclidean `ext_gcd` in one place for inversion.
5. **Matrix/vector:**  
   Introduce STL-based vector/matrix types and concepts; refactor `tvector`/`tmatrix` to use STL and satisfy the concepts; then migrate call sites.
6. **Bit matrix/vector:**  
   Keep as-is; optionally add concept and document that they are the preferred F2 bit-packed implementation.

---

## 9. Summary table

| Area              | Current state                          | Proposal                                                                 |
|-------------------|----------------------------------------|--------------------------------------------------------------------------|
| Coefficients      | No formal contract                     | Concept `Ring_element<C>` for polynomial coefficients                    |
| Polynomials       | fp_poly_t, f2n_poly_t, fpn_poly_t, …   | `polynomial_of<Coeff>` + type aliases; one implementation                |
| F2[x]             | f2_poly_t (bit-packed)                 | Keep as dedicated class; same interface/concept as other polynomials     |
| Euclidean/GCD     | Ad hoc per type                        | Concept `Euclidean_domain<E>` (integral or polynomial)                     |
| Residue rings     | intmod_t, f2_polymod_t, fp_polymod_t   | Concept + optional template `residue_of<E>`; all use Euclidean GCD       |
| Matrix/vector     | tvector, tmatrix                       | Concepts; implement with STL; keep tvector/tmatrix as wrappers or replace |
| Bit matrix/vector | bit_vector_t, bit_matrix_t             | Keep specialized bit-packing; do not use matrix-of-byte                  |

This structure removes duplication (especially in polynomial and residue code) while keeping the ad-hoc f2_poly_t and bit matrix/vector as intentional, performance-preserving special cases.
