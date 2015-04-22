
all: lextest ns

lextest: lextest_src
	gcc -g -o lextest miniawk_lex.c

lextest_src: miniawk.l
	flex -o miniawk_lex.c miniawk.l

ns: ns.y ns.l ns_def.h
	bison -d ns.y 
	flex -o ns_lex.c ns.l
	
	g++ -g -o ns  ns.tab.c ns_lex.c 

