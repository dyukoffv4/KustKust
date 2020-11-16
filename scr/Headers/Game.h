#pragma once

#include "Def.h"

class Game {

private:
	PlayGround* ground;
	Player* player;
	Context* context;
	std::list<Command*> commands;

public:
	Game(const char*);
	~Game();

	void loop();
};