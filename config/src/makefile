
configlib=config.a
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
CXXFLAGS += -Wall -g -D_DEBUG


$configlib:$(OBJ)
	ar rvl $(configlib) $(OBJ)
	@ranlib $(configlib)

$(OBJ):$(SRC:.cpp=.hpp)

.PYONY: clean
clean:
	rm -f *.o *.a

