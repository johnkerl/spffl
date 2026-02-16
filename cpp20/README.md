## spffl C++20 port (`cpp20/`)

This directory contains an in‑progress C++20 port of `spffl`, focused on:

- **C++20 concepts** (see `spffl/concepts.hpp`)
- A generic **`polynomial_of<Coeff>`** template (see `spffl/polynomials/polynomial_of.hpp`)
- **Type aliases** such as `fp_poly_t = polynomial_of<intmod_t>` (see `spffl/polynomials/aliases.hpp`)
- **`f2_poly_t`** (F2[x]) in `spffl/polynomials/f2_poly_t.hpp`: bit-packed, models `Polynomial_with_ext_gcd`; `from_string("1,0,1")` (comma-separated 0/1, leading first) and `operator>>`
- A minimal **`intmod_t`** (Z/nZ) in `spffl/intmath/intmod_t.hpp` for Fp[x] coefficients
- **`fp_polymod_t`** (Fp[x]/(m)) in `spffl/polynomials/fp_polymod_t.hpp` for the residue ring, with `recip` and `exp`
- **Generic `residue_of<E>`** in `spffl/residue_of.hpp`: residue ring over any `E` (e.g. `int` → Z/nZ, `fp_poly_t` → Fp[x]/(m), `f2_poly_t` → F2[x]/(m)); models `Residue_ring` and `Residue_ring_with_recip`; inversion via unified `euclidean::ext_gcd`
- **STL-based `vector_over<T>`** and **`matrix_over<T>`** in `spffl/containers/` (satisfy `Vector_over`, `Matrix_over`, `Matrix_vector_product`)
- **Bit vector/matrix concepts**: `Bit_vector_like<V>` and `Bit_matrix_like<M>` in `concepts.hpp` describe bit-packed F2 vectors/matrices (e.g. `get(i)`, `set(i,b)`, row access, ring ops). Legacy `bit_vector_t` / `bit_matrix_t` can satisfy these; no new implementation in cpp20 yet.
- **Euclidean ops**: `spffl/intmath/euclidean_int.hpp` (int: quot_and_rem, gcd, ext_gcd); **unified** `spffl/euclidean.hpp` with `quot_and_rem`, `gcd`, and `ext_gcd` for both `int` and any `Euclidean_domain_with_ext_gcd<E>` so generic residue-ring code can use one interface
- **fp_poly_t / fp_polymod_t I/O**: `fp_poly_from_string(s, p)`, `fp_polymod_from_string(s, modulus)`, and `operator>>` for both in `spffl/polynomials/fp_poly_io.hpp` (comma-separated coefficients, leading first)
- A small Catch2‑based test suite under `test/`

The code is experimental and currently lives alongside the existing C++03 code in the parent tree.

---

### Prerequisites

- CMake **≥ 3.24**
- A C++20‑capable compiler (e.g. recent Clang / GCC)
- Git + internet access for fetching Catch2 (via CMake `FetchContent`)

On macOS with Xcode command‑line tools, the default AppleClang is sufficient.

---

### Configure and build

From the `cpp20/` directory:

```bash
cd cpp20
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

This will:

- Build the `spffl20_src` library pieces under `spffl/` (currently only a small subset),
- Fetch and build Catch2 (as an external dependency),
- Build all test executables under `test/` (e.g. `test_mod`, `test_concepts`, `test_polynomial_of`, `test_intmod_t`, `test_euclidean_int`, `test_vector_over`, `test_matrix_over`).

---

### Running tests

From `cpp20/build`:

```bash
cd cpp20/build
ctest --output-on-failure
```

You can also run individual tests directly, e.g.:

```bash
./test/mod/test_mod
./test/concepts/test_concepts
./test/polynomials/test_polynomial_of
./test/intmath/test_intmod_t
./test/containers/test_vector_over
./test/containers/test_matrix_over
./test/intmath/test_euclidean_int
```

---

### Layout overview

- `CMakeLists.txt` – top‑level CMake configuration for the C++20 port
- `spffl/`
  - `CMakeLists.txt` – adds subdirectories for modules (currently only `mod/`)
  - `concepts.hpp` – C++20 concepts used to drive refactoring
  - `polynomials/polynomial_of.hpp` – generic polynomial template
  - `polynomials/aliases.hpp` – `fp_poly_t` etc. as `polynomial_of<…>`
  - `polynomials/f2_poly_t.hpp` – F2[x] (bit-packed), models `Polynomial_with_ext_gcd`; `from_string`, `operator>>` (comma-separated 0/1)
  - `polynomials/fp_polymod_t.hpp` – Fp[x]/(m) residue ring
  - `polynomials/fp_poly_io.hpp` – `fp_poly_from_string`, `operator>>` for fp_poly_t
  - `intmath/intmod_t.hpp` – header‑only Z/nZ for Fp[x]
  - `intmath/euclidean_int.hpp` – `quot_and_rem`, `gcd` for int
  - `euclidean.hpp` – unified `quot_and_rem` / `gcd` for int and any `Euclidean_domain<E>`
  - `containers/vector_over.hpp`, `containers/matrix_over.hpp` – STL-based vector/matrix over a ring
  - `residue_of.hpp` – generic **`residue_of<E>`** (E = int, fp_poly_t, or f2_poly_t); models `Residue_ring` and `Residue_ring_with_recip`
  - `algorithms/optional_inverse.hpp` – generic `optional_inverse<R>`, `optional_solve_ax_eq_b<R>` for `Residue_ring_with_recip<R>`
  - `mod/` – example module (`foo.h` / `foo.cpp`) used by tests
- `test/`
  - Top‑level `CMakeLists.txt` – fetches Catch2 and adds test subdirectories
  - `mod/` – tests for `spffl::mod::foo`
  - `concepts/` – tests that `spffl/concepts.hpp` compiles and behaves as expected
  - `polynomials/` – tests for `polynomial_of<>` and `fp_poly_t`
  - `intmath/` – tests for `intmod_t`, `euclidean_int`
  - `containers/` – tests for `vector_over<T>`, `matrix_over<T>`
  - `residue/` – tests for `residue_of<int>`, `residue_of<fp_poly_t>`, `residue_of<f2_poly_t>`
  - `algorithms/` – tests for `optional_inverse`, `optional_solve_ax_eq_b` (residue_of<int>, fp_polymod_t, residue_of<f2_poly_t>)

---

### Next steps (suggested)

- **F2[x] residue:** Done: `residue_of<f2_poly_t>` for F2[x]/(m) with `recip` and `exp` (via `f2_poly_t::one()` and a dedicated recip path in `residue_of`).
- **Generic algorithms:** Further examples using `euclidean::`, `Vector_over`, `Matrix_over` (e.g. linear algebra over a residue ring). A minimal start exists in `spffl/algorithms/optional_inverse.hpp` (`optional_inverse`, `optional_solve_ax_eq_b`).
- **Migration:** Use `polynomial_of<>`, `residue_of<>`, and cpp20 types in the main spffl tree (incremental, with tests).

---

### Notes

- The C++20 port is intentionally **incremental**: only a subset of the original library is wired up here so far.
- If CMake re‑fetches Catch2 frequently, you may want to persist the `_deps/` directory or use CMake’s package mechanism instead of `FetchContent` in the future.

