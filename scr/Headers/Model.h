#pragma once

#include "Defines.h"
#include <string>

class Area;
class Context;
class Observer;
class Bridge;
class State;
class Object;
class List;

class Model {

private:
	Area* area;
	Object* player;
	List* warriors;
	Context* context;
	Observer* observer;
	Bridge* bridge;
	State* state;

	bool game_pause;

public:

	bool game_end;

	Model(std::string = GROUND_PATH, std::string = LOG_PATH);
	~Model();

	void moveAll(char);
	void swapPause();

	void setState(State*);
	Object* getPlayer();
	List* getWarrs();
	Area* getArea();
	bool isPause();
};