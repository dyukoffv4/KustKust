#include "sprite.hpp"

mgl::Sprite_I::Sprite_I() : Texture_I() {

	len_s = 1;
	tick = 0;
	spd = 1;
}

mgl::Sprite_I::Sprite_I(vect<byte_2> s, vect<byte_2> c, sf::Texture* t) : Texture_I(s, { 0, c.y }, t) {

	len_s = c.x;
	tick = 0;
	spd = 1;
}

sf::RectangleShape mgl::Sprite_I::getImage(vect<byte_2> s) {

	this->update();

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(s.x, s.y));
	rect.setTexture(texture);
	rect.setTextureRect(sf::Rect<int>(size.x * curr.x, size.y * curr.y, size.x, size.y));
	return rect;
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