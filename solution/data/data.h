#ifndef SOLUTION_DATA_H
#define SOLUTION_DATA_H

#include <vector>
#include <string>
#include <optional>

struct Event {
public:
    int time; // in minutes
    int id;
    std::string client_name;
    std::optional<int> table_number; // if the event is a person sits down at the table,
    // then the variable will contain the table number, otherwise nullopt

    Event(int time_, int id_, const std::string &client_name_);

    Event(int time_, int id_, const std::string &client_name_, int table_number_);

};

struct Data {
public:
    int number_of_tables{};
    int start_time{}; // in minutes
    int end_time{}; // also in minutes
    int price_per_hour{};
    std::vector<Event> events; // list of input events

    Data() = default;
};


#endif //SOLUTION_DATA_H
