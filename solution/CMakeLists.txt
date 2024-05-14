cmake_minimum_required(VERSION 3.28)
project(solution)

add_compile_options(-Wall -Wextra -fsanitize=address -fsanitize=undefined)
add_link_options(-Wall -Wextra -fsanitize=address -fsanitize=undefined)

set(CMAKE_CXX_STANDARD 17)

add_executable(solution
        main.cpp
        parser/converter.cpp
        parser/validator.cpp
        parser/parser.cpp
        data/data.cpp
        data/exceptions.cpp
        executor/executor.cpp)

add_executable(tests
        parser/converter.cpp
        parser/validator.cpp
        parser/parser.cpp
        data/data.cpp
        data/exceptions.cpp
        executor/executor.cpp
        tests/converter_test.cpp
        tests/parser_test.cpp
        tests/validator_test.cpp
        tests/doctest_main.cpp
        tests/main_test.cpp)
