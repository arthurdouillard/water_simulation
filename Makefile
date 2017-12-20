CC= clang++
CXXFLAGS= -Wall -pedantic -std=c++11 -Wextra -Iglad/include
LDFLAGS= -lglfw

VPATH= src
SRC= src/main.cc glad/src/glad.c
BIN= synth

all:
	$(CC) $(CXXFLAGS) $(LDFLAGS) $(SRC) -o $(BIN)

.PHONY: clean
clean:
	rm -rf $(OBJS)
	rm -rf $(BIN)
