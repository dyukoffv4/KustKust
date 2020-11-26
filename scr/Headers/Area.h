#pragma once

#include "Defines.h"
#include <fstream>
#include <string>

class DrawIterator;
class CommonObject;
class Tile;

///	---------------------//
//	Concrete PlayGround	///

class Area {

private:
	Tile* data;
	int data_len;
	short width;
	short height;

	//-------------------------

	Area(std::string);
	~Area();

	void read(std::istream&);

public:
	static Area& getArea(std::string path = "");

	//-------------------------

	void pushTile(Tile);
	void popTile(Tile);

	bool isGood();
	short getWidth();
	short getHeight();
	DrawIterator getIterator();
	Tile* getTile(short, short);
	short getStartX();
	short getStartY();
};