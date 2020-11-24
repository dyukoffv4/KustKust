#include "../Headers/Wrapper.h"
#include "../Headers/Player.h"
#include "../Headers/Strategy.h"
#include "../Headers/PlayGround.h"

Wrapper::Wrapper(PlayGround* _ground, Player* _player, Context* _context)  {

	this->ground = _ground; 
	this->player = _player; 
	this->context = _context;
	this->game_end = false;
	this->game_pause = false;
}

Wrapper::~Wrapper() {

	delete player;
	delete context;
}

void Wrapper::movePlayer(char direct) {

	short x = player->getX();
	short y = player->getY();

	switch (direct) {

	case UP:
		player->Move(x, --y);
		break;

	case DOWN:
		player->Move(x, ++y);
		break;

	case LEFT:
		player->Move(--x, y);
		break;

	case RIGHT:
		player->Move(++x, y);
		break;
	}
}

void Wrapper::gameLogic() {

	if (context->mainWork()) game_end = true;
}

Player* Wrapper::getPlayer() {

	return player;
}