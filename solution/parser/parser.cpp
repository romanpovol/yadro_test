#include "parser.h"
#include "../data/exceptions.h"
#include "converter.h"
#include "validator.h"

#include <sstream>

Parser::Parser(const std::string &input_file_) : input_file(input_file_) {}

Parser::~Parser() { input_file.close(); }

Data Parser::parse() {
    Data data;
    data.number_of_tables = parse_number_of_tables();
    auto [start_time, end_time] = parse_time();
    data.start_time = start_time;
    data.end_time = end_time;
    data.price_per_hour = parse_price_per_hour();
    data.events = parse_events(data.number_of_tables);
    return data;
}

int Parser::parse_number_of_tables() {
    int line_number = 1;
    Validator validator(line_number);
    std::string input_line;
    if (std::getline(input_file, input_line)) {
        std::stringstream sstream(input_line);
        int number_of_tables = 0;
        if (sstream >> number_of_tables && number_of_tables > 0) {
            validator.check_line_is_over(sstream);
            return number_of_tables;
        } else {
            throw ErrorInInputFileException(line_number);
        }
    } else {
        throw std::runtime_error("Unable to read " + std::to_string(line_number) +
                                 " line");
    }
}

std::pair<int, int> Parser::parse_time() {
    int line_number = 2;
    Validator validator(line_number);
    std::string input_line;
    if (std::getline(input_file, input_line)) {
        std::stringstream sstream(input_line);
        std::pair<int, int> time;
        std::string start;
        std::string end;
        if (sstream >> start && sstream >> end) {
            validator.check_line_is_over(sstream);
            validator.check_time_is_correct(start);
            validator.check_time_is_correct(end);
            time = {Converter::convert_time_in_string_to_minutes(start),
                    Converter::convert_time_in_string_to_minutes(end)};
            return time;
        } else {
            throw ErrorInInputFileException(line_number);
        }
    } else {
        throw std::runtime_error("Unable to read " + std::to_string(line_number) +
                                 " line");
    }
}

int Parser::parse_price_per_hour() {
    int line_number = 3;
    Validator validator(line_number);
    std::string input_line;
    if (std::getline(input_file, input_line)) {
        std::stringstream sstream(input_line);
        int price_per_hour = 0;
        if (sstream >> price_per_hour && price_per_hour > 0) {
            validator.check_line_is_over(sstream);
            return price_per_hour;
        } else {
            throw ErrorInInputFileException(line_number);
        }
    } else {
        throw std::runtime_error("Unable to read " + std::to_string(line_number) +
                                 " line");
    }
}

std::vector<Event> Parser::parse_events(int number_of_tables) {
    int line_number = 4;
    Validator validator(line_number);
    std::string input_line;
    std::vector<Event> events;
    while (std::getline(input_file, input_line)) {
        std::stringstream sstream(input_line);
        std::string time;
        int id = 0;
        std::string client_name;
        int table_number = 0;
        if (sstream >> time && sstream >> id && sstream >> client_name) {
            validator.check_id_is_correct(id);
            if (id == 2) {
                if (sstream >> table_number) {
                    validator.check_table_number_is_correct(table_number,
                                                            number_of_tables);
                } else {
                    throw ErrorInInputFileException(line_number);
                }
            }

            validator.check_time_is_correct(time);
            validator.check_name_is_correct(client_name);
            validator.check_line_is_over(sstream);

            int time_in_minutes = Converter::convert_time_in_string_to_minutes(time);
            if (!events.empty()) {
                validator.check_time_is_in_chronological_order(time_in_minutes,
                                                               events.back().time);
            }

            if (id == 2) {
                events.emplace_back(time_in_minutes, id, client_name, table_number);
            } else {
                events.emplace_back(time_in_minutes, id, client_name);
            }

            line_number++;
        } else {
            throw ErrorInInputFileException(line_number);
        }
    }
    return events;
}
