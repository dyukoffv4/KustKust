#include "../Headers/Game.h"

int WinMain() {

	Game game("Game", "C:/GameRes/ground.txt", "C:/GameRes/sprites.png");
	game.loop();

	return 0;
}