HEADERS=./Headers/Def.h ./Headers/PG.h ./Headers/PG_it.h ./Headers/Cell.h
OBJECTS=Main.o Cell.o PG_it.o PG.o

all: Main
	
Main: $(OBJECTS)
	g++ $(OBJECTS) -o Presentation
	
PG.o: $(HEADERS) ./Sources/PG.cpp
	g++ -c ./Sources/PG.cpp
	
PG_it.o: $(HEADERS) ./Sources/PG_it.cpp
	g++ -c ./Sources/PG_it.cpp
	
Cell.o: $(HEADERS) ./Sources/Cell.cpp
	g++ -c ./Sources/Cell.cpp
	
Main.o: $(HEADERS) ./Sources/Main.cpp
	g++ -c ./Sources/Main.cpp
	
clean:
	rm -rf *.o Main
