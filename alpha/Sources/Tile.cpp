#include "../Headers/Tile.h"
#include "../Headers/TileObject.h"

Tile::Tile(short _x, short _y) : someone(nullptr), thing(nullptr), x(_x), y(_y) {}

Tile::~Tile() {

	if (someone) delete someone;
	if (thing) delete thing;
}

short Tile::getX() {

	return x;
}

short Tile::getY() {

	return y;
}

void Tile::setSom(Object* _object) {

	someone = _object;
}

void Tile::delSom() {

	if (someone) delete someone;
	someone = nullptr;
}

Object* Tile::getSom() {

	return someone;
}

void Tile::setThg(Object* _object) {

	thing = _object;
}

void Tile::delThg() {

	if (thing) delete thing;
	thing = nullptr;
}

Object* Tile::getThg() {

	return thing;
}