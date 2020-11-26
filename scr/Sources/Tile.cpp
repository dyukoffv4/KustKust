#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"
#include "../Headers/Area.h"

Tile::Tile(short _x, short _y) : object(nullptr), x(_x), y(_y) {}

void Tile::setObj(CommonObject* _object) {

	if (object) delete object;
	object = _object;
}

CommonObject* Tile::getObj() {

	return this->object;
}

int Tile::getNum() {

	return y * Area::getArea().getHeight() + x;
}

bool Tile::operator==(Tile& tile) {

	return (this->x == tile.x) && (this->y == tile.y);
}