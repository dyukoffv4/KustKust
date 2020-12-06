#pragma once

#include "Defines.h"

class Model;

///	-----------------//
//	Interface State	///

class State {

protected:
	Model* model;

public:
	void setModel(Model*);
	virtual void playerMove() = 0;
	virtual void warriorMove() = 0;
};

///	-----------------//
//	Concrete States	///

class PlayerState : public State {

public:
	virtual void playerMove();
	virtual void warriorMove();
};

class WarriorState : public State {

public:
	virtual void playerMove();
	virtual void warriorMove();
};