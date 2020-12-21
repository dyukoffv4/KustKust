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