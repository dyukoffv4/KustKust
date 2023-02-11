#include "texture.hpp"

mgl::Texture_I::Texture_I() {

	curr = { 0, 0 };
	size = { 64, 64 };
	texture = &standart_t;
}

mgl::Texture_I::Texture_I(vect<byte_2> s, vect<byte_2> c, sf::Texture* t) {

	curr = c;
	size = s;
	texture = t;
}

sf::RectangleShape mgl::Texture_I::getImage(vect<byte_2> s) {

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(s.x, s.y));
	rect.setTexture(texture);
	rect.setTextureRect(sf::Rect<int>(size.x * curr.x, size.y * curr.y, size.x, size.y));
	return rect;
}

char mgl::Texture_I::getSN() {

	return SIM_I;
}

void mgl::Texture_I::setCurr(vect<byte_2> c) {

	curr = c;
}

mgl::vect<mgl::byte_2> mgl::Texture_I::getCurr() {

	return curr;
}

void mgl::Texture_I::setSize(vect<byte_2> s) {

	size = s;
}

mgl::vect<mgl::byte_2> mgl::Texture_I::getSize() {

	return size;
}

void mgl::Texture_I::setTexture(sf::Texture* t) {

	texture = t;
}