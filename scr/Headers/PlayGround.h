#pragma once

#include "Defines.h"
#include <fstream>
#include <string>
class IteratorPG;
class Title;

///	---------------------//
//	Concrete PlayGround	///

class PlayGround {

private:
	Title** data;
	short width;
	short height;
	short x_start;
	short y_start;
	bool good;

	//-------------------------

	PlayGround(std::string);
	~PlayGround();

	friend std::istream& operator>> (std::istream&, PlayGround&);

public:
	static PlayGround& getPG(std::string path = "");

	//-------------------------

	bool isGood();
	short getWidth();
	short getHeight();
	IteratorPG getIterator();
	Title& getTitle(short, short);
	short getStartX();
	short getStartY();
};