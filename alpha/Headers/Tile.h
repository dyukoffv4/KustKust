#pragma once

#include "Defines.h"

class Object;

class Tile {

private:
	Object* someone;
	Object* thing;
	short x;
	short y;

public:
	Tile(short = 0, short = 0);
	~Tile();

	short getX();
	short getY();

	void setSom(Object*);
	void delSom();
	Object* getSom();
	void setThg(Object*);
	void delThg();
	Object* getThg();
};