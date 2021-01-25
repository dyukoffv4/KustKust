#include "Image.h"

mgl::Image::Image() {

	curr = { 0, 0 };
	size = { 64, 64 };
	texture = &standart_t;
}

mgl::Image::Image(vect<byte_2> s, vect<byte_2> c, sf::Texture* t) {

	curr = c;
	size = s;
	texture = t;
}

sf::Sprite mgl::Image::getSpr() {

	sf::Sprite spr;
	spr.setTexture(*texture);
	spr.setTextureRect(sf::Rect<int>(size.x * curr.x, size.y * curr.y, size.x, size.y));
	return spr;
}

char mgl::Image::getSN() {

	return SIM_I;
}

void mgl::Image::setCurr(vect<byte_2> c) {

	curr = c;
}

mgl::vect<mgl::byte_2> mgl::Image::getCurr() {

	return curr;
}

void mgl::Image::setSize(vect<byte_2> s) {

	size = s;
}

mgl::vect<mgl::byte_2> mgl::Image::getSize() {

	return size;
}

void mgl::Image::setTexture(sf::Texture* t) {

	texture = t;
}