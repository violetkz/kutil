
configlib=config.a
SRC= $(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o)
CXXFLAGS += -Wall -g -D_DEBUG


$configlib:$(OBJ)
	@ar r $(configlib) $(OBJ)
	@ranlib $(configlib)

$(OBJ):$(SRC:.cpp=.hpp) $(SRC)

.PYONY: clean
clean:
	rm -f *.o *.a

