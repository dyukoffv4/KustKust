#include "../Headers/State.h"
#include "../Headers/Model.h"
#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"
#include "../Headers/Area.h"

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