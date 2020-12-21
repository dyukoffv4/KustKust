#include "../Headers/Command.h"
#include "../Headers/Model.h"

// Player's command handler //

PlayerMove_C::PlayerMove_C(Model* _receiver, char _direct) : receiver(_receiver), direct(_direct) {}

void PlayerMove_C::execute() {

	receiver->moveAll(direct);
}

// Wripper's command handler //

GamePause_C::GamePause_C(Model* _receiver) : receiver(_receiver) {}

void GamePause_C::execute() {

	receiver->swapPause();
}