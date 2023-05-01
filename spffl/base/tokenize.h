// ================================================================
// Copyright (c) 2004, 2023 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

#ifndef TOKENIZE_H
#define TOKENIZE_H

namespace spffl::base {

int tokenize(char *line, const char *seps, char **argv, int max_arguments);

int count_tokens(char *line, const char *seps);

} // namespace spffl::base

#endif // TOKENIZE_H
