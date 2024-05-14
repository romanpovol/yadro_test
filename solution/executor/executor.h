#ifndef SOLUTION_EXECUTOR_H
#define SOLUTION_EXECUTOR_H

#include "../data/data.h"
#include <map>
#include <queue>
#include <unordered_set>
#include <unordered_map>

struct Executor {
private:
    Data& data;
    std::queue<std::string> queue; // current queue
    std::map<std::string, int> clients; // the id of the last operation associated with a person
    // this is the person’s status

    std::vector<std::string> tables; // if the table is busy, the customer's name is written in the cell, otherwise an empty line
    std::unordered_map<std::string, int> table_number_by_client;
    std::unordered_set<int> free_table_numbers; // the numbers of the tables that are free
    std::ostream& ostream; // in order to redirect std::cout during testing

    struct InformationAboutTable {
        int revenue{};
        int time_table_was_busy{};
        std::optional<int> time_when_table_begin_busy;

        InformationAboutTable() = default;
    };

    std::vector<InformationAboutTable> tables_info; // for each table, we store the amount of revenue and how long it was busy

    void update_information_about_table(int number, int time);

    void client_arrived(const Event &event);

    void client_sat(const Event &event);

    void client_waiting(const Event &event);

    void client_left_from_table(const Event &event);

    void client_from_queue_sat(int time, int table_number);

    void client_left(const std::string &client_name, int time);

    void print_event(const Event &event);

    void print_error(int time, const std::string &error_message);

public:
    explicit Executor(Data &data);

    explicit Executor(Data &data, std::ostream& ostream_);


    void run();
};

#endif //SOLUTION_EXECUTOR_H
