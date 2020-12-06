#pragma once

#include "Defines.h"
#include <string>

class Model;
class View;

class Controller {

private:
	Model* model;
	View* view;
	bool key_p;

	void getEvent();

public:
	Controller(Model*, View*);

	void looping();
};