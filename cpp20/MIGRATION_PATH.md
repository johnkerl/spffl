# Path to a single C++20 codebase (leave nothing behind)

This document proposes a path to migrate the entire spffl repository to C++20 so that:

- There is **one** source tree at the repo root (no `cpp20/` subdirectory).
- All code uses the **cpp20 design**: concepts, `polynomial_of<>`, `residue_of<>`, `vector_over`/`matrix_over`, unified euclidean, etc.
- **No** legacy pre-C++20 implementations remain; no ABI or backward compatibility is required.

The root `CMakeLists.txt` already sets `CMAKE_CXX_STANDARD` to 20, so the build is C++20-ready. The work is to replace old implementations with the cpp20 ones and then remove the duplicate tree.

---

## End state (single tree)

**Layout at repo root:**

- **`spffl/`** – Single library:
  - **`concepts.hpp`** – Ring_element, Euclidean_domain, Residue_ring, Vector_over, Matrix_over, Bit_vector_like, Bit_matrix_like, etc.
  - **`euclidean.hpp`** – Unified quot_and_rem, gcd, ext_gcd (int + any Euclidean_domain_with_ext_gcd).
  - **`residue_of.hpp`** – Generic residue ring (int, fp_poly_t, f2_poly_t).
  - **`intmath/`** – intmod_t (with exp), euclidean_int; other intmath (gcd, sqrt, primes, etc.) as needed.
  - **`polynomials/`** – polynomial_of.hpp, aliases (fp_poly_t, etc.), f2_poly_t.hpp (bit-packed), fp_polymod_t.hpp, f2_polymod_t (or residue_of<f2_poly_t>), f2n/fpn via polynomial_of<…> and corresponding polymods.
  - **`containers/`** – vector_over.hpp, matrix_over.hpp (replace tvector/tmatrix usage everywhere).
  - **`bits/`** – bit_t, bit_vector_t, bit_matrix_t (keep bit-packed; make them satisfy Bit_vector_like / Bit_matrix_like where useful).
  - **`algorithms/`** – optional_inverse, optional_solve_2x2, etc.
  - **`base/`**, **`random/`**, **`factorization/`**, **`linalg/`**, **`rationals/`**, **`units/`**, **`list/`**, **`cli_parser/`**, **`bitrand/`**, **`q_cyclotomic/`** – All updated to use the above types and headers; no `.cpp` that implement old poly/intmod/tvector/tmatrix.

- **`lib/`**, **`cli/`**, **`test/`** – All link against the single spffl and use the new types.

- **`cpp20/`** – **Removed.** Its contents have been merged into `spffl/` and `test/`; its tests live under `test/`.

**Header convention:** Migrated code can use `.hpp` (as in cpp20) for new/converted headers; existing `.h` can be converted to `.hpp` when touched, or left as `.h` until the file is replaced. Adjust `install(FILES_MATCHING PATTERN "*.h")` to include `*.hpp` if needed.

---

## Phased migration (recommended order)

### Phase 1: Core types in place (replace under spffl, no call-site changes yet)

Goal: The new implementations live in the main tree and build, even if some old code still builds alongside.

1. **intmath**
   - Replace `spffl/intmath/intmod_t.{h,cpp}` with the cpp20 version (header-only, with `exp(int)`). Remove `intmod_t.cpp`.
   - Add `spffl/intmath/euclidean_int.hpp` (from cpp20).
   - Keep other intmath (int_gcd, int_sqrt, primes, etc.) as-is for now; they don’t conflict.

2. **Concepts and euclidean**
   - Add `spffl/concepts.hpp` (from cpp20).
   - Add `spffl/euclidean.hpp` (from cpp20).

