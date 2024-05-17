#include "exceptions.h"

ErrorInInputFileException::ErrorInInputFileException(const std::string& string_with_error) :
        std::runtime_error(string_with_error) {}