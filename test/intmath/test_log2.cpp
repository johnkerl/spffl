#include <catch2/catch_test_macros.hpp>

#include "log2.h"
#include "intfc.h"

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
    CHECK(calc_log2_unsigned(0, IFLOOR) == 0);
    CHECK(calc_log2_unsigned(1, IFLOOR) == 0);
    CHECK(calc_log2_unsigned(2, IFLOOR) == 1);
    CHECK(calc_log2_unsigned(3, IFLOOR) == 1);
    CHECK(calc_log2_unsigned(4, IFLOOR) == 2);
    CHECK(calc_log2_unsigned(5, IFLOOR) == 2);
    CHECK(calc_log2_unsigned(0x0000ffff, IFLOOR) == 15);
    CHECK(calc_log2_unsigned(0x00010000, IFLOOR) == 16);
    CHECK(calc_log2_unsigned(0x00010001, IFLOOR) == 16);

    CHECK(calc_log2_unsigned(0, ICEIL) == 1); // TODO: weird
    CHECK(calc_log2_unsigned(1, ICEIL) == 0); // TODO: weird
    CHECK(calc_log2_unsigned(2, ICEIL) == 1);
    CHECK(calc_log2_unsigned(3, ICEIL) == 2);
    CHECK(calc_log2_unsigned(4, ICEIL) == 2);
    CHECK(calc_log2_unsigned(5, ICEIL) == 3);
    CHECK(calc_log2_unsigned(0x0000ffff, ICEIL) == 16);
    CHECK(calc_log2_unsigned(0x00010000, ICEIL) == 16);
    CHECK(calc_log2_unsigned(0x00010001, ICEIL) == 17);
}

TEST_CASE("calc_log2_unsigned_ll") {
    CHECK(calc_log2_unsigned_ll(0, IFLOOR) == 0);
    CHECK(calc_log2_unsigned_ll(1, IFLOOR) == 0);
    CHECK(calc_log2_unsigned_ll(2, IFLOOR) == 1);
    CHECK(calc_log2_unsigned_ll(3, IFLOOR) == 1);
    CHECK(calc_log2_unsigned_ll(4, IFLOOR) == 2);
    CHECK(calc_log2_unsigned_ll(5, IFLOOR) == 2);
    CHECK(calc_log2_unsigned_ll(0x0000ffff, IFLOOR) == 15);
    CHECK(calc_log2_unsigned_ll(0x00010000, IFLOOR) == 16);
    CHECK(calc_log2_unsigned_ll(0x00010001, IFLOOR) == 16);
    CHECK(calc_log2_unsigned_ll(0xffffffff, IFLOOR) == 31);
    CHECK(calc_log2_unsigned_ll(0x0000000100000000, IFLOOR) == 32);
    CHECK(calc_log2_unsigned_ll(0x0000000100000001, IFLOOR) == 32);
    CHECK(calc_log2_unsigned_ll(0x0000ffffabcd0123, IFLOOR) == 47);
    CHECK(calc_log2_unsigned_ll(0x00010000abcd0123, IFLOOR) == 48);
    CHECK(calc_log2_unsigned_ll(0x00010001abcd0123, IFLOOR) == 48);
    CHECK(calc_log2_unsigned_ll(0xffffffffffffffff, IFLOOR) == 63);

    CHECK(calc_log2_unsigned_ll(0, ICEIL) == 1); // TODO: weird
    CHECK(calc_log2_unsigned_ll(1, ICEIL) == 0); // TODO: weird
    CHECK(calc_log2_unsigned_ll(2, ICEIL) == 1);
    CHECK(calc_log2_unsigned_ll(3, ICEIL) == 2);
    CHECK(calc_log2_unsigned_ll(4, ICEIL) == 2);
    CHECK(calc_log2_unsigned_ll(5, ICEIL) == 3);
    CHECK(calc_log2_unsigned_ll(0x0000ffff, ICEIL) == 16);
    CHECK(calc_log2_unsigned_ll(0x00010000, ICEIL) == 16);
    CHECK(calc_log2_unsigned_ll(0x00010001, ICEIL) == 17);
    CHECK(calc_log2_unsigned_ll(0xffffffff, ICEIL) == 32);
    CHECK(calc_log2_unsigned_ll(0x0000000100000000, ICEIL) == 32);
    CHECK(calc_log2_unsigned_ll(0x0000000100000001, ICEIL) == 33);
    CHECK(calc_log2_unsigned_ll(0x0000ffffabcd0123, ICEIL) == 48);
    CHECK(calc_log2_unsigned_ll(0x00010000abcd0123, ICEIL) == 49);
    CHECK(calc_log2_unsigned_ll(0x00010001abcd0123, ICEIL) == 49);
    CHECK(calc_log2_unsigned_ll(0xffffffffffffffff, ICEIL) == 64);
}
