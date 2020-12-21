#pragma once

#include "Defines.h"
#include <string>

class Model;
class View;
class Command;

class Controller {

private:
	Model* model;
	View* view;
	Command* command;

	void getEvent();

public:
	Controller(Model*, View*);

	void looping();
};