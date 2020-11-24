#include "../Headers/Command.h"
#include "../Headers/Wrapper.h"

// Player's command handler //

PlayerMove_C::PlayerMove_C(Wrapper* _receiver, char _direct) : receiver(_receiver), direct(_direct) {}

void PlayerMove_C::execute() {

	if (!receiver->game_pause) receiver->movePlayer(direct);
}

// Wripper's command handler	//

GamePause_C::GamePause_C(Wrapper* _receiver) : receiver(_receiver) {}

void GamePause_C::execute() {

	receiver->game_pause = !receiver->game_pause;
}