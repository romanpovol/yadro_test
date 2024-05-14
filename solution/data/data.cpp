#include "data.h"

Event::Event(int time_,
             int id_,
             const std::string &client_name_) : time(time_), id(id_), client_name(client_name_), table_number() {}

Event::Event(int time_,
             int id_,
             const std::string &client_name_,
             int table_number_) : time(time_), id(id_), client_name(client_name_), table_number(table_number_) {}
