#ifndef SOLUTION_PARSER_H
#define SOLUTION_PARSER_H

#include "../data/data.h"

#include <fstream>
#include <string>

struct Parser {
public:
    Parser(const std::string &filename);

    ~Parser();

    Parser(const Parser &other) = delete;

    Parser(Parser &&other) noexcept = default;

    Parser &operator=(const Parser &other) = delete;

    Parser &operator=(Parser &&other) noexcept = default;
    // rule of five

    Data parse();

private:
    std::ifstream input_file;

    int parse_number_of_tables(); // function parse and returns a number of tables

    std::pair<int, int> parse_time(); // function parse and returns a pair of
    // values {start_time, end_time}

    int parse_price_per_hour(); // function parse and returns a price per hour for
    // table

    std::vector<Event> parse_events(
            int number_of_tables); // function parse and returns a vector of events
};

#endif // SOLUTION_PARSER_H
