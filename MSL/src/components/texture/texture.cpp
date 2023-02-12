#include "texture.hpp"

MGL::Texture_I::Texture_I() {
	curr = { 0, 0 };
	size = { 64, 64 };
	texture = &standart_t;
}

MGL::Texture_I::Texture_I(Vector<byte_2> s, Vector<byte_2> c, sf::Texture* t) {
	curr = c;
	size = s;
	texture = t;
}

sf::RectangleShape MGL::Texture_I::getImage(Vector<byte_2> s) {
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(s.x, s.y));
	rect.setTexture(texture);
	rect.setTextureRect(sf::Rect<int>(size.x * curr.x, size.y * curr.y, size.x, size.y));
	return rect;
}

char MGL::Texture_I::getSN() {
	return SIM_I;
}

void MGL::Texture_I::setCurr(Vector<byte_2> c) {
	curr = c;
}

MGL::Vector<MGL::byte_2> MGL::Texture_I::getCurr() {
	return curr;
}

void MGL::Texture_I::setSize(Vector<byte_2> s) {
	size = s;
}

MGL::Vector<MGL::byte_2> MGL::Texture_I::getSize() {
	return size;
}

void MGL::Texture_I::setTexture(sf::Texture* t) {
	texture = t;
}