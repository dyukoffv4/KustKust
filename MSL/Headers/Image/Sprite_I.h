#pragma once

#include "Image.h"

namespace mgl {

	class Sprite_I : public Image {

	public:
		Sprite_I(coord s, short n, short h, sf::Texture* t);

		virtual void setSpeed(float s);
		virtual void update();

	protected:
		short len_s;
		short tick;
		float spd;
	};
}