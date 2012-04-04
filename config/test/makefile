
.PHONY:all
all: test_config strcmp test_lexer

test_lexer: test_lexer.cpp ../src/config.a
	g++ -g -o test_lexer.out test_lexer.cpp -I../src ../src/config.a -D_DEBUG

strcmp: strcmp.cpp ../src/config.a
	g++ -g strcmp.cpp -o strcmp.out

test_config: config_test.cpp ../src/config.a
	g++ -o test_config.out config_test.cpp -I../src ../src/config.a -D_DEBUG

.PHONY:clean

clean:
	rm -f *.o  *.out
