CC = g++

SRC = sudoku.cpp sudoku_test.cpp

EXE = sudoku_test

all:
	$(CC) -o $(EXE) $(SRC)

clean:
	rm -f $(EXE)