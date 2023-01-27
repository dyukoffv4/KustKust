LIB = src/lib/
SRC = src/example/
DST = dst/

NAME = get-opt


all: $(DST)main.o $(DST)paint.o $(DST)key.o $(DST)terminal.o
	g++ $(DST)main.o $(DST)paint.o $(DST)key.o $(DST)terminal.o -o $(DST)$(NAME)

$(DST)main.o: $(SRC)main.cpp $(SRC)paint.hpp $(LIB)terminal.hpp
	g++ -c $(SRC)main.cpp -o $(DST)main.o

$(DST)paint.o: $(SRC)paint.cpp $(SRC)paint.hpp
	g++ -c $(SRC)paint.cpp -o $(DST)paint.o

$(DST)key.o: $(LIB)key.cpp $(LIB)key.hpp
	g++ -c $(LIB)key.cpp -o $(DST)key.o

$(DST)terminal.o: $(LIB)terminal.cpp $(LIB)terminal.hpp
	g++ -c $(LIB)terminal.cpp -o $(DST)terminal.o

clean:
	rm -rf $(DST)*.o $(DST)$(NAME)