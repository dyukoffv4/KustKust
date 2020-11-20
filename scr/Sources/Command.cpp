#include "../Headers/Command.h"
#include "../Headers/Player.h"

PlayerMove_C::PlayerMove_C(Player* _receiver, char _direct) : receiver(_receiver), direct(_direct) {}

void PlayerMove_C::execute() {

	receiver->Move(direct);
}