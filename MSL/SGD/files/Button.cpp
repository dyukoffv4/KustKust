#include "Button.h"

mgl::Button::Button() : Object(), image(&standart_s) {

	size = { 64, 64 };
	scale = { 1, 1 };
	key = -1;
	im_pos = { {0, 1}, {2, 3} };
}

mgl::Button::Button(int i, vect<short> p, vect<byte_2> s, Image* im) : Object(i, p) {

	image = im;
	size = s;
	key = -1;
	scale = { float(size.x) / image->getSize().x, float(size.y) / image->getSize().y };
	im_pos = { {0, 1}, {2, 3} };
}

char mgl::Button::getSN() {

	return SIM_B;
}

void mgl::Button::setSize(vect<byte_2> s) {

	size = s;
	scale = { float(size.x) / image->getSize().x, float(size.y) / image->getSize().y };
}

mgl::vect<mgl::byte_2> mgl::Button::getSize() {

	return size;
}

void mgl::Button::setImage(Image* im) {

	image = im;
	scale = { float(size.x) / image->getSize().x, float(size.y) / image->getSize().y };
}

mgl::Image* mgl::Button::getImage() {

	return image;
}

void mgl::Button::setKey(short k) {

	key = k;
}

void mgl::Button::draw(layout& win) {

	image->update();

	if (stat.x) image->setCurr({ image->getCurr().x, im_pos.x.y });
	else image->setCurr({ image->getCurr().x, im_pos.x.x });
	
	sf::Sprite spr = image->getSpr();
	spr.setPosition(cord.x, cord.y);
	spr.setScale(scale.x, scale.y);
	win.draw(spr);
}

void mgl::Button::update(sf::Event& e) {

	if (!stat.x) {

		if (e.type == event::MouseButtonPressed) {

			short x = e.mouseButton.x - cord.x;
			short y = e.mouseButton.y - cord.y;
			if (e.mouseButton.button == sf::Mouse::Button::Left)
				if (x > 0 && y > 0 && x < size.x && y < size.y)
					stat.x = true;
		}
		if (e.type == event::KeyPressed && e.key.code == key)
			stat.x = true;
	}
	else {

		if (e.type == event::MouseButtonReleased) {

			short x = e.mouseButton.x - cord.x;
			short y = e.mouseButton.y - cord.y;
			if (e.mouseButton.button == sf::Mouse::Button::Left)
				if (x > 0 && y > 0 && x < size.x && y < size.y)
					stat = !stat;
				else stat.x = false;
		}
		if (e.type == event::KeyReleased && e.key.code == key)
			stat = !stat;
	}
}

bool mgl::Button::getStat() {

	if (stat.y) {

		stat.y = false;
		return true;
	}
	return false;
}