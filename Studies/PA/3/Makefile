BIN = bin/
SRC = src/

all:	serial # parallel improved

serial:		$(SRC)serial.cpp
	mkdir -p $(BIN)
	g++ -fopenmp $(SRC)serial.cpp -o $(BIN)serial

# parallel: 	$(SRC)parallel.cpp
# 	mkdir -p $(BIN)
# 	g++ -fopenmp $(SRC)parallel.cpp -o $(BIN)parallel

# improved:	$(SRC)improved.cpp
# 	mkdir -p $(BIN)
# 	g++ -fopenmp $(SRC)improved.cpp -o $(BIN)improved

clear:
	rm -rf $(BIN)
