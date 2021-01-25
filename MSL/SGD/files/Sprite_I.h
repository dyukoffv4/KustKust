#pragma once

#include "Image.h"

namespace mgl {

	class Sprite_I : public Image {

	public:
		Sprite_I(vect<byte_2> s, vect<byte_2> c, sf::Texture* t = &standart_t);

		virtual char getSN();
		virtual void setSpeed(float s);
		virtual void update();

	protected:
		byte_2 len_s;
		byte_2 tick;
		float spd;
	};
}