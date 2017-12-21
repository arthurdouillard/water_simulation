CC= clang++
CXXFLAGS= -Wall -pedantic -std=c++11 -Wextra -Iglad/include
LDFLAGS= -lglfw

VPATH= src
SRC= src/main.cc src/waves.cc glad/src/glad.c
BIN= water

all:
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(SRC) -o $(BIN)

.PHONY: clean
clean:
	rm -rf *.o
	rm -rf $(BIN)
