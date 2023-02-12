#include "simple_b.hpp"

MGL::Simple_B::Simple_B() : Button() {}

MGL::Simple_B::Simple_B(int i, Vector<short> p, Vector<byte_2> s, Texture_I* im) : Button(i, p, s, im) {}

char MGL::Simple_B::getSN() {
	return SIM_B;
}

void MGL::Simple_B::draw(layout& win) {
	if (stat.x) image->setCurr({ image->getCurr().x, 1 });
	else image->setCurr({ image->getCurr().x, 0 });
	
	sf::RectangleShape rect = image->getImage(size);
	rect.setPosition(cord.x, cord.y);
	win.draw(rect);
}

void MGL::Simple_B::update(sf::Event& e) {
	if (!stat.x) {
		if (e.type == event::MouseButtonPressed) {
			short x = e.mouseButton.x - cord.x;
			short y = e.mouseButton.y - cord.y;
			if (e.mouseButton.button == sf::Mouse::Button::Left) {
				if (x > 0 && y > 0 && x < size.x && y < size.y) stat.x = true;
			}
		}
		if (e.type == event::KeyPressed && e.key.code == key) stat.x = true;
	}
	else {
		if (e.type == event::MouseButtonReleased) {
			short x = e.mouseButton.x - cord.x;
			short y = e.mouseButton.y - cord.y;
			if (e.mouseButton.button == sf::Mouse::Button::Left) {
				if (x > 0 && y > 0 && x < size.x && y < size.y) stat = !stat;
				else stat.x = false;
			}
		}
		if (e.type == event::KeyReleased && e.key.code == key) stat = !stat;
	}
}

bool MGL::Simple_B::getStat() {
	if (stat.y) {
		stat.y = false;
		return true;
	}
	return false;
}