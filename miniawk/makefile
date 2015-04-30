
all: lextest ns

lextest: lextest_src
	gcc -g -o lextest miniawk_lex.c

lextest_src: miniawk.l
	flex -o miniawk_lex.c miniawk.l

ns: ns.y ns.l ns_def.h ns_def.cpp
	bison -t -d ns.y 
	flex -o ns_lex.cpp ns.l
	
	#mv ns.tab.c ns.tab.cpp
	g++ -g -o ns ns.tab.c ns_lex.cpp ns_def.cpp

clean:
	rm -rf *.o *.exe  *.out *.dSYM ns lextest ns.tab.c ns.tab.cpp ns.tab.h ns_lex.c ns_lex.cpp *.stackdump

