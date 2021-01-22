#include "../../Headers/Image/Label.h"

mgl::Label::Label(int i, vect<short> k, const char* s, sf::Font* f) : Drawable(i, k) {

	font = f;
	if (!s) str = nullptr;
	else {

		short len = 0;
		for (len = 0; s[len] != '\0'; len++);
		str = new char[int(len) + 1];
		for (int i = 0; i < int(len) + 1; i++) str[i] = s[i];
	}
}

mgl::Label::~Label() {

	if (str) delete[] str;
}

sf::Text mgl::Label::getText() {

	sf::Text text;
	text.setString(str);
	text.setStyle(sf::Text::Bold);
	if (size.y < size.x) {

		text.setCharacterSize(size.y);
		text.setScale(sf::Vector2f(float(size.x) / size.y, 1));
	}
	else {

		text.setCharacterSize(size.x);
		text.setScale(sf::Vector2f(1, float(size.y) / size.x));
	}
	text.setFont(*font);
	return text;
}

void mgl::Label::setString(const char* s) {

	if (str) delete[] str;
	if (s) {

		int len;
		for (len = 0; s[len] != '\0'; len++);
		str = new char[int(len) + 1];
		for (int i = 0; i < int(len) + 1; i++) str[i] = s[i];
	}
}

void mgl::Label::setSize(vect<short> k) {

	size = k;
}

mgl::vect<short> mgl::Label::getSize() {

	return size;
}