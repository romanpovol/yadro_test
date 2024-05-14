#include "doctest.h"
#include "../parser/converter.h"

TEST_CASE("time in minutes to string") {
    CHECK(Converter::convert_time_in_minutes_to_string(0) == "00:00");
    CHECK(Converter::convert_time_in_minutes_to_string(59) == "00:59");
    CHECK(Converter::convert_time_in_minutes_to_string(60) == "01:00");
    CHECK(Converter::convert_time_in_minutes_to_string(148) == "02:28");
    CHECK(Converter::convert_time_in_minutes_to_string(817) == "13:37");
    CHECK(Converter::convert_time_in_minutes_to_string(931) == "15:31");
    CHECK(Converter::convert_time_in_minutes_to_string(1439) == "23:59");
}

TEST_CASE("time in string to minutes") {
    CHECK(Converter::convert_time_in_string_to_minutes("00:00") == 0);
    CHECK(Converter::convert_time_in_string_to_minutes("00:59") == 59);
    CHECK(Converter::convert_time_in_string_to_minutes("01:00") == 60);
    CHECK(Converter::convert_time_in_string_to_minutes("02:28") == 148);
    CHECK(Converter::convert_time_in_string_to_minutes("13:37") == 817);
    CHECK(Converter::convert_time_in_string_to_minutes("11:34") == 694);
    CHECK(Converter::convert_time_in_string_to_minutes("23:59") == 1439);
}