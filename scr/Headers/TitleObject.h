#pragma once

#include "Def.h"

class Object {

public:
	virtual ~Object() {};
	virtual char getName() = 0;
};

class Apple_O : public Object {

public:
	virtual char getName();
};

class Rock_O : public Object {

public:
	virtual char getName();
};

class Plate_O : public Object {

public:
	virtual char getName();
};

class Wall_O : public Object {

public:
	virtual char getName();
};

class Start_O : public Object {

public:
	virtual char getName();
};

class Exit_O : public Object {

public:
	virtual char getName();
};