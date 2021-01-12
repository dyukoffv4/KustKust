#include "../../Headers/Image/Image.h"

mgl::Image::Image(coord s, coord c, sf::Texture* t) {

	texture = t;
	size = s;
	curr = c;
}

sf::Sprite mgl::Image::getSpr() {

	sf::Sprite spr;
	spr.setTextureRect(sf::Rect<int>(size.x * curr.x, size.y * curr.y, size.x, size.y));
	spr.setTexture(*texture);
	return spr;
}

void mgl::Image::setCurr(coord c) {

	curr = c;
}

mgl::coord mgl::Image::getCurr() {

	return curr;
}

void mgl::Image::setSize(coord s) {

	size = s;
}

mgl::coord mgl::Image::getSize() {

	return size;
}