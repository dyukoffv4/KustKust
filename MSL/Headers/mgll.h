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
#define TIL		0b01000000
#define LAY		0b10000000
#define PAL		0b11000000

#include <SFML/Graphics.hpp>

namespace mgl {

	typedef unsigned char byte;

	struct coord {

		short x;
		short y;
		coord operator+(const coord& r) { return { x + r.x, y + r.y }; };
		coord operator-(const coord& r) { return { x - r.x, y - r.y }; };
		coord operator/(const int& i) { return { x / 2 , y / 2 }; };
		coord& operator+=(const coord& r) { *this = *this + r; return *this; };
		coord& operator-=(const coord& r) { *this = *this - r; return *this; };
	};
	struct rect {

		coord pos;
		coord size;
	};

	/// <Object>
	/// 
	/// Object - interface class. It's the parent of classes:
	/// 
	///		Button classes
	///		Group classes
	///		Tile class
	/// 
	/// It class have an moving VF, resizing VF, draw VF, indification VF.
	/// 
	/// <\/ \/ \/ \/ \/ \/>

	class Object;

	/// <Image>
	/// 
	/// Image - the parent class of classes Sprite_I and Color_I.
	/// It can create the object itself. It's just return static sf::Sprite from sf::Texture.
	/// 
	/// Sprite_I controlled sf::Sprite that would be returned from sf::Texture by current time.
	/// 
	/// Color_I work like the Image class, but add color to returning sf::Sprite.
	/// 
	/// All classes can be including in Button class.
	/// All classes can work with 2D textures.
	/// 
	/// <\/ \/ \/ \/ \/ \/>

	class Image;
	class Sprite_I;
	class Color_I;

	/// <Button>
	/// 
	/// Button - the parent class of classes Toggle_B and Timer_B.
	/// It is controlling mouse clicking on window and self-clicked condition.
	/// Return signal if it was first request to her and she was clicked.
	/// 
	/// Toggle_B work like the Button class, but return signal, until she's turn on.
	/// 
	/// Timer_B work like the Button class, but return signal until she's not turn off or her timer runs out.
	/// 
	/// All classes can be including in Group class.
	/// 
	/// <\/ \/ \/ \/ \/ \/>

	class Button;
	class Toggle_B;
	class Timer_B;

	/// <Group>
	/// 
	/// Group - the parent class of classes Radio_G and Texture_G.
	/// This class contain objects of Object class, controll they position and size.
	/// It is can drawing content, and geting signal from content to return this.
	/// 
	/// Radio_G
	/// 
	/// Texture_G
	/// 
	/// <\/ \/ \/ \/ \/ \/>

	class Group;
	class Radio_G;
	class Texture_G;

	/// <Other classes>
	/// 
	/// Tile - class that just keep a coordinate on map, and Image.
	/// 
	/// Layer
	/// 
	/// Palette
	/// 
	/// <\/ \/ \/ \/ \/ \/>

	class Tile;
	class Layer;
	class Palette;
}