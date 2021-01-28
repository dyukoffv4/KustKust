#include "Label.h"

mgl::Label::Label() {

	font = &standart_f;
	out_p = { 0, 255 };
	keg = 30;
}

mgl::Label::Label(std::string s, sf::Color c, sf::Font* f) {

	font = f;
	string = s;
	color = c;
	out_p = { 0, 255 };
	keg = 30;
}

sf::Text mgl::Label::getText() {

	sf::Text text;
	text.setString(string.substr(out_p.x, out_p.y));
	text.setStyle(sf::Text::Bold);
	text.setCharacterSize(keg);
	text.setFillColor(color);
	text.setFont(*font);
	return text;
}

void mgl::Label::setString(std::string s) {

	string = s;
}

std::string mgl::Label::getString() {

	return string;
}

void mgl::Label::setFont(sf::Font* f) {

	font = f;
}

sf::Font* mgl::Label::getFont() {

	return font;
}

void  mgl::Label::setOutpart(vect<byte_1> o) {

	out_p = o;
}

mgl::vect<mgl::byte_1> mgl::Label::getOutpart() {

	return out_p;
}

void mgl::Label::setKeg(byte_1 k) {

	keg = k;
}

mgl::byte_1 mgl::Label::getKeg() {

	return keg;
}

void mgl::Label::setColor(sf::Color c) {

	color = c;
}

sf::Color mgl::Label::getColor() {

	return color;
}