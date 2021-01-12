#pragma once

#include "../mgll.h"

namespace mgl {

	class Object {

	public:
		Object(coord c, int i);

		int getId();
		virtual void setCoord(coord c);
		virtual coord getCoord();

		virtual char getName() = 0;
		virtual void draw(sf::RenderWindow&) = 0;
		virtual void setSize(coord s) = 0;
		virtual coord getSize() = 0;

	protected:
		coord pos;
		int id;
	};
}