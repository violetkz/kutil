SRC= $(wildcard *.c)
OBJ= $(SRC:.c=.o)
LIB= -L/usr/local/lib -levent -lpcre
CFLAGS += -Wall -g -D__DEBUG__ -I/usr/local/include

all: test.exe

test.exe: $(OBJ)
	gcc -o test $(CFLAGS) $(OBJ) $(LIB)
	
.PYONY: clean
clean:
	rm -f *.o *.a test test.exe

