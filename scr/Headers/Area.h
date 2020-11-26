#pragma once

#include "Defines.h"
#include <fstream>
#include <string>
#include <list>

class Iterator;
class CommonObject;
class Tile;

///	---------------------//
//	Concrete PlayGround	///

class Area {

private:
	Tile** data;
	short width;
	short height;
	std::list<CommonObject*> objects;

	//-------------------------

	Area(std::string);
	~Area();

	void read(std::istream&);

public:
	static Area& getPG(std::string path = "");

	//-------------------------

	std::list<CommonObject*> getObjects();
	bool isGood();
	short getWidth();
	short getHeight();
	Iterator getIterator();
	Tile& getTitle(short, short);
	short getStartX();
	short getStartY();
};