#pragma once

#include "Defines.h"

class Tile;

///	---------------------//
//	Concrete Iterator	///

class DrawIterator {

private:
	bool line_end;
	bool iter_end;
	const short i_height;
	const short i_width;
	short h_count;
	short w_count;
	Tile* container;
	int length;

public:
	DrawIterator(Tile*, short, short, int);

	DrawIterator& operator++();
	DrawIterator& operator--();

	DrawIterator operator++(int);
	DrawIterator operator--(int);

	void setBegin();
	void setEnd();

	void setX(short);
	void setY(short);

	bool lineEnd();
	bool iterEnd();

	short getX();
	short getY();

	Tile* getCurr();
};