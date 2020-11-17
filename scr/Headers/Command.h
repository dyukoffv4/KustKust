#pragma once

#include "Defines.h"

class Player;

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
	Player* receiver;
	char direct;

public:
	PlayerMove_C(Player* _receiver, char _direct);
	virtual void execute();
};