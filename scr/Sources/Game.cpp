#include "../Headers/Game.h"
#include "../Headers/Title.h"
#include "../Headers/PlayGround.h"
#include "../Headers/Iterator.h"
#include "../Headers/Player.h"
#include "../Headers/Strategy.h"
#include "../Headers/TitleObject.h"
#include "../Headers/Command.h"
#include "../Headers/Wrapper.h"

Game::Game(std::string title, std::string path, std::string sprites) : sf::RenderWindow() {

	key_used = false;
	command = nullptr;

	PlayGround* ground = &PlayGround::getPG(path);
	Player* player = new Player(ground->getStartX(), ground->getStartY());
	Context* context = new Context(player);

	wrapper = new Wrapper(ground, player, context);

	texture.loadFromFile(sprites);
	this->create(sf::VideoMode(TIT_W * ground->getWidth() - TIT_W + SPR_W, TIT_H * ground->getHeight() - TIT_H + SPR_H), title);
}

Game::~Game() {

	delete wrapper;
}

void Game::draw() {

	sf::Sprite sprite(texture);
	int x_curr = 0, y_curr = 0;
	this->clear(sf::Color::Cyan);

	for (IteratorPG i = PlayGround::getPG().getIterator(); !i.iterEnd(); i++) {

		if (i.lineEnd()) {

			x_curr = 0;
			y_curr += TIT_H;
		}

		if (wrapper->getPlayer()->getX() == i.getX() && wrapper->getPlayer()->getY() == i.getY()) {

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

		sf::RenderWindow::draw(sprite);

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

void Game::doWork() {

	sf::Event event;
	while (this->pollEvent(event)) {

		if (event.type == sf::Event::Closed) this->close();
		if (event.type == sf::Event::KeyPressed && !key_used) {

			if (event.key.code == sf::Keyboard::Up) command = new PlayerMove_C(wrapper, UP);
			if (event.key.code == sf::Keyboard::Down) command = new PlayerMove_C(wrapper, DOWN);
			if (event.key.code == sf::Keyboard::Left) command = new PlayerMove_C(wrapper, LEFT);
			if (event.key.code == sf::Keyboard::Right) command = new PlayerMove_C(wrapper, RIGHT);
			if (event.key.code == sf::Keyboard::Escape) command = new GamePause_C(wrapper);
			key_used = true;
		}
		if (event.type == sf::Event::KeyReleased && key_used) key_used = false;
	}

	if (command) {

		command->execute();
		delete command;
		command = nullptr;
	}
}

void Game::loop() {

	PlayGround& ground = PlayGround::getPG();

	while (ground.isGood() && this->isOpen()) {

		wrapper->gameLogic();

		this->draw();

		if (wrapper->game_end) {

			this->close();
			continue;
		}

		this->doWork();
	}
}