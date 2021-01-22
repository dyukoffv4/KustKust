#include "../../../Headers/Object/Button/Toggle_B.h"

mgl::Toggle_B::Toggle_B(int i, rect<short, short> r, Image* i_l) : Button(i, r, i_l) {}

char mgl::Toggle_B::getName() {

	return TOG_B;
}

void mgl::Toggle_B::draw(sf::RenderWindow& win) {

	sf::Sprite spr;
	byte row = 0;
	if (image) {

		if (!start && click) row = 2;
		else if (start) row = 1;
		image->setCurr({ image->getCurr().x ,row });
		spr = image->getSpr();
	}
	else spr = standart_s.getSpr();

	spr.setPosition(pos.x, pos.y);
	spr.setScale(size.x / float(image->getSize().x), size.y / float(image->getSize().y));
	win.draw(spr);
}

bool mgl::Toggle_B::getSignal() {

	return click;
}