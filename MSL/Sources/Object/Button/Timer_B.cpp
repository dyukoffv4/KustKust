#include "../../../Headers/Object/Button/Timer_B.h"

#include <string>
const char* ftos(float num) {

	std::string str = "";
	int g = floor(num);
	int d = floor((num - g) * 100);
	int gn, dn;
	for (gn = 1; g / pow(10, gn); gn++);
	for (dn = 1; d / pow(10, dn); dn++);

	for (int i = gn - 1; i > -1; i--) str += (g / int(pow(10, i)));
	str += '.';
	for (int i = dn - 1; i > -1; i--) str += (d / int(pow(10, i)));

	const char* str_ = str.c_str();

	return str_;
}

mgl::Timer_B::Timer_B(int i, rect<short, short> r, short sec, Image* i_l) : Button(i, r, i_l) {

	timer = sec * short(SEC);
	tick = 0;
	static sf::Font time_f;
	time_f.loadFromFile("");
	static Label time_l(-1, { 12, 12 }, "", &time_f);
}

void mgl::Timer_B::update_m(sf::Event::MouseButtonEvent event, bool press) {

	Button::update_m(event, press);

	if (click) tick = (int)clock();
}

void mgl::Timer_B::update_b(sf::Event::KeyEvent event, bool press) {

	Button::update_b(event, press);

	if (click) tick = (int)clock();
}

char mgl::Timer_B::getName() {

	return TIM_B;
}

void mgl::Timer_B::draw(sf::RenderWindow& win) {

	sf::Sprite spr;
	byte row = 0;
	if (image) {

		if (!start && click) row = 3;
		else if (start) row = 1;
		image->setCurr({ image->getCurr().x ,row });
		spr = image->getSpr();
	}
	else spr = standart_s.getSpr();

	spr.setPosition(pos.x, pos.y);
	spr.setScale(size.x / float(image->getSize().x), size.y / float(image->getSize().y));
	win.draw(spr);

	if (row == 3) {

		static sf::Font time_f;
		static Label time_l(-1, { 12, 12 }, "", &time_f);
		time_l.setString(ftos(float(timer - clock() + tick) / 1000));
		sf::Text text = time_l.getText();
		text.setPosition(pos.x + 4 * (float)size.x / image->getSize().x, pos.y + 4 * (float)size.y / image->getSize().y);
		win.draw(text);
	}
}

bool mgl::Timer_B::getSignal() {

	if (click && abs(int(clock()) - tick) > timer) {

		click = false;
		return true;
	}
	return false;
}