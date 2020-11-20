#include "../Headers/Game.h"

int main() {

	Game game("Game", "C:/GameRes/ground.txt", "C:/GameRes/sprites.png");
	game.Loop();

	return 0;
}