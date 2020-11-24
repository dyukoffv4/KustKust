#pragma once

#include "Defines.h"

class PlayGround;
class Player;
class Context;

class Wrapper {

private:
	PlayGround* ground;
	Player* player;
	Context* context;

public:
	bool game_pause;
	bool game_end;

	Wrapper(PlayGround*, Player*, Context*);
	~Wrapper();

	void movePlayer(char);
	void gameLogic();

	Player* getPlayer();
};