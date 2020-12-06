#include "../Headers/Model.h"
#include "../Headers/TileObject.h"
#include "../Headers/Tile.h"
#include "../Headers/Strategy.h"
#include "../Headers/Area.h"

Model::Model(std::string a_path, std::string l_path) {

	this->game_end = false;
	this->game_pause = false;
	this->area = &Area::getArea(a_path);
	if (!this->area->isGood()) this->game_end = true;
	this->player = area->getTile(area->getStartX(), area->getStartY())->getSom();
	if (!this->player) this->game_end = true;
	this->context = new Context(this);
}

Model::~Model() {

	delete context;
}

void Model::movePlayer(char direct) {

	if (game_pause) return;

	short x = player->getX();
	short y = player->getY();

	switch (direct) {
	case UP:
		player->move(x, --y);
		break;
	case DOWN:
		player->move(x, ++y);
		break;
	case LEFT:
		player->move(--x, y);
		break;
	case RIGHT:
		player->move(++x, y);
		break;
	}

	if (context->mainWork()) game_end = true;
}

void Model::swapPause() {

	game_pause = !game_pause;
}

Object* Model::getPlr() {

	return player;
}

Area* Model::getArea() {

	return area;
}