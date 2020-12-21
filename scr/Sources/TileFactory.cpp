#include "../Headers/TileFactory.h"
#include "../Headers/TileObject.h"


Object* Player_F::getObject(Tile* tile) {

	return new Player_O(tile);
}

Object* Apple_F::getObject(Tile* tile) {

	return new Coin_O(tile);
}

Object* Key_F::getObject(Tile* tile) {

	return new Key_O(tile);
}

Object* Pie_F::getObject(Tile* tile) {

	return new Bag_O(tile);
}

Object* Wall_F::getObject(Tile* tile) {

	return new Wall_O(tile);
}

Object* Start_F::getObject(Tile* tile) {

	return new Start_O(tile);
}

Object* Exit_F::getObject(Tile* tile) {

	return new Exit_O(tile);
}