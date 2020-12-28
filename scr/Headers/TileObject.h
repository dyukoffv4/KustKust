#pragma once

#include "Defines.h"
#include "List.h"

class Tile;

///	---------------------//
//	Interface Object	///

class Object {

protected:
	Tile* tile;
	Tile* etile;

public:
	Object(Tile*);

	virtual Tile* getTile();
	virtual void move(Tile*);
	virtual void mback();
	virtual List* getInvent();

	virtual char getName() = 0;
	virtual void operator+=(Object*) = 0;
	virtual void operator-=(Object*) = 0;
};

///	---------------------//
//	Concrete Objects	///

class Player_O : public Object {

protected:
	List list;

public:
	Player_O(Tile* _tile) : Object(_tile) {};
	virtual List* getInvent();
	virtual char getName();
	virtual void operator+=(Object*);
	virtual void operator-=(Object*);
};

//

struct stan {

public:
	char state;
	stan() { state = 1; }
};

struct rndm {

public:
	char state;
	rndm() { state = 2; }
};

struct towr {

public:
	char state;
	towr() { state = 3; }
};

class Warrior_OI : public Object {

public:
	Warrior_OI(Tile* _tile) : Object(_tile) {};
	virtual char getName() = 0;
	virtual int getAtt() = 0;
};

template<class T>
class Warrior_O : Warrior_OI {

public:
	Warrior_O(Tile* _tile) : Warrior_OI(_tile) {};
	virtual int getAtt() {

		T t;
		if (t.state == 1) return 1;
		if (t.state == 2) return 2;
		if (t.state == 3) return 3;
	}
	virtual char getName() {

		T t;
		if (t.state == 1) return SWAR;
		if (t.state == 2) return RWAR;
		if (t.state == 3) return TWAR;
	}
	virtual void operator+=(Object*) {};
	virtual void operator-=(Object*) {};
};

//

class Coin_O : public Object {
	 
public:
	Coin_O(Tile* _tile) : Object(_tile) {};
	virtual char getName();
	virtual void operator+=(Object*) {};
	virtual void operator-=(Object*) {};
};

class Key_O : public Object {

public:
	Key_O(Tile* _tile) : Object(_tile) {};
	virtual char getName();
	virtual void operator+=(Object*) {};
	virtual void operator-=(Object*) {};
};

class Bag_O : public Object {

public:
	Bag_O(Tile* _tile) : Object(_tile) {};
	virtual char getName();
	virtual void operator+=(Object*) {};
	virtual void operator-=(Object*) {};
};

class Wall_O : public Object {

public:
	Wall_O(Tile* _tile) : Object(_tile) {};
	virtual char getName();
	virtual void operator+=(Object*) {};
	virtual void operator-=(Object*) {};
};

class Start_O : public Object {

public:
	Start_O(Tile* _tile) : Object(_tile) {};
	virtual char getName();
	virtual void operator+=(Object*) {};
	virtual void operator-=(Object*) {};
};

class Exit_O : public Object {

public:
	Exit_O(Tile* _tile) : Object(_tile) {};
	virtual char getName();
	virtual void operator+=(Object*) {};
	virtual void operator-=(Object*) {};
};