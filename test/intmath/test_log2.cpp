#include <catch2/catch_test_macros.hpp>

#include "log2.h"

TEST_CASE("find_msb_16") {
  CHECK(find_msb_16(0) == 0); // TODO: weird
  CHECK(find_msb_16(1) == 0);
  CHECK(find_msb_16(2) == 1);
  CHECK(find_msb_16(3) == 1);
  CHECK(find_msb_16(4) == 2);
  CHECK(find_msb_16(5) == 2);
  CHECK(find_msb_16(0xff) == 7);
  CHECK(find_msb_16(0xfff) == 11);
  CHECK(find_msb_16(0xcafe) == 15);
  CHECK(find_msb_16(0xffff) == 15);
}

TEST_CASE("find_msb_32") {
  CHECK(find_msb_32(0) == 0); // TODO: weird
  CHECK(find_msb_32(1) == 0);
  CHECK(find_msb_32(2) == 1);
  CHECK(find_msb_32(3) == 1);
  CHECK(find_msb_32(4) == 2);
  CHECK(find_msb_32(5) == 2);
  CHECK(find_msb_32(0xff) == 7);
  CHECK(find_msb_32(0xfff) == 11);
  CHECK(find_msb_32(0xcafe) == 15);
  CHECK(find_msb_32(0xffff) == 15);
  CHECK(find_msb_32(0x00ab00ef) == 23);
  CHECK(find_msb_32(0x01ab00ef) == 24);
  CHECK(find_msb_32(0xcafefeed) == 31);
}

TEST_CASE("find_msb_64") {
  CHECK(find_msb_64(0) == 0); // TODO: weird
  CHECK(find_msb_64(1) == 0);
  CHECK(find_msb_64(2) == 1);
  CHECK(find_msb_64(3) == 1);
  CHECK(find_msb_64(4) == 2);
  CHECK(find_msb_64(5) == 2);
  CHECK(find_msb_64(0xff) == 7);
  CHECK(find_msb_64(0xfff) == 11);
  CHECK(find_msb_64(0xcafe) == 15);
  CHECK(find_msb_64(0xffff) == 15);
  CHECK(find_msb_64(0x00ab00ef) == 23);
  CHECK(find_msb_64(0x01ab00ef) == 24);
  CHECK(find_msb_64(0xcafefeed) == 31);
  CHECK(find_msb_64(0x00ab00efabcd0123) == 55);
  CHECK(find_msb_64(0x01ab00efabcd0123) == 56);
  CHECK(find_msb_64(0xdeadbeefcafefeed) == 63);
}

TEST_CASE("find_lsb_32") {
  CHECK(find_lsb_32(0) == 28); // TODO: weird and wrong
  CHECK(find_lsb_32(1) == 0);
  CHECK(find_lsb_32(2) == 1);
  CHECK(find_lsb_32(3) == 0);
  CHECK(find_lsb_32(4) == 2);
  CHECK(find_lsb_32(5) == 0);
  CHECK(find_lsb_32(0xff) == 0);
  CHECK(find_lsb_32(0xfff) == 0);
  CHECK(find_lsb_32(0xcafe) == 1);
  CHECK(find_lsb_32(0xffff) == 0);
  CHECK(find_lsb_32(0x00ab00ef) == 0);
  CHECK(find_lsb_32(0x00abfc00) == 10);
}

TEST_CASE("find_lsb_64") {
  CHECK(find_lsb_64(0) == 60); // TODO: weird and wrong
  CHECK(find_lsb_64(1) == 0);
  CHECK(find_lsb_64(2) == 1);
  CHECK(find_lsb_64(3) == 0);
  CHECK(find_lsb_64(4) == 2);
  CHECK(find_lsb_64(5) == 0);
  CHECK(find_lsb_64(0xff) == 0);
  CHECK(find_lsb_64(0xfff) == 0);
  CHECK(find_lsb_64(0xcafe) == 1);
  CHECK(find_lsb_64(0xffff) == 0);
  CHECK(find_lsb_64(0x00ab00ef) == 0);
  CHECK(find_lsb_64(0x00abfc00) == 10);
  CHECK(find_lsb_64(0x00000000abfc0000) == 18);
  CHECK(find_lsb_64(0x000000abfc000000) == 26);
  CHECK(find_lsb_64(0x0000abfc00000000) == 34);
}

