#ifndef SOLUTION_EXCEPTIONS_H
#define SOLUTION_EXCEPTIONS_H

#include <stdexcept>

struct ErrorInInputFileException : std::runtime_error {
    explicit ErrorInInputFileException(const std::string& string_with_error);
};


#endif //SOLUTION_EXCEPTIONS_H
