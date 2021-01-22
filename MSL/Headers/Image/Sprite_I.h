#pragma once

#include "Image.h"

namespace mgl {

	class Sprite_I : public Image {

	public:
		Sprite_I(vect<short> s, vect<byte> c, sf::Texture* t = &standart_t);

		virtual void setSpeed(float s);
		virtual void update();

	protected:
		short len_s;
		short tick;
		float spd;
	};
}