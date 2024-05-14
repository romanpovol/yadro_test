#ifndef SOLUTION_CONVERTER_H
#define SOLUTION_CONVERTER_H

#include <string>

struct Converter {
public:
    static int convert_time_in_string_to_minutes(const std::string &time); // convert minutest in int to string time format

    static std::string convert_time_in_minutes_to_string(int time); // convert string time format to minutes in int
};

#endif //SOLUTION_CONVERTER_H
