#include <catch2/catch_test_macros.hpp>

#include "spffl/base/tokenize.h"

#include <string.h>

// ----------------------------------------------------------------
TEST_CASE("spffl::base::line_scan::tokenize_0") {
  char *line = strdup((char *)"");
  char *seps = (char *)" ";
  char *argv[11];
  int max_arguments = 10;

  int argc = spffl::base::tokenize(line, seps, argv, max_arguments);

  CHECK(argc == 0);
}

TEST_CASE("spffl::base::line_scan::tokenize_1") {
  char *line = strdup((char *)"abc");
  char *seps = (char *)" ";
  char *argv[11];
  int max_arguments = 10;

  int argc = spffl::base::tokenize(line, seps, argv, max_arguments);

  CHECK(argc == 1);
  CHECK(strcmp(argv[0], "abc") == 0);
}

TEST_CASE("spffl::base::line_scan::tokenize_2") {
  char *line = strdup((char *)"abc def");
  char *seps = (char *)" ";
  char *argv[11];
  int max_arguments = 10;

  int argc = spffl::base::tokenize(line, seps, argv, max_arguments);

  CHECK(argc == 2);
  CHECK(strcmp(argv[0], "abc") == 0);
  CHECK(strcmp(argv[1], "def") == 0);
}

TEST_CASE("spffl::base::line_scan::tokenize_3") {
  char *line = strdup((char *)",,abc,,def,,");
  char *seps = (char *)",";
  char *argv[11];
  int max_arguments = 10;

  int argc = spffl::base::tokenize(line, seps, argv, max_arguments);

  CHECK(argc == 2);
  CHECK(strcmp(argv[0], "abc") == 0);
  CHECK(strcmp(argv[1], "def") == 0);
}

TEST_CASE("spffl::base::line_scan::tokenize_4") {
  char *line = strdup((char *)",,abc, def,, ");
  char *seps = (char *)" ,";
  char *argv[11];
  int max_arguments = 10;

  int argc = spffl::base::tokenize(line, seps, argv, max_arguments);

  CHECK(argc == 2);
  CHECK(strcmp(argv[0], "abc") == 0);
  CHECK(strcmp(argv[1], "def") == 0);
}

// ----------------------------------------------------------------
TEST_CASE("spffl::base::line_scan::count_tokens_0") {
  char *line = (char *)"";
  char *seps = (char *)" ";

  int ntok = spffl::base::count_tokens(line, seps);

  CHECK(ntok == 0);
}

TEST_CASE("spffl::base::line_scan::count_tokens_1") {
  char *line = (char *)"abc";
  char *seps = (char *)" ";

  int ntok = spffl::base::count_tokens(line, seps);

  CHECK(ntok == 1);
}

TEST_CASE("spffl::base::line_scan::count_tokens_2") {
  char *line = (char *)"abc def";
  char *seps = (char *)" ";

  int ntok = spffl::base::count_tokens(line, seps);

  CHECK(ntok == 2);
}

TEST_CASE("spffl::base::line_scan::count_tokens_3") {
  char *line = (char *)",,abc,,def,,";
  char *seps = (char *)",";

  int ntok = spffl::base::count_tokens(line, seps);

  CHECK(ntok == 2);
}

TEST_CASE("spffl::base::line_scan::count_tokens_4") {
  char *line = (char *)",,abc, def,, ";
  char *seps = (char *)" ,";

  int ntok = spffl::base::count_tokens(line, seps);

  CHECK(ntok == 2);
}
