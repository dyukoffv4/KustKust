#include "../../Headers/Image/Sprite_I.h"

mgl::Sprite_I::Sprite_I(vect<short> s, vect<byte> c, sf::Texture* t) : Image(s, vect<byte>{ 0, c.y }, t) {

	len_s = c.x;
	tick = 0;
	spd = SPR_Z;
}

void mgl::Sprite_I::setSpeed(float s) {

	spd = s;
}

void mgl::Sprite_I::update() {

	if (spd == 0) return;
	if (short(clock() - tick) > short(SEC / spd) || short(clock() - tick) < 0) {

		tick = (unsigned short)clock();
		curr.x++;
		if (curr.x >= len_s) curr.x = 0;
	}
}