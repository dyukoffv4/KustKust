#include "../Headers/TileFactory.h"
#include "../Headers/TileObject.h"

Object* Coin_F::getObject(short x, short y) {

	return new Coin_O(x, y);
}

Object* Key_F::getObject(short x, short y) {

	return new Key_O(x, y);
}

Object* Bag_F::getObject(short x, short y) {

	return new Bag_O(x, y);
}

Object* Wall_F::getObject(short x, short y) {

	return new Wall_O(x, y);
}

Object* Start_F::getObject(short x, short y) {

	return new Start_O(x, y);
}

Object* Exit_F::getObject(short x, short y) {

	return new Exit_O(x, y);
}