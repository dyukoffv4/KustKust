#pragma once

#include "Defines.h"
#include <string>
#include <SFML/Graphics.hpp>

class Model;

///	-----------------//
//	Concrete Game	///

class View : public sf::RenderWindow {

private:
	sf::Texture loot_t;
	sf::Texture base_t;
	sf::Font font;
	std::string title;

public:
	View(std::string = WINDOW_TITLE);

	void resize(Model*);

	void areaDraw(Model*);
	void pauseDraw(Model*);
	void statDraw(Model*);
};