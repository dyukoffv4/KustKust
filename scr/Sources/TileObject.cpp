#include "../Headers/TileObject.h"
#include "../Headers/Tile.h"

Object::Object(Tile* _tile) {

	this->tile = _tile;
	this->etile = _tile;
}

Tile* Object::getTile() {

	return tile;
}

void Object::move(Tile* _tile) {

	etile = tile;
	tile = _tile;
	etile->getObjs().pop(this);
	tile->getObjs().push(this);
}

void Object::mback() {

	Tile* _tile = tile;
	tile = etile;
	etile = _tile;
	etile->getObjs().pop(this);
	tile->getObjs().push(this);
}

List* Object::getInvent() {

	return nullptr;
}

//

List* Player_O::getInvent() {

	return &list;
}

char Player_O::getName() {

	return PLR;
}

void Player_O::operator+=(Object* obj) {

	list.push(obj);
}

void Player_O::operator-=(Object* obj) {

	delete list.pop(obj);
}

//

char Coin_O::getName() {

	return COIN;
}

//

char Key_O::getName() {

	return KEY;
}

//

char Bag_O::getName() {

	return BAG;
}

//

char Wall_O::getName() {

	return WALL;
}

//

char Start_O::getName() {

	return START;
}

//

char Exit_O::getName() {

	return EXIT;
}