compiler     	= clang++-15# with g++ and ubuntu 22.04 I've been getting this bug https://github.com/actions/runner-images/issues/9524
flags 			= -std=c++17 -Wall -Werror -Wextra -fsanitize=undefined

main		    = main.cpp
src_main		= parser/parser.cpp parser/converter.cpp parser/validator.cpp executor/executor.cpp data/data.cpp data/exceptions.cpp
src_test 		= tests/converter_test.cpp  tests/parser_test.cpp  tests/validator_test.cpp tests/doctest_main.cpp tests/main_test.cpp
files = main test
.PHONY: all clean run

main:
	mkdir bin
	$(compiler) $(main) $(flags) $(src_main) -o bin/main

test:
	mkdir bin
	$(compiler) $(flags) $(src_main) $(src_test) -o bin/test
	./bin/test

clean:
	rm -rf bin