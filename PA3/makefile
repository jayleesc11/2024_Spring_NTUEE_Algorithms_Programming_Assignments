CC = g++
CFLAGS = -c -Wall -std=c++11
OPTFLAGS = -O3

BIN = bin/cb

all	: $(BIN)

$(BIN): main.o CBSolver.o
	$(CC) $(OPTFLAGS) $^ -o $@

main.o: src/main.cpp
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

CBSolver.o: src/CBSolver.cpp src/CBSolver.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

clean:
	rm -f *.o $(BIN)