#include <iostream>
#include "doctest.h"
#include "../parser/validator.h"

TEST_CASE("check line is over") {
    std::stringstream sstream("abcd abcd abcd");
    Validator validator("");
    CHECK_THROWS(validator.check_line_is_over(sstream));
    std::string s;
    sstream >> s;
    CHECK_THROWS(validator.check_line_is_over(sstream));
    CHECK_NOTHROW(validator.check_line_is_over(sstream));
}

TEST_CASE("check time is correct") {
    Validator validator("");
    CHECK_NOTHROW(validator.check_time_is_correct("00:00"));
    CHECK_NOTHROW(validator.check_time_is_correct("23:59"));
    CHECK_NOTHROW(validator.check_time_is_correct("01:30"));
    CHECK_NOTHROW(validator.check_time_is_correct("15:01"));
    CHECK_THROWS(validator.check_time_is_correct("00:60"));
    CHECK_THROWS(validator.check_time_is_correct("24:00"));
    CHECK_THROWS(validator.check_time_is_correct("23:75"));
    CHECK_THROWS(validator.check_time_is_correct(""));
}

TEST_CASE("check name is correct") {
    Validator validator("");
    CHECK_NOTHROW(validator.check_name_is_correct("name"));
    CHECK_NOTHROW(validator.check_name_is_correct("a1so_ok_name"));
    CHECK_THROWS(validator.check_name_is_correct("Not_ok_name1"));
    CHECK_THROWS(validator.check_name_is_correct("not_ok_name$"));
    CHECK_THROWS(validator.check_name_is_correct("not_ok_name!"));
    CHECK_THROWS(validator.check_name_is_correct(""));
}

TEST_CASE("check table number is correct") {
    Validator validator("");
    CHECK_NOTHROW(validator.check_table_number_is_correct(1, 1));
    CHECK_NOTHROW(validator.check_table_number_is_correct(4, 15));
    CHECK_THROWS(validator.check_table_number_is_correct(0, 15));
    CHECK_THROWS(validator.check_table_number_is_correct(16, 15));
}

TEST_CASE("check id is correct") {
    Validator validator("");
    CHECK_NOTHROW(validator.check_id_is_correct(1));
    CHECK_NOTHROW(validator.check_id_is_correct(2));
    CHECK_NOTHROW(validator.check_id_is_correct(3));
    CHECK_NOTHROW(validator.check_id_is_correct(4));
    CHECK_THROWS(validator.check_id_is_correct(0));
    CHECK_THROWS(validator.check_id_is_correct(5));
}

TEST_CASE("check time is in chronological order") {
    Validator validator("");
    CHECK_NOTHROW(validator.check_time_is_in_chronological_order(1, 0));
    CHECK_NOTHROW(validator.check_time_is_in_chronological_order(1111, 101));
    CHECK_THROWS(validator.check_time_is_in_chronological_order(0, 1));
    CHECK_THROWS(validator.check_time_is_in_chronological_order(1, 111));
}

