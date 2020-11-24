#include "../Headers/Player.h"
#include "../Headers/TitleObject.h"
#include "../Headers/PlayGround.h"

void operator+= (Player& plr, Object* obj) {

	if (obj->getName() == APPLE) plr.apple++;
	if (obj->getName() == PIE) plr.pie++;
	if (obj->getName() == KEY) plr.key++;
}

Player::Player(short x, short y) {

	this->x_pos = x;
	this->y_pos = y;
	this->x_prepos = x;
	this->y_prepos = y;
	this->apple = 0;
	this->pie = 0;
	this->key = 0;
}

short Player::getX() {

    return this->x_pos;
}

short Player::getY() {

    return this->y_pos;
}

unsigned char Player::getApple() {

    return this->apple;
}

unsigned char Player::getPie() {

    return this->pie;
}

unsigned char Player::getKey() {

	return this->key;
}

void Player::Move(short x, short y) {

	this->x_prepos = this->x_pos;
	this->y_prepos = this->y_pos;

	y_pos = y;
	x_pos = x;

	if (this->x_pos < 0 || this->x_pos > PlayGround::getPG().getWidth() - 1) this->moveBack();
	if (this->y_pos < 0 || this->y_pos > PlayGround::getPG().getHeight() - 1) this->moveBack();
}

void Player::moveBack() {

	this->x_pos = this->x_prepos;
	this->y_pos = this->y_prepos;
}