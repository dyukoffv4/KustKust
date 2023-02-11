#pragma once

#include "../texture/texture.hpp"

namespace mgl {

	class Sprite_I : public Texture_I {

	public:
		Sprite_I();
		Sprite_I(vect<byte_2>, vect<byte_2>, sf::Texture*);

		virtual sf::RectangleShape getImage(vect<byte_2>);
		virtual char getSN();

		void setSpeed(float);
		void update();

	protected:
		byte_2 len_s;
		byte_2 tick;
		float spd;
	};
}