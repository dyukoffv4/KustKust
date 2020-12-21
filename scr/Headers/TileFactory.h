#pragma once

#include "Defines.h"

class Object;
class Tile;

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

class Apple_F : Factory {

public:
	virtual Object* getObject(Tile*);
};

class Key_F : Factory {

public:
	virtual Object* getObject(Tile*);
};

class Pie_F : Factory {

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