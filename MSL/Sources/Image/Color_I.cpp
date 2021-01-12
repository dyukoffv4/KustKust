#include "../../Headers/Image/Color_I.h"

mgl::Color_I::Color_I(coord s, coord c, sf::Texture* t, sf::Color cl) : Image(s, c, t) {

	color = cl;
}

sf::Sprite mgl::Color_I::getSpr() {

	sf::Sprite spr;
	spr.setTextureRect(sf::Rect<int>(size.x * curr.x, size.y * curr.y, size.x, size.y));
	spr.setTexture(*texture);
	spr.setColor(color);
	return spr;
}
