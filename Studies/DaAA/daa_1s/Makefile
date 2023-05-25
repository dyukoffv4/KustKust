all:	main.o daa.o
	g++ main.o daa.o -o rbt
	
main.o: daa.h main.cpp
	g++ -c main.cpp
	
daa.o:	daa.h daa.cpp
	g++ -c daa.cpp
