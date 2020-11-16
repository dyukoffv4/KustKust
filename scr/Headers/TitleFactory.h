#pragma once

#include "Def.h"

class Factory {

public:
	virtual Object* getObject() = 0;
};

class Apple_F : Factory {

public:
	virtual Object* getObject();
};

class Rock_F : Factory {

public:
	virtual Object* getObject();
};

class Plate_F : Factory {

public:
	virtual Object* getObject();
};

class Wall_F : Factory {

public:
	virtual Object* getObject();
};

class Start_F : Factory {

public:
	virtual Object* getObject();
};

class Exit_F : Factory {

public:
	virtual Object* getObject();
};