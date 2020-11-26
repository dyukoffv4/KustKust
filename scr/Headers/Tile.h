#pragma once

#include "Defines.h"
#include <iostream>

class CommonObject;

class Tile {

private:
	CommonObject* object;
	short x;
	short y;

public:
	Tile(short = 0, short = 0);

	void setObj(CommonObject*);
	CommonObject* getObj();
	int getNum();

	bool operator==(Tile&);
};