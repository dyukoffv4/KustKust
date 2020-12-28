#include "../Headers/State.h"
#include "../Headers/Model.h"
#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"
#include "../Headers/Area.h"
#include "../Headers/Iterator.h"

State::State(Model* model) : ruled(model) {}

void PlrStepState::MakeStep(char dir) {

	Tile* tile = ruled->getPlayer()->getTile();

	switch (dir) {
	case UP:
		tile = ruled->getArea()->getTile(tile->getx(), tile->gety() - 1);
		break;
	case DOWN:
		tile = ruled->getArea()->getTile(tile->getx(), tile->gety() + 1);
		break;
	case LEFT:
		tile = ruled->getArea()->getTile(tile->getx() - 1, tile->gety());
		break;
	case RIGHT:
		tile = ruled->getArea()->getTile(tile->getx() + 1, tile->gety());
		break;
	}

	ruled->getPlayer()->move(tile);
}

void WarStepState::MakeStep(char dir) {

	int dx = 0, dy = 0;
	int num;

	for (int i = 0; (*ruled->getWarrs())[i] != nullptr; i++) {

		if ((*ruled->getWarrs())[i]->getName() == SWAR) {

			if ((*ruled->getWarrs())[i]->getTile()->getx() - ruled->getPlayer()->getTile()->getx() > 0) dx = -1;
			if ((*ruled->getWarrs())[i]->getTile()->getx() - ruled->getPlayer()->getTile()->getx() < 0) dx = 1;
			if ((*ruled->getWarrs())[i]->getTile()->gety() - ruled->getPlayer()->getTile()->gety() > 0) dy = -1;
			if ((*ruled->getWarrs())[i]->getTile()->gety() - ruled->getPlayer()->getTile()->gety() < 0) dy = 1;

			Tile* tile = ruled->getArea()->getTile((*ruled->getWarrs())[i]->getTile()->getx() + dx, (*ruled->getWarrs())[i]->getTile()->gety() + dy);
			(*ruled->getWarrs())[i]->move(tile);
			continue;
		}
		if ((*ruled->getWarrs())[i]->getName() == RWAR) {

			num = rand() % 3;
			Tile* tile = ruled->getArea()->getTile((*ruled->getWarrs())[i]->getTile()->getx() - 1 + num, (*ruled->getWarrs())[i]->getTile()->gety() - 1 + num);
			(*ruled->getWarrs())[i]->move(tile);
			continue;
		}
		if ((*ruled->getWarrs())[i]->getName() == TWAR) {}
	}
}