#pragma once

class Object;

///	---------------------//
//	Interface Factory	///

class Factory {

public:
	virtual Object* getObject() = 0;
};

///	---------------------//
//	Concrete Factorys	///

class Apple_F : Factory {

public:
	virtual Object* getObject();
};

class Key_F : Factory {

public:
	virtual Object* getObject();
};

class Pie_F : Factory {

public:
	virtual Object* getObject();
};

class Wall_F : Factory {

public:
	virtual Object* getObject();
};

class Start_F : Factory {

public:
	virtual Object* getObject();
};

class Exit_F : Factory {

public:
	virtual Object* getObject();
};