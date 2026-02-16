## spffl C++20 port (`cpp20/`)

This directory contains an in‑progress C++20 port of `spffl`, focused on:

- **C++20 concepts** (see `spffl/concepts.hpp`)
- A generic **`polynomial_of<Coeff>`** template (see `spffl/polynomials/polynomial_of.hpp`)
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
- Build all test executables under `test/` (e.g. `test_mod`, `test_concepts`, `test_polynomial_of`).

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
```

---

### Layout overview

- `CMakeLists.txt` – top‑level CMake configuration for the C++20 port
- `spffl/`
  - `CMakeLists.txt` – adds subdirectories for modules (currently only `mod/`)
  - `concepts.hpp` – C++20 concepts used to drive refactoring
  - `polynomials/polynomial_of.hpp` – generic polynomial template
  - `mod/` – example module (`foo.h` / `foo.cpp`) used by tests
- `test/`
  - Top‑level `CMakeLists.txt` – fetches Catch2 and adds test subdirectories
  - `mod/` – tests for `spffl::mod::foo`
  - `concepts/` – tests that `spffl/concepts.hpp` compiles and behaves as expected
  - `polynomials/` – tests for `polynomial_of<>`

---

### Notes

- The C++20 port is intentionally **incremental**: only a subset of the original library is wired up here so far.
- If CMake re‑fetches Catch2 frequently, you may want to persist the `_deps/` directory or use CMake’s package mechanism instead of `FetchContent` in the future.

