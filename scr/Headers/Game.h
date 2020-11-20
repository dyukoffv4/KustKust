#pragma once

#include <list>
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class PlayGround;
class Player;
class Context;
class Command;



class Game : public sf::RenderWindow {

private:
	PlayGround* ground;
	Player* player;
	Context* context;
	sf::Texture texture;
	std::list<Command*> commands;

public:
	Game(std::string title, std::string path, std::string sprites);
	~Game();

	void Draw();

	void Loop();
};