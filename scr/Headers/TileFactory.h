#pragma once

#include "Defines.h"

class Object;
class Tile;
template<class T>
class Warrior_O;

///	---------------------//
//	Interface Factory	///

class Factory {

public:
	virtual Object* getObject(Tile*) = 0;
};

///	---------------------//
//	Concrete Factorys	///

class Player_F : Factory {

public:
	virtual Object* getObject(Tile*);
};

template<class T>
class Warrior_F : Factory {

public:
	virtual Object* getObject(Tile* tile) {

		return (Object*)new Warrior_O<T>(tile);
	};
};

class Coin_F : Factory {

public:
	virtual Object* getObject(Tile*);
};

class Key_F : Factory {

public:
	virtual Object* getObject(Tile*);
};

class Bag_F : Factory {

public:
	virtual Object* getObject(Tile*);
};

class Wall_F : Factory {

public:
	virtual Object* getObject(Tile*);
};

class Start_F : Factory {

public:
	virtual Object* getObject(Tile*);
};

class Exit_F : Factory {

public:
	virtual Object* getObject(Tile*);
};