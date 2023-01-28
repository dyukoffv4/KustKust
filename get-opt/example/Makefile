SRC = src/
DST = ../bin/
NAME = getopt


all: $(DST)main.o $(DST)paint.o
	g++ $(DST)main.o $(DST)paint.o -L. $(DST)$(NAME).so -o $(DST)$(NAME)

$(DST)main.o: $(SRC)main.cpp $(SRC)paint.hpp
	g++ -c $(SRC)main.cpp -o $(DST)main.o

$(DST)paint.o: $(SRC)paint.cpp $(SRC)paint.hpp
	g++ -c $(SRC)paint.cpp -o $(DST)paint.o

clean:
	rm -rf $(DST)main.o $(DST)paint.o $(DST)$(NAME)