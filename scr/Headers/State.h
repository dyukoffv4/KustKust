#pragma once

#include "Defines.h"

class Model;

class State {

protected:
	Model* ruled;

public:
	State(Model*);
	virtual void MakeStep(char) = 0;
};

//

class PlrStepState : public State {

public:
	PlrStepState(Model* model) : State(model) {}
	virtual void MakeStep(char);
};

class WarStepState : public State {

public:
	WarStepState(Model* model) : State(model) {}
	virtual void MakeStep(char);
};