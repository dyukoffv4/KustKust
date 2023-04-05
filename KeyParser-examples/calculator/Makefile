SRC = src/
DST = bin/


all: $(SRC)main.cpp
	mkdir -p $(DST)
	g++ $(SRC)main.cpp -l$(LNAME) -o $(DST)count

clean:
	rm -rf $(DST)count
