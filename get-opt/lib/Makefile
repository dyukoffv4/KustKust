SRC = src/
DST = ../bin/
NAME = getopt


all: $(DST)key.o $(DST)terminal.o
	g++ -shared $(DST)key.o $(DST)terminal.o -o $(DST)$(NAME).so

$(DST)key.o: $(SRC)key.cpp $(SRC)key.hpp $(SRC)defines.hpp
	g++ -fPIC -c $(SRC)key.cpp -o $(DST)key.o

$(DST)terminal.o: $(SRC)terminal.cpp $(SRC)terminal.hpp $(SRC)defines.hpp
	g++ -fPIC -c $(SRC)terminal.cpp -o $(DST)terminal.o

clean:
	rm -rf $(DST)key.o $(DST)terminal.o $(DST)$(NAME).so