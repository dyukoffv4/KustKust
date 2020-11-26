#pragma once

#include "Defines.h"

class CommonObject;

///	---------------------//
//	Interface Factory	///

class Factory {

public:
	virtual CommonObject* getObject(short, short) = 0;
};

///	---------------------//
//	Concrete Factorys	///

class Apple_F : Factory {

public:
	virtual CommonObject* getObject(short, short);
};

class Key_F : Factory {

public:
	virtual CommonObject* getObject(short, short);
};

class Pie_F : Factory {

public:
	virtual CommonObject* getObject(short, short);
};

class Wall_F : Factory {

public:
	virtual CommonObject* getObject(short, short);
};

class Start_F : Factory {

public:
	virtual CommonObject* getObject(short, short);
};

class Exit_F : Factory {

public:
	virtual CommonObject* getObject(short, short);
};