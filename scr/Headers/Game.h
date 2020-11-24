#pragma once

#include "Defines.h"
#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Command;
class Wrapper;

///	-----------------//
//	Concrete Game	///

class Game : public sf::RenderWindow {

private:
	Wrapper* wrapper;
	Command* command;
	sf::Texture texture;
	bool key_used;

public:
	Game(std::string title, std::string path, std::string sprites);
	~Game();

	void draw();
	void doWork();

	void loop();
};