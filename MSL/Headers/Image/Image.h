#pragma once

#include "../mgll.h"

namespace mgl {

	class Image {

	public:
		Image(coord s, coord c, sf::Texture* t);

		virtual sf::Sprite getSpr();
		virtual void setCurr(coord c);
		virtual coord getCurr();

		virtual void setSize(coord s);
		virtual coord getSize();

		virtual void setSpeed(float s) {};
		virtual void update() {};

	protected:
		sf::Texture* texture;
		coord size;
		coord curr;
	};

	static Image standart = mgl::Image({ 64, 64 }, { 0, 0 }, &sf::Texture());
}