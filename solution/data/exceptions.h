#ifndef SOLUTION_EXCEPTIONS_H
#define SOLUTION_EXCEPTIONS_H

#include <stdexcept>

struct ErrorInInputFileException : std::runtime_error {
    explicit ErrorInInputFileException(int line_number_with_error);
};


#endif //SOLUTION_EXCEPTIONS_H
