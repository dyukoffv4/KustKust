#pragma once

#define SEC		1000.0
#define SPR_Z	1.0

// Object ID

#define SIM_B	0b00000001
#define TOG_B	0b00000011
#define TIM_B	0b00000101
#define SIM_G	0b00001000
#define RAD_G	0b00011000
#define STR_G	0b00101000

#include <SFML/Graphics.hpp>

namespace mgl {

	typedef unsigned char byte;

	template <typename T>
	struct vect {

		T x;
		T y;
		vect<T> operator+(const vect<T>& r) { return { x + r.x, y + r.y }; };
		vect<T> operator-(const vect<T>& r) { return { x - r.x, y - r.y }; };
		vect<T> operator/(const int& i) { return { x / i , y / i }; };
		vect<T>& operator+=(const vect<T>& r) { *this = *this + r; return *this; };
		vect<T>& operator-=(const vect<T>& r) { *this = *this - r; return *this; };
	};

	template <typename T, typename U>
	struct rect {

		vect<T> pos;
		vect<U> size;
	};

	class Object;

	class Button;
	class Toggle_B;
	class Timer_B;

	class Group;
	class Grid_G;
	class Radio_G;

	class Image;
	class Sprite_I;
	class Label;

	static sf::Texture standart_t = sf::Texture();
}