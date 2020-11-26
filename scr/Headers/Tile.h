#pragma once

#include "Defines.h"
#include <iostream>

class CommonObject;

class Tile {

private:
	CommonObject* object;

public:
	Tile();
	~Tile();

	void setObj(CommonObject*);
	CommonObject* getObj();
};