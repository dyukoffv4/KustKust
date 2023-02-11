SRC = src/
OUT = out/
SFML=-lsfml-graphics -lsfml-window -lsfml-system

all:
	g++ $(SRC)main.cpp $(FROM) $(SFML) -o $(NAME)

part: $(HPP) $(CPP) $(SRC_DEF)
	mkdir -p $(OUT)
	g++ -c $(CPP) -o $(OUT)$(NAME).o

clean:
	rm -rf $(DST)*.o