#pragma once

#include "Def.h"

class PlayGround {

private:
	Title** data;
	short width;
	short height;
	short x_start;
	short y_start;
	bool good;

	//-------------------------

	PlayGround(const char*);
	~PlayGround();

	PlayGround(const PlayGround&);
	PlayGround& operator = (const PlayGround&);

	friend std::istream& operator>> (std::istream&, PlayGround&);

public:
	static PlayGround& getPG(const char* path = "");

	PlayGround(PlayGround&&) noexcept;
	PlayGround& operator = (PlayGround&&) noexcept;

	//-------------------------

	bool isGood();
	short getWidth();
	short getHeight();
	IteratorPG getIterator();
	Title& getTitle(short, short);
	short getStartX();
	short getStartY();
};