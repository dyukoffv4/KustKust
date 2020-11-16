#pragma once

#include "Def.h"

class IteratorPG {

private:
	bool line_end;
	bool iter_end;
	const short i_height;
	const short i_width;
	short h_count;
	short w_count;
	Title** container;

public:
	IteratorPG(Title**, short, short);

	IteratorPG& operator++();
	IteratorPG& operator--();

	IteratorPG operator++(int);
	IteratorPG operator--(int);

	void setBegin();
	void setEnd();

	void setX(short);
	void setY(short);

	bool lineEnd();
	bool iterEnd();

	short getX();
	short getY();

	Title& getCurr();
};