
all: lextest

lextest: lextest_src
	gcc -g -o lextest miniawk_lex.c

lextest_src: miniawk.l
	flex -o miniawk_lex.c miniawk.l
