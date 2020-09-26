#pragma once

#include "Defenition.h"

class Cell {

private:
	unsigned char condition;

public:
	void setFree();
	void setWall();
	void setStart();
	void setExit();

	bool ifFree();
	bool ifWall();
	bool ifStart();
	bool ifExit();

	friend std::ostream& operator<< (std::ostream&, const Cell&);
};