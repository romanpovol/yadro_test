#include "exceptions.h"

ErrorInInputFileException::ErrorInInputFileException(int line_number_with_error_) :
        std::runtime_error("Error in input file in line: " + std::to_string(line_number_with_error_)) {}