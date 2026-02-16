// ================================================================
// Default stream read with optional context (e.g. modulus).
// Overload read_element(istringstream&, const T& zero, T& out) in T's
// namespace for types that need context (e.g. f2n_polyrat_t).
// ================================================================

#ifndef SPFFL_BASE_READ_ELEMENT_H
#define SPFFL_BASE_READ_ELEMENT_H

#include <sstream>

template <class T>
void read_element(std::istringstream& iss, const T& zero, T& out) {
  (void)zero;
  iss >> out;
}

#endif  // SPFFL_BASE_READ_ELEMENT_H
