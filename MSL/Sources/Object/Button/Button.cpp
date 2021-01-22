#include "../../../Headers/Object/Button/Button.h"

mgl::Button::Button(int i, rect<short, short> r, Image* i_l) : Object(i, r.pos) {

	size = r.size;
	image = i_l;
	start = false;
	click = false;
	key = 0;
}

void mgl::Button::update_m(sf::Event::MouseButtonEvent event, bool press) {

	if (press) {
		if (!start && event.button == sf::Mouse::Button::Left)
			if (event.x > pos.x && event.y > pos.y)
				if (event.x < pos.x + size.x && event.y < pos.y + size.y)
				start = true;
	}
	else {
		if (start && event.button == sf::Mouse::Button::Left) {
			if (event.x > pos.x && event.y > pos.y)
				if (event.x < pos.x + size.x && event.y < pos.y + size.y)
					click = !click;
			start = false;
		}
	}
}

void mgl::Button::update_b(sf::Event::KeyEvent event, bool press) {

	if (press && !start && event.code == key) start = true;
	if (!press && start && event.code == key) {

		click = !click;
		start = false;
	}
}

void mgl::Button::setSize(vect<short> s) {

	size = s;
}

mgl::vect<short> mgl::Button::getSize() {

	return size;
}

char mgl::Button::getName() {

	return SIM_B;
}

void mgl::Button::setImage(Image* i_l) {

	image = i_l;
}

void mgl::Button::draw(sf::RenderWindow& win) {

	sf::Sprite spr;
	byte row = 0;
	if (image) {

		if (start) row = 1;
		image->setCurr({ image->getCurr().x ,row });
		spr = image->getSpr();
	}
	else spr = standart_s.getSpr();

	spr.setPosition(pos.x, pos.y);
	spr.setScale(size.x / float(image->getSize().x), size.y / float(image->getSize().y));
	win.draw(spr);
}

bool mgl::Button::getSignal() {

	if (click) {

		click = false;
		return true;
	}
	return false;
}