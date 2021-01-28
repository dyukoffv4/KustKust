#include "Edit_B.h"

mgl::Edit_B::Edit_B() : Button() {

	label = new Label;
	crs = 0;
}

mgl::Edit_B::Edit_B(int i, vect<short> p, vect<byte_2> s, Image* im, Label* l) : Button(i, p, s, im) {

	label = new Label(*l);
	crs = label->getString().size();
	label->setOutpart({ 0, byte_1(size.x / float(label->getKeg())) });
}

mgl::Edit_B::~Edit_B() {

	if (label) delete label;
}

char mgl::Edit_B::getSN() {

	return TXT_B;
}

void mgl::Edit_B::draw(layout& win) {

	image->update();
	image->setSize({ byte_2(image->getSize().x / 4), image->getSize().y });

	if (stat.x) image->setCurr({ byte_2(image->getCurr().x * 4), 1 });
	else image->setCurr({ byte_2(image->getCurr().x * 4), 0 });
	sf::Sprite sprs = image->getSpr();

	sprs.setPosition(cord.x, cord.y);
	sprs.setScale(scale.y, scale.y);
	win.draw(sprs);

	if (stat.x) image->setCurr({ byte_2(image->getCurr().x + 1), 1 });
	else image->setCurr({ byte_2(image->getCurr().x + 1), 0 });
	sprs = image->getSpr();

	sprs.setPosition(cord.x + image->getSize().x * scale.y, cord.y);
	sprs.setScale(scale.x * 4 - 2 * scale.y, scale.y);
	win.draw(sprs);

	if (stat.x) image->setCurr({ byte_2(image->getCurr().x + 2), 1 });
	else image->setCurr({ byte_2(image->getCurr().x + 2), 0 });
	sprs = image->getSpr();

	sprs.setPosition(cord.x + size.x - image->getSize().x, cord.y);
	sprs.setScale(scale.y, scale.y);
	win.draw(sprs);

	image->setSize({ byte_2(image->getSize().x * 4), image->getSize().y });
	image->setCurr({ byte_2((image->getCurr().x - 3) / 4), 0 });

	sf::Text txt = label->getText();
	txt.setPosition(cord.x + 10, cord.y);
	win.draw(txt);

	if (stat.x) {

		txt.setFillColor(crs_c);
		txt.setPosition(txt.findCharacterPos(crs).x, cord.y);
		if (crs < label->getString().size()) txt.setString(label->getString()[crs]);
		else txt.setString("*");
		win.draw(txt);
	}
}

void mgl::Edit_B::setLabel(Label* l) {

	if (label) delete label;
	label = new Label(*l);
}

mgl::Label* mgl::Edit_B::getLabel() {

	return new Label(*label);
}

void mgl::Edit_B::setColor(sf::Color c) {

	crs_c = c;
}

sf::Color mgl::Edit_B::getColor() {

	return crs_c;
}

void mgl::Edit_B::update(sf::Event& e) {

	if (e.type == event::MouseButtonPressed) {

		short x = e.mouseButton.x - cord.x;
		short y = e.mouseButton.y - cord.y;
		if (e.mouseButton.button == sf::Mouse::Button::Left) {
			
			if (!stat.x && x > 0 && y > 0 && x < size.x && y < size.y) stat.x = true;
			if (stat.x && (x < 0 || y < 0 || x > size.x || y > size.y)) {

				stat.x = false;
				crs = label->getString().size();
			}
		}
		return;
	}
	if (e.type == event::KeyPressed) {

		if (!stat.x && e.key.code == key) stat.x = true;
		if (stat.x) {

			if (e.key.code == sf::Keyboard::Left && crs != 0) crs--;
			if (e.key.code == sf::Keyboard::Right && crs != label->getString().size()) crs++;
			if (e.key.code == sf::Keyboard::Enter) {

				stat.x = false;
				crs = label->getString().size();
			}
		}
		return;
	}
	if (e.type == event::TextEntered && stat.x && e.text.unicode < 128) {

		if (e.text.unicode == 8) {

			if (crs != 0) {

				std::string str = label->getString().substr(0, crs - 1);
				label->setString(str + label->getString().substr(crs, label->getString().size() - crs));
				crs--;
			}
		}
		else if (e.text.unicode != 13) {

			std::string str = label->getString().substr(0, crs) + char(e.text.unicode);
			label->setString(str + label->getString().substr(crs, label->getString().size() - crs));
			crs++;
		}
	}
}

bool mgl::Edit_B::getStat() {

	return stat.y;
}