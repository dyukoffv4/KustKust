#include "../Headers/Game.h"
#include "../Headers/Title.h"
#include "../Headers/PlayGround.h"
#include "../Headers/Iterator.h"
#include "../Headers/Player.h"
#include "../Headers/Strategy.h"
#include "../Headers/TitleObject.h"
#include "../Headers/Command.h"

Game::Game(std::string title, std::string path, std::string sprites) : sf::RenderWindow() {

	ground = &PlayGround::getPG(path);
	texture.loadFromFile(sprites);
	player = new Player(ground->getStartX(), ground->getStartY());
	context = new Context(player);
	this->create(sf::VideoMode(TIT_W * ground->getWidth() - TIT_W + SPR_W, TIT_H * ground->getHeight() - TIT_H + SPR_H), title);
}

Game::~Game() {

	delete player;
	delete context;
}

void Game::Draw() {

	sf::Sprite sprite(texture);
	int x_curr = 0, y_curr = 0;
	this->clear(sf::Color::White);

	for (IteratorPG i = ground->getIterator(); !i.iterEnd(); i++) {

		if (i.lineEnd()) {

			x_curr = 0;
			y_curr += TIT_H;
		}

		if (player->getX() == i.getX() && player->getY() == i.getY()) {

			sprite.setTextureRect(sf::Rect<int>(SPR_W * 6, 0, SPR_W, SPR_H));
		}
		else if (i.getCurr().getObj()) {

			switch (i.getCurr().getObj()->getName()) {
			case APPLE:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 3, 0, SPR_W, SPR_H));
				break;
			case PIE:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 4, 0, SPR_W, SPR_H));
				break;
			case KEY:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 5, 0, SPR_W, SPR_H));
				break;
			case WALL:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 2, 0, SPR_W, SPR_H));
				break;
			case START:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 0, 0, SPR_W, SPR_H));
				break;
			case EXIT:
				sprite.setTextureRect(sf::Rect<int>(SPR_W * 1, 0, SPR_W, SPR_H));
				break;
			}
		}
		else sprite.setTextureRect(sf::Rect<int>(SPR_W * 8, 0, SPR_W, SPR_H));

		sprite.setPosition(x_curr, y_curr);

		this->draw(sprite);

		x_curr += TIT_W;
	}

	this->display();
}

void Game::Loop() {

	while (ground->isGood() && this->isOpen()) {

		sf::Event event;
		while (this->pollEvent(event)) {
		
			if (event.type == sf::Event::Closed) this->close();
			if (event.type == sf::Event::KeyPressed) {

				if (event.key.code == sf::Keyboard::Up) commands.push_back(new PlayerMove_C(player, UP));
				if (event.key.code == sf::Keyboard::Down) commands.push_back(new PlayerMove_C(player, DOWN));
				if (event.key.code == sf::Keyboard::Left) commands.push_back(new PlayerMove_C(player, LEFT));
				if (event.key.code == sf::Keyboard::Right) commands.push_back(new PlayerMove_C(player, RIGHT));
				if (event.key.code == sf::Keyboard::Escape) this->close();
			}
		}

		std::list<Command*>::iterator it = commands.begin();
		while (it != commands.end()) {

			(*it)->execute();
			delete (*it);
			it++;
		}
		commands.clear();

		if (context->mainWork()) break;

		this->Draw();
	}

	if (ground->isGood()) std::cout << "\nGame Complete\n";
	else std::cout << "\nGame level file error\n";
}