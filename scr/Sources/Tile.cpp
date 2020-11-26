#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"

Tile::Tile() : object(nullptr) {}

Tile::~Tile() {

	if (object) delete object;
}

void Tile::setObj(CommonObject* _object) {

	if (object) delete object;
	object = _object;
}

CommonObject* Tile::getObj() {

	return this->object;
}