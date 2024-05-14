#include "converter.h"

int Converter::convert_time_in_string_to_minutes(const std::string& time) {
    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');
    return hours * 60 + minutes;
}

std::string Converter::convert_time_in_minutes_to_string(int time) {
    char time_in_string_format[6];
    int hours = time / 60;
    int minutes = time % 60;
    std::sprintf(time_in_string_format, "%02d:%02d", hours, minutes);
    return time_in_string_format;
}