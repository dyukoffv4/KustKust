BIN = bin/
SRC = src/

all:		serial parallel improved

serial:		$(SRC)serial.cpp $(BIN)shared.o
	g++ -fopenmp $(SRC)serial.cpp $(BIN)shared.o -o $(BIN)serial

parallel:	$(SRC)parallel.cpp $(BIN)shared.o
	g++ -fopenmp $(SRC)parallel.cpp $(BIN)shared.o -o $(BIN)parallel

improved:	$(SRC)improved.cpp $(BIN)shared.o
	g++ -fopenmp $(SRC)improved.cpp $(BIN)shared.o -o $(BIN)improved

$(BIN)shared.o:		$(SRC)shared.hpp $(SRC)shared.cpp
	mkdir -p $(BIN)
	g++ -c $(SRC)shared.cpp -o $(BIN)shared.o

clear:
	rm -rf $(BIN)
