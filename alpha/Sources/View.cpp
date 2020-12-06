#include "../Headers/View.h"
#include "../Headers/Tile.h"
#include "../Headers/Area.h"
#include "../Headers/Iterator.h"
#include "../Headers/TileObject.h"
#include "../Headers/Model.h"
#include "../List.h"

View::View(std::string title) : sf::RenderWindow(sf::VideoMode(11 * TIT_W, 11 * TIT_H + SPR_H - TIT_H), title) {

	this->width = 11;
	this->height = 11;
	this->title = title;
	this->person_t.loadFromFile(PERSON_T_PATH);
	this->object_t.loadFromFile(OBJECT_T_PATH);
	this->base_t.loadFromFile(BASE_T_PATH);
	this->font.loadFromFile(FONT_PATH);
}

void View::resize(short _width, short _height) {

	width = _width;
	height = _height;
	this->close();
	this->create(sf::VideoMode(width * TIT_W, height * TIT_H + SPR_H - TIT_H), title);
}

void View::areaDraw(Model* model) {

	sf::Sprite base_s(base_t), object_s(object_t), person_s(person_t);

	if (model->game_pause) this->clear(sf::Color::Blue);
	else this->clear(sf::Color::Cyan);

	for (Iterator i = model->getArea()->getIterator(); !i.iterEnd(); i++) {

		base_s.setPosition(i.getCurr().getX() * TIT_H, i.getCurr().getY() * TIT_W);
		this->draw(base_s);

		if (i.getCurr().getThg()) {

			switch (i.getCurr().getThg()->getName()) {
			case COIN:
				object_s.setTextureRect(sf::Rect<int>(SPR_W * 0, 0, SPR_W, SPR_H));
				break;
			case BAG:
				object_s.setTextureRect(sf::Rect<int>(SPR_W * 1, 0, SPR_W, SPR_H));
				break;
			case KEY:
				object_s.setTextureRect(sf::Rect<int>(SPR_W * 2, 0, SPR_W, SPR_H));
				break;
			case WALL:
				object_s.setTextureRect(sf::Rect<int>(SPR_W * 5, 0, SPR_W, SPR_H));
				break;
			case START:
				object_s.setTextureRect(sf::Rect<int>(SPR_W * 3, 0, SPR_W, SPR_H));
				break;
			case EXIT:
				object_s.setTextureRect(sf::Rect<int>(SPR_W * 4, 0, SPR_W, SPR_H));
				break;
			}
			object_s.setPosition(i.getCurr().getX() * TIT_W, i.getCurr().getY() * TIT_H);
			this->draw(object_s);
		}
		if (i.getCurr().getSom()) {

			person_s.setTextureRect(sf::Rect<int>(SPR_W * 0, 0, SPR_W, SPR_H));
			person_s.setPosition(i.getCurr().getX() * TIT_W, i.getCurr().getY() * TIT_H);
			this->draw(person_s);
		}
	}
}

void View::pauseDraw() {

	sf::Text text;
	text.setString("Pause");
	text.setFont(font);
	text.setCharacterSize(75);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);
	text.setOutlineThickness(4);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(width * TIT_W / 2 - 100, height * TIT_H / 2 - 50));
	this->draw(text);
}

void View::statDraw(Model* model) {

	std::string s1 = "Coins:  ";
	std::string s2 = "Bags:   ";
	std::string s3 = "Keys:   ";

	int num1 = 0, num2 = 0, num3 = 0;
	List list = *model->getPlr()->getInvent();

	for (int i = 0; list[i] != nullptr; i++) {

		if (list[i]->getName() == COIN) num1++;
		if (list[i]->getName() == BAG) num2++;
		if (list[i]->getName() == KEY) num3++;
	}

	sf::Text text1, text2, text3;
	text1.setString(s1 + (char)(num1 + 48));
	text2.setString(s2 + (char)(num2 + 48));
	text3.setString(s3 + (char)(num3 + 48));

	text1.setFont(font);
	text2.setFont(font);
	text3.setFont(font);

	text1.setCharacterSize(25);
	text2.setCharacterSize(25);
	text3.setCharacterSize(25);

	text1.setStyle(sf::Text::Bold);
	text2.setStyle(sf::Text::Bold);
	text3.setStyle(sf::Text::Bold);

	text1.setOutlineThickness(2);
	text2.setOutlineThickness(2);
	text3.setOutlineThickness(2);

	text1.setOutlineColor(sf::Color::Black);
	text2.setOutlineColor(sf::Color::Black);
	text3.setOutlineColor(sf::Color::Black);

	text1.setPosition(sf::Vector2f(10, 10));
	text2.setPosition(sf::Vector2f(10, 45));
	text3.setPosition(sf::Vector2f(10, 80));

	sf::RenderWindow::draw(text1);
	sf::RenderWindow::draw(text2);
	sf::RenderWindow::draw(text3);
}