TEST_CASE("calc_log2_unsigned") {
  CHECK(calc_log2_unsigned_floor(0) == 0);
  CHECK(calc_log2_unsigned_floor(1) == 0);
  CHECK(calc_log2_unsigned_floor(2) == 1);
  CHECK(calc_log2_unsigned_floor(3) == 1);
  CHECK(calc_log2_unsigned_floor(4) == 2);
  CHECK(calc_log2_unsigned_floor(5) == 2);
  CHECK(calc_log2_unsigned_floor(0x0000ffff) == 15);
  CHECK(calc_log2_unsigned_floor(0x00010000) == 16);
  CHECK(calc_log2_unsigned_floor(0x00010001) == 16);

  CHECK(calc_log2_unsigned_ceil(0) == 1); // TODO: weird
  CHECK(calc_log2_unsigned_ceil(1) == 0); // TODO: weird
  CHECK(calc_log2_unsigned_ceil(2) == 1);
  CHECK(calc_log2_unsigned_ceil(3) == 2);
  CHECK(calc_log2_unsigned_ceil(4) == 2);
  CHECK(calc_log2_unsigned_ceil(5) == 3);
  CHECK(calc_log2_unsigned_ceil(0x0000ffff) == 16);
  CHECK(calc_log2_unsigned_ceil(0x00010000) == 16);
  CHECK(calc_log2_unsigned_ceil(0x00010001) == 17);
}

TEST_CASE("calc_log2_unsigned_ll") {
  CHECK(calc_log2_unsigned_ll_floor(0) == 0);
  CHECK(calc_log2_unsigned_ll_floor(1) == 0);
  CHECK(calc_log2_unsigned_ll_floor(2) == 1);
  CHECK(calc_log2_unsigned_ll_floor(3) == 1);
  CHECK(calc_log2_unsigned_ll_floor(4) == 2);
  CHECK(calc_log2_unsigned_ll_floor(5) == 2);
  CHECK(calc_log2_unsigned_ll_floor(0x0000ffff) == 15);
  CHECK(calc_log2_unsigned_ll_floor(0x00010000) == 16);
  CHECK(calc_log2_unsigned_ll_floor(0x00010001) == 16);
  CHECK(calc_log2_unsigned_ll_floor(0xffffffff) == 31);
  CHECK(calc_log2_unsigned_ll_floor(0x0000000100000000) == 32);
  CHECK(calc_log2_unsigned_ll_floor(0x0000000100000001) == 32);
  CHECK(calc_log2_unsigned_ll_floor(0x0000ffffabcd0123) == 47);
  CHECK(calc_log2_unsigned_ll_floor(0x00010000abcd0123) == 48);
  CHECK(calc_log2_unsigned_ll_floor(0x00010001abcd0123) == 48);
  CHECK(calc_log2_unsigned_ll_floor(0xffffffffffffffff) == 63);

  CHECK(calc_log2_unsigned_ll_ceil(0) == 1); // TODO: weird
  CHECK(calc_log2_unsigned_ll_ceil(1) == 0); // TODO: weird
  CHECK(calc_log2_unsigned_ll_ceil(2) == 1);
  CHECK(calc_log2_unsigned_ll_ceil(3) == 2);
  CHECK(calc_log2_unsigned_ll_ceil(4) == 2);
  CHECK(calc_log2_unsigned_ll_ceil(5) == 3);
  CHECK(calc_log2_unsigned_ll_ceil(0x0000ffff) == 16);
  CHECK(calc_log2_unsigned_ll_ceil(0x00010000) == 16);
  CHECK(calc_log2_unsigned_ll_ceil(0x00010001) == 17);
  CHECK(calc_log2_unsigned_ll_ceil(0xffffffff) == 32);
  CHECK(calc_log2_unsigned_ll_ceil(0x0000000100000000) == 32);
  CHECK(calc_log2_unsigned_ll_ceil(0x0000000100000001) == 33);
  CHECK(calc_log2_unsigned_ll_ceil(0x0000ffffabcd0123) == 48);
  CHECK(calc_log2_unsigned_ll_ceil(0x00010000abcd0123) == 49);
  CHECK(calc_log2_unsigned_ll_ceil(0x00010001abcd0123) == 49);
  CHECK(calc_log2_unsigned_ll_ceil(0xffffffffffffffff) == 64);
}
