#ifndef SOLUTION_VALIDATOR_H
#define SOLUTION_VALIDATOR_H

#include <sstream>
#include <memory>

struct Validator {
private:
    int& line_number;

public:

    explicit Validator(int& line_number_);

    void check_line_is_over(std::stringstream &sstreamer) const; // checks that the line has ended

    void check_time_is_correct(const std::string &time) const; // checks that the time is provided in the correct form

    void check_name_is_correct(const std::string &name) const; // checks that the time of the client's name consists of valid characters

    void check_table_number_is_correct(int table_number, int number_of_tables) const; // checks that the table number is correct

    void check_id_is_correct(int id) const; // checks that the id is correct

    void check_time_is_in_chronological_order(int curren_time, int previous_time) const; // checks that the events are given in chronological order

};

#endif //SOLUTION_VALIDATOR_H
