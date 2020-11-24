#pragma once

#include "Defines.h"

class Wrapper;

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
	Wrapper* receiver;
	char direct;

public:
	PlayerMove_C(Wrapper*, char);
	virtual void execute();
};

class GamePause_C : public Command {

private:
	Wrapper* receiver;

public:
	GamePause_C(Wrapper*);
	virtual void execute();
};