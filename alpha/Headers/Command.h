#pragma once

#include "Defines.h"

class Model;

///	---------------------//
//	Interface Command	///

class Command {

public:
	virtual void execute() = 0;
};

///	---------------------//
//	Concrete Commands	///

class PlayerMove_C : public Command {

private:
	Model* receiver;
	char direct;

public:
	PlayerMove_C(Model*, char);
	virtual void execute();
};

class GamePause_C : public Command {

private:
	Model* receiver;

public:
	GamePause_C(Model*);
	virtual void execute();
};