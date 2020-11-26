#include "../Headers/View.h"
#include "../Headers/Tile.h"
#include "../Headers/Area.h"
#include "../Headers/Iterator.h"
#include "../Headers/Player.h"
#include "../Headers/TileObject.h"

View::View(std::string title, std::string sprites) : sf::RenderWindow() {

	this->texture.loadFromFile(sprites);
	this->create(sf::VideoMode(1280, 960), title);
}

void View::winDraw(Player* player, Area* area) {

	sf::Sprite sprite(texture);
	int x_curr = 0, y_curr = 0;
	this->clear(sf::Color::Cyan);

	for (Iterator i = area->getIterator(); !i.iterEnd(); i++) {

		if (i.lineEnd()) {

			x_curr = 0;
			y_curr += TIT_H;
		}

		if (player->getX() == i.getX() && player->getY() == i.getY()) {

			sprite.setTextureRect(sf::Rect<int>(SPR_W * 8, 0, SPR_W, SPR_H));
		}
		else if (i.getCurr().getObj()) {

			switch (i.getCurr().getObj()->getName()) {
			case APPLE:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 5, 0, SPR_W, SPR_H));
				break;
			case PIE:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 6, 0, SPR_W, SPR_H));
				break;
			case KEY:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 7, 0, SPR_W, SPR_H));
				break;
			case WALL:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 3, 0, SPR_W, SPR_H));
				break;
			case START:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 1, 0, SPR_W, SPR_H));
				break;
			case EXIT:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 2, 0, SPR_W, SPR_H));
				break;
			}
		}
		else sprite.setTextureRect(sf::Rect<int>(SPR_W * 0, 0, SPR_W, SPR_H));

		sprite.setPosition(x_curr, y_curr);

		this->draw(sprite);

		x_curr += TIT_W;
	}
	/*
	sf::Text text;
	if (wrapper->game_pause) {
		
		text.setString("Pause");
		text.setScale(sf::Vector2f(4, 4));
		text.setStyle(sf::Text::Bold);
		text.setFillColor(sf::Color::Red);
		text.setPosition(sf::Vector2f(PlayGround::getPG().getWidth() * TIT_W / 2, PlayGround::getPG().getHeight() * TIT_H / 2));
		sf::RenderWindow::draw(text);
	}
	*/
	this->display();
}