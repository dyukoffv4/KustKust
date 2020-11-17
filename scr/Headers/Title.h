#pragma once

#include "Defines.h"
#include <iostream>
class Object;

class Title {

private:
	Object* object;
	short x_coord;
	short y_coord;

public:
	Title(short x = 0, short y = 0);
	~Title();

	void setObj(Object*);
	Object* getObj();

	friend std::ostream& operator<<(std::ostream&, Title*);
};