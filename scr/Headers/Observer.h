#pragma once

#include "Defines.h"
#include <string>
#include <fstream>
class Publisher;

///	---------------------//
//	Interface Observer	///

class Observer {

public:
	virtual void update(Publisher*, std::string) = 0;
};

///	---------------------//
//	Concrete Observers	///

class TileObs : Observer {

private:
	std::ofstream file;

public:
	TileObs(std::string);
	~TileObs();

	virtual void update(Publisher*, std::string);
};