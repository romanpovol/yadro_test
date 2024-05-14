#include <sstream>
#include "doctest.h"
#include "../executor/executor.h"
#include "../parser/parser.h"


TEST_CASE("check parser") {
    CHECK_NOTHROW(Parser("tests/input/00.in").parse());
    CHECK_NOTHROW(Parser("tests/input/01.in").parse());
    CHECK_THROWS(Parser("tests/input/02.in").parse());
    CHECK_THROWS(Parser("tests/input/03.in").parse());
    CHECK_THROWS(Parser("tests/input/04.in").parse());
    CHECK_THROWS(Parser("tests/input/05.in").parse());
    CHECK_NOTHROW(Parser("tests/input/06.in").parse());
    CHECK_NOTHROW(Parser("tests/input/07.in").parse());
}

TEST_CASE("check parser") {
    std::vector<int> good_tests = {0, 1, 6, 7};
    for (auto &test_number: good_tests) {
        Parser parser("tests/input/0" + std::to_string(test_number) + ".in");
        Data data = parser.parse();
        std::stringstream output;
        Executor(data, output).run();
        std::ifstream answer_file("tests/output/0" + std::to_string(test_number) + ".out");
        std::stringstream answer;
        answer << answer_file.rdbuf();
        answer_file.close();
        CHECK(answer.str() == output.str());
    }
}
