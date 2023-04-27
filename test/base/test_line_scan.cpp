#include <catch2/catch_test_macros.hpp>

#include "line_scan.h"
#include <string.h>

TEST_CASE("spffl::base::line_scan::chomp") {

  char *input = strdup((char *)"abc");
  spffl::base::chomp(input);
  CHECK(strcmp(input, "abc") == 0);

  input = strdup((char *)"ab\nc");
  spffl::base::chomp(input);
  CHECK(strcmp(input, "ab\nc") == 0);

  input = strdup((char *)"abc\n");
  spffl::base::chomp(input);
  CHECK(strcmp(input, "abc") == 0);

  input = strdup((char *)"abc\n\n");
  spffl::base::chomp(input);
  CHECK(strcmp(input, "abc\n") == 0);
}

TEST_CASE("spffl::base::line_scan::is_whitespace_line") {

  CHECK(spffl::base::is_whitespace_line(""));
  CHECK(spffl::base::is_whitespace_line(" "));
  CHECK(spffl::base::is_whitespace_line("\t"));
  CHECK(spffl::base::is_whitespace_line("\n"));
  CHECK(spffl::base::is_whitespace_line("  \t\n "));
  CHECK(!spffl::base::is_whitespace_line("  \tn "));
  CHECK(!spffl::base::is_whitespace_line(" x "));
}
