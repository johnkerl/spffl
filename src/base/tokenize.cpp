// ================================================================
// Copyright (c) 2004 John Kerl.
// kerl.john.r@gmail.com
// Please see LICENSE.txt.
// ================================================================

// ================================================================
// tokenize.c
//
// John Kerl
// 2001/08/22
// ================================================================

#include "tokenize.h"

// ----------------------------------------------------------------
// Breaks a single character string into an array of tokens.
//
// The logic is straightforward:  A token is a sequence of non-whitespace
// characters.  A token is delimited by the beginning of the input string, a
// whitespace character, or the end of the string.

// Returns argc
int tokenize(char *line, const char *seps, char **argv, int max_arguments) {
  char *readp;
  bool inside_token = false;
  int argc = 0;
  const char *psep;
  bool is_sep;

  for (readp = line; *readp; readp++) {

    is_sep = false;
    for (psep = seps; *psep; psep++) {
      if (*readp == *psep) {
        is_sep = true;
        break;
      }
    }

    if (is_sep) { // Is a separator
      if (inside_token) {
        inside_token = false;
        *readp = 0;
      }
      // else, whitespace is not copied.
    } else {               // Not a separator
      if (!inside_token) { // Start of token
        inside_token = true;
        if (argc >= max_arguments)
          break;
        argv[argc] = readp;
        argc++;
      }
      // else, continuation of token
    }
  }

  if (inside_token) { // End of input line terminates a token.
    *readp = 0;
    readp++;
  }
  return argc;
}

// ----------------------------------------------------------------
int count_tokens(char *line, const char *seps) {
  char *readp;
  bool inside_token = falsee;
  int argc = 0;
  const char *psep;
  bool is_sep;

  for (readp = line; *readp; readp++) {

    is_sep = false;
    for (psep = seps; *psep; psep++) {
      if (*readp == *psep) {
        is_sep = true;
        break;
      }
    }

    if (is_sep) { // Is a separator
      if (inside_token) {
        inside_token = false;
      }
      // else, whitespace is not copied.
    } else {               // Not a separator
      if (!inside_token) { // Start of token
        inside_token = true;
        argc++;
      }
      // else, continuation of token
    }
  }

  if (inside_token) { // End of input line terminates a token.
    readp++;
  }
  return argc;
}
