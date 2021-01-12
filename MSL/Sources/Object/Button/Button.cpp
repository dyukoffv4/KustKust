#include "../../../Headers/Object/Button/Button.h"
#include "../../../Headers/Image/Image.h"

mgl::Button::Button(rect r, int i, Image* i_l) : Object(r.pos, i) {

	size = r.size;
	image_line = i_l;
	start = false;
	click = false;
}

void mgl::Button::update(sf::Event::MouseButtonEvent event, bool press) {

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

void mgl::Button::setSize(coord s) {

	size = s;
}

mgl::coord mgl::Button::getSize() {

	return size;
}

char mgl::Button::getName() {

	return SIM_B;
}

void mgl::Button::setImage(Image* i_l) {

	image_line = i_l;
}

void mgl::Button::draw(sf::RenderWindow& win) {

	sf::Sprite spr;
	short row = 0;
	if (image_line) {

		if (!start && click) row = 2;
		else if (start) row = 1;
		image_line->setCurr({ image_line->getCurr().x ,row });
		spr = image_line->getSpr();
	}
	else spr = standart.getSpr();

	spr.setPosition(pos.x, pos.y);
	spr.setScale(size.x / float(image_line->getSize().x), size.y / float(image_line->getSize().y));
	win.draw(spr);
}

bool mgl::Button::getSignal() {

	if (click) {

		click = false;
		return true;
	}
	return false;
}