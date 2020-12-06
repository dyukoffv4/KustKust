#include "../Headers/TileObject.h"
#include "../Headers/TileFactory.h"
#include "../Headers/Tile.h"
#include "../Headers/Area.h"
#include "../List.h"

// parent handler //

Object::Object(short _x, short _y) {

	this->x = _x;
	this->y = _y;
	this->x_p = _x;
	this->y_p = _y;
}

short Object::getX() {

	return x;
}

short Object::getY() {

	return y;
}

void Object::move(short _x, short _y) {

	x_p = x;
	y_p = y;

	y = _y;
	x = _x;

	if (x < 0 || x >= Area::getArea().getWidth()) x = x_p;
	if (y < 0 || y >= Area::getArea().getHeight()) y = y_p;

	if (x == x_p && y == y_p) return;

	if (this->getName() == PLR) {

		Area::getArea().getTile(x_p, y_p)->setSom(nullptr);
		Area::getArea().getTile(x, y)->delSom();
		Area::getArea().getTile(x, y)->setSom(this);
	}
	else {

		Area::getArea().getTile(x_p, y_p)->setThg(nullptr);
		Area::getArea().getTile(x, y)->delThg();
		Area::getArea().getTile(x, y)->setThg(this);
	}
}

void Object::moveBack() {

	x = x_p;
	y = y_p;

	if (x == x_p && y == y_p) return;

	if (this->getName() == PLR) {

		Area::getArea().getTile(x, y)->setSom(nullptr);
		Area::getArea().getTile(x_p, y_p)->delSom();
		Area::getArea().getTile(x_p, y_p)->setSom(this);
	}
	else {

		Area::getArea().getTile(x, y)->setThg(nullptr);
		Area::getArea().getTile(x_p, y_p)->delThg();
		Area::getArea().getTile(x_p, y_p)->setThg(this);
	}
}

List* Object::getInvent() {

	return new List;
}

// virtual handler //

char Player_O::getName() {

	return PLR;
}

Player_O::Player_O(short x, short y) : Object(x, y) {

	invent = new List;
}

Player_O::~Player_O() {

	delete invent;
}

List* Player_O::getInvent() {

	return this->invent;
}

void operator< (Player_O& plr, Object& obj) {

	Factory* factory = nullptr;

	switch (obj.getName()) {

	case COIN:
		factory = (Factory*)new Coin_F;
		break;
	case BAG:
		factory = (Factory*)new Bag_F;
		break;
	case KEY:
		factory = (Factory*)new Key_F;
		break;
	}

	Object* _obj = nullptr;
	if (factory) _obj = factory->getObject(0, 0);
	plr.invent->push(_obj);
}

void operator> (Player_O& plr, Object& obj) {

	delete plr.invent->pop(&obj);
}

void operator<< (Player_O& plr, Object* obj) {

	plr.invent->push(obj);
}

void operator>> (Player_O& plr, Object* obj) {

	plr.invent->pop(obj);
}

char Coin_O::getName() {

	return COIN;
}

char Key_O::getName() {

	return KEY;
}

char Bag_O::getName() {

	return BAG;
}

char Wall_O::getName() {

	return WALL;
}

char Start_O::getName() {

	return START;
}

char Exit_O::getName() {

	return EXIT;
}