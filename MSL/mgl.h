#pragma once

#include <SFML/Graphics.hpp>

namespace mgl {

	typedef unsigned char	byte_1;
	typedef unsigned short	byte_2;
	typedef unsigned int	byte_4;
	typedef unsigned long	byte_8;

	typedef sf::Event event;
	typedef sf::RenderWindow layout;

	static sf::Texture standart_t = sf::Texture();
	static sf::Font standart_f = sf::Font();
	static float SEC(1000.0);

	template <class T>
	class vect;

	class Object;

	class Button;
	class Simple_B;
	class Toggle_B;

	class Group;
	class Simple_G;
	class Toggle_G;

	class Image;
	class Texture_I;
	class Sprite_I;
}