#include "Toggle_B.h"

mgl::Toggle_B::Toggle_B() : Button() {}

mgl::Toggle_B::Toggle_B(int i, vect<short> p, vect<byte_2> s, Image* im) : Button(i, p, s, im) {}

char mgl::Toggle_B::getSN() {

	return TOG_B;
}

void mgl::Toggle_B::draw(layout& win) {

	image->update();

	if (stat.x) image->setCurr({ image->getCurr().x, im_pos.x.y });
	else if (stat.y) image->setCurr({ image->getCurr().x, im_pos.y.x });
	else image->setCurr({ image->getCurr().x, im_pos.x.x });

	sf::Sprite spr = image->getSpr();
	spr.setPosition(cord.x, cord.y);
	spr.setScale(scale.x, scale.y);
	win.draw(spr);
}

bool mgl::Toggle_B::getStat() {

	return stat.y;
}