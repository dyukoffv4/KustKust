#include "../Headers/Game.h"
#include "../Headers/Title.h"
#include "../Headers/PlayGround.h"
#include "../Headers/Iterator.h"
#include "../Headers/Player.h"
#include "../Headers/Strategy.h"
#include "../Headers/TitleObject.h"
#include "../Headers/Command.h"

Game::Game(const char* path) {

	ground = &PlayGround::getPG(path);
	player = new Player(ground->getStartX(), ground->getStartY());
	context = new Context(player);
}

Game::~Game() {

	delete player;
	delete context;
}

void Game::loop() {

	while (ground->isGood()) {

		system("cls");
		std::cout << player->getX() << ' ' << player->getY() << '\n';
		std::cout << (int)player->getApple() << ' ' << (int)player->getPie() << ' ' << (int)player->getKey() << '\n';

		commands.push_back(new PlrMove_C(player));

		if (context->mainWork()) break;

		std::list<Command*>::iterator it = commands.begin();
		while (it != commands.end()) {

			(*it)->execute();
			delete (*it);
			it++;
		}
		commands.clear();
	}

	if (ground->isGood()) std::cout << "\nGame Complete\n";
	else std::cout << "\nGame level file error\n";

	system("pause");
}