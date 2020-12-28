#include "../Headers/View.h"
#include "../Headers/Tile.h"
#include "../Headers/Area.h"
#include "../Headers/Iterator.h"
#include "../Headers/TileObject.h"
#include "../Headers/Model.h"
#include "../Headers/List.h"

View::View(std::string title) : sf::RenderWindow(sf::VideoMode(11 * TIT_W, 11 * TIT_H + SPR_H - TIT_H), title) {

	this->title = title;
	this->loot_t.loadFromFile(LOOT_T_PATH);
	this->base_t.loadFromFile(BASE_T_PATH);
	this->font.loadFromFile(FONT_PATH);
}

void View::resize(Model* model) {

	this->close();
	this->create(sf::VideoMode(model->getArea()->getWidth() * TIT_W, model->getArea()->getHeight() * TIT_H + SPR_H - TIT_H), title);
}

void View::areaDraw(Model* model) {

	sf::Sprite loot_s(loot_t), base_s(base_t);
	int x_curr = 0, y_curr = 0;
	this->clear(sf::Color::Cyan);

	for (Iterator i = model->getArea()->getIterator(); !i.iterEnd(); i++) {

		if (i.lineEnd()) {

			x_curr = 0;
			y_curr += TIT_H;
		}

		base_s.setTextureRect(sf::Rect<int>(SPR_W * 0, 0, SPR_W, SPR_H));
		base_s.setPosition(x_curr, y_curr);
		this->draw(base_s);

		if (!i.getCurr().getObjs().empty()) {

			for (int j = 0; i.getCurr().getObjs()[j]; j++) {

				switch (i.getCurr().getObjs()[j]->getName()) {
				case PLR:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 0, 0, SPR_W, SPR_H));
					break;
				case SWAR:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 1, 0, SPR_W, SPR_H));
					break;
				case RWAR:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 1, 0, SPR_W, SPR_H));
					break;
				case TWAR:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 1, 0, SPR_W, SPR_H));
					break;
				case COIN:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 2, 0, SPR_W, SPR_H));
					break;
				case BAG:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 3, 0, SPR_W, SPR_H));
					break;
				case KEY:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 4, 0, SPR_W, SPR_H));
					break;
				case START:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 5, 0, SPR_W, SPR_H));
					break;
				case EXIT:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 6, 0, SPR_W, SPR_H));
					break;
				case WALL:
					loot_s.setTextureRect(sf::Rect<int>(SPR_W * 7, 0, SPR_W, SPR_H));
					break;
				}

				loot_s.setPosition(x_curr, y_curr);
				this->draw(loot_s);
			}
		}

		x_curr += TIT_W;
	}
}

void View::pauseDraw(Model* model) {

	sf::Text text;
	text.setString("Pause");
	text.setFont(font);
	text.setCharacterSize(75);
	text.setStyle(sf::Text::Bold);
	text.setFillColor(sf::Color::Red);
	text.setOutlineThickness(4);
	text.setOutlineColor(sf::Color::Black);
	text.setPosition(sf::Vector2f(model->getArea()->getWidth() * TIT_W / 2 - 100, model->getArea()->getHeight() * TIT_H / 2 - 50));
	this->draw(text);
}

void View::statDraw(Model* model) {

	std::string s1 = "Coins:  ";
	std::string s2 = "Bags:   ";
	std::string s3 = "Keys:   ";

	int num_c = 0;
	int num_b = 0;
	int num_k = 0;

	List* list = model->getPlayer()->getInvent();
	for (int i = 0; (*list)[i] != nullptr; i++) {

		if ((*list)[i]->getName() == COIN) num_c++;
		if ((*list)[i]->getName() == BAG) num_b++;
		if ((*list)[i]->getName() == KEY) num_k++;
	}

	sf::Text text1, text2, text3;
	text1.setString(s1 + (char)(num_c + 48));
	text2.setString(s2 + (char)(num_b + 48));
	text3.setString(s3 + (char)(num_k + 48));

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

	text1.setPosition(sf::Vector2f(10, 45));
	text2.setPosition(sf::Vector2f(10, 80));
	text3.setPosition(sf::Vector2f(10, 115));

	this->draw(text1);
	this->draw(text2);
	this->draw(text3);
}