3. **Polynomials**
   - Add `spffl/polynomials/polynomial_of.hpp` (from cpp20).
   - Add `spffl/polynomials/aliases.hpp` with `fp_poly_t = polynomial_of<intmod_t>` (and any others that already exist in cpp20).
   - **Replace** `fp_poly_t.{h,cpp}`: delete the old implementation; make `fp_poly_t` the alias from aliases.hpp. All fp_poly_t call sites now use polynomial_of<intmod_t>. Fix any API differences (e.g. constructor or method names) in call sites.
   - **Replace** `f2_poly_t.{h,cpp}` with the cpp20 bit-packed `f2_poly_t.hpp` (header-only). Update call sites if the API differs (e.g. get_coeff, from_string).
   - Add `spffl/polynomials/fp_poly_io.hpp` (from cpp20) and use it where fp_poly I/O is needed.
   - **Replace** `fp_polymod_t.{h,cpp}` with the cpp20 `fp_polymod_t.hpp` (Fp[x]/(m), uses fp_poly_t and ext_gcd). Update call sites.
   - **f2n_poly_t / f2n_polymod_t:** Implement as `polynomial_of<residue_of<f2_poly_t>>` (or a dedicated f2_polymod_t type) and `residue_of<f2_poly_t>` (or alias). Remove old f2n_poly_t.cpp, f2n_polymod_t.cpp once migrated.
   - **fpn_poly_t / fpn_polymod_t:** Similarly, polynomial_of<fp_polymod_t> and a suitable residue type; remove old fpn .cpp.
   - **q_poly_t:** Either `polynomial_of<intrat_t>` with existing intrat_t, or defer; remove or replace q_poly_t.cpp when done.

4. **Residue and algorithms**
   - Add `spffl/residue_of.hpp` (from cpp20).
   - Add `spffl/algorithms/optional_inverse.hpp`, `optional_solve_2x2.hpp` (from cpp20).

5. **Containers**
   - Add `spffl/containers/vector_over.hpp` and `matrix_over.hpp` (from cpp20).
   - **Do not delete** `tvector`/`tmatrix` yet; keep them in parallel. Migrate call sites in a later phase, then remove.

After Phase 1, the library should build with both old and new types present where you’ve already switched (e.g. fp_poly_t, f2_poly_t, fp_polymod_t are the new implementations). Run existing tests and fix any regressions.

---

### Phase 2: Migrate call sites to new types and remove old implementations

Goal: No remaining references to old polynomial/intmod implementations or to tvector/tmatrix where we’ve chosen to use vector_over/matrix_over.

6. **Linalg**
   - `f2_linear_algebra`: Uses tmatrix<bit_t>, tvector<bit_t>, f2_poly_t. Switch to the new f2_poly_t; keep tmatrix/tvector for now unless you also migrate to matrix_over<bit_t> (and Bit_vector_like) in this step.
   - `fp_linear_algebra`: Uses tmatrix, tvector over intmod_t or fp_poly_t. Prefer matrix_over<intmod_t>, vector_over<intmod_t> (or fp_poly_t) and update APIs (e.g. row access, get_num_rows) to match.
   - `f2_polymod_linear_algebra`, `f2_polymod_convert`: Use new f2_polymod type (residue_of<f2_poly_t> or dedicated) and new containers where chosen.

7. **Factorization**
   - fp_poly_factor, f2_poly_factor, f2n_poly_factor: Already use fp_poly_t, f2_poly_t, f2n_poly_t. After Phase 1 these are the new types; fix any API differences. Replace tvector/tmatrix with vector_over/matrix_over if you’ve standardized on them.

8. **Random, units, rationals, list, q_cyclotomic**
   - Update to include new headers and use new types (fp_poly_t, fp_polymod_t, f2_poly_t, intmod_t, etc.). Replace tvector/tmatrix with vector_over/matrix_over where you want a single container abstraction.

9. **CLI and lib**
   - cli_parser (cmd_line_vector_ops, cmd_line_matrix_ops, etc.), cli tools (spiff, gcd, etc.), lib: Update to new types and containers. Ensure all CLI tools build and tests pass.

10. **Bits**
    - Keep bit_t, bit_vector_t, bit_matrix_t implementations; add concept conformance (Bit_vector_like, Bit_matrix_like) if desired. No need to change behavior.

11. **Remove old implementations**
    - Delete any .cpp that implemented old fp_poly_t, f2_poly_t, fp_polymod_t, f2n_*, fpn_*, q_poly_t, intmod_t, and (once migrated) tvector/tmatrix.
    - Delete or merge duplicate headers. Ensure no #include points at removed files.

---

### Phase 3: Single test tree and remove cpp20/

12. **Consolidate tests** ✓ (done)
    - cpp20 tests merged into main: `test_polynomial_of.cpp` → `test/polynomials/`, `test_intmod_t.cpp` and `test_euclidean_int.cpp` → `test/intmath/`, `test_mod.cpp` → `test/mod/` (with `spffl/mod/` added). Catch2 is already used in the root test tree. f2_poly_t I/O tests use main-tree hex format (low-bit-first).
    - Remaining: test/concepts, test/containers, test/residue, test/algorithms were already present in main; no further merge needed from cpp20 for those.

