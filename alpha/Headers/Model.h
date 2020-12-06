#pragma once

#include "Defines.h"
#include <string>

class Area;
class Object;
class Context;

class Model {

private:
	Area* area;
	Object* player;
	Context* context;

public:
	bool game_pause;
	bool game_end;

	Model(std::string = GROUND_PATH, std::string = LOG_PATH);
	~Model();

	void movePlayer(char);
	void swapPause();

	Object* getPlr();
	Area* getArea();
};