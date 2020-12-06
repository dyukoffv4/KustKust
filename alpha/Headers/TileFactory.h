#pragma once

#include "Defines.h"

class Object;

///	---------------------//
//	Interface Factory	///

class Factory {

public:
	virtual Object* getObject(short, short) = 0;
};

///	---------------------//
//	Concrete Factorys	///

class Coin_F : Factory {

public:
	virtual Object* getObject(short, short);
};

class Key_F : Factory {

public:
	virtual Object* getObject(short, short);
};

class Bag_F : Factory {

public:
	virtual Object* getObject(short, short);
};

class Wall_F : Factory {

public:
	virtual Object* getObject(short, short);
};

class Start_F : Factory {

public:
	virtual Object* getObject(short, short);
};

class Exit_F : Factory {

public:
	virtual Object* getObject(short, short);
};