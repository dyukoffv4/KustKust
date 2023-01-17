SRC_DIR = src/
DST_DIR = dst/
NAME = test

all: $(DST_DIR)main.o $(DST_DIR)utils.o $(DST_DIR)key.o $(DST_DIR)terminal.o
	g++ $(DST_DIR)main.o $(DST_DIR)utils.o $(DST_DIR)key.o $(DST_DIR)terminal.o -o $(DST_DIR)$(NAME)

$(DST_DIR)main.o: $(SRC_DIR)main.cpp $(SRC_DIR)utils.hpp $(SRC_DIR)key.hpp
	g++ -c $(SRC_DIR)main.cpp -o $(DST_DIR)main.o

$(DST_DIR)utils.o: $(SRC_DIR)utils.cpp $(SRC_DIR)utils.hpp
	g++ -c $(SRC_DIR)utils.cpp -o $(DST_DIR)utils.o

$(DST_DIR)key.o: $(SRC_DIR)key.cpp $(SRC_DIR)key.hpp
	g++ -c $(SRC_DIR)key.cpp -o $(DST_DIR)key.o

$(DST_DIR)terminal.o: $(SRC_DIR)terminal.cpp $(SRC_DIR)terminal.hpp
	g++ -c $(SRC_DIR)terminal.cpp -o $(DST_DIR)terminal.o

clean:
	rm -rf $(DST_DIR)*.o $(DST_DIR)$(NAME)