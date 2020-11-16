#include "../Headers/Player.h"
#include "../Headers/PlayGround.h"
#include "../Headers/TitleObject.h"
#include "../Headers/Strategy.h"

void operator+= (Player& plr, Object* obj) {

	if (obj->getName() == APPLE) plr.apple++;
	if (obj->getName() == PIE) plr.pie++;
	if (obj->getName() == KEY) plr.key++;
}

Player::Player(short x, short y) {

    x_pos = x;
    y_pos = y;
    x_prepos = x;
    y_prepos = y;
    apple = 0;
    pie = 0;
	key = 0;
}

short Player::getX() {

    return x_pos;
}

short Player::getY() {

    return y_pos;
}

unsigned char Player::getApple() {

    return apple;
}

unsigned char Player::getPie() {

    return pie;
}

unsigned char Player::getKey() {

	return key;
}

void Player::Move(char direct) {

    x_prepos = x_pos;
    y_prepos = y_pos;

	switch (direct) {
	case UP:
		y_pos--;
		break;
	case DOWN:
		y_pos++;
		break;
	case LEFT:
		x_pos--;
		break;
	case RIGHT:
		x_pos++;
		break;
	}
}

void Player::moveBack() {

	x_pos = x_prepos;
	y_pos = y_prepos;
}

std::ostream& operator<<(std::ostream& out, Player* player) {

	out << "Player now at x: " << player->getX() << " y: " << player->getY() << " ";
	out << "Score: " << (int)player->getApple() << " Super: " << (int)player->getPie() << '\n';
	return out;
}