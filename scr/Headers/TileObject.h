#pragma once

#include "Defines.h"

///	---------------------//
//	Interface Object	///

class CommonObject {

protected:
	short x_pos;
	short y_pos;
	short x_prepos;
	short y_prepos;

public:
	CommonObject(short, short);

	virtual short getX();
	virtual short getY();

	virtual char getName() = 0;
};

///	---------------------//
//	Concrete Objects	///

class Apple_CO : public CommonObject {
	 
public:
	Apple_CO(short x, short y) : CommonObject(x, y) {};
	virtual char getName();
};

class Key_CO : public CommonObject {

public:
	Key_CO(short x, short y) : CommonObject(x, y) {};
	virtual char getName();
};

class Pie_CO : public CommonObject {

public:
	Pie_CO(short x, short y) : CommonObject(x, y) {};
	virtual char getName();
};

class Wall_CO : public CommonObject {

public:
	Wall_CO(short x, short y) : CommonObject(x, y) {};
	virtual char getName();
};

class Start_CO : public CommonObject {

public:
	Start_CO(short x, short y) : CommonObject(x, y) {};
	virtual char getName();
};

class Exit_CO : public CommonObject {

public:
	Exit_CO(short x, short y) : CommonObject(x, y) {};
	virtual char getName();
};