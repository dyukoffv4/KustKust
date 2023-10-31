BIN = bin/
SRC = src/

all:		cmain fmain

cmain:		$(SRC)main.cpp shared serial parallel improved
	g++ -fopenmp $(SRC)main.cpp $(BIN)shared.o $(BIN)serial.o $(BIN)parallel.o $(BIN)improved.o -o $(BIN)cmain

fmain:		$(SRC)main.cpp shared serial parallel improved
	g++ -fopenmp $(SRC)fmain.cpp $(BIN)shared.o $(BIN)serial.o $(BIN)parallel.o $(BIN)improved.o -o $(BIN)fmain

serial:		$(SRC)serial.cpp shared
	g++ -c -fopenmp $(SRC)serial.cpp $(BIN)shared.o -o $(BIN)serial.o

parallel:	$(SRC)parallel.cpp shared
	g++ -c -fopenmp $(SRC)parallel.cpp $(BIN)shared.o -o $(BIN)parallel.o

improved:	$(SRC)improved.cpp shared
	g++ -c -fopenmp $(SRC)improved.cpp $(BIN)shared.o -o $(BIN)improved.o

shared:		$(SRC)shared.hpp $(SRC)shared.cpp
	mkdir -p $(BIN)
	g++ -c $(SRC)shared.cpp -o $(BIN)shared.o

clear:
	rm -rf $(BIN)
