#pragma once

#include "../texture/texture.hpp"

namespace MGL {
	class Sprite_I : public Texture_I {
	public:
		Sprite_I();
		Sprite_I(Vector<byte_2>, Vector<byte_2>, sf::Texture*);

		virtual sf::RectangleShape getImage(Vector<byte_2>);
		virtual char getSN();

		void setSpeed(float);
		void update();

	protected:
		byte_2 len_s;
		byte_2 tick;
		float spd;
	};
}