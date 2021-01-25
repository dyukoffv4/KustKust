#include "Sprite_I.h"

mgl::Sprite_I::Sprite_I(vect<byte_2> s, vect<byte_2> c, sf::Texture* t) : Image(s, { 0, c.y }, t) {

	len_s = c.x;
	tick = 0;
	spd = 1;
}

char mgl::Sprite_I::getSN() {

	return SPR_I;
}

void mgl::Sprite_I::setSpeed(float s) {

	spd = s;
}

void mgl::Sprite_I::update() {

	if (spd == 0) return;
	if (abs(byte_2(clock()) - tick) > short(SEC / spd)) {

		tick = (byte_2)clock();
		curr.x++;
		if (curr.x >= len_s) curr.x = 0;
	}
}