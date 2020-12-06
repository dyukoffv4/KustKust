#pragma once

#include "Defines.h"
#include <string>
#include <SFML/Graphics.hpp>

class Model;

///	-----------------//
//	Concrete Game	///

class View : public sf::RenderWindow {

private:
	sf::Texture person_t;
	sf::Texture object_t;
	sf::Texture base_t;
	sf::Font font;
	std::string title;
	short width;
	short height;

public:
	View(std::string = WINDOW_TITLE);

	void resize(short, short);

	void areaDraw(Model*);
	void pauseDraw();
	void statDraw(Model*);
};