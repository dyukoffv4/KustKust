#pragma once

#include "Defines.h"

///	---------------------//
//	Interface Object	///

class Object {

public:
	virtual ~Object() {};
	virtual char getName() = 0;
};

///	---------------------//
//	Concrete Objects	///

class Apple_O : public Object {

public:
	virtual char getName();
};

class Key_O : public Object {

public:
	virtual char getName();
};

class Pie_O : public Object {

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