#include "../../Headers/Image/Sprite_I.h"

mgl::Sprite_I::Sprite_I(coord s, short n, short r, sf::Texture* t) : Image(s, { 0, r }, t) {

	len_s = n;
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