13. **Remove cpp20/**
    - Delete the entire `cpp20/` directory (or leave only this MIGRATION_PATH.md and REFACTORING_PROPOSAL.md at the root if you want to keep the docs). Root CMakeLists.txt no longer references cpp20.

14. **Cleanup**
    - Single top-level CMakeLists.txt; no cpp20-specific targets. Update README and any docs to describe the single C++20 codebase. Optionally add a top-level `make -f try.mk build` (or similar) that builds and runs the unified test suite.

---

## Optional simplifications (since you’re the only user)

- **tvector / tmatrix:** Remove them entirely and use only vector_over / matrix_over everywhere. Then delete tvector.h, tmatrix.h and any .cpp that only existed for them.
- **Header extension:** Standardize on `.hpp` for all spffl headers when you touch them; update install and includes.
- **f2n / fpn:** If you rarely use F2^n or Fp^n polynomials, implement them as thin wrappers (e.g. type aliases) over polynomial_of<residue_of<f2_poly_t>> and polynomial_of<fp_polymod_t>, and delete the old multi-file implementations.
- **q_poly_t / intrat_t:** If rational polynomials are optional, keep intrat_t and polynomial_of<intrat_t> as the only q_poly implementation and remove the old q_poly_t.cpp.

---

## Risk and order

- **Highest impact:** Replacing polynomials and polymods (Phase 1.3–1.4) and linalg/factorization (Phase 2). Do one polynomial type at a time (e.g. fp_poly_t first), run tests, then the next.
- **tmatrix/tvector:** Used in many places; migrate module-by-module (linalg, then factorization, then cli_parser, then cli) and run tests after each step.
- **No backward compatibility:** You can rename symbols (e.g. tvector → vector_over at call sites) and change APIs in one go per module, which simplifies the migration.

---

## Summary checklist

- [x] Phase 1.1: intmod_t + euclidean_int in main spffl
- [x] Phase 1.2: concepts.hpp, euclidean.hpp in main spffl
- [x] Phase 1.3: polynomial_of, aliases, fp_poly_t replacement, fp_polymod_t replacement (f2_poly_t still legacy; replace in follow-up if desired)
- [x] Phase 1.4 (Option B complete): f2n/fpn as polynomial_of/residue_of; fpn_f2n_aliases.hpp + fpn_f2n_io.hpp (prime_subfield_element, from_string, read_element); old f2n/fpn .cpp removed from build (polynomials + lib); rationals, factorization, units, linalg, cli (f2n/fpn handlers) migrated. q_poly_t deferred.
- [x] Phase 1.5: residue_of.hpp, optional_inverse.hpp in main spffl (optional_solve_2x2 with Phase 1.6)
- [x] Phase 1.6: vector_over, matrix_over, optional_solve_2x2 in main spffl (tvector/tmatrix still present)
- [x] Phase 2 (f2n/fpn): linalg, factorization, random, units, rationals, list, cli_parser, cli use new f2n/fpn types and API (no operator>>; read_element + explicit modulus).
- [ ] Phase 2: Migrate remaining modules to vector_over/matrix_over; remove other old .cpp as applicable
- [x] Phase 2: Remove legacy f2n/fpn .cpp (f2n_poly_t, f2n_polymod_t, fpn_poly_t, fpn_polymod_t deleted from spffl/polynomials/)
- [ ] Phase 2: Remove other obsolete headers and dead .cpp as applicable
- [x] Phase 3 (partial): algorithms and containers tests added to main test/ (test/algorithms, test/containers); residue_of supports legacy f2_poly_t (is_zero_poly)
- [x] Phase 3 (partial): concepts and residue tests merged into main test/ (test/concepts, test/residue)
- [ ] Phase 3: Merge remaining cpp20 tests (intmath, polynomials, mod) into test/, remove cpp20/
- [x] Phase 3: Update README and build docs (cpp20/README.md updated with migration status and next steps)

Done: one C++20 codebase, nothing left behind.

**Suggested next step:** Merge cpp20 tests into repo-root `test/` (test_polynomial_of, test_intmod_t, test_euclidean_int, test_mod) and wire in root `test/CMakeLists.txt`, then remove `cpp20/`. Alternatively, start Phase 2 vector_over/matrix_over migration in one module.
