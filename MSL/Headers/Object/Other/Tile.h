#pragma once

#include "../Object.h"

namespace mgl {

	class Tile : public Object {

	public:
		Tile(coord c, int i, Image* i_l);

		virtual void setSize(coord s) {};
		virtual coord getSize() { return { 0, 0 }; };

		virtual char getName();
		virtual void setImage(Image* l_i);
		void draw(sf::RenderWindow&);

	protected:
		Image* image_line;
	};
}