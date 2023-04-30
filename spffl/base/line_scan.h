// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef LINESCAN_H
#define LINESCAN_H

namespace spffl::base {

// Removes trailing CR, if any.  (The name "chomp" comes from Perl.)
void chomp(char *line);

bool is_whitespace_line(char *line);

} // namespace spffl::base

#endif // LINESCAN_H
