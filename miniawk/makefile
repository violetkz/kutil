CPPFLAGS=-g -Wall

all: ns

ns: ns.y ns.l ns_ast.h ns_ast.cpp
	bison -t -d ns.y 
	flex -o ns_lex.cpp ns.l
	
	#mv ns.tab.c ns.tab.cpp
	g++ -g -o ns ns.tab.c ns_lex.cpp ns_ast.cpp

ut_value: ut_ns_value.o ns_value.o
	g++ -g -o ut_value $^ 

ns_value.o: ns_value.h ns_value.cpp

ut_ns_value.o: ut_ns_value.cpp

clean:
	rm -rf *.o *.exe  *.out *.dSYM ns lextest ns.tab.c ns.tab.cpp ns.tab.h ns_lex.c ns_lex.cpp *.stackdump ut_value

