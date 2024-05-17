#include "validator.h"

#include <regex>
#include "../data/exceptions.h"

Validator::Validator(const std::string& line_) : line(line_) {}

void Validator::check_line_is_over(std::stringstream &sstream) const {
    std::string buffer;
    if (sstream >> buffer) {
        throw ErrorInInputFileException(line);
    }
}

void Validator::check_time_is_correct(const std::string &time) const {
    std::regex pattern("(^(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9])$)");
    if (time.empty() || !std::regex_match(time, pattern)) {
        throw ErrorInInputFileException(line);
    }
}

void Validator::check_name_is_correct(const std::string &name) const {
    std::regex pattern("(^[a-z0-9_-]+$)");
    if (name.empty() || !std::regex_match(name, pattern)) {
        throw ErrorInInputFileException(line);
    }
}

void Validator::check_table_number_is_correct(int table_number, int number_of_tables) const {
    if (0 >= table_number || table_number > number_of_tables) {
        throw ErrorInInputFileException(line);
    }
}

void Validator::check_id_is_correct(int id) const {
    if (0 >= id || id > 4) {
        throw ErrorInInputFileException(line);
    }
}

void Validator::check_time_is_in_chronological_order(int curren_time, int previous_time) const {
    if (curren_time <= previous_time) {
        throw ErrorInInputFileException(line);
    }
}

