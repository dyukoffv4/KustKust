#include "../../Headers/Image/Image.h"

mgl::Image::Image(int i, vect<short> s, vect<byte> c, sf::Texture* t) {

	size = s;
	texture = t;
	curr = c;
}

sf::Sprite mgl::Image::getSpr() {

	sf::Sprite spr;
	spr.setTextureRect(sf::Rect<int>(size.x * curr.x, size.y * curr.y, size.x, size.y));
	spr.setTexture(*texture);
	return spr;
}

void mgl::Image::setCurr(vect<byte> c) {

	curr = c;
}

mgl::vect<mgl::byte> mgl::Image::getCurr() {

	return curr;
}

void mgl::Image::setSize(vect<short> s) {

	size = s;
}

mgl::vect<short> mgl::Image::getSize() {

	return size;
}