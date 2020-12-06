#pragma once

#include "Defines.h"

class List;

///	---------------------//
//	Interface Object	///

class Object {

protected:
	short x;
	short y;
	short x_p;
	short y_p;

public:
	Object(short, short);
	virtual ~Object() {};

	virtual short getX();
	virtual short getY();

	virtual void move(short, short);
	virtual void moveBack();

	virtual List* getInvent();
	virtual char getName() = 0;
};

///	---------------------//
//	Concrete Objects	///

class Player_O : public Object {

protected:
	List* invent;

public:
	Player_O(short, short);
	~Player_O();

	virtual List* getInvent();
	virtual char getName();

	friend void operator< (Player_O&, Object&);
	friend void operator> (Player_O&, Object&);
	friend void operator<< (Player_O&, Object*);
	friend void operator>> (Player_O&, Object*);
};

class Coin_O : public Object {
	 
public:
	Coin_O(short x, short y) : Object(x, y) {};
	virtual char getName();
};

class Key_O : public Object {

public:
	Key_O(short x, short y) : Object(x, y) {};
	virtual char getName();
};

class Bag_O : public Object {

public:
	Bag_O(short x, short y) : Object(x, y) {};
	virtual char getName();
};

class Wall_O : public Object {

public:
	Wall_O(short x, short y) : Object(x, y) {};
	virtual char getName();
};

class Start_O : public Object {

public:
	Start_O(short x, short y) : Object(x, y) {};
	virtual char getName();
};

class Exit_O : public Object {

public:
	Exit_O(short x, short y) : Object(x, y) {};
	virtual char getName();
};