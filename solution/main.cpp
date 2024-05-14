#include <iostream>

#include "executor/executor.h"
#include "parser/parser.h"
#include <string>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "The input must receive one argument - a file with input data"
                  << '\n';
        return 0;
    }
    std::string filename = argv[1];
    try {
        Parser parser(filename);
        Data data = parser.parse();
        Executor executor(data);
        executor.run();
    } catch (std::exception &e) {
        std::cout << e.what() << '\n';
    }
    return 0;
}
