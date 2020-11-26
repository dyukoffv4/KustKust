#pragma once

#include "Defines.h"
#include <string>
#include <SFML/Graphics.hpp>

class Model;

///	-----------------//
//	Concrete Game	///

class View : public sf::RenderWindow {

private:
	sf::Texture texture;

public:
	View(std::string = WINDOW_TITLE, std::string = SPRITE_PATH);

	void winDraw(Model*);
};