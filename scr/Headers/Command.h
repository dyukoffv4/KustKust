#pragma once

#include "Def.h"

class Command {

public:
	virtual void execute() = 0;
};

class PlrMove_C : public Command {

private:
	Player* receiver;

public:
	PlrMove_C(Player* _receiver);
	virtual void execute();
};