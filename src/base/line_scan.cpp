// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#include "line_scan.h"
#include <cctype>
#include <string.h>

namespace spffl::base {

// ----------------------------------------------------------------
// Removes trailing CR, if any.  (The name "chomp" comes from Perl.)
void chomp(char *line) {
  int len = strlen(line);
  if (len > 0) {
    if (line[len - 1] == '\n') {
      line[len - 1] = 0;
    }
  }
}

// ----------------------------------------------------------------
bool is_whitespace_line(char *line) {
  char *p;
  for (p = line; *p; p++) {
    if (!isspace(*p)) {
      return false;
    }
  }
  return true;
}

} // namespace spffl::base
