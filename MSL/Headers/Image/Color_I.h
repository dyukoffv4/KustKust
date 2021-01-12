#pragma once

#include "Image.h"

namespace mgl {

	class Color_I : public Image {

	public:
		Color_I(coord s, coord c, sf::Texture* t, sf::Color cl);

		virtual sf::Sprite getSpr();

	protected:
		sf::Color color;
		// 4 byte
	};
}