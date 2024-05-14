#include "executor.h"

#include <iostream>
#include "../parser/converter.h"

Executor::Executor(Data &data_) : data(data_), ostream(std::cout) {
    tables.resize(data.number_of_tables + 1);
    for (int i = 1; i <= data.number_of_tables; i++) {
        free_table_numbers.insert(i);
    }
    tables_info.resize(data.number_of_tables + 1);
}
Executor::Executor(Data &data_, std::ostream& ostream_) : data(data_), ostream(ostream_) {
    tables.resize(data.number_of_tables + 1);
    for (int i = 1; i <= data.number_of_tables; i++) {
        free_table_numbers.insert(i);
    }
    tables_info.resize(data.number_of_tables + 1);
}

void Executor::run() {
    ostream << Converter::convert_time_in_minutes_to_string(data.start_time) << '\n';
    for (auto const &event: data.events) {
        switch (event.id) {
            case 1: {
                client_arrived(event);
                break;
            }
            case 2: {
                client_sat(event);
                break;
            }
            case 3: {
                client_waiting(event);
                break;
            }
            case 4: {
                client_left_from_table(event);
                break;
            }
            default: {
                throw std::runtime_error("WTF");
            }
        }
    }


    for (auto const &[client_name, status]: clients) {
        if (status == 2) {
            client_left(client_name, data.end_time);
        }
    }
    ostream << Converter::convert_time_in_minutes_to_string(data.end_time) << '\n';
    for (std::size_t i = 1; i < tables_info.size(); i++) {
        int revenue = tables_info[i].revenue;
        int time_table_was_busy = tables_info[i].time_table_was_busy;
        ostream << i << ' ' << revenue << ' ' << Converter::convert_time_in_minutes_to_string(time_table_was_busy)
                  << '\n';
    }


}

void Executor::client_arrived(const Event &event) {
    print_event(event);
    if (event.time < data.start_time || event.time > data.end_time) {
        print_error(event.time, "NotOpenYet");
        return;
    }
    if (clients.find(event.client_name) != clients.end()) {
        print_error(event.time, "YouShallNotPass");
        return;
    }
    clients[event.client_name] = 1;
}

void Executor::client_sat(const Event &event) {
    print_event(event);
    if (clients.find(event.client_name) == clients.end()) {
        print_error(event.time, "ClientUnknown");
        return;
    }
    if (!tables[event.table_number.value()].empty()) {
        print_error(event.time, "PlaceIsBusy");
        return;
    }
    if (table_number_by_client.find(event.client_name) != table_number_by_client.end()) {
        int previous_table_number = table_number_by_client[event.client_name];
        update_information_about_table(previous_table_number, event.time);
        tables[previous_table_number] = "";
        free_table_numbers.insert(previous_table_number);
    }
    update_information_about_table(event.table_number.value(), event.time);
    table_number_by_client[event.client_name] = event.table_number.value();
    tables[event.table_number.value()] = event.client_name;
    free_table_numbers.erase(event.table_number.value());
    clients[event.client_name] = 2;
}

void Executor::client_waiting(const Event &event) {
    print_event(event);
    if (!free_table_numbers.empty()) {
        print_error(event.time, "ICanWaitNoLonger!");
        return;
    }
    if (static_cast<int>(queue.size()) == data.number_of_tables) {
        client_left(event.client_name, event.time);
        if (clients.find(event.client_name) != clients.end()) {
            clients.erase(event.client_name);
        }
        return;
    }
    queue.push(event.client_name);
    clients[event.client_name] = 3;
}

void Executor::client_left_from_table(const Event &event) {
    print_event(event);
    if (clients.find(event.client_name) == clients.end()) {
        print_error(event.time, "ClientUnknown");
        return;
    }

    if (table_number_by_client.find(event.client_name) == table_number_by_client.end()) {
        clients.erase(event.client_name);
        return;
    }

    int previous_table_number = table_number_by_client[event.client_name];
    update_information_about_table(previous_table_number, event.time);
    tables[previous_table_number] = "";
    table_number_by_client.erase(event.client_name);
    free_table_numbers.insert(previous_table_number);
    clients.erase(event.client_name);

    if (!queue.empty()) {
        client_from_queue_sat(event.time, previous_table_number);
    }
}

void Executor::client_from_queue_sat(int time, int table_number) {
    std::string client_from_queue = queue.front();
    queue.pop();
    ostream << Converter::convert_time_in_minutes_to_string(time) << ' ' << 12 << ' ' << client_from_queue
              << ' ' << table_number << '\n';

    update_information_about_table(table_number, time);
    free_table_numbers.erase(table_number);
    table_number_by_client[client_from_queue] = table_number;
    tables[table_number] = client_from_queue;
    clients[client_from_queue] = 2;

}

void Executor::client_left(const std::string &client_name, int time) {
    ostream << Converter::convert_time_in_minutes_to_string(time) << ' ' << 11 << ' ' << client_name << '\n';
    if (table_number_by_client.find(client_name) != table_number_by_client.end()) {
        int previous_table_number = table_number_by_client[client_name];
        update_information_about_table(previous_table_number, time);
        tables[previous_table_number] = "";
        free_table_numbers.insert(previous_table_number);
    }
}

void Executor::print_event(const Event &event) {
    ostream << Converter::convert_time_in_minutes_to_string(event.time) << ' ' << event.id << ' '
              << event.client_name;
    if (event.table_number.has_value()) {
        ostream << ' ' << event.table_number.value();
    }
    ostream << '\n';
}

void Executor::print_error(int time, const std::string &error_message) {
    ostream << Converter::convert_time_in_minutes_to_string(time) << ' ' << 13 << ' ' << error_message << '\n';
}

void Executor::update_information_about_table(int number, int time) {
    if (tables_info[number].time_when_table_begin_busy.has_value()) {
        int time_when_table_begin_busy = tables_info[number].time_when_table_begin_busy.value();
        int diff_time = time - time_when_table_begin_busy;
        tables_info[number].time_table_was_busy += diff_time;
        tables_info[number].revenue += (diff_time + 59) / 60 * data.price_per_hour;
        tables_info[number].time_when_table_begin_busy.reset();
    } else {
        tables_info[number].time_when_table_begin_busy.emplace(time);
    }
}
