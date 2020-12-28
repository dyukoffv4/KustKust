#pragma once

#include "Defines.h"
#include <fstream>
#include <string>

class Iterator;
class Object;
class Tile;
class List;

///	---------------------//
//	Concrete PlayGround	///

class Area {

private:
	Tile** data;
	short width;
	short height;

	//-------------------------

	Area(std::string);
	~Area();

	void read(std::istream&);

public:
	static Area& getArea(std::string path = "");

	//-------------------------

	bool isGood();
	short getWidth();
	short getHeight();
	Iterator getIterator();
	Tile* getTile(short, short);
	Object* getPlr();
	List* getWarr();
};