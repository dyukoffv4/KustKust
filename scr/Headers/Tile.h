#pragma once

#include "Defines.h"
#include "List.h"
#include <iostream>
#include <list>
#include <string>

class Bridge;
class Object;

///	---------------------//
//	Interface Publisher	///

class Publisher {

protected:
	std::list<Bridge*> observers;

public:
	virtual void attach(Bridge*) = 0;
	virtual void detach(Bridge*) = 0;
	virtual void notify(std::string = "") = 0;
};

///	---------------------//
//	Concrete Publisher	///

class Tile : public Publisher {

private:
	List objects;
	short x;
	short y;

public:
	Tile(short = 0, short = 0);
	~Tile();

	List& getObjs();
	short getx();
	short gety();

	virtual void attach(Bridge*);
	virtual void detach(Bridge*);
	virtual void notify(std::string = "");

	friend std::ostream& operator<<(std::ostream&, Tile*);
};