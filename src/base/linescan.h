// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef LINESCAN_H
#define LINESCAN_H

// Removes trailing CR, if any.  (The name "chomp" comes from Perl.)
void chomp(char *line);

bool is_whitespace_line(char *line);

#endif // LINESCAN_H
