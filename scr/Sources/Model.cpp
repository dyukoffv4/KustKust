#include "../Headers/Model.h"
#include "../Headers/Player.h"
#include "../Headers/Strategy.h"
#include "../Headers/Area.h"

Model::Model(std::string a_path, std::string l_path)  {

	this->game_end = false;
	this->game_pause = false;
	this->area = &Area::getArea(a_path);
	if (!this->area->isGood()) this->game_end = true;
	this->player = new Player(area->getStartX(), area->getStartY());
	this->context = new Context(player);
}

Model::~Model() {

	delete player;
	delete context;
}

void Model::movePlayer(char direct) {

	if (game_pause) return;

	short x = player->getX();
	short y = player->getY();

	switch (direct) {

	case UP:
		player->Move(x, --y);
		break;

	case DOWN:
		player->Move(x, ++y);
		break;

	case LEFT:
		player->Move(--x, y);
		break;

	case RIGHT:
		player->Move(++x, y);
		break;
	}

	if (context->mainWork()) game_end = true;
}

void Model::swapPause() {

	game_pause = !game_pause;
}

Player* Model::getPlayer() {

	return player;
}

Area* Model::getArea() {

	return area;
}

bool Model::isPause() {

	return game_pause;
}