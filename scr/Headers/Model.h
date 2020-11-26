 #pragma once

#include "Defines.h"
#include <string>

class Area;
class Player;
class Context;

class Model {

private:
	Area* area;
	Player* player;
	Context* context;

	bool game_pause;

public:

	bool game_end;

	Model(std::string = GROUND_PATH, std::string = LOG_PATH);
	~Model();

	void movePlayer(char);
	void swapPause();

	Player* getPlayer();
	Area* getArea();
	bool isPause();
};