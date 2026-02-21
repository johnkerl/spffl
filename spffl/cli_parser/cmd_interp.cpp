#include "spffl/base/spffl_exception.h"
#include "spffl/base/tokenize.h"
#include <iostream>
#include <stdio.h> // For perror
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

namespace spffl::cli_parser {

#define LBRK "{"
#define RBRK "}"

// ----------------------------------------------------------------
static int find_first_bracket(int argc, char **argv, char *brkt, int &idx) {
  idx = -1;
  for (int argi = 0; argi < argc; argi++) {
    if (strcmp(argv[argi], brkt) == 0) {
      idx = argi;
      return 1;
    }
  }
  return 0;
}

// ----------------------------------------------------------------
static int check_balance(int argc, char **argv) {
  int depth = 0;
  for (int argi = 0; argi < argc; argi++) {
    if (depth < 0) {
      std::stringstream ss;
      ss << "Bracket imbalance.\n";
      return 0;
    }
    if (strcmp(argv[argi], LBRK) == 0) {
      depth++;
    } else if (strcmp(argv[argi], RBRK) == 0) {
      depth--;
    }
  }
  if (depth != 0) {
    std::stringstream ss;
    ss << "Bracket imbalance.\n";
    return 0;
  }
  return 1;
}

// ----------------------------------------------------------------
static void find_matching_right_bracket(int argc, char **argv, int lefti, int &righti) {
  int depth = 1;
  for (righti = lefti + 1; righti < argc; righti++) {
    if (strcmp(argv[righti], RBRK) == 0) {
      if (--depth == 0) {
        return;
      }
    } else if (strcmp(argv[righti], LBRK) == 0) {
      depth++;
    }
  }
}

// ----------------------------------------------------------------
// The caller must free the return value.
static char *flatten(char *exename, int argc, char **argv) {
  int len = strlen(exename) + 1;
  for (int argi = 0; argi < argc; argi++) {
    len += strlen(argv[argi]) + 1;
  }
  char *rv = (char *)malloc(len);
  if (rv == 0) {
    std::stringstream ss;
    ss << "malloc(" << len << ") failed.\n";
    throw spffl::exception_t(ss.str());
  }
  strcpy(rv, exename);
  for (int argi = 0; argi < argc; argi++) {
    strcat(rv, " ");
    strcat(rv, argv[argi]);
  }
  return rv;
}

// ----------------------------------------------------------------
static void replace(char *exename, int argcin, char **argvin, int &argcout, char **&argvout) {
  char *flat_cmd = flatten(exename, argcin, argvin);

  FILE *pipe = popen(flat_cmd, "r");
  if (pipe == 0) {
    std::stringstream ss;
    ss << "Failed popen \"" << flat_cmd << "\".\n";
    throw spffl::exception_t(ss.str());
  }

  char line[4096];
  int totlen = 0;
  char *buf = 0;
  while (fgets(line, sizeof(line), pipe)) {
    int curlen = strlen(line);
    if (line[curlen - 1] == '\n') {
      line[curlen - 1] = 0;
      curlen--;
    }
    if (buf == 0) {
      buf = (char *)malloc(curlen + 1);
      strcpy(buf, line);
      totlen = curlen + 1;
    } else {
      buf = (char *)realloc(buf, totlen + curlen + 2);
      strcat(buf, " ");
      strcat(buf, line);
      totlen += curlen + 2;
    }
  }
  pclose(pipe);

  if (buf == 0) {
    buf = strdup("");
  }

  argcout = spffl::base::count_tokens(buf, " \t");
  argvout = (char **)malloc(argcout * sizeof(char *));

  int check = spffl::base::tokenize(buf, " \t", argvout, argcout);
  if (check != argcout) {
    std::stringstream ss;
    ss << "Coding error in replace.\n";
    throw spffl::exception_t(ss.str());
  }
  // buf is not freed since argvout points into it.
}

// ----------------------------------------------------------------
static void cmd_interpolate_once(char *exename, int &argc, char **&argv, int &interpolated) {
  interpolated = 0;
  int lefti, righti;
  if (!find_first_bracket(argc, argv, (char *)LBRK, lefti)) {
    int dummy;
    if (find_first_bracket(argc, argv, (char *)RBRK, dummy)) {
      std::stringstream ss;
      ss << "Bracket imbalance.\n";
      throw spffl::exception_t(ss.str());
    }
    return;
  }
  if (!check_balance(argc, argv)) {
    std::stringstream ss;
    ss << "Bracket imbalance.\n";
    throw spffl::exception_t(ss.str());
  }

  find_matching_right_bracket(argc, argv, lefti, righti);

  // a  b  c  {  d  e  f  }  g  h  i
  // 0  1  2  3  4  5  6  7  8  9  10

  // Before brackets: count = lefti,          ptrs = argv[0]
  // Left   bracket:  count = 1,              ptrs = argv[lefti]
  // During brackets: count = righti-lefti-1, ptrs = argv[lefti+1]
  // Right  bracket:  count = 1,              ptrs = argv[righti]
  // After  brackets: count = argc-righti-1,  ptrs = argv[righti+1]

  int argcout;
  char **argvout;

  replace(exename, righti - lefti - 1, &argv[lefti + 1], argcout, argvout);

  int newargc = lefti + argcout + argc - righti - 1;
  char **newargv = (char **)malloc(newargc * sizeof(char *));
  int si, di = 0;
  for (si = 0; si < lefti; si++, di++) {
    newargv[di] = argv[si];
  }
  for (si = 0; si < argcout; si++, di++) {
    newargv[di] = argvout[si];
  }
  for (si = righti + 1; si < argc; si++, di++) {
    newargv[di] = argv[si];
  }

  argc = newargc;
  argv = newargv;
  interpolated = 1;
}

// ----------------------------------------------------------------
void cmd_interpolate(char *exename, int &argc, char **&argv) {
  int interpolated = 0;
  do {
    cmd_interpolate_once(exename, argc, argv, interpolated);
  } while (interpolated);
}

} // namespace spffl::cli_